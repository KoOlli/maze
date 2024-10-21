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
//    enum class Direction {
//        Right,
//        Left,
//        Up,
//        Down,
//    };

    Maze(int row, int col);
    Maze(int row, int col, int bias);

    int getRow() const { return row_; };
    int getCol() const { return col_; };
    int getSize() const { return getRow() * getCol(); };

    std::vector<std::vector<int>> getRightWalls() const { return rightWalls_; };
    std::vector<std::vector<int>> getBottomWalls() const { return bottomWalls_; };

    void setRow(int row) { row_ = row; };
    void setCol(int col) { col_ = col; };

//    std::vector<std::vector<int>> FindPath(int startPosX, int startPosY, int endPosX, int endPosY);
    void Generate(int n, int m);


    void unionSets(int  cell1, int cell2);

    void Init();
//    void PathFinder(int startPosX, int startPosY, int endPosX, int endPosY);
//    int find(int x, std::vector<int>& parent);
//    void unionSet(int x, int y, std::vector<int>& parent);


 private:
    int row_;
    int col_;
    int Bias;
    int BiasMax;
    std::vector<std::vector<int>> rightWalls_;
    std::vector<std::vector<int>> bottomWalls_;
//    std::vector<std::vector<int>> path_;


    struct Cell {
        bool right;
        bool down;
//        int parent_; // Номер родительского узла (для объединения)
    };
        std::vector<std::vector<Cell>> grid;
};

class FindPath {
public:
    enum class Direction {
        Right,
        Left,
        Up,
        Down,
    };

    FindPath(Maze maze);
    std::vector<std::vector<int>> Find(int startPosX, int startPosY, int endPosX, int endPosY);
    std::vector<std::vector<int>> getPath() const { return path__; };

    bool CanStep(Direction direction, const std::vector<int>& position) const;
    static std::vector<int> NextCell(Direction direction, const std::vector<int>& position);
    static Direction ChangeClockwise(Direction direction);
    static Direction ChangeCounterClockwise(Direction direction);
    bool containsStart(const std::vector<int>& Start);

private:
    Maze maze_;
//    s21::FindPath findPath(Maze);
    std::vector<int> End;
    std::vector<int> Start;
    std::vector<std::vector<int>> path__;
    std::vector<int> currentPosition;
};

}  // namespace s21

#endif  // MAZE_H_
