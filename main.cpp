#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    qInfo() << "Launch Broski";

    w.show();
    return a.exec();
}
