#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>

using namespace std;


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

// стена вокруг текущей клетки
bool hasWall(const vector<vector<bool>>& verticalWalls, const vector<vector<bool>>& horizontalWalls, int row, int col) {
    return verticalWalls[row][col - 1] || verticalWalls[row][col + 1] || horizontalWalls[row - 1][col] || horizontalWalls[row + 1][col];
}

// печать лабиринта в консоль
void Maze::print() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cout << (grid[r][c].visited ? " " : "#");
            if (grid[r][c].right) {
                cout << (grid[r][c].down ? " " : "#");
            } else {
                cout << "#";
            }
        }
        cout << endl;
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c].down) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// Новый метод для сохранения в файл
void Maze::saveToFile(const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << rows << " " << cols << endl; // Записываем размеры лабиринта

        // Первая матрица (горизонтальные стены)
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                // Если границы справа, то 1, иначе 0
                outFile << (grid[r][c].right ? 1 : 0) << " ";
            }
            outFile << endl;
        }

        // Вторая матрица (вертикальные стены)
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                // Если границы снизу, то 1, иначе 0
                outFile << (grid[r][c].down ? 1 : 0) << " ";
            }
            outFile << endl;
        }

        outFile.close(); // Закрываем файл
    } else {
        cerr << "Ошибка открытия файла" << endl;
    }
}

int main() {
    int rows, cols;
    cout << "Введите количество строк и столбцов лабиринта: ";
    cin >> rows >> cols;

    Maze maze(rows, cols);
    maze.generate();
    maze.print();

    string filename;
    cout << "Введите имя файла для сохранения лабиринта: ";
    cin >> filename;
    maze.saveToFile(filename); // Сохраняем лабиринт в файл

    return 0;
}

