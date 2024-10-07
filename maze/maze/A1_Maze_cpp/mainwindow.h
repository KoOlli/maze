#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_CreateBtn_clicked();

    void on_SaveBtn_clicked();

    void on_LoadBtn_clicked();

    void buttonClicked(int i, int j);
//    void createGridButtons(int n, int m);

//    void on_AddButton_clicked();

private:
    Ui::MainWindow *ui;
//    QGridLayout *gridLayout;  // Указатель на QGridLayout для добавления кнопок
//    int currentRow;           // Счетчик текущей строки для размещения кнопок
//    int currentCol;          // Счетчик текущего столбца для размещения кнопок

};
#endif // MAINWINDOW_H
