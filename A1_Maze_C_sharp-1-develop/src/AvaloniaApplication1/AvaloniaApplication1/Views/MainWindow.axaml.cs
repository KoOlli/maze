using System;
using System.Collections.Generic;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Shapes;
using Avalonia.Interactivity;
using Avalonia.Media;
// using AvaloniaApplication1.Models;
// using DynamicData;
using s21_Maze;
using System.IO;

namespace AvaloniaApplication1.Views;

public partial class MainWindow : Window {
  private int[] point1 = { -1, -1 };
  private int[] point2 = { -1, -1 };
  private int countElements;
  private Maze maze;

  public MainWindow() {
    InitializeComponent();
    MaxHeight = 700;
    MinHeight = 700;
    MaxWidth = 600;
    MinWidth = 600;
    Background = Brushes.Beige;
  }

  public void StartButtonClicked(object source, RoutedEventArgs args) {
    maze = new Maze((int)Rows.Value, (int)Cols.Value);
    maze.Generate();

    DrawMaze();
  }

  private void SaveButton_Click(object sender, RoutedEventArgs e) {
    maze.Save("settings.txt");
  }

  private void LoadButton_Click(object sender, RoutedEventArgs e) {
    try {
      var tempMaze = new Maze();
      tempMaze.ReadFromFile("settings.txt");
      maze = tempMaze;
      DrawMaze();
    } catch (FileNotFoundException ex) {
      Console.WriteLine("Файл не найден: " + ex.Message);
    } catch (Exception ex) {
      Console.WriteLine("Произошла ошибка: " + ex.Message);
    }
  }

  public void DrawMaze() {
    ClearMaze();
    CreateScene();
    CreateLeftWall();
    CreateTopWall();
    CreateVerticalWalls();
    CreateHorizontalWalls();
    CreateFildButtons();
  }

  public void ClearMaze() {
    point1[0] = -1;
    point1[1] = -1;
    point2[0] = -1;
    point2[1] = -1;

    chessGrid.Children.Clear();
  }

  void CreateScene() {
    var scene = new Rectangle() { Width = 500, Height = 500, Margin = new Thickness(10, 20, 30, 40),
                                  Name = "Scene", Fill = Brushes.Chartreuse };

    chessGrid.Children.Add(scene);
  }

  void CreateLeftWall() {
    Line l = new Line() { StartPoint = new Point(-230, -230),
                          EndPoint = new Point(-230, 270),
                          Margin = new Thickness(10, 20, 30, 40),
                          Width = 40,
                          Height = 40,
                          Name = "Wall",
                          StrokeThickness = 2,
                          Stroke = Brushes.Chocolate };
    chessGrid.Children.Add(l);
  }

  void CreateTopWall() {
    Line l2 = new Line() { StartPoint = new Point(-230, -230),
                           EndPoint = new Point(270, -230),
                           Margin = new Thickness(10, 20, 30, 40),
                           Width = 40,
                           Height = 40,
                           Name = "Wall",
                           StrokeThickness = 2,
                           Stroke = Brushes.Chocolate };
    chessGrid.Children.Add(l2);
  }

  void CreateVerticalWalls() {
    for (int i = 0; i < maze.Row; i++) {
      for (int j = 0; j < maze.Col; j++) {
        if (maze.RightWalls[i][j] == 1) {
          chessGrid.Children.Add(
              new Line() { StartPoint = new Point(-230 + 500f / maze.Col + 500f / maze.Col * j,
                                                  -230 + 500f / maze.Row * i),
                           EndPoint = new Point(-230 + 500f / maze.Col + 500f / maze.Col * j,
                                                -230 + 500f / maze.Row * (i + 1)),
                           Margin = new Thickness(10, 20, 30, 40), Width = 40, Height = 40,
                           Name = "Wall", StrokeThickness = 2, Stroke = Brushes.Chocolate });
        }
      }
    }
  }

  void CreateHorizontalWalls() {
    for (int i = 0; i < maze.Row; i++) {
      for (int j = 0; j < maze.Col; j++) {
        if (maze.BottomWalls[i][j] == 1) {
          chessGrid.Children.Add(
              new Line() { StartPoint = new Point(-230 + 500f / maze.Col * j,
                                                  -230 + 500f / maze.Row + 500f / maze.Row * i),
                           EndPoint = new Point(-230 + 500f / maze.Col * (j + 1),
                                                -230 + 500f / maze.Row + 500f / maze.Row * i),
                           Margin = new Thickness(10, 20, 30, 40), Width = 40, Height = 40,
                           Name = "Wall", StrokeThickness = 2, Stroke = Brushes.Chocolate });
        }
      }
    }
  }

  void CreateFildButtons() {
    for (int i = 0; i < maze.Row; i++) {
      for (int j = 0; j < maze.Col; j++) {
        int row = i;
        int col = j;
        Button button = new Button() {
          Height = 500 / maze.Row,
          Width = 500 / maze.Col,
          Margin = new Thickness(40 + 500 / maze.Col * j, 20 + 500 / maze.Row * i, 0, 0),
          HorizontalAlignment = Avalonia.Layout.HorizontalAlignment.Left,
          VerticalAlignment = Avalonia.Layout.VerticalAlignment.Top,
          Background = Brushes.Transparent,
          Name = $"button_{i}_{j}"
        };

        button.Click += (sender, e) => { PrintCoordinate(row, col); };

        chessGrid.Children.Add(button);
      }
    }
  }

  void PrintCoordinate(int h, int w) {
    if (point2[0] != -1) {
      List<Line> linesToRemove = new List<Line>();
      foreach (var child in chessGrid.Children) {
        if (child is Line && ((Line)child).Name == "linePath") {
          linesToRemove.Add((Line)child);
        }
      }

      foreach (var line in linesToRemove) {
        chessGrid.Children.Remove(line);
      }
    }

    point2[0] = point1[0];
    point2[1] = point1[1];
    point1[0] = w;
    point1[1] = h;

    if (point2[0] != -1) {
      countElements = chessGrid.Children.Count;
      maze.FindPath(point1[0], point1[1], point2[0], point2[1]);
      int[] currentPoint1 = maze.Path[0];
      int[] currentPoint2 = maze.Path[0];

      foreach (var item in maze.Path) {
        currentPoint1 = item;
        chessGrid.Children.Add(new Line() {
          StartPoint = new Point(-230 + 500 / maze.Col / 2 + 500 / maze.Col * currentPoint1[0],
                                 -230 + 500 / maze.Row / 2 + 500 / maze.Row * currentPoint1[1]),
          EndPoint = new Point(-230 + 500 / maze.Col / 2 + 500 / maze.Col * currentPoint2[0],
                               -230 + 500 / maze.Row / 2 + 500 / maze.Row * currentPoint2[1]),
          Margin = new Thickness(10, 20, 30, 40), Width = 40, Height = 40, Name = "linePath",
          StrokeThickness = 2, Stroke = Brushes.AliceBlue
        });
        currentPoint2 = currentPoint1;
      }
    }
  }
}
