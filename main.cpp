#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <cstddef>
#include <cstdlib>
#include <sqlite3.h>
#include <sstream>

int main(int argc, char *argv[]) {
    std::ostringstream connStrStream;
    connStrStream << "file:" << getenv("HOME") << "/finance.db";
    std::string connStr = connStrStream.str();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qInfo() << "Launch Broski";
    return a.exec();
}
