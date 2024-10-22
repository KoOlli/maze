#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->CreatePathBtn->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGridButtons(int n, int m)
{
    clearGrid();
    ui->gridLayout->setHorizontalSpacing(3);
    ui->gridLayout->setVerticalSpacing(8);
    ui->gridLayout->setContentsMargins(2, 2, 2, 2);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            QPushButton *button = new QPushButton(QString(" "), this);
            connect(button, &QPushButton::clicked, this, [this, i, j]() { MainWindow::buttonClicked(i,j);} );
//            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            ui->gridLayout->addWidget(button, i, j);
        }
    }
    setButtonsVisibility(false);
}

void MainWindow::setButtonsVisibility(bool visible)
{
    for (int i = 0; i < ui->gridLayout->rowCount(); ++i) {
        for (int j = 0; j < ui->gridLayout->columnCount(); ++j) {
            if (ui->gridLayout->itemAtPosition(i, j)) {
                if (ui->gridLayout->itemAtPosition(i, j)->widget()) {
                    ui->gridLayout->itemAtPosition(i, j)->widget()->setVisible(visible);
                }
            }
        }
    }
}

void MainWindow::clearGrid() {
    // Получить количество строк и столбцов (можно использовать m и n, если сохраняете эти значения)
    QLayoutItem* item;
    while ((item = ui->gridLayout->takeAt(0))) {
        // Удаляем виджет
        QWidget* widget = item->widget();
        if (widget) {
            // Удаление виджета
            delete widget;
        }
        // Удаление самого элемента компоновщика
        delete item;
    }
}

void MainWindow::on_CreateBtn_clicked()
{
    int n = (int)ui->spinBox->value();
    int m = (int)ui->spinBox_2->value();
    ui->openGLWidget->CreateMaze(n, m);
    createGridButtons(n, m);
    ui->openGLWidget->ClearPoints();
    setButtonsVisibility(false);
    countClick = 0;
    ui->openGLWidget->repaint();
    ui->CreatePathBtn->setVisible(true);
}

void MainWindow::buttonClicked(int i, int j){
    std::cout << i << j << std::endl;
    ui->openGLWidget->EnterPoint(i, j);
    countClick++;
    if(countClick == 2){
        setButtonsVisibility(false);
    }
}

void MainWindow::on_SaveBtn_clicked()
{

}


void MainWindow::on_LoadBtn_clicked()
{

}


void MainWindow::on_CreatePathBtn_clicked()
{
    setButtonsVisibility(true);
    countClick = 0;
    ui->openGLWidget->ClearPoints();
    ui->openGLWidget->repaint();
}

