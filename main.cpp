#include <QApplication>
#include <QDebug>
#include <QProcess>
#include <QTimer>
#include <QThread>
#include <QWidget>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();
    return a.exec();
}
