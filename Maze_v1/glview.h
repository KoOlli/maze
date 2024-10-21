#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include "maze.h"

class glView : public QOpenGLWidget {
  Q_OBJECT
 private:
    s21::Maze *maze_;
    int point1_[2] = {-1, -1};
    int point2_[2] = {-1, -1};
    int newPoint_[2] = {-1, -1};
    void CreateLeftWall();
    void CreateTopWall();
    void CreateRightWalls();
    void CreateBottomWalls();
    void DrawPath(int h, int w);

 public:
  glView(QWidget* parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void CreateMaze(int n, int m);
//  void Generate(int n, int m);

  void EnterPoint(int x, int y);
  void ClearPoints();
};

#endif  // GLVIEW_H
