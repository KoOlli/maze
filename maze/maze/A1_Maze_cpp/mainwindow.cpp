#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
//QMainWindow(parent),
ui(new Ui::MainWindow)
//currentRow(0),  // Инициализируем счетчики строк и столбцов
//currentCol(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::createGridButtons(int n, int m)
//{
//    // Создание кнопок и добавление их в сетку
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j) {
//            QPushButton *button = new QPushButton(QString("Button %1").arg(i * m + j + 1), this);
//            gridLayout->addWidget(button, i, j);  // Добавление кнопки в сетку
//        }
//    }
//}

//void MainWindow::on_AddButton_clicked()
//{
//    // Добавление новой кнопки в текущую позицию
//    QPushButton *button = new QPushButton(QString("New Button [%1, %2]").arg(currentRow).arg(currentCol), this);

//    gridLayout->addWidget(button, currentRow, currentCol);  // Добавляем кнопку в сетку

//    // Обработка перехода к следующей позиции
//    currentCol++;
//    if (currentCol >= 4) {  // Измените 4 на количество столбцов, если оно меняется
//        currentCol = 0;     // Сбросить на следующий уровень
//        currentRow++;       // Увеличить количество строк
//    }
//}

void MainWindow::on_CreateBtn_clicked()
{
    int n = (int)ui->spinBox->value();
    int m = (int)ui->spinBox_2->value();
    ui->openGLWidget->CreateMaze(n, m);
    ui->openGLWidget->repaint();
//    for (int i = 0; i < n; ++i) {
//                for (int j = 0; j < m; ++j) {
//                    QPushButton *button = new QPushButton(QString("Button %1").arg(i * m + j + 1), this);

//                    // Соединение сигнала нажатия кнопки с методом-обработчиком
//                    connect(button, &QPushButton::clicked, this, [this, i, j]() { buttonClicked(i, j); });
//                    addWidget(button, i, j);  // Добавление кнопки в сетку
//                }
//            }
//    createGridButtons(3, 4); // Пример вызова с 3 строками и 4 столбцами
}

void MainWindow::buttonClicked(int i, int j){

}

void MainWindow::on_SaveBtn_clicked()
{
//     ui->openGLWidget->repaint();
}


void MainWindow::on_LoadBtn_clicked()
{
//    ui->openGLWidget->repaint();
}

