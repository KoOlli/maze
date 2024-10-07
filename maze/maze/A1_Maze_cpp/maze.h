#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <vector>

class Maze {
   public:
    Maze(int rows, int cols);
    void generate();
    void display() const;
    void saveToFile(const std::string& filename) const;

   private:
    int findSet(int v);
    void unionSets(int a, int b);

    int rows;
    int cols;
    std::vector<std::vector<int>> maze;
    std::vector<int> parent;
};
