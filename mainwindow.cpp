#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtGui/qicon.h>
#include <iostream>

const char *sql = "CREATE TABLE IF NOT EXISTS COMPANY("
                  "ID INT PRIMARY KEY     NOT NULL,"
                  "NAME           TEXT    NOT NULL,"
                  "AGE            INT     NOT NULL,"
                  "ADDRESS        CHAR(50),"
                  "SALARY         REAL );";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("Finance!"));
    fileMenu = menuBar()->addMenu(tr("&File"));

    newAct = new QAction(tr("&New"), this);
    newAct->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));

    fileMenu->addAction(newAct);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/adf/finance.db");

    bool ok = db.open();

    if (!ok) {
        std::cerr << "what";
    } else {
        QSqlQuery query;
        if (!query.exec(sql)) {
            std::cerr << "err: " << ok;
        } else {
            std::cerr << "good to go";
        }
    }
}

MainWindow::~MainWindow() {}
