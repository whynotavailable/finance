#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <cstddef>
#include <cstdlib>
#include <sqlite3.h>
#include <sstream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qInfo() << "Launch Broski";
    return a.exec();
}
