

using System;
using System.Collections.Generic;

namespace s21_Maze {
  internal class PathFinder {
    public Vector2D Start { get; }
    public Vector2D End { get; }
    private List<Vector2D> _path;
    private Maze Maze { get; }
    private enum Direction {
      Right,
      Left,
      Up,
      Down,
    }
    public int PathLength { get => _path.Count; }

    public PathFinder(Maze maze, int startPosX = 0, int startPosY = 0, int endPosX = 0,
                      int endPosY = 0) {
      Start = new Vector2D(startPosX, startPosY);
      End = new Vector2D(endPosX, endPosY);
      _path = new List<Vector2D>();
      Maze = maze;
    }

    public IEnumerable<int[]> ToList() {
      var list = new List<int[]>();
      foreach (var item in _path) list.Add(new int[2] { item.X, item.Y });
      return list;
    }

    public IEnumerable<int[]> FindPath() {
      if (Start.X >= Maze.Col || Start.X < 0 || End.X >= Maze.Col || End.X < 0 ||
          Start.Y >= Maze.Row || Start.Y < 0 || End.Y >= Maze.Row || End.Y < 0)
        return null;

      var currentPosition = new Vector2D(Start.X, Start.Y);
      Direction currentDirection = Direction.Left;

      while (currentPosition != End) {
        _path.Add(currentPosition);
        currentDirection = ChangeCounterСlockwise(currentDirection);
        Vector2D nextPosition;
        while (true) {
          nextPosition = NextCell(currentDirection, currentPosition);

          if (nextPosition.X >= 0 && nextPosition.X < Maze.Col && nextPosition.Y >= 0 &&
              nextPosition.Y < Maze.Row && CanStep(currentDirection, nextPosition))
            break;

          currentDirection = ChangeСlockwise(currentDirection);
        }
        currentPosition = nextPosition;
        if (_path.Exists(x => x == currentPosition)) {
          _path.RemoveAt(_path.Count - 1);
          _path.RemoveAt(_path.Count - 1);
        }
      }
      _path.Add(currentPosition);

      return ToList();
    }

    private bool CanStep(Direction direction, Vector2D position) {
      if (direction == Direction.Right && Maze.RightWalls[position.Y][position.X - 1] == 0)
        return true;
      if (direction == Direction.Left && Maze.RightWalls[position.Y][position.X] == 0)
        return true;
      if (direction == Direction.Up && Maze.BottomWalls[position.Y][position.X] == 0)
        return true;
      if (direction == Direction.Down && Maze.BottomWalls[position.Y - 1][position.X] == 0)
        return true;
      return false;
    }

    private static Vector2D NextCell(Direction direction, Vector2D position) => direction switch {
      Direction.Up => new Vector2D(position.X, position.Y - 1),
      Direction.Down => new Vector2D(position.X, position.Y + 1),
      Direction.Left => new Vector2D(position.X - 1, position.Y),
      Direction.Right => new Vector2D(position.X + 1, position.Y),
      _ => throw new ArgumentOutOfRangeException(nameof(direction),
                                                 $"Not expected direction value: {direction}"),
    };

    private static Direction ChangeСlockwise(Direction direction) => direction switch {
      Direction.Up => Direction.Right,
      Direction.Right => Direction.Down,
      Direction.Down => Direction.Left,
      Direction.Left => Direction.Up,
      _ => throw new ArgumentOutOfRangeException(nameof(direction),
                                                 $"Not expected direction value: {direction}"),
    };

    private static Direction ChangeCounterСlockwise(Direction direction) => direction switch {
      Direction.Up => Direction.Left,
      Direction.Left => Direction.Down,
      Direction.Down => Direction.Right,
      Direction.Right => Direction.Up,
      _ => throw new ArgumentOutOfRangeException(nameof(direction),
                                                 $"Not expected direction value: {direction}"),
    };
  }
}