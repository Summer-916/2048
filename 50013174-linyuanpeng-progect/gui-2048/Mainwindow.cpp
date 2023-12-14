#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../core-2048/core_2048.hpp"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                surfaceBoard[i][j]=0;

        button = new QPushButton("Start",this);
        button->setGeometry(60,400,200,50);
        srand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        connect(button,SIGNAL(clicked()),this,SLOT(slotStart()));

        //connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBrush(Qt::blue);
    p.setFont(QFont("微软雅黑",20,700,false));

    QString strscore;
    p.drawText(QPoint(20,60),"Score："+QString::number(score));
    p.drawText(QPoint(20,100),"Highest score: "+QString::number(score));

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            p.setPen(Qt::transparent);
            if(surfaceBoard[i][j] == 0){
                p.setBrush(Qt::gray);
                p.drawRect(i*60+40,j*60+120,55,55);
            }
            else if(surfaceBoard[i][j] == 2){
                p.setBrush(Qt::red);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(2),QTextOption(Qt::AlignCenter));
            }
            else if(surfaceBoard[i][j] == 4){
                p.setBrush(Qt::darkRed);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(4),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 8){
                p.setBrush(Qt::green);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(8),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 16){
                p.setBrush(Qt::darkGreen);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(16),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 32){
                p.setBrush(Qt::yellow);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(32),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 64){
                p.setBrush(Qt::darkYellow);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(64),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 128){
                p.setBrush(Qt::cyan);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(128),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 256){
                p.setBrush(Qt::darkCyan);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(256),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 512){
                p.setBrush(Qt::magenta);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(512),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 1024){
                p.setBrush(Qt::darkMagenta);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(1024),QTextOption(Qt::AlignCenter));            }
            else if(surfaceBoard[i][j] == 2048){
                p.setBrush(Qt::blue);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(2048),QTextOption(Qt::AlignCenter));            }
            else{
                p.setBrush(Qt::darkBlue);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("",10,700,false));
               p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(surfaceBoard[i][j]),QTextOption(Qt::AlignCenter));
            }

        }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!state)
        return;

   switch(event->key())
   {
    case Qt::Key_W:
        PressUp();

        myRand();
       update();
         break;
    case Qt::Key_S:
       PressDown();
         randomTile();
               boardUpdate();
       update();
         break;
    case Qt::Key_A:
       PressLeft();
         randomTile();
               boardUpdate();
       update();
         break;
    case Qt::Key_D:
       PressRight();
         randomTile();
               boardUpdate();
       update();
         break;
    default:return;
   }
}


void MainWindow::slotStart()
{
   QMessageBox::about(this,"Instrucction","Use W(up),A(left),S(down),D(right) to move the tiles.");
    score = 0;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            surfaceBoard[i][j]=0;
    button->setText("Restart");
    // - Generate first two numbers.
    randomTile();
    randomTile();
    boardUpdate();

    state = true;
    update();

}






void MainWindow::PressUp()
{

    for(int i=0;i<4;i++)
        for(int j=1;j<4;j++){
             if(surfaceBoard[i][j] == 0){
               continue;
             }
            for(int p=0;p<j;p++){
                if(surfaceBoard[i][p] == 0){
                       surfaceBoard[i][p] = surfaceBoard[i][j];
                       surfaceBoard[i][j] = 0;
                       break;
                   }
               }
            }
            //Merge
    for(int i=0;i<4;i++)
         for(int j=0;j<3;j++){
             if(surfaceBoard[i][j] == surfaceBoard[i][j+1]){
                 surfaceBoard[i][j] = surfaceBoard[i][j]*2;
                 surfaceBoard[i][j+1] = 0;
                 score += surfaceBoard[i][j];
                 for(int p=j+2;p<4;p++)
                        surfaceBoard[i][p-1] = surfaceBoard[i][p];
             }

        }

}

void MainWindow::PressDown()
{
    for(int i=0;i<4;i++)
         for(int j=2;j>=0;j--){
             if(surfaceBoard[i][j] == 0){
                 continue;
             }
            for(int p=3;p>j;p--){
                if(surfaceBoard[i][p] == 0){
                    surfaceBoard[i][p] = surfaceBoard[i][j];
                    surfaceBoard[i][j] = 0;
                    break;
                }
            }
         }
    //Merge
    for(int i=0;i<4;i++)
         for(int j=3;j>0;j--){
             if(surfaceBoard[i][j] == surfaceBoard[i][j-1]){
                 surfaceBoard[i][j] = surfaceBoard[i][j]*2;
                 surfaceBoard[i][j-1] = 0;
                 score += surfaceBoard[i][j];
                 for(int p=j-2;p>=0;p--)
                     surfaceBoard[i][p+1] = surfaceBoard[i][p];
             }

         }
}
void MainWindow::PressLeft()
{

    for(int j=0;j<4;j++)
         for(int i=1;i<4;i++){
             if(surfaceBoard[i][j] == 0){
                 continue;
             }
            for(int p=0;p<i;p++){
                if(surfaceBoard[p][j] == 0){
                   surfaceBoard[p][j] = surfaceBoard[i][j];
                    surfaceBoard[i][j] = 0;
                    break;
                }
            }
         }
    //Merge
    for(int j=0;j<4;j++)
         for(int i=0;i<3;i++){
             if(surfaceBoard[i][j] ==surfaceBoard[i+1][j]){
                 surfaceBoard[i][j] = surfaceBoard[i][j]*2;
                 surfaceBoard[i+1][j] = 0;
                 score += surfaceBoard[i][j];
                 for(int p=i+2;p<4;p++)
                     surfaceBoard[p-1][j] = surfaceBoard[p][j];
             }

         }

}
void MainWindow::PressRight()
{

    for(int j=0;j<4;j++)
         for(int i=2;i>=0;i--){
             if(surfaceBoard[i][j] == 0){
                 continue;
             }
            for(int p=3;p>i;p--){
                if(surfaceBoard[p][j] == 0){
                    surfaceBoard[p][j] = surfaceBoard[i][j];
                    surfaceBoard[i][j] = 0;
                    break;
                }
            }
         }
    //Merge
    for(int j=0;j<4;j++)
         for(int i=3;i>0;i--){
             if(surfaceBoard[i][j] == surfaceBoard[i-1][j]){
                 surfaceBoard[i][j] = surfaceBoard[i][j]*2;
                 surfaceBoard[i-1][j] = 0;
                 score += surfaceBoard[i][j];
                 for(int p=i-2;p>=0;p--)
                     surfaceBoard[p+1][j] = surfaceBoard[p][j];
             }

         }

}
void MainWindow::myRand()
{
    int i,j;

   struct Ns n[15];
   int ni=0;
   for(i=0;i<4;i++)
       for(j=0;j<4;j++){
           if(surfaceBoard[i][j] == 0)
           {
               n[ni].i=i;
               n[ni].j=j;
               ++ni;
           }
       }

   //game is over?
   if(ni == 0){
       // row merge
       for(i=0;i<4;i++)
           for(j=0;j<3;j++)
               if(surfaceBoard[i][j] == surfaceBoard[i][j+1])
                  return;
       //col merge
       for(j=0;j<4;j++)
            for(i=0;i<3;i++)
                if(surfaceBoard[i][j] == surfaceBoard[i+1][j])
                   return;
      QMessageBox::about(this,"Game over","Your score is: "+QString::number(score)+"       ");
      return;
   }

   int rand1 = rand() % (ni);
   int random = 0;
   int a = rand() % 10;
   if (a != 9)
        random = 2;
    else
        random = 4;
   surfaceBoard[n[rand1].i][n[rand1].j] = random;

}




