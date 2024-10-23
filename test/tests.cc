#include <gtest/gtest.h>

#include <iostream>

#include "../A1_Maze_cpp/findpath.h"
#include "../A1_Maze_cpp/maze.h"

TEST(Maze, InitMaze) {
  s21::Maze *maze = new s21::Maze(4, 4);
  ASSERT_TRUE(maze != nullptr);
}

TEST(Maze, MazePath) {
  s21::Maze *maze = new s21::Maze(2, 2);
  maze->ReadFromFile("test/settingsBig.txt");
  s21::FindPath *find = new s21::FindPath(*maze);
  find->Find(0, 0, 1, 18);
  std::vector<std::vector<int>> path;
  path = find->getPath();
  ASSERT_TRUE(!path.empty());
  int expected = 0;
  ASSERT_NE(find->getPath().size(), expected);
}

TEST(Maze, MazePathNull) {
  s21::Maze *maze = new s21::Maze(2, 2);
  maze->ReadFromFile("test/settingsBig.txt");
  s21::FindPath *find = new s21::FindPath(*maze);
  find->Find(0, 0, 1, 21);
  std::vector<std::vector<int>> path;
  path = find->getPath();
  ASSERT_TRUE(path.empty());
}

TEST(Maze, ReadFromFileSize) {
  s21::Maze *maze = new s21::Maze(4, 4);
  int expected = 4;
  ASSERT_EQ(maze->getRow(), expected);
  ASSERT_EQ(maze->getCol(), expected);
}

TEST(Maze, ReadFromFileRightWalls) {
  s21::Maze *maze = new s21::Maze(4, 4);
  maze->ReadFromFile("test/settings.txt");
  std::vector<std::vector<int>> expected = {
      {0, 0, 0, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {0, 0, 0, 1}};
  for (int i = 0; i < maze->getRow(); i++)
    for (int j = 0; j < maze->getCol(); j++)
      ASSERT_EQ(maze->getRightWalls()[i][j], expected[i][j]);
}

TEST(Maze, ReadFromFileBottomWalls) {
  s21::Maze *maze = new s21::Maze(4, 4);
  maze->ReadFromFile("test/settings.txt");
  std::vector<std::vector<int>> expected = {
      {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}, {1, 1, 1, 1}};
  for (int i = 0; i < maze->getRow(); i++)
    for (int j = 0; j < maze->getCol(); j++)
      ASSERT_EQ(maze->getBottomWalls()[i][j], expected[i][j]);
}

TEST(Maze, SaveFileNotEmpty) {
  s21::Maze *maze = new s21::Maze(4, 4);
  std::string path = "test/save.txt";
  maze->Save(path);
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open the file.");
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  file.close();
  int expected = 0;
  ASSERT_NE(lines.size(), expected);
}

TEST(Maze, SaveFileSize) {
  s21::Maze *maze = new s21::Maze(4, 4);
  std::string path = "test/save.txt";
  maze->Save(path);
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open the file.");
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  file.close();
  std::istringstream firstLine(lines[0]);
  int expectedRow = 0;
  int expectedCol = 0;
  firstLine >> expectedRow >> expectedCol;
  ASSERT_EQ(maze->getRow(), expectedRow);
  ASSERT_EQ(maze->getCol(), expectedCol);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
