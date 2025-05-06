#include "MainWindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), filterWidget(new ResumeFilterWidget(this)) {

    loadDataFromDatabase();
    filterWidget->setResumeManager(&manager);
    setCentralWidget(filterWidget);
    resize(1000, 600);
    setWindowTitle("简历数据分析系统");
}

MainWindow::~MainWindow() {}

void MainWindow::loadDataFromDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("MySQL"); // DSN 名称
    db.setUserName("root");
    db.setPassword("20020904");

    if (!db.open()) {
        QMessageBox::critical(this, "数据库错误", "无法连接数据库: " + db.lastError().text());
        return;
    }

    QSqlQuery query("SELECT resume_id, user_id, education, experience, skills, languages, created_at FROM resumes");
    while (query.next()) {
        Resume res(
                query.value(0).toInt(),
                query.value(1).toInt(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toDateTime()
        );
        manager.addResume(res);
    }
}
