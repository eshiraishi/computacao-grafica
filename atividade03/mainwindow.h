#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>

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
public slots:
    void SelectedDraw(int);
    void SelectedColor(int);
private:
    Ui::MainWindow *ui;
    int typeOfDraw{0}; // serah o CLEAN
    int typeOfColor{0}; // serah o RED
};
#endif // MAINWINDOW_H
