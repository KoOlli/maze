#include "glview.h"

#include <QTimer>

#include <iostream>
//#include "gif.h"

#define GL_SILENCE_DEPRECATION

glView::glView(QWidget* parent) : QOpenGLWidget(parent) {}

    void glView::initializeGL() {

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Черный фон
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 500, 0, 500, -1, 1); // Установка проекции
        glMatrixMode(GL_MODELVIEW);
    }

    void glView::resizeGL(int w, int h) {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 500, 0, 500, -1, 1); // Установка проекции
        glMatrixMode(GL_MODELVIEW);
    }

    void glView::paintGL() {
        // Очистка экрана
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLineWidth(2);
        // Установка цвета для сетки
        glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
        if(maze != nullptr){
//            float n = maze->getCol();
//            float m = maze->getRow();
//             for (int i = 0; i <= n; ++i) {
//                 float x = i/n * 500;
//                 glBegin(GL_LINES);
//                     glVertex2f(x, 0);
//                     glVertex2f(x, 500);
//                 glEnd();
//             }

//             for (int i = 0; i <= m; ++i) {
//                 float y = i/m * 500;
//                 glBegin(GL_LINES);
//                     glVertex2f(0, y);
//                     glVertex2f(500, y);
//                 glEnd();
//             }
            CreateLeftWall();
            CreateTopWall();
            CreateRightWalls();
            CreateBottomWalls();
        }
    }

    void glView::CreateLeftWall() {
       glBegin(GL_LINES);
           glVertex2f(0, 0);
           glVertex2f(0, 500);
       glEnd();
    }

    void glView::CreateTopWall() {
        glBegin(GL_LINES);
            glVertex2f(0, 500);
            glVertex2f(500, 500);
        glEnd();
    }

    void glView::CreateRightWalls() {
        for (int i = 0; i < maze->getRow(); i++) {
          for (int j = 0; j < maze->getCol(); j++) {
              if (maze->getRightWalls()[maze->getRow() - i - 1][j] == 1) {
                  glBegin(GL_LINES);
                      glVertex2f(500 / maze->getCol() + 500 / maze->getCol() * j,
                                 500 / maze->getRow() * i);
                      glVertex2f(500 / maze->getCol() + 500 / maze->getCol() * j,
                                 500 / maze->getRow() * (i + 1));
                  glEnd();

              }
          }
        }
    }

    void glView::CreateBottomWalls() {
        for (int i = 0; i < maze->getRow(); i++) {
          for (int j = 0; j < maze->getCol(); j++) {
              if (maze->getBottomWalls()[maze->getRow() - i - 1][j] == 1) {
                  glBegin(GL_LINES);
                      glVertex2f(500 / maze->getCol() * j,
                                 500 / maze->getRow()  + 500 / maze->getRow()  * (i - 1));
                      glVertex2f(500 / maze->getCol() * (j + 1),
                                 500 / maze->getRow()  + 500 / maze->getRow()  * (i - 1));
                  glEnd();

              }
          }
        }
    }

    void glView::CreateMaze(int n, int m) {
        maze = new s21::Maze(n, m); //generate maze and run
    }

    void glView::DrawPath(){

    }

