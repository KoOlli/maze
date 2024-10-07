
#include <iostream>
#include <vector>
#include <stdexcept>
#include <list>
#include <algorithm>

class Maze {
public:
    int Row, Col;
    std::vector<std::vector<int>> RightWalls;
    std::vector<std::vector<int>> BottomWalls;

    Maze(int row, int col) : Row(row), Col(col) {
        RightWalls.resize(row, std::vector<int>(col));
        BottomWalls.resize(row, std::vector<int>(col));
    }
};
