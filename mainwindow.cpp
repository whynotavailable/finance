#include "mainwindow.h"
#include "migrations.h"
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QString>
#include <QtCore/qhashfunctions.h>
#include <QtCore/qstandardpaths.h>
#include <QtGui/qicon.h>
#include <QtWidgets/qapplication.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("Finance!"));
    fileMenu = menuBar()->addMenu(tr("&File"));

    newAct = new QAction(tr("&New"), this);
    newAct->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));

    fileMenu->addAction(newAct);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString appData =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir appDataPath(appData);
    if (!appDataPath.exists()) {
        appDataPath.mkpath(".");
    }

    // TODO: At some point, make this user selectable;
    auto dbFile = appData + "/finance.db";

    qInfo() << "Db:" << dbFile;

    db.setDatabaseName(dbFile);

    bool ok = db.open();

    if (!ok) {
        qFatal() << "Db Failed to load";
        QApplication::quit();
    }

    migrate_db();
}

MainWindow::~MainWindow() {}
