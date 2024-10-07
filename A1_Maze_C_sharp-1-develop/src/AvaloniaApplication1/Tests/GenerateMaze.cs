using s21_Maze;
using System.IO;
using Xunit.Sdk;

namespace Tests {
  public class GenerateMaze {
    [Fact]
    public void InitMaze() {
      var maze = new Maze(4, 4);
      Assert.NotNull(maze);
    }

    [Fact]
    public void MazePath() {
      var maze = new Maze();
      maze.ReadFromFile("settingsBig.txt");
      maze.FindPath(0, 0, 1, 18);
      Assert.NotNull(maze.Path);
      int expected = 0;
      Assert.NotEqual(maze.PathLength, expected);
    }

    [Fact]
    public void MazePathNull() {
      var maze = new Maze();
      maze.ReadFromFile("settingsBig.txt");
      maze.FindPath(0, 0, 1, 21);
      Assert.Null(maze.Path);
    }

    [Fact]
    public void GenerateNotNullMaze() {
      var maze = new Maze(4, 4);
      maze.Generate();
      Assert.NotNull(maze);
    }

    [Fact]
    public void SetRowMaze() {
      var maze = new Maze();
      maze.SetSize(10, 5);
      int expected = 10;
      Assert.Equal(maze.Row, expected);
    }

    [Fact]
    public void SetColMaze() {
      var maze = new Maze();
      maze.SetSize(10, 5);
      int expected = 5;
      Assert.Equal(maze.Col, expected);
    }

    [Fact]
    public void ReadFromFileRowSize() {
      var maze = new Maze();
      maze.ReadFromFile("settings.txt");
      int expected = 4;
      Assert.Equal(maze.Row, expected);
    }

    [Fact]
    public void ReadFromFileColSize() {
      var maze = new Maze();
      maze.ReadFromFile("settings.txt");
      int expected = 4;
      Assert.Equal(maze.Col, expected);
    }

    [Fact]
    public void ReadFromFileRightWalls() {
      var maze = new Maze();
      maze.ReadFromFile("settings.txt");
      List<int[]> expected = new() { new int[] { 0, 0, 0, 1 }, new int[] { 1, 0, 1, 1 },
                                     new int[] { 0, 1, 0, 1 }, new int[] { 0, 0, 0, 1 } };
      Assert.Equal(maze.RightWalls, expected);
    }

    [Fact]
    public void ReadFromFileBottomWalls() {
      var maze = new Maze();
      maze.ReadFromFile("settings.txt");
      List<int[]> expected = new() { new int[] { 1, 0, 1, 0 }, new int[] { 0, 0, 1, 0 },
                                     new int[] { 1, 1, 0, 1 }, new int[] { 1, 1, 1, 1 } };
      Assert.Equal(maze.BottomWalls, expected);
    }

    [Fact]
    public void SaveFileNotEmpty() {
      var maze = new Maze();
      string path = "save.txt";
      maze.Save(path);
      var file = File.ReadAllLines(path);

      int expected = 0;

      Assert.NotEqual(file.Length, expected);
    }

    [Fact]
    public void SaveFileRowSize() {
      var maze = new Maze();
      string path = "save.txt";
      maze.Save(path);
      var file = File.ReadAllLines(path);

      int[] data = file[0].Split(' ').Select(int.Parse).ToArray();
      var expected = data[0];

      Assert.Equal(maze.Row, expected);
    }
    [Fact]
    public void SaveFileColSize() {
      var maze = new Maze();
      string path = "save.txt";
      maze.Save(path);
      var file = File.ReadAllLines(path);

      int[] data = file[0].Split(' ').Select(int.Parse).ToArray();
      var expected = data[1];

      Assert.Equal(maze.Col, expected);
    }
  }
}