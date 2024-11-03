#include "maze.h"

s21::Maze::Maze(int row, int col) {
  row_ = row;
  col_ = col;

  Generate(row_, col_);
}

void s21::Maze::Init() {
  rightWalls_ = std::vector<std::vector<int>>(row_, std::vector<int>(col_, 0));
  bottomWalls_ = std::vector<std::vector<int>>(row_, std::vector<int>(col_, 0));

  for (int i = 0; i < row_; ++i) {
    rightWalls_.push_back(std::vector<int>());
    bottomWalls_.push_back(std::vector<int>());
    rightWalls_[i][col_ - 1] = 1;
  }
  for (int i = 0; i < col_; ++i) {
    bottomWalls_[row_ - 1][i] = 1;
  }
}

void s21::Maze::Generate(int n, int m) {
  Init();
  int setUniqueNumber = col_;
  std::vector<int> set(col_);
  for (int i = 1; i < col_; ++i) {
    set[i - 1] = i;
  }
  for (int row = 0; row < row_; ++row) {
    if (row > 0) {
      for (int i = 0; i < col_; ++i) {
        if (bottomWalls_[row - 1][i] == 1) set[i] = setUniqueNumber++;
      }
    }

    std::vector<int> rand(col_ * 2);
    for (int i = 0; i < rand.size(); ++i) rand[i] = random() % (biasMax_ + 2);
    for (int i = 0; i < col_; ++i) {
      if (i < col_ - 1 && (rand[i] == 1 || set[i + 1] == set[i]))
        rightWalls_[row][i] = 1;
      else if (i < col_ - 1) {
        std::vector<int> newSet;
        for (int x : set) {
          if (x == set[i + 1]) {
            newSet.push_back(set[i]);
          } else {
            newSet.push_back(x);
          }
        }
        set = newSet;
      }
    }

    for (int i = 0; i < col_; i++) {
      int allSetLength = 0;
      for (int x : set) {
        if (x == set[i]) {
          allSetLength++;
        }
      }
      int setLength = 0;
      for (int j = 0; j <= i; j++) {
        if (set[j] == set[i]) {
          setLength++;
        }
      }
      int bottomCount = 0;
      for (auto it = bottomWalls_[row].begin() + (i - setLength + 1);
           it != bottomWalls_[row].begin() + (i + 1); it++) {
        if (*it == 1) {
          bottomCount++;
        }
      }
      if (rand[i + col_] > bias_) {
        if ((rightWalls_[row][i] != 1) ||
            (!(bottomCount == setLength - 1) && setLength > 1))
          bottomWalls_[row][i] = 1;
      } else if (rightWalls_[row][i] == 1 && setLength > 1 &&
                 bottomCount == 0) {
        bottomWalls_[row][i] = 1;
      }
    }
  }
  for (int i = 0; i < col_; ++i) {
    if ((i < col_ - 1 && set[i + 1] != set[i]) && (i != col_ - 1))
      rightWalls_[row_ - 1][i] = 0;
    if (i < col_ - 1) {
      int nextValue = set[i + 1];
      int currentValue = set[i];
      for (int& x : set) {
        if (x == nextValue) {
          x = currentValue;
        }
      }
    }
  }
}

void s21::Maze::Save(const std::string& path) {
  std::ostringstream stringStream;
  stringStream << row_ << " " << col_ << std::endl;
  for (int i = 0; i < row_; ++i) {
    std::vector<std::string> rowValues;
    for (int j = 0; j < col_; ++j) {
      rowValues.push_back(std::to_string(rightWalls_[i][j]));
    }
    stringStream << Join(rowValues, " ") << std::endl;
  }
  stringStream << std::endl;
  for (int i = 0; i < row_; ++i) {
    std::vector<std::string> rowValues;
    for (int j = 0; j < col_; ++j) {
      rowValues.push_back(std::to_string(bottomWalls_[i][j]));
    }
    stringStream << Join(rowValues, " ") << std::endl;
  }

  std::ofstream outFile(path);
  if (outFile) {
    outFile << stringStream.str();
    outFile.close();
    std::cout << "Good opening file for writing: " << path << std::endl;
  } else {
    std::cerr << "Error opening file for writing: " << path << std::endl;
  }
}

std::string s21::Maze::Join(const std::vector<std::string>& strings,
                            const std::string& delimiter) {
  std::ostringstream result;
  for (size_t i = 0; i < strings.size(); ++i) {
    result << strings[i];
    if (i < strings.size() - 1) {
      result << delimiter;
    }
  }
  return result.str();
}

void s21::Maze::ReadFromFile(const std::string& path) {
  bottomWalls_.clear();
  rightWalls_.clear();

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

  if (lines.empty()) {
    throw std::runtime_error("Incorrect file format.");
  }

  std::istringstream firstLine(lines[0]);
  firstLine >> row_ >> col_;

  if (lines.size() != row_ * 2 + 2) {
    throw std::runtime_error("Incorrect file format.");
  }

  for (int i = 0; i < row_; ++i) {
    bottomWalls_.push_back(ParseLine(lines[i + row_ + 2]));
    rightWalls_.push_back(ParseLine(lines[i + 1]));
  }
}

std::vector<int> s21::Maze::ParseLine(const std::string& line) {
  std::vector<int> result;
  std::istringstream ss(line);
  int value;
  while (ss >> value) {
    result.push_back(value);
  }
  return result;
}
