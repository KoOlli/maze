#ifndef MAZE_H_
#define MAZE_H_

#include <list>
#include <iostream>
#include <utility>

#include <vector>
#include <random>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

namespace s21 {

class Maze {
 public:
    enum class Direction {
        Right,
        Left,
        Up,
        Down,
    };

    Maze(int row, int col);
    Maze(int row, int col, int bias);

    int getRow() const { return row_; };
    int getCol() const { return col_; };
    int getSize() const { return getRow() * getCol(); };
    std::vector<std::vector<int>> getPath() const { return path_; };
    std::vector<std::vector<int>> getRightWalls() const { return rightWalls_; };
    std::vector<std::vector<int>> getBottomWalls() const { return bottomWalls_; };
//    std::vector<std::vector<int>> getPath() { return path_; };

    void setRow(int row) { row_ = row; };
    void setCol(int col) { col_ = col; };

    std::vector<std::vector<int>> FindPath(int startPosX, int startPosY, int endPosX, int endPosY);
    void Generate(int n, int m);
//    int FindRoot(int x);
    void unionSets(int  cell1, int cell2);
    bool CanStep(Direction direction, const std::vector<int>& position) const;
    static std::vector<int> NextCell(Direction direction, const std::vector<int>& position);
    static Direction ChangeClockwise(Direction direction);
    static Direction ChangeCounterClockwise(Direction direction);
    bool containsStart(const std::vector<int>& Start);
//    void pushBackPath(std::pair<int, int> push_) { path_.push_back({push_.first, push_.second}); };
//    int find(int x);
    void Init();
    std::vector<int> parent;
    void PathFinder(int startPosX, int startPosY, int endPosX, int endPosY);


 private:
    std::vector<int> End;
    std::vector<int> Start;
    int row_;
    int col_;
    int Bias;
    int BiasMax;
    std::vector<std::vector<int>> rightWalls_;
    std::vector<std::vector<int>> bottomWalls_;
    std::vector<std::vector<int>> path_;
    std::vector<int> currentPosition;

//    void RandomValue(); //Для теста отрисовки

    struct Cell {
        bool right;
        bool down;
//        int parent_; // Номер родительского узла (для объединения)
    };


        std::vector<std::vector<Cell>> grid;
};

}  // namespace s21

#endif  // MAZE_H_
