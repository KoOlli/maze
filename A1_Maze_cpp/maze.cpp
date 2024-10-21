#include "maze.h"
#include <qDebug>

s21::Maze::Maze(int row, int col) {
    row_ = row;
    col_ = col;
//    RandomValue();
    Generate(row_, col_);
}

s21::Maze::Maze(int row, int col, int bias) {
  row_ = row > 0 ? row <= 50 ? row : 50 : 1;
  col_ = col > 0 ? col <= 50 ? col : 50 : 1;

  Bias = bias;
  BiasMax = 100;

//  Init();
//    RandomValue();
  Generate(row_, col_);
}

//void s21::Maze::RandomValue(){
//    rightWalls_.resize(row_, std::vector<int>(col_, 0));
//    bottomWalls_.resize(row_, std::vector<int>(col_, 0));

//    for (int i = 0; i < row_; ++i) {
//        for (int j = 0; j < col_; ++j) {
//            rightWalls_[i][j] = std::rand() % 2;  // Установка правой стены
//            std::cout << rightWalls_[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

//    for (int i = 0; i < row_; ++i) {
//        for (int j = 0; j < col_; ++j) {
//            bottomWalls_[i][j] = std::rand() % 2;  // Установка правой стены
//            std::cout << bottomWalls_[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//}


//int s21::Maze::find(int x) {
//    if (parent[x] != x) {
//        parent[x] = find(parent[x]); // Сжимаем путь
//    }
//    return parent[x];
//}

//void s21::Maze::unionSets(int x, int y) {
//    int rootX = find(x);
//    int rootY = find(y);
//    if (rootX != rootY) {
//        parent[rootY] = rootX; // Объединяем множества
//    }
//}

//std::vector<std::vector<int>> s21::Maze::FindPath(int startX, int startY, int endX, int endY) {
//    std::vector<std::vector<int>> path; // Путь от начальной до конечной точки
//    std::vector<std::vector<bool>> visited(row_, std::vector<bool>(col_, false));
//    std::vector<std::vector<int>> parent(row_ * col_, std::vector<int>(2, -1));

//    // Очередь для BFS
//    std::queue<std::pair<int, int>> q;
//    q.push({startX, startY});
//    visited[startY][startX] = true;

//    // Векторы для соседних клеток (вправо, вниз, влево, вверх)
//    std::vector<std::pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

//    while (!q.empty()) {
//        auto current = q.front();
//        int x = current.first, y = current.second;
//        q.pop();

//        // Проверка, достигли ли мы целевой точки
//        if (x == endX && y == endY) {
//            // Восстановление пути
//            while (current.first != startX || current.second != startY) {
//                path.push_back({ current.first, current.second });
//                current = { parent[current.second * col_ + current.first][0],
//                             parent[current.second * col_ + current.first][1] };
//            }
//            path.push_back({ startX, startY });
//            std::reverse(path.begin(), path.end()); // Разворачиваем, чтобы получить правильный порядок
//            return path;
//        }

//        // Проверка всех четырех направлений
//        for (auto& dir : directions) {
//            int newX = x + dir.first;
//            int newY = y + dir.second;

//            // Проверяем границы и стены
//            if (newX >= 0 && newX < col_ && newY >= 0 && newY < row_ &&
//                !visited[newY][newX] &&
//                (dir.first == 1 && !isWall(x, y, 'R') || dir.first == 0 && dir.second == 1 && !isWall(x, y, 'D') ||
//                 dir.first == -1 && isWall(newX, newY, 'R') || dir.second == -1 && isWall(newX, newY, 'D'))) {

//                visited[newY][newX] = true;
//                parent[newY * col_ + newX] = { x, y }; // Запоминаем родительскую клетку
//                q.push({ newX, newY });
//            }
//        }
//    }



void s21::Maze::PathFinder(int startPosX = 0, int startPosY = 0, int endPosX = 0,
                           int endPosY = 0) {
    Start = std::vector<int>({startPosX, startPosY});
    End = std::vector<int>({endPosX, endPosY});
    path_ = std::vector<std::vector<int>>();
}


std::vector<std::vector<int>> s21::Maze::FindPath(int startPosX, int startPosY, int endPosX, int endPosY) {
    if (startPosX >= col_ || startPosX < 0 || endPosX >= col_ || endPosX < 0 ||
        startPosY >= row_ || startPosY < 0 || endPosY >= row_ || endPosY < 0) {
        return {};
    }

    currentPosition = std::vector<int>(Start.begin(), Start.end());
    Direction currentDirection = Direction::Left;

    while (currentPosition != End) {
        path_.push_back(currentPosition);

        currentDirection = ChangeCounterClockwise(currentDirection);
        std::vector<int> nextPosition;

        while (true) {
            nextPosition = NextCell(currentDirection, currentPosition);

            if (nextPosition[0] >= 0 && nextPosition[0] < col_ &&
                nextPosition[1] >= 0 && nextPosition[1] < row_ &&
                CanStep(currentDirection, nextPosition)) {
                break;
            }

            currentDirection = ChangeClockwise(currentDirection);
        }

        currentPosition = nextPosition;

        if (containsStart(currentPosition)) {
            getPath().pop_back();
            getPath().pop_back();
        }
    }

    path_.push_back(currentPosition);
    return getPath();
}


void s21::Maze::Init() {
    path_ = std::vector<std::vector<int>>(row_, std::vector<int>(2, 0));
    rightWalls_ = std::vector<std::vector<int>>(row_, std::vector<int>(col_, 0));
    bottomWalls_ = std::vector<std::vector<int>>(row_, std::vector<int>(col_, 0));

    for (int i = 0; i < row_; ++i) {
            rightWalls_.push_back(std::vector<int>());
            bottomWalls_.push_back(std::vector<int>());
            rightWalls_[i][col_ - 1] = 1;
          }
          for (int i = 0; i < col_; ++i) {
            bottomWalls_[row_ - 1][i] = 1;
          }
}


void s21::Maze::Generate(int n, int m) {
    Init();
    int setUniqueNumber = col_;
    std::vector<int> set(col_);
    std::iota(set.begin(), set.end(), 1); // Заполняем вектор значениями от 1 до col_

    for (int row = 0; row < row_; row++) {
        if (row > 0) {
            for (int i = 0; i < col_; i++) {
                if (bottomWalls_[row - 1][i] == 1)
                    set[i] = ++setUniqueNumber;
            }
        }

        std::vector<int> rand(col_ * 2);
        for (int i = 0; i < rand.size(); ++i)
            rand[i] = std::rand() % (BiasMax + 2);

        for (int i = 0; i < col_; ++i) {
            if (i < col_ - 1 && (rand[i] < Bias || set[i + 1] == set[i]))
                rightWalls_[row][i] = 1;
            else if (i < col_ - 1)
                std::transform(set.begin(), set.end(), set.begin(), [&](int x) { return (x == set[i + 1]) ? set[i] : x; });
        }

        for (int i = 0; i < col_; ++i) {

            int allSetLength = std::count(set.begin(), set.end(), set[i]);
            int setLength = std::count(set.begin(), set.begin() + i + 1, set[i]);
            int bottomCount = std::count_if(bottomWalls_[row].begin() + (i - setLength + 1), bottomWalls_[row].begin() + (i + 1),
                [](int x) { return x == 1; });

            if (rand[i + col_] > Bias) {
                if ((rightWalls_[row][i] != 1) || (!(bottomCount == setLength - 1) && setLength > 1))
                    bottomWalls_[row][i] = 1;
            } else if (rightWalls_[row][i] == 1 && setLength > 1 && bottomCount == 0) {
                bottomWalls_[row][i] = 1;
            }
        }
    }

    for (int i = 0; i < col_; ++i) {
        if ((i < col_ - 1 && set[i + 1] != set[i]) && (i != col_ - 1))
            rightWalls_[row_ - 1][i] = 0;
        if (i < col_ - 1) std::transform(set.begin(), set.end(), set.begin(), [&](int x) {
                return (x == set[i + 1]) ? set[i] : x; });
    }
}


bool s21::Maze::containsStart(const std::vector<int>& Start) {
    for (const auto& path : getPath()) {
        if (path.size() == 2 && path[0] == Start[0] && path[1] == Start[1]) {
            return true;
        }
    }
    return false;
}

bool s21::Maze::CanStep(Direction direction, const std::vector<int>& position) const {
    if (direction == Direction::Right && rightWalls_[position[1]][position[0] - 1] == 0)
        return true;
    if (direction == Direction::Left && rightWalls_[position[1]][position[0]] == 0)
        return true;
    if (direction == Direction::Up && bottomWalls_[position[1]][position[0]] == 0)
        return true;
    if (direction == Direction::Down && bottomWalls_[position[1] - 1][position[0]] == 0)
        return true;
    return false;
}

std::vector<int> s21::Maze::NextCell(s21::Maze::Direction direction, const std::vector<int>& position) {
    switch (direction) {
        case s21::Maze::Direction::Up: return {position.begin(), position.end() - 1};
        case s21::Maze::Direction::Down: return {position.begin(), position.end() + 1};
        case s21::Maze::Direction::Left: return {position.begin() - 1, position.end()};
        case s21::Maze::Direction::Right: return {position.begin() + 1, position.end()};
        default: throw std::out_of_range("Not expected direction value");
    }
}

s21::Maze::Direction s21::Maze::ChangeClockwise(s21::Maze::Direction direction) {
    switch (direction) {
        case s21::Maze::Direction::Up: return s21::Maze::Direction::Right;
        case s21::Maze::Direction::Right: return s21::Maze::Direction::Down;
        case s21::Maze::Direction::Down: return s21::Maze::Direction::Left;
        case s21::Maze::Direction::Left: return s21::Maze::Direction::Up;
        default: throw std::out_of_range("Not expected direction value");
    }
}
s21::Maze::Direction s21::Maze::ChangeCounterClockwise(s21::Maze::Direction direction) {
    switch (direction) {
        case s21::Maze::Direction::Up: return s21::Maze::Direction::Left;
        case s21::Maze::Direction::Left: return s21::Maze::Direction::Down;
        case s21::Maze::Direction::Down: return s21::Maze::Direction::Right;
        case s21::Maze::Direction::Right: return s21::Maze::Direction::Up;
        default: throw std::out_of_range("Not expected direction value");
    }
}
