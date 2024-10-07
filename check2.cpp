#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

bool checkWall(const std::vector<std::vector<bool>>& maze, int row, int col) {
    return maze[row][col - 1] || maze[row][col + 1] || maze[row - 1][col] || maze[row][col + 1];
}

// void printMaze(const std::vector<std::vector<bool>>& maze) {
//     for (const auto& row : maze) {
//         for (const auto& cell : row) {
//             if  (cell) {
//                 std::cout << "X";
//             } else {
//                 std::cout << " ";
//             }
//         }
//         std::cout << "\n";
//     }
// }

void printMaze(const std::vector<std::vector<bool>>& maze, int rows, int cols) {
    // for (size_t i = 0; i < maze.; ++i) {
    //     for (size_t j = 0; j < maze[i].size(); ++j) {
    //         if (maze[i][j]) {
    //             std::cout << "X";
    //         } else {
    //             std::cout << " ";
    //         }
    //     }
    //     std::cout << "\n";
    // }
    for (int i = 0; i <= rows; ++i) {
        for (int j =  0; j <= cols; ++j) {
            if (maze[i][j]) {
                std::cout << "X";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

}

// bool isIsolated(const std::vector<std::vector<bool>>& maze, int row, int col) {
//     const int dirs[] = {-1, 0, 1};
//     int count = 0;
//     for (auto d : dirs) {
//         int newRow = row + d;
//         int newCol = col;
//         while (newRow >= 0 && newRow < maze.size() && newCol >= 0 && newCol < maze[0].size()) {
//             if (maze[newRow][newCol]) {
//                 count++;
//                 break;
//             }
//             newCol += d;
//         }
//     }
//     return count <= 1;
// }

// bool isIsolated(const std::vector<std:::vector<bool>>& maze, int row, int col) {
//     const int dirs[] = {-1, 0, 1};
//     int count = 0;
//     for (auto d : dirs) {
//         int newRow = row + d;
//         int newCol = col;
//         while (newRow >= 0 && newRow < maze.size() && newCol >= 0 && newCol < maze[0].size()) {
//             if (maze[newRow][newCol]) {
//                 count++;
//                 break;
//             }
//             newCol += d;
//         }
//     }
//     return count <= 1;
// }


// bool isIsolated(const std::vector<std::vector<bool>>& maze, int row, int col) {
//     const int dirs[] = {-1, 0, 1};
//     int count = 0;
//     for (auto d : dirs) {
//         int newRow = row + d;
//         int newCol = col;
//         while (newRow >= 0 && static_cast<int>(newRow) < maze.size() && newCol >= 0 && newCol < maze[0].size()) {
//             if (maze[newRow][newCol]) {
//                 count++;
//                 break;
//             }
//             newCol += d;
//         }
//     }
//     return count <= 1;
// }


// bool isLooped(const std::vector<std::vector<bool>>& maze, int row, int col) {
//     const int dirs[] = {-1, 0, 1};
//     bool visited[maze.size() * maze[0].size()];
//     memset(visited, false, sizeof(visited));
//     queue<pair<int, int>> q;
//     q.push({row, col});
//     visited[row * maze[0].size() + col] = true;
//     while (!q.empty()) {
//         pair<int, int> curr = q.front();
//         q.pop();
//         for (auto d : dirs) {
//             int newRow = curr.first + d;
//             int newCol = curr.second;
//             if (static_cast<int>(newRow) >= 0 && static_cast<int>(newRow) < maze.size() && newCol >= 0 && newCol < maze[0].size() && !visited[newRow * maze[0].size() + newCol] && maze[newRow][newCol]) {
//                 visited[newRow * maze[0].size() + newCol] = true;
//                 q.push({newRow, newCol});
//             }
//         }
//     }
//     return !visited[row * maze[0].size() + col];
// }

void Generate(int rows, int cols) {
    std::vector<std::vector<bool>> maze(rows, std::vector<bool>(cols));

    int start_row = rand() % rows;
    int start_col = rand() % cols;

    maze[start_row][start_col] = true;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (!maze[r][c]) {
                continue;
            }

            // выбор направление движения
            int random_ = rand() % 4;
            if (random_ == 0 && (r > 0 && !maze[r - 1][c])) {
                maze[r - 1][c] = true;
            } else if (random_ == 1 && (r + 1 < rows && !maze[r + 1][c])) {
                maze[r + 1][c] = true;
            } else if (random_ == 2 && (c + 1 < cols && !maze[r][c + 1])) {
                maze[r][c + 1] = true;
            } else if (random_ == 3 && (c > 0 && !maze[r][c - 1])) {
                maze[r][c - 1] = true;
            } else {
                break;
            }
            //  проверка изолированных областей
        //    isIsolated(maze, rows, cols);

    bool isoArea = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j]) {
                if (checkWall(maze, i, j)) {
                    isoArea = true;
                    break;
                }
            }
        }
        if (isoArea) {
            break;
        }
    }

            if (isoArea) {
                std::cout << "Есть изолированные области" << std::endl;
            } else {
                printMaze(maze, rows, cols);
            }
        }
    }
}


int main() {
    // srand(time(NULL)); // Инициализация генератора случайных чисел
    std::cout << "Введите количество строк и столбцов: ";

    int rows, cols;
    std::cin >> rows >> cols;
    
    Generate(rows, cols);
    
    return 0;
}