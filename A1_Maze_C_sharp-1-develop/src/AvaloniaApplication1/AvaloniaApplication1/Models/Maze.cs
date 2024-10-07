using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace s21_Maze {
  public class Maze {
    private int _row;
    private int _col;

    private List<int[]> _rightWalls;
    private List<int[]> _bottomWalls;
    public int Row { get => _row; }
    public int Col { get => _col; }
    public int Bias { get; set; }
    public int BiasMax { get; private set; }
    public List<int[]> RightWalls { get => _rightWalls; }
    public List<int[]> BottomWalls { get => _bottomWalls; }
    public List<int[]> Path { get; private set; }
    public int PathLength { get => Path.Count; }

    public Maze(int row = 4, int col = 4, int bias = 50) {
      _row = row > 0 ? row <= 50 ? row : 50 : 1;
      _col = col > 0 ? col <= 50 ? col : 50 : 1;

      Bias = bias;
      BiasMax = 100;

      Init();
    }
    public void SetSize(int rows, int cols) {
      _row = rows;
      _col = cols;
      Init();
    }
    public void ReadFromFile(string path) {
      _bottomWalls.Clear();
      _rightWalls.Clear();
      Path.Clear();
      var file = File.ReadAllLines(path);

      if (file.Length == 0)
        throw new Exception("Incorrect file format.");

      int[] data = file[0].Split(' ').Select(int.Parse).ToArray();
      _row = data[0];
      _col = data[1];

      if (file.Length != _row * 2 + 2)
        throw new Exception("Incorrect file format.");

      for (int i = 0; i < _row; ++i) {
        _bottomWalls.Add(file[i + _row + 2].Split(' ').Select(int.Parse).ToArray());
        _rightWalls.Add(file[i + 1].Split(' ').Select(int.Parse).ToArray());
      }
    }
    private void Init() {
      Path = new List<int[]>();
      _rightWalls = new List<int[]>();
      _bottomWalls = new List<int[]>();
      for (int i = 0; i < Row; ++i) {
        _rightWalls.Add(new int[_col]);
        _bottomWalls.Add(new int[_col]);
        _rightWalls[i][Col - 1] = 1;
      }
      for (int i = 0; i < Col; ++i) {
        _bottomWalls[Row - 1][i] = 1;
      }
    }
    public void Generate() {
      Init();
      int setUniqueNumber = _col;
      var set = new List<int>(_row);
      for (int i = 1; i <= _col; ++i) set.Add(i);
      for (int row = 0; row < _row; row++) {
        if (row > 0)
          for (int i = 0; i < _col; i++)
            if (_bottomWalls[row - 1][i] == 1)
              set[i] = ++setUniqueNumber;

        int[] rand = new int[_col * 2];
        for (int i = 0; i < rand.Length; ++i) rand[i] = new Random().Next(BiasMax + 2);

        for (int i = 0; i < _col; ++i) {
          if (i < _col - 1 && (rand[i] < Bias || set[i + 1] == set[i]))
            _rightWalls[row][i] = 1;
          else if (i < _col - 1)
            set = set.Select(x => x == set[i + 1] ? set[i] : x).ToList();
        }
        for (int i = 0; i < _col; ++i) {
          int allSetLength = set.Count(x => x == set[i]);
          int setLength = set.GetRange(0, i + 1).Count(x => x == set[i]);
          int bootomCount =
              _bottomWalls[row].Skip(i - setLength + 1).Take(setLength).Count(x => x == 1);
          if (rand[i + _col] > Bias) {
            if ((_rightWalls[row][i] != 1) || (!(bootomCount == setLength - 1) && setLength > 1))
              _bottomWalls[row][i] = 1;
          } else if (_rightWalls[row][i] == 1 && setLength > 1 && bootomCount == 0) {
            _bottomWalls[row][i] = 1;
          }
        }
      }

      for (int i = 0; i < _col; ++i) {
        if ((i < _col - 1 && set[i + 1] != set[i]) && (i != _col - 1))
          _rightWalls[_row - 1][i] = 0;
        if (i < _col - 1)
          set = set.Select(x => x == set[i + 1] ? set[i] : x).ToList();
      }
    }
    public void Save(string path) {
      StringBuilder stringBuilder = new StringBuilder();
      stringBuilder.AppendLine(_row + " " + _col);
      List<string> stringRows = new List<string>();
      for (int i = 0; i < _row; i++) {
        List<string> rowValues = new List<string>();
        for (int j = 0; j < _col; j++) {
          rowValues.Add(_rightWalls[i][j].ToString());
        }
        stringRows.Add(string.Join(" ", rowValues));
      }
      stringBuilder.AppendLine(string.Join("\n", stringRows));
      stringBuilder.AppendLine();
      stringRows.Clear();
      for (int i = 0; i < _row; i++) {
        List<string> rowValues = new List<string>();
        for (int j = 0; j < _col; j++) {
          rowValues.Add(_bottomWalls[i][j].ToString());
        }
        stringRows.Add(string.Join(" ", rowValues));
      }
      stringBuilder.Append(string.Join("\n", stringRows));
      File.WriteAllText(path, stringBuilder.ToString());
    }

    public void FindPath(int startPosX, int startPosY, int endPosX, int endPosY) => Path =
        (List<int[]>)new PathFinder(this, startPosX, startPosY, endPosX, endPosY).FindPath();
  }

}
