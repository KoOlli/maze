#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <random>

class Maze {
private:
    int _row;
    int _col;
    std::vector<std::vector<int>> _rightWalls;
    std::vector<std::vector<int>> _bottomWalls;
    std::vector<std::vector<int>> Path;

public:
    int Bias;
    const int BiasMax = 100;

    Maze(int row = 4, int col = 4, int bias = 50)
        : _row(std::min(std::max(row, 1), 50)),
          _col(std::min(std::max(col, 1), 50)),
          Bias(bias) {
        Init();
    }

    void SetSize(int rows, int cols) {
        _row = rows;
        _col = cols;
        Init();
    }

    void ReadFromFile(const std::string& path) {
        _bottomWalls.clear();
        _rightWalls.clear();
        Path.clear();
        
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file.");
        }

        std::string line;
        if (!std::getline(file, line)) {
            throw std::runtime_error("Incorrect file format.");
        }

        std::istringstream iss(line);
        iss >> _row >> _col;

        if (std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n') != _row * 2 + 2) {
            throw std::runtime_error("Incorrect file format.");
        }

        file.clear(); // Clear EOF flag
        file.seekg(0); // Go back to the beginning of the file

        for (int i = 0; i < _row; ++i) {
            std::getline(file, line);
            std::istringstream rowStream(line);
            std::vector<int> rowValues(_col);
            for (int j = 0; j < _col; ++j) {
                rowStream >> rowValues[j];
            }
            _rightWalls.push_back(rowValues);
        }

        for (int i = 0; i < _row; ++i) {
            std::getline(file, line);
            std::istringstream rowStream(line);
            std::vector<int> rowValues(_col);
            for (int j = 0; j < _col; ++j) {
                rowStream >> rowValues[j];
            }
            _bottomWalls.push_back(rowValues);
        }
    }

private:
    void Init() {
        Path.clear();
        _rightWalls.assign(_row, std::vector<int>(_col, 0));
        _bottomWalls.assign(_row, std::vector<int>(_col, 0));

        for (int i = 0; i < _row; ++i) {
            _rightWalls[i][_col - 1] = 1;
        }
        for (int i = 0; i < _col; ++i) {
            _bottomWalls[_row - 1][i] = 1;
        }
    }

public:
    void Generate() {
        Init();
        int setUniqueNumber = _col;
        std::vector<int> set(_row + 1);
        for (int i = 1; i <= _col; ++i) set[i] = i;

        std::random_device rd;
        std::mt19937 gen(rd());
        
        for (int row = 0; row < _row; row++) {
            if (row > 0) {
                for (int i = 0; i < _col; i++) {
                    if (_bottomWalls[row - 1][i] == 1) {
                        set[i] = ++setUniqueNumber;
                    }
                }
            }

            std::vector<int> rand(2 * _col);
            for (int& r : rand) r = gen() % (BiasMax + 2);

            for (int i = 0; i < _col; ++i) {
                if (i < _col - 1 && (rand[i] < Bias && set[i + 1] == set[i])) {
                    _rightWalls[row][i] = 1;
                } else if (i < _col - 1) {
                    std::replace(set.begin(), set.end(), set[i + 1], set[i]);
                }
            }

            for (int i = 0; i < _col; ++i) {
                int allSetLength = std::count(set.begin(), set.end(), set[i]);
                int setLength = std::count(set.begin(), set.begin() + i + 1, set[i]);
                int bottomCount = std::count(_bottomWalls[row].begin() + std::max(0, i - setLength + 1), 
                                             _bottomWalls[row].begin() + i + 1, 
                                             1);
                if (rand[i + _col] > Bias) {
                    if (_rightWalls[row][i] != 1 && !(bottomCount == setLength - 1 && setLength > 1)) {
                        _bottomWalls[row][i] = 1;
                    }
                } else if (_rightWalls[row][i] == 1 && setLength > 1 && bottomCount == 0) {
                    _bottomWalls[row][i] = 1;
                }
            }
        }
    }
};

int main() {
    Maze maze(4, 4, 50);
    maze.Generate();

    // Пример использования ReadFromFile
    // maze.ReadFromFile("path_to_file.txt");

    return 0;
}
