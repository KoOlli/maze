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

 private:
    int row_;
    int col_;
    std::vector<std::vector<int>> rightWalls_;
    std::vector<std::vector<int>> bottomWalls_;
    std::vector<std::vector<int>> path_;

    void RandomValue(); //Для теста отрисовки
    void Generate(int getRow(), int getCol());
    bool checkWall(const std::vector<std::vector<bool>>& maze, int row, int col);
    void printMaze(const std::vector<std::vector<bool>>& maze);

};

}  // namespace s21

#endif  // MAZE_H_
