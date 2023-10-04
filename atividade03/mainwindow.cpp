#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SelectedDraw(int d){
    qDebug() << "Type of draw: " << d << "\n";
    typeOfDraw = d;
    // chama paintEvent
    update();
}

void MainWindow::SelectedColor(int d){
    qDebug() << "Type of color: " << d << "\n";
    typeOfColor = d;
    // chama paintEvent
    update();
}

void MainWindow::paintEvent(QPaintEvent *){
    // define os desenhos
    QPainter painter(this);

    switch(typeOfColor) {
    case 0:
        painter.setPen(Qt::red);
        break;
    case 1:
        painter.setPen(Qt::green);
        break;
    case 2:
        painter.setPen(Qt::blue);
        break;
    }

    switch (typeOfDraw) {
    case 0:
        break;
    case 1:
        painter.drawRect(30,30,30,60);
        break;
    case 2:
        painter.drawEllipse(30,30,30,30);
        break;
    }
}
