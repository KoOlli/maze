#include "maze.h"
#include <qDebug>
#include <random>
#include <algorithm>

s21::Maze::Maze(int row, int col) {
    row_ = row;
    col_ = col;

    Generate(row_, col_);
}

s21::Maze::Maze(int row, int col, int bias) {
  row_ = row > 0 ? row <= 50 ? row : 50 : 1;
  col_ = col > 0 ? col <= 50 ? col : 50 : 1;

  Bias = bias;
  BiasMax = 100;

  Generate(row_, col_);
}

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


//int s21::Maze::find(int x, std::vector<int>& parent) {
//    if (parent[x] != x) {
//        parent[x] = find(parent[x], parent); // Сжатие пути
//    }
//    return parent[x];
//}

//void s21::Maze::unionSet(int x, int y, std::vector<int>& parent) {
//    int rootX = find(x, parent);
//    int rootY = find(y, parent);
//    if (rootX != rootY) {
//        parent[rootY] = rootX; // Объединение
//    }
//}


void s21::Maze::Generate(int n, int m) {
    Init();
    int setUniqueNumber = col_;
    std::vector<int> set(col_);
//    std::iota(set.begin(), set.end(), 1);
    // Заполняем вектор значениями от 1 до col_
    for (int i = 1; i < col_; ++i) {
        set[i-1] = i; // добавляем элемент в множество
    }

    for (int row = 0; row < row_; ++row) {
        if (row > 0) {
            for (int i = 0; i < col_; ++i) {
                if (bottomWalls_[row - 1][i] == 1)
                    set[i] = setUniqueNumber++;
        }
    }
    std::vector<int> rand(col_ * 2);
    for (int i = 0; i < rand.size(); ++i)
        rand[i] = random() % (BiasMax + 2);
    for (int i = 0; i < col_; ++i) {
        if (i < col_ - 1 && (rand[i] == 1 || set[i + 1] == set[i]))
//        if (i < col_ - 1 && rand[i] == 1)
            rightWalls_[row][i] = 1;
        else if (i < col_ - 1) {
            std::vector<int> newSet; // Создаем пустой вектор для хранения результатов
            for (int x : set) {
                if (x == set[i + 1]) {
                    newSet.push_back(set[i]);
                } else {
                    newSet.push_back(x);
                }
            }
            set = newSet;
        }
    }
    for (int i = 0; i < col_; i++) {
        int allSetLength = 0; // Инициализируем счетчик
        // Проходим через все элементы вектора set
        for (int x : set) {
            if (x == set[i]) {
                allSetLength++; // Увеличиваем счетчик, если условие выполняется
            }
        }
        int setLength = 0;
        for (int j = 0; j <= i; j++) {
            // Проходим от 0 до i (включительно)
            if (set[j] == set[i]) {
                setLength++; // Увеличиваем счетчик, если условие выполняется
            }
        }
        int bottomCount = 0;
        for (auto it = bottomWalls_[row].begin() + (i - setLength + 1);
        it != bottomWalls_[row].begin() + (i + 1); it++) {
            if (*it == 1) { // Сравниваем значение с 1
                bottomCount++; // Увеличиваем счетчик, если условие выполняется
            }
        } if (rand[i + col_] > Bias) {
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
        if (i < col_ - 1) {
            int nextValue = set[i + 1]; // Значение следующего элемента
            int currentValue = set[i]; // Значение текущего элемента
            // Проходим по всем элементам, чтобы заменить значения
            for (int& x : set) {
                if (x == nextValue) {
                    x = currentValue; // Заменяем nextValue на текущий элемент
                }
            }
        }
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
