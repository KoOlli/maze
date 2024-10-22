#include "maze.h"
#include <QDebug>

s21::FindPath::FindPath(Maze maze)
    : maze_(maze), path__(), Start({0, 0}), End({0, 0}) {
}

std::vector<std::vector<int>> s21::FindPath::Find(int startPosX, int startPosY, int endPosX, int endPosY) {
    if (startPosX >= maze_.getCol() || startPosX < 0 || endPosX >= maze_.getCol() || endPosX < 0 ||
        startPosY >= maze_.getRow() || startPosY < 0 || endPosY >= maze_.getRow() || endPosY < 0) {
        return {};
    }
    Start = {startPosX, startPosY};
    End = {endPosX, endPosY};
    currentPosition = {startPosX, startPosY};

    Direction currentDirection = Direction::Left;
    path__.clear();
    while (currentPosition != End) {
        path__.push_back(currentPosition);

        currentDirection = ChangeCounterClockwise(currentDirection);
        std::vector<int> nextPosition;
        while (true) {
            nextPosition = NextCell(currentDirection, currentPosition);

            if (nextPosition[0] >= 0 && nextPosition[0] < maze_.getCol() &&
                nextPosition[1] >= 0 && nextPosition[1] < maze_.getRow() &&
                CanStep(currentDirection, nextPosition)) {

                break;
            }

            // Если не нашли, пробуем другое направление
            currentDirection = ChangeClockwise(currentDirection);
        }
        currentPosition = nextPosition;

        if (containsStart(currentPosition)) {
            path__.pop_back();
            path__.pop_back();
        }
    }
    path__.push_back(currentPosition);

    return path__;
}


bool s21::FindPath::containsStart(const std::vector<int>& Start) {
    for (const auto& path : path__) {
        if (path.size() == 2 && path[0] == Start[0] && path[1] == Start[1]) {
            return true;
        }
    }
    return false;
}

bool s21::FindPath::CanStep(Direction direction, const std::vector<int>& position) const {
    if (direction == Direction::Right && maze_.getRightWalls()[position[1]][position[0] - 1] == 0)
        return true;
    if (direction == Direction::Left && maze_.getRightWalls()[position[1]][position[0]] == 0)
        return true;
    if (direction == Direction::Up && maze_.getBottomWalls()[position[1]][position[0]] == 0)
        return true;
    if (direction == Direction::Down && maze_.getBottomWalls()[position[1] - 1][position[0]] == 0)
        return true;
    return false;
}

std::vector<int> s21::FindPath::NextCell(s21::FindPath::Direction direction, const std::vector<int>& position) {
    std::vector<int> nextPosition = position; // Создаем копию текущей позиции
    switch (direction) {
        case s21::FindPath::Direction::Up:
            nextPosition[1] -= 1; // Уменьшаем Y (движение вверх)
            break;
        case s21::FindPath::Direction::Down:
            nextPosition[1] += 1; // Увеличиваем Y (движение вниз)
            break;
        case s21::FindPath::Direction::Left:
            nextPosition[0] -= 1; // Уменьшаем X (движение влево)
            break;
        case s21::FindPath::Direction::Right:
            nextPosition[0] += 1; // Увеличиваем X (движение вправо)
            break;
        default:
            throw std::out_of_range("Not expected direction value");
    }
    return nextPosition; // Возвращаем новое положение
}

s21::FindPath::Direction s21::FindPath::ChangeClockwise(s21::FindPath::Direction direction) {
    switch (direction) {
        case s21::FindPath::Direction::Up: return s21::FindPath::Direction::Right;
        case s21::FindPath::Direction::Right: return s21::FindPath::Direction::Down;
        case s21::FindPath::Direction::Down: return s21::FindPath::Direction::Left;
        case s21::FindPath::Direction::Left: return s21::FindPath::Direction::Up;
        default: throw std::out_of_range("Not expected direction value");
    }
}
s21::FindPath::Direction s21::FindPath::ChangeCounterClockwise(s21::FindPath::Direction direction) {
    switch (direction) {
        case s21::FindPath::Direction::Up: return s21::FindPath::Direction::Left;
        case s21::FindPath::Direction::Left: return s21::FindPath::Direction::Down;
        case s21::FindPath::Direction::Down: return s21::FindPath::Direction::Right;
        case s21::FindPath::Direction::Right: return s21::FindPath::Direction::Up;
        default: throw std::out_of_range("Not expected direction value");
    }
}


//std::vector<int> s21::FindPath::NextCell(s21::FindPath::Direction direction, const std::vector<int>& position) {
//    std::vector<int> nextPosition = position;
//    switch (direction) {
//        case s21::FindPath::Direction::Up: return {position.begin(), position.end() - 1};
//        case s21::FindPath::Direction::Down: return {position.begin(), position.end() + 1};
//        case s21::FindPath::Direction::Left: return {position.begin() - 1, position.end()};
//        case s21::FindPath::Direction::Right: return {position.begin() + 1, position.end()};
//        default: throw std::out_of_range("Not expected direction value");
//    }
//}
