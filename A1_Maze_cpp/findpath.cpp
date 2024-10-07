#include "findpath.h"

class PathFinder {
public:
    std::pair<int, int> Start;
    std::pair<int, int> End;
    std::vector<std::pair<int, int>> _path;
    Maze Maze;

    enum class Direction {
        Right,
        Left,
        Up,
        Down,
    };

    PathFinder(Maze maze, int startPosX = 0, int startPosY = 0, int endPosX = 0, int endPosY = 0)
        : Start(startPosX, startPosY), End(endPosX, endPosY), Maze(maze) {}

    std::vector<std::pair<int, int>> ToList() {
        return _path;
    }

    std::vector<std::pair<int, int>> FindPath() {
        if (Start.first >= Maze.Col || Start.first < 0 || End.first >= Maze.Col || End.first < 0 ||
            Start.second >= Maze.Row || Start.second < 0 || End.second >= Maze.Row || End.second < 0) {
            return {};
        }

        auto currentPosition = Start;
        Direction currentDirection = Direction::Left;

        while (currentPosition != End) {
            _path.push_back(currentPosition);
            currentDirection = ChangeCounterClockwise(currentDirection);
            std::pair<int, int> nextPosition;

            while (true) {
                nextPosition = NextCell(currentDirection, currentPosition);

                if (nextPosition.first >= 0 && nextPosition.first < Maze.Col &&
                    nextPosition.second >= 0 && nextPosition.second < Maze.Row &&
                    CanStep(currentDirection, nextPosition)) {
                    break;
                }

                currentDirection = ChangeClockwise(currentDirection);
            }

            currentPosition = nextPosition;

            if (std::find(_path.begin(), _path.end(), currentPosition) != _path.end()) {
                _path.pop_back();
                _path.pop_back();
            }
        }

        _path.push_back(currentPosition);
        return ToList();
    }

private:
    bool CanStep(Direction direction, const std::pair<int, int>& position) {
        if (direction == Direction::Right && position.first > 0 && Maze.RightWalls[position.second][position.first - 1] == 0)
            return true;
        if (direction == Direction::Left && Maze.RightWalls[position.second][position.first] == 0)
            return true;
        if (direction == Direction::Up && position.second > 0 && Maze.BottomWalls[position.second][position.first] == 0)
            return true;
        if (direction == Direction::Down && position.second > 0 && Maze.BottomWalls[position.second - 1][position.first] == 0)
            return true;
        return false;
    }

    static std::pair<int, int> NextCell(Direction direction, const std::pair<int, int>& position) {
        switch (direction) {
            case Direction::Up: return {position.first, position.second - 1};
            case Direction::Down: return {position.first, position.second + 1};
            case Direction::Left: return {position.first - 1, position.second};
            case Direction::Right: return {position.first + 1, position.second};
            default: throw std::out_of_range("Not expected direction value");
        }
    }

    static Direction ChangeClockwise(Direction direction) {
        switch (direction) {
            case Direction::Up: return Direction::Right;
            case Direction::Right: return Direction::Down;
            case Direction::Down: return Direction::Left;
            case Direction::Left: return Direction::Up;
            default: throw std::out_of_range("Not expected direction value");
        }
    }
        static Direction ChangeCounterClockwise(Direction direction) {
        switch (direction) {
            case Direction::Up: return Direction::Left;
            case Direction::Left: return Direction::Down;
            case Direction::Down: return Direction::Right;
            case Direction::Right: return Direction::Up;
            default: throw std::out_of_range("Not expected direction value");
        }
    }
};

int main() {
    // Пример использования
    Maze maze(5, 5);
    PathFinder pathFinder(maze, 0, 0, 4, 4);

    auto path = pathFinder.FindPath();

    for (const auto& pos : path) {
        std::cout << "(" << pos.first << ", " << pos.second << ") ";
    }

    return 0;
}
