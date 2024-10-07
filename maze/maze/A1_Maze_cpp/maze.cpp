// #include <iostream>
// #include <vector>
// #include <fstream>
// #include <random>
// #include <set>

// class Maze {
// public:
// Maze(int rows, int cols);
// void generate();
// void display() const;
// void saveToFile(const std::string& filename) const;

// private:
// int findSet(int v);
// void unionSets(int a, int b);

// int rows;
// int cols;
// std::vector<std::vector<int>> maze;
// std::vector<int> parent;
// };

#include "Maze.h"

Maze::Maze(int rows, int cols) : rows(rows), cols(cols) {
    maze.resize(rows, std::vector<int>(cols, 1));  // Изначально все стены
    parent.resize(rows * cols);
    for (int i = 0; i < rows * cols; ++i) {
        parent[i] = i;
    }
}

int Maze::findSet(int v) {
    if (v == parent[v]) return v;
    return parent[v] = findSet(parent[v]);
}

void Maze::unionSets(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        parent[b] = a;
    }
}

void Maze::generate() {
    std::vector<std::pair<int, int>> walls;

    // Инициализация стен
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (j < cols - 1) walls.emplace_back(i * cols + j, i * cols + (j + 1));  // Горизонтальные стены
            if (i < rows - 1) walls.emplace_back(i * cols + j, (i + 1) * cols + j);  // Вертикальные стены
        }
    }

    std::shuffle(walls.begin(), walls.end(), std::mt19937{std::random_device{}()});

    for (const auto& wall : walls) {
        int a = wall.first;
        int b = wall.second;

        if (findSet(a) != findSet(b)) {
            maze[a / cols][a % cols] = 0;  // Удаление стены
            unionSets(a, b);
        }
    }
}

void Maze::display() const {
    for (const auto& row : maze) {
        for (int cell : row) {
            std::cout << (cell ? "#" : " ");
        }
        std::cout << "\n";
    }
}

void Maze::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи.\n";
        return;
    }

    for (const auto& row : maze) {
        for (int cell : row) {
            file << (cell ? "#" : " ");
        }
        file << "\n";
    }

    file.close();
}

int main() {
    int rows, cols;
    std::cout << "Введите количество строк и столбцов: ";
    std::cin >> rows >> cols;

    Maze maze(rows, cols);
    maze.generate();

    maze.display();

    maze.saveToFile("maze.txt");

    return 0;
}
