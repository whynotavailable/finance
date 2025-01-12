#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sqlite3.h>
#include <sstream>

int main(int argc, char *argv[]) {
    std::ostringstream connStrStream;
    connStrStream << "file:" << getenv("HOME") << "/finance.db";
    std::string connStr = connStrStream.str();

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open_v2(
        connStr.c_str(), &db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
            SQLITE_OPEN_FULLMUTEX, // Qt is technically multi-threaded so...
        NULL);

    if (rc) {
        std::cerr << "Can't open database: " << rc << std::endl;
        return 1;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS COMPANY("
                      "ID INT PRIMARY KEY     NOT NULL,"
                      "NAME           TEXT    NOT NULL,"
                      "AGE            INT     NOT NULL,"
                      "ADDRESS        CHAR(50),"
                      "SALARY         REAL );";

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Table created successfully" << std::endl;
    }

    sqlite3_close(db);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qInfo() << "Launch Broski";
    return a.exec();
}
