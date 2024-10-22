#include "glview.h"

#include <QTimer>

#include <iostream>
#include<QDebug>>
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
        glLineWidth(5);
        // Установка цвета для сетки
        glColor3f(1.0, 0.0, 0.0); // Красный цвет
        if(maze_ != nullptr){
            CreateLeftWall();
            CreateTopWall();
            CreateRightWalls();
            CreateBottomWalls();
//            Generate();
            glColor3f(0.0, 1.0, 0.0);
            DrawPath(newPoint_[0], newPoint_[1]);
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
        for (int i = 0; i < maze_->getRow(); i++) {
          for (int j = 0; j < maze_->getCol(); j++) {
              if (maze_->getRightWalls()[maze_->getRow() - i - 1][j] == 1) {
                  glBegin(GL_LINES);
                      glVertex2f(500 / (float)maze_->getCol() + 500 / (float)maze_->getCol() * j,
                                 500 / (float)maze_->getRow() * i);
                      glVertex2f(500 / (float)maze_->getCol() + 500 / (float)maze_->getCol() * j,
                                 500 / (float)maze_->getRow() * (i + 1));
                  glEnd();

              }
          }
        }
    }

    void glView::CreateBottomWalls() {
        for (int i = 0; i < maze_->getRow(); i++) {
          for (int j = 0; j < maze_->getCol(); j++) {
              if (maze_->getBottomWalls()[maze_->getRow() - i - 1][j] == 1) {
                  glBegin(GL_LINES);
                      glVertex2f(500 / (float)maze_->getCol() * j,
                                 500 / (float)maze_->getRow()  + 500 / (float)maze_->getRow()  * (i - 1));
                      glVertex2f(500 / (float)maze_->getCol() * (j + 1),
                                 500 / (float)maze_->getRow()  + 500 / (float)maze_->getRow()  * (i - 1));
                  glEnd();

              }
          }
        }
    }

    void glView::CreateMaze(int n, int m) {
        maze_ = new s21::Maze(n, m); //generate maze and run
//        maze_->Generate(n, m);


    }

    void glView::EnterPoint(int x, int y){
        newPoint_[0] = x;
        newPoint_[1] = y;
        repaint();
    }

    void glView::DrawPath(int h, int w){
        point2_[0] = point1_[0];
        point2_[1] = point1_[1];
        point1_[0] = w;
        point1_[1] = h;
        std::cout << point1_[0] << " " << point1_[1] << " " << point2_[0] << " " << point2_[1] << std::endl;
        if (point2_[0] != -1) {
          find_ = new s21::FindPath(*maze_);
          find_->Find(point1_[0], point1_[1], point2_[0], point2_[1]);
          std::vector<std::vector<int>> path = find_->getPath();
          for(auto elem : path)
              for(auto elem2 : elem)
                    qDebug() << elem2;

          std::vector<int> currentPoint1 = path[0];
          std::vector<int> currentPoint2 = path[0];

          for(auto item : path) {
            currentPoint1 = item;
            glBegin(GL_LINES);
              glVertex2f(500 / (float)maze_->getCol() / 2 + 500 / (float)maze_->getCol() * currentPoint1[0],
                                     500 / (float)maze_->getRow() / 2 + 500 / (float)maze_->getRow() * (maze_->getRow() - currentPoint1[1] - 1));
              glVertex2f(500 / (float)maze_->getCol() / 2 + 500 / (float)maze_->getCol() * currentPoint2[0],
                                   500 / (float)maze_->getRow() / 2 + 500 / (float)maze_->getRow() * (maze_->getRow() - currentPoint2[1] - 1));
            glEnd();
            currentPoint2 = currentPoint1;
          }
        }
    }

    void glView::ClearPoints(){
        point2_[0] = point1_[0] = newPoint_[0] = -1;
        point2_[1] = point1_[1] = newPoint_[1] = -1;
    }

    void glView::SaveFile(){
        maze_->Save("settings.txt");
    }

    void glView::LoadFile(){
        maze_->ReadFromFile("settings.txt");
        repaint();
    }

    int glView::getRow(){
        return maze_->getRow();
    }

    int glView::getCol(){
        return maze_->getCol();
    }
