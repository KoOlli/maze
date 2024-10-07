

using System.Security.Cryptography.X509Certificates;

namespace s21_Maze {
  internal class Vector2D {
    public int X { get; set; }
    public int Y { get; set; }

    public Vector2D(int x, int y) {
      X = x;
      Y = y;
    }
    public static bool operator ==(Vector2D position1,
                                   Vector2D position2) => position1.X == position2.X
                                                              ? position1.Y == position2.Y
                                                              : false;
    public static bool operator !=(Vector2D position1,
                                   Vector2D position2) => position1 == position2 ? false : true;

    override public string ToString() => $"{X} {Y}";
  }
}
