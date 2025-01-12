#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QIcon>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStackedWidget>
#include <QStatusBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenu *fileMenu;
    QAction *newAct;
    QStackedWidget *stack;
};
#endif // MAINWINDOW_H
