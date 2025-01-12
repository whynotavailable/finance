#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QString>
#include <QtCore/qhashfunctions.h>
#include <QtCore/qstandardpaths.h>
#include <QtGui/qicon.h>
#include <QtWidgets/qapplication.h>
#include <iostream>
#include <sstream>

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
    QString appData =
        QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    // TODO: At some point, make this user selectable;
    auto dbFile = appData + "/finance.db";

    qInfo() << "Db:" << dbFile;

    db.setDatabaseName(dbFile);

    bool ok = db.open();

    if (!ok) {
        std::cerr << "what";
    } else {
        QSqlQuery query;
        if (!query.exec(sql)) {
            std::cerr << "err: " << ok;
        } else {
            qInfo() << "db good to go";
        }
    }
}

MainWindow::~MainWindow() {}
