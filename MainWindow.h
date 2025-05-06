#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ResumeManager.h"
#include "ResumeFilterWidget.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ResumeManager manager;
    ResumeFilterWidget *filterWidget;

    void loadDataFromDatabase();
};

#endif // MAINWINDOW_H
