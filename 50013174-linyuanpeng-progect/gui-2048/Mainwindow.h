#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QPainter>
#include <QTime>
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

    void PressUp();
    void PressDown();
    void PressLeft();
    void PressRight();
    void myRand();
    void gameIsover();


    QPushButton *button;
    int score;
    bool state;

    struct Ns{  //保存空格
        int i;
        int j;
    };


signals:

public slots:
    void slotStart();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
