#ifndef A1_MAZE_CPP_MAINWINDOW_H_
#define A1_MAZE_CPP_MAINWINDOW_H_

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
    void on_SaveBtn_clicked();
    void on_LoadBtn_clicked();
    void on_CreateBtn_clicked();
    void on_CreatePathBtn_clicked();

private:
    Ui::MainWindow *ui;

    int countClick_ = 0;

    void clearGrid();
    void buttonClicked(int i, int j);
    void ButtonsView(bool isVisible);
    void createGridButtons(int n, int m);
    void setButtonsVisibility(bool visible);

};
#endif // A1_MAZE_CPP_MAINWINDOW_H_
