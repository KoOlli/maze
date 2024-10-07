#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGridButtons(int n, int m)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            QPushButton *button = new QPushButton(QString(" "), this);
            connect(button, &QPushButton::clicked, this, [this, i, j]() { MainWindow::buttonClicked(i,j);} );
            ui->gridLayout->addWidget(button, i, j);
        }
    }
}

void MainWindow::on_CreateBtn_clicked()
{
    int n = (int)ui->spinBox->value();
    int m = (int)ui->spinBox_2->value();
    ui->openGLWidget->CreateMaze(n, m);
    ui->openGLWidget->repaint();
    createGridButtons(n, m);
}

void MainWindow::buttonClicked(int i, int j){
    std::cout << i << j << std::endl;
    ui->openGLWidget->EnterPoint(i, j);
}

void MainWindow::on_SaveBtn_clicked()
{

}


void MainWindow::on_LoadBtn_clicked()
{

}

