#include "mainwindow.h"
#include <QCoreApplication>
#include <solver.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            square[i][j] = new QPushButton("",this);
            connect(square[i][j],SIGNAL(released()),this,SLOT(squareClicked()));
        }

    for (int i=0;i<9;++i)
    {
        number[i]=new QPushButton(QString::number(i+1),this);
        connect(number[i],SIGNAL(released()),this,SLOT(numberClicked()));
    }

    emtyButton = new QPushButton("Emty",this);
    emtyButton->setGeometry(QRect(QPoint(25,460),QSize(150,40)));
    connect(emtyButton,SIGNAL(released()),this,SLOT(emtyClicked()));

    solveButton = new QPushButton("Solve",this);
    solveButton->setGeometry(QRect(QPoint(200,340),QSize(115,67)));
    connect(solveButton,SIGNAL(released()),this,SLOT(solveClicked()));

    clearButton = new QPushButton("Clear",this);
    clearButton->setGeometry(QRect(QPoint(200,433),QSize(115,67)));
    connect(clearButton,SIGNAL(released()),this,SLOT(clearClicked()));

    redText = new QPalette();
    redText->setColor(QPalette::ButtonText,Qt::red);

    blueText = new QPalette();
    blueText->setColor(QPalette::ButtonText,Qt::blue);

    blackText = new QPalette();
    blackText->setColor(QPalette::ButtonText,Qt::black);

    setSquareGeo();
    setNumberGeo();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setSquareGeo()
{
    int x,y;
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            int a=0,b=0;
            if(i>2&&i<6)
                a=10;
            if(i>5)
                a=20;
            if(j>2&&j<6)
                b=10;
            if(j>5)
                b=20;
            x=a+25+i*30;
            y=b+25+j*30;
            square[i][j]->setGeometry(QRect(QPoint(x,y),QSize(30,30)));
            square[i][j]->setStyleSheet("background-color: white");
        }
}

void MainWindow::setNumberGeo()
{
    for (int i=0;i<3;++i)
        number[i]->setGeometry(QRect(QPoint(25+i*50,420),QSize(50,40)));
    for (int i=3;i<6;++i)
        number[i]->setGeometry(QRect(QPoint(25+(i-3)*50,380),QSize(50,40)));
    for (int i=6;i<9;++i)
        number[i]->setGeometry(QRect(QPoint(25+(i-6)*50,340),QSize(50,40)));
}

void MainWindow::numberClicked()
{
    QPushButton *virButton =(QPushButton *)sender();
    value=virButton->text();
}

void MainWindow::emtyClicked()
{
    value="";
}

void MainWindow::squareClicked()
{
    QPushButton *virSquare =(QPushButton *)sender();
    virSquare->setText(value);
}

void MainWindow::clearClicked()
{
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            square[i][j]->setEnabled(true);
            value="";
            square[i][j]->setText(value);
            square[i][j]->setPalette(*blackText);
            grid[i][j]='\0';
        }
     solveButton->setEnabled(true);
}

void MainWindow::solveClicked()
{
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            if(square[i][j]->text()=="")
                grid[i][j]='0';
            else
            {
            int x = QString(square[i][j]->text())[0].unicode();
            grid[i][j]=(char)x;
            }
        }
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
            if (identical_row(grid, i, j) + identical_collumn(grid, i, j) + identical_block(grid, i, j) != 0)
                return;

    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            square[i][j]->setEnabled(false);
            square[i][j]->setPalette(*blackText);
        }
    solveButton->setEnabled(false);
    char workingArr[9][9];
    copyGrid(workingArr);

    solve(workingArr);
    setGrid(workingArr);
    display();


}

void MainWindow::display()
{
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            if(square[i][j]->text() == "")
            {
            square[i][j]->setText(QString(grid[i][j]));
            square[i][j]->setPalette(*blueText);
            }

        }
}

void MainWindow::setGrid(char arr[9][9])
{
   memcpy(grid, arr, sizeof(char) * 9 * 9);
}

void MainWindow::copyGrid(char arr[9][9])
{
   memcpy(arr, grid, sizeof(char) * 9 * 9);
}
