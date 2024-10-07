#ifndef MAZE_H_
#define MAZE_H_

#include <list>
#include <iostream>

namespace s21 {

class Maze {
 public:

    Maze(int row, int col);
    Maze(int row, int col, int bias);
    int getRow() {return row_; };
    int getCol() {return col_; };

    std::vector<std::vector<int>> getRightWalls() { return rightWalls_; };
    std::vector<std::vector<int>> getBottomWalls() { return bottomWalls_; };
    std::vector<std::vector<int>> getPath() { return path_; };

    void FindPath(int startPosX, int startPosY, int endPosX, int endPosY);
    void SaveToFile(const std::string& filenam)

    void setRow(int row) { row_ = std::min(std::max(row, 1), 50);}
    void setCol(int col) { col_ = std::min(std::max(col, 1), 50);}
    void setBias(int bias) { bias_ = std::min(std::max(bias, 0), biasMax); }

    void setSize(int rows, int cols) {
        setRow(rows);
        setCol(cols);
    }

 private:
    int row_;
    int col_;
    int bias_;
    const int biasMax = 100;

    std::vector<std::vector<int>> rightWalls_;
    std::vector<std::vector<int>> bottomWalls_;
    std::vector<std::vector<int>> path_;

    void RandomValue(); //Для теста отрисовки
    void Generate();
    void HasWall();
    void Print();
};

}  // namespace s21

#endif  // MAZE_H_

