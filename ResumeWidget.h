#ifndef RESUMEWIDGET_H
#define RESUMEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QtSql/QSqlDatabase>
#include "Resume.h"

class ResumeWidget : public QWidget {
Q_OBJECT

public:
    ResumeWidget(int userId, QSqlDatabase &db, QWidget *parent = nullptr);

private slots:
    void addResume();
    void editResume();
    void refreshResumes();

private:
    int userId;
    QSqlDatabase &db;
    QLineEdit *educationEdit;
    QLineEdit *experienceEdit;
    QLineEdit *skillsEdit;
    QLineEdit *languagesEdit;
    QPushButton *addButton;
    QPushButton *editButton;
    QTableWidget *resumeTable;

    void setupUI();
    void loadResumes();
};

#endif // RESUMEWIDGET_H