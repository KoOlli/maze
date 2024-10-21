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

void s21::Maze::Init() {
//    path_ = std::vector<std::vector<int>>(row_, std::vector<int>(2, 0));
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
//    std::iota(set.begin(), set.end(), 1);
    // Заполняем вектор значениями от 1 до col_
    for (int i = 1; i < col_; ++i) {
        set[i - 1] = i; // добавляем элемент в множество
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
