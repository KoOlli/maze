#ifndef FINDPATH_H
#define FINDPATH_H

#include "maze.h"

namespace s21 {

class FindPath {
public:
    enum class Direction {
        kRight,
        kLeft,
        kUp,
        kDown,
    };

    FindPath(Maze maze);
    std::vector<std::vector<int>> getPath() const { return path_; };
    std::vector<std::vector<int>> Find(int startPosX, int startPosY, int endPosX, int endPosY);

private:
    Maze maze_;
    std::vector<int> end_;
    std::vector<int> start_;
    std::vector<int> currentPosition_;
    std::vector<std::vector<int>> path_;

    bool containsStart(const std::vector<int>& Start);
    static Direction ChangeClockwise(Direction direction);
    static Direction ChangeCounterClockwise(Direction direction);
    bool CanStep(Direction direction, const std::vector<int>& position) const;
    static std::vector<int> NextCell(Direction direction, const std::vector<int>& position);
};

}  // namespace s21

#endif // FINDPATH_H
