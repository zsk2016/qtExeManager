#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QProcess>
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
