#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QtSql/QSqlDatabase>
#include "ResumeManager.h"
#include "ResumeFilterWidget.h"
#include "User.h"
#include "JobWidget.h"
#include "ResumeWidget.h"
#include "RecommendationWidget.h"
#include "AdminWidget.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(const User &user, QWidget *parent = nullptr);
    ~MainWindow();

private:
    User currentUser;
    ResumeManager manager;
    ResumeFilterWidget *filterWidget;
    JobWidget *jobWidget;
    ResumeWidget *resumeWidget;
    RecommendationWidget *recommendationWidget;
    AdminWidget *adminWidget;
    QTabWidget *tabWidget;
    QSqlDatabase db;

    void setupDatabase();
    void loadDataFromDatabase();
    void setupUI();
};

#endif // MAINWINDOW_H