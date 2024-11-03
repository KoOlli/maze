#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include "maze.h"
#include "findPath.h"
#include <QFile>
#include <QDir>
#include <QCoreApplication>

class glView : public QOpenGLWidget {
  Q_OBJECT
 public:
    glView(QWidget* parent = nullptr);

    int getCol();
    int getRow();
    void SaveFile();
    void LoadFile();
    void ClearPoints();
    void CreateMaze(int n, int m);
    void EnterPoint(int x, int y);

private:
   s21::Maze *maze_;
   s21::FindPath *find_;

   int point1_[2] = {-1, -1};
   int point2_[2] = {-1, -1};
   int newPoint_[2] = {-1, -1};

   void CreateLeftWall();
   void CreateTopWall();
   void CreateRightWalls();
   void CreateBottomWalls();

   void paintGL() override;
   void DrawPath(int h, int w);
   void initializeGL() override;
   void resizeGL(int w, int h) override;
};

#endif  // GLVIEW_H
