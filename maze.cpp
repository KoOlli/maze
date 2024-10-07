// Новый метод для сохранения в файл
void s21::Maze::SaveToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << getRow() << " " << getCol() << endl; // Записываем размеры лабиринта

        // Первая матрица (горизонтальные стены)
        for (int r = 0; r < getRow(); ++r) {
            for (int c = 0; c < getCol(); ++c) {
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





#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

// Функция для генерации идеального лабиринта
void generateIdealLabyrinth(int rows, int cols) {
    // Массив для хранения лабиринта
    std::vector<std::vector<bool>> labyrinth(rows, std::vector<bool>(cols));
    
    // Случайная начальная точка
    int start_row = rand() % rows;
    int start_col = rand() % cols;
    
    // Начинаем с одной открытой клетки
    labyrinth[start_row][start_col] = true;
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (!labyrinth[row][col]) {
                continue;
            }
            
            // Генерация случайного направления
            int direction = rand() % 4;
            
            switch (direction) {
                case 0: // Вверх
                    if (row > 0 && !labyrinth[row - 1][col]) {
                        labyrinth[row - 1][col] = true;
                    }
                    break;
                case 1: // Вниз
                    if (row + 1 < rows && !labyrinth[row + 1][col]) {
                        labyrinth[row + 1][col] = true;
                    }
                    break;
                case 2: // Вправо
                    if (col + 1 < cols && !labyrinth[row][col + 1]) {
                        labyrinth[row][col + 1] = true;
                    }
                    break;
                case 3: // Влево
                    if (col > 0 && !labyrinth[row][col - 1]) {
                        labyrinth[row][col - 1] = true;
                    }
                    break;
            }
        }
    }
    
    // Проверка наличия изолированных областей и петель
    bool hasIsolatedArea = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (labyrinth[i][j]) {
                if (hasWall(labyrinth, i, j)) {
                    hasIsolatedArea = true;
                    break;
                }
            }
        }
        if (hasIsolatedArea) {
            break;
        }
    }
    
    if (hasIsolatedArea) {
        std::cout << "Лабиринт содержит изолированные области." << std::endl;
    } else {
        printLabyrinth(labyrinth);
    }
}

// Функция для проверки наличия стены вокруг текущей клетки
bool hasWall(const std::vector<std::vector<bool>>& labyrinth, int row, int col) {
    return labyrinth[row][col - 1] || labyrinth[row][col + 1] ||
           labyrinth[row - 1][col] || labyrinth[row + 1][col];
}

// Функция для печати лабиринта
void printLabyrinth(const std::vector<std::vector<bool>>& labyrinth) {
    for (const auto& row : labyrinth) {
        for (const auto& cell : row) {
            if (cell) {
                std::cout << "X";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел
    
    int rows, cols;
    std::cin >> rows >> cols;
    
    generateIdealLabyrinth(rows, cols);
    
    return 0;
}
