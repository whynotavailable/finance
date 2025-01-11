#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QIcon>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenu *fileMenu;
    QAction *newAct;
};
#endif // MAINWINDOW_H
