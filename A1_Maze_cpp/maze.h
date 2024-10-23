#ifndef A1_MAZE_CPP_MAZE_H_
#define A1_MAZE_CPP_MAZE_H_

#include <list>
#include <iostream>
#include <utility>

#include <vector>
#include <random>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace s21 {

class Maze {
 public:
    Maze(int row, int col);
    Maze(int row, int col, int bias);

    int getRow() const { return row_; };
    int getCol() const { return col_; };
    std::vector<std::vector<int>> getRightWalls() const { return rightWalls_; };
    std::vector<std::vector<int>> getBottomWalls() const { return bottomWalls_; };

    void Save(const std::string& path);
    void ReadFromFile(const std::string& path);

 private:
    struct Cell {
        bool right_;
        bool down_;
    };

    int row_;
    int col_;
    int bias_;
    int biasMax_;

    std::vector<std::vector<Cell>> grid_;
    std::vector<std::vector<int>> rightWalls_;
    std::vector<std::vector<int>> bottomWalls_;

    void Init();
    void Generate(int n, int m);
    std::vector<int> ParseLine(const std::string& line);
    std::string Join(const std::vector<std::string>& strings, const std::string& delimiter);

};

}  // namespace s21

#endif  // A1_MAZE_CPP_MAZE_H_
