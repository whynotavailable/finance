#include "mainwindow.h"
#include "common.h" // IWYU pragma: export
#include "migrations.h"
#include <QDir>
#include <QDirIterator>
#include <QIcon>
#include <QLabel>
#include <QStandardPaths>

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
