#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QtSql/QSqlDatabase>

class AdminWidget : public QWidget {
Q_OBJECT

public:
    AdminWidget(QSqlDatabase &db, QWidget *parent = nullptr);
    void logOperation(const QString &operation); // 移到 public

private:
    QSqlDatabase &db;
    QTabWidget *adminTabs;
    QTableWidget *userTable;
    QTableWidget *resumeTable;
    QTableWidget *jobTable;
    QTableWidget *logTable;

    void setupUI();
    void loadUsers();
    void loadResumes();
    void loadJobs();
    void loadLogs();
};

#endif // ADMINWIDGET_H