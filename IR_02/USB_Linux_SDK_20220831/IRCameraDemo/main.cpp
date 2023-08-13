#include "mainwindow.h"
#include <QApplication>

#define VERSION "v1.0(20191017)-ubuntu"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(w.windowTitle());

    w.show();

    return a.exec();
}
