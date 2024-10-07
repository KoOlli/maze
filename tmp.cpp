#include <iostream>
#include <vector>
#include <random>
#include <stack>
#include <fstream>

using namespace std;

struct Cell {
    bool right; // соединение справа
    bool down;  // соединение вниз
    bool visited; // была ли посещена
};

class Maze {
public:
    Maze(int rows, int cols);
    void generate();
    void print();
    void saveToFile(const string& filename); // Новый метод для сохранения в файл

private:
    int rows, cols;
    vector<vector<Cell>> grid;
};

Maze::Maze(int rows, int cols) : rows(rows), cols(cols), grid(rows, vector<Cell>(cols)) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = { true, true, false }; // По умолчанию все стены присутствуют
        }
    }
}

void Maze::generate() {
    int random_ = random();

    for (int r = 0; r < rows; ++r) {
        vector<int> horizontalRuns; // Массив для хранения длин горизонтальных пробелов
        for (int c = 0; c < cols; ++c) {
            grid[r][c].visited = false;
            horizontalRuns.push_back(c);
            // Если это последний или следующий горизонтальный узел, создаем соединение
            if (c == cols - 1 || random_ % 2 == 0) {
                for (int i = 0; i < horizontalRuns.size(); ++i) {
                    if (r > 0 && grid[r][horizontalRuns[i]].visited) {
                        grid[r][horizontalRuns[i]].down = false;
                    } else {
                        grid[r][horizontalRuns[i]].visited = true;
                    }
                }
                horizontalRuns.clear();
            }
        }
        // Обрабатываем элементы последнего горизонтального пробела
        if (!horizontalRuns.empty()) {
            for (int i = 0; i < horizontalRuns.size(); ++i) {
                if (r > 0 && grid[r][horizontalRuns[i]].visited) {
                    grid[r][horizontalRuns[i]].down = false;
                } else {
                    grid[r][horizontalRuns[i]].visited = true;
                }
            }
        }
    }

    // Генерация вертикальных соединений
    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows; ++r) {
            if (r < rows - 1 && grid[r][c].down) {
                if (random_ % 2 == 0) {
                    grid[r][c].down = false;
                    grid[r + 1][c].visited = true;
                }
            }
        }
    }
}





