#include "mainwindow.h"
#include "migrations.h"
#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QString>

void init_db() {
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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(tr("Finance!"));
    fileMenu = menuBar()->addMenu(tr("&File"));

    newAct = new QAction(tr("&New"), this);
    newAct->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));

    fileMenu->addAction(newAct);

    init_db();

    QStackedWidget *stackWidge = new QStackedWidget(this);
    setCentralWidget(stackWidge);
}

MainWindow::~MainWindow() {}
