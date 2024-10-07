#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include "maze.h"

class glView : public QOpenGLWidget {
  Q_OBJECT
 private:
    s21::Maze *maze;
    void CreateLeftWall();
    void CreateTopWall();
    void CreateRightWalls();
    void CreateBottomWalls();
    void DrawPath();

 public:

  glView(QWidget* parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void CreateMaze(int n, int m);
};

#endif  // GLVIEW_H
