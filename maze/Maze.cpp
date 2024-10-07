#include "maze.h"

s21::Maze::Maze(int row, int col) {
    row_ = row;
    col_ = col;
    RandomValue();
}

s21::Maze::Maze(int row, int col, int bias) {
  row_ = row > 0 ? row <= 50 ? row : 50 : 1;
  col_ = col > 0 ? col <= 50 ? col : 50 : 1;

//  Bias = bias;
//  BiasMax = 100;

//  Init();
    RandomValue();
}

void s21::Maze::RandomValue(){
    rightWalls_.resize(row_, std::vector<int>(col_, 0));
    bottomWalls_.resize(row_, std::vector<int>(col_, 0));

    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            rightWalls_[i][j] = std::rand() % 2;  // Установка правой стены
            std::cout << rightWalls_[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            bottomWalls_[i][j] = std::rand() % 2;  // Установка правой стены
            std::cout << bottomWalls_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void s21::Maze::FindPath(int startPosX, int startPosY, int endPosX, int endPosY){

}

void s21::Maze::Generate(int getRow(), int getCol()) {
    std::vector<std::vector<bool>> maze(getRow(), std::vector<bool>(getCol()));

    int start_row = std::rand() % getRow();
    int start_col = std::rand() % getCol();

    maze[start_row][start_col] = true;

    for (int r = 0; r < getRow(); ++r) {
        for (int c = 0; c < getCol(); ++c) {
            if (!maze[r][c]) {
                continue;
            }

            // выбор направление движения
            int random_ = std::rand() % 4;
            if (random_ == 0 && (r > 0 && !maze[r - 1][c])) {  // вверх
                maze[r - 1][c] = true;
            } else if (random_ == 1 && (r + 1 < getRow() && !maze[r + 1][c])) {  // вниз
                maze[r + 1][c] = true;
            } else if (random_ == 2 && (c + 1 < getCol() && !maze[r][c + 1])) {  // вправо
                maze[r][c + 1] = true;
            } else if (random_ == 3 && (c > 0 && !maze[r][c - 1])) {  // влево
                maze[r][c - 1] = true;
            } else {
                break;
            }

            //  проверка изолированных областей
            bool isoArea = false;
            for (int i = 0; i < getRow(); ++i) {
                for (int j = 0; j < getCol(); ++j) {
                    if (maze[i][j]) {
                        if (checkWall(maze, i, j)) {
                            isoArea = true;
                            break;
                        }
                    }
                }
                if (isoArea) {
                    break;
                }
            }

            if (isoArea) {
                std::cout << "Есть изолированные области" << std::endl;
            } else {
                printMaze(maze);
            }
        }
    }
}

bool s21::Maze::checkWall(const std::vector<std::vector<bool>>& maze, int row, int col) {
    return maze[row][col - 1] || maze[row][col + 1] || maze[row - 1][col] || maze[row][col + 1];
}

void s21::Maze::printMaze(const std::vector<std::vector<bool>>& maze) {
    for (const auto& row : maze) {
        for (const auto& cell : row) {
            if  (cell) {
                 std::cout << "X";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
