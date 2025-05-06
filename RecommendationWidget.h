#ifndef RECOMMENDATIONWIDGET_H
#define RECOMMENDATIONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QtSql/QSqlDatabase>
#include "Resume.h"

class RecommendationWidget : public QWidget {
Q_OBJECT

public:
    RecommendationWidget(int userId, QSqlDatabase &db, QWidget *parent = nullptr);

private slots:
    void recommendJobs();

private:
    int userId;
    QSqlDatabase &db;
    QPushButton *recommendButton;
    QTableWidget *jobTable;
    QList<Resume> userResumes;

    void setupUI();
    void loadUserResumes();
};

#endif // RECOMMENDATIONWIDGET_H