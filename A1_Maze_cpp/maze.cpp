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

