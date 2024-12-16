#include "findPath.h"

s21::FindPath::FindPath(Maze maze)
    : maze_(maze), path_(), start_({0, 0}), end_({0, 0}) {}

std::vector<std::vector<int>> s21::FindPath::Find(int startPosX, int startPosY,
                                                  int endPosX, int endPosY) {
  if (startPosX >= maze_.getCol() || startPosX < 0 ||
      endPosX >= maze_.getCol() || endPosX < 0 || startPosY >= maze_.getRow() ||
      startPosY < 0 || endPosY >= maze_.getRow() || endPosY < 0) {
    return {};
  }
  start_ = {startPosX, startPosY};
  end_ = {endPosX, endPosY};
  currentPosition_ = {startPosX, startPosY};

  Direction currentDirection = Direction::kLeft;
  path_.clear();
  while (currentPosition_ != end_) {
    path_.push_back(currentPosition_);

    currentDirection = ChangeCounterClockwise(currentDirection);
    std::vector<int> nextPosition;
    while (true) {
      nextPosition = NextCell(currentDirection, currentPosition_);

      if (nextPosition[0] >= 0 && nextPosition[0] < maze_.getCol() &&
          nextPosition[1] >= 0 && nextPosition[1] < maze_.getRow() &&
          CanStep(currentDirection, nextPosition)) {
        break;
      }
      currentDirection = ChangeClockwise(currentDirection);
    }
    currentPosition_ = nextPosition;

    if (containsStart(currentPosition_)) {
      path_.pop_back();
      path_.pop_back();
    }
  }
  path_.push_back(currentPosition_);

  return path_;
}

bool s21::FindPath::containsStart(const std::vector<int>& Start) {
  for (const auto& path : path_) {
    if (path.size() == 2 && path[0] == Start[0] && path[1] == Start[1]) {
      return true;
    }
  }
  return false;
}

bool s21::FindPath::CanStep(Direction direction,
                            const std::vector<int>& position) const {
  if (direction == Direction::kRight &&
      maze_.getRightWalls()[position[1]][position[0] - 1] == 0)
    return true;
  if (direction == Direction::kLeft &&
      maze_.getRightWalls()[position[1]][position[0]] == 0)
    return true;
  if (direction == Direction::kUp &&
      maze_.getBottomWalls()[position[1]][position[0]] == 0)
    return true;
  if (direction == Direction::kDown &&
      maze_.getBottomWalls()[position[1] - 1][position[0]] == 0)
    return true;
  return false;
}

std::vector<int> s21::FindPath::NextCell(s21::FindPath::Direction direction,
                                         const std::vector<int>& position) {
  std::vector<int> nextPosition = position;
  switch (direction) {
    case s21::FindPath::Direction::kUp:
      nextPosition[1] -= 1;
      break;
    case s21::FindPath::Direction::kDown:
      nextPosition[1] += 1;
      break;
    case s21::FindPath::Direction::kLeft:
      nextPosition[0] -= 1;
      break;
    case s21::FindPath::Direction::kRight:
      nextPosition[0] += 1;
      break;
    default:
      throw std::out_of_range("Not expected direction value");
  }
  return nextPosition;
}

s21::FindPath::Direction s21::FindPath::ChangeClockwise(
    s21::FindPath::Direction direction) {
  switch (direction) {
    case s21::FindPath::Direction::kUp:
      return s21::FindPath::Direction::kRight;
    case s21::FindPath::Direction::kRight:
      return s21::FindPath::Direction::kDown;
    case s21::FindPath::Direction::kDown:
      return s21::FindPath::Direction::kLeft;
    case s21::FindPath::Direction::kLeft:
      return s21::FindPath::Direction::kUp;
    default:
      throw std::out_of_range("Not expected direction value");
  }
}
s21::FindPath::Direction s21::FindPath::ChangeCounterClockwise(
    s21::FindPath::Direction direction) {
  switch (direction) {
    case s21::FindPath::Direction::kUp:
      return s21::FindPath::Direction::kLeft;
    case s21::FindPath::Direction::kLeft:
      return s21::FindPath::Direction::kDown;
    case s21::FindPath::Direction::kDown:
      return s21::FindPath::Direction::kRight;
    case s21::FindPath::Direction::kRight:
      return s21::FindPath::Direction::kUp;
    default:
      throw std::out_of_range("Not expected direction value");
  }
}
