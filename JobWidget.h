#ifndef JOBWIDGET_H
#define JOBWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QtSql/QSqlDatabase>
#include "Job.h"

class JobWidget : public QWidget {
Q_OBJECT

public:
    JobWidget(int userId, QSqlDatabase &db, QWidget *parent = nullptr);

private slots:
    void addJob();
    void deleteJob();
    void refreshJobs();

private:
    int userId;
    QSqlDatabase &db;
    QLineEdit *titleEdit;
    QLineEdit *companyEdit;
    QLineEdit *salaryMinEdit;
    QLineEdit *salaryMaxEdit;
    QLineEdit *tagsEdit;
    QLineEdit *descriptionEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QTableWidget *jobTable;

    void setupUI();
    void loadJobs();
};

#endif // JOBWIDGET_H