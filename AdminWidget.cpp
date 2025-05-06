#include "AdminWidget.h"
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QHeaderView>
#include <QDateTime>
AdminWidget::AdminWidget(QSqlDatabase &db, QWidget *parent)
        : QWidget(parent), db(db) {
    // 创建日志表（如果不存在）
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS logs ("
               "log_id INT AUTO_INCREMENT PRIMARY KEY, "
               "operation TEXT, "
               "created_at DATETIME)");

    setupUI();
    loadUsers();
    loadResumes();
    loadJobs();
    loadLogs();
}

void AdminWidget::setupUI() {
    adminTabs = new QTabWidget(this);
    userTable = new QTableWidget(this);
    resumeTable = new QTableWidget(this);
    jobTable = new QTableWidget(this);
    logTable = new QTableWidget(this);

    userTable->setColumnCount(5);
    userTable->setHorizontalHeaderLabels({"ID", "用户名", "角色", "邮箱", "创建时间"});
    userTable->horizontalHeader()->setStretchLastSection(true);

    resumeTable->setColumnCount(6);
    resumeTable->setHorizontalHeaderLabels({"ID", "用户ID", "教育", "经验", "技能", "语言"});
    resumeTable->horizontalHeader()->setStretchLastSection(true);

    jobTable->setColumnCount(7);
    jobTable->setHorizontalHeaderLabels({"ID", "职位", "公司", "最低薪资", "最高薪资", "标签", "描述"});
    jobTable->horizontalHeader()->setStretchLastSection(true);

    logTable->setColumnCount(3);
    logTable->setHorizontalHeaderLabels({"ID", "操作", "时间"});
    logTable->horizontalHeader()->setStretchLastSection(true);

    adminTabs->addTab(userTable, "用户");
    adminTabs->addTab(resumeTable, "简历");
    adminTabs->addTab(jobTable, "职位");
    adminTabs->addTab(logTable, "日志");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(adminTabs);
}

void AdminWidget::loadUsers() {
    QSqlQuery query(db);
    query.exec("SELECT user_id, username, role, email, created_at FROM users");

    userTable->setRowCount(0);
    while (query.next()) {
        int row = userTable->rowCount();
        userTable->insertRow(row);
        userTable->setItem(row, 0, new QTableWidgetItem(query.value("user_id").toString()));
        userTable->setItem(row, 1, new QTableWidgetItem(query.value("username").toString()));
        userTable->setItem(row, 2, new QTableWidgetItem(query.value("role").toString()));
        userTable->setItem(row, 3, new QTableWidgetItem(query.value("email").toString()));
        userTable->setItem(row, 4, new QTableWidgetItem(query.value("created_at").toDateTime().toString("yyyy-MM-dd hh:mm")));
    }
}

void AdminWidget::loadResumes() {
    QSqlQuery query(db);
    query.exec("SELECT resume_id, user_id, education, experience, skills, languages FROM resumes");

    resumeTable->setRowCount(0);
    while (query.next()) {
        int row = resumeTable->rowCount();
        resumeTable->insertRow(row);
        resumeTable->setItem(row, 0, new QTableWidgetItem(query.value("resume_id").toString()));
        resumeTable->setItem(row, 1, new QTableWidgetItem(query.value("user_id").toString()));
        resumeTable->setItem(row, 2, new QTableWidgetItem(query.value("education").toString()));
        resumeTable->setItem(row, 3, new QTableWidgetItem(query.value("experience").toString()));
        resumeTable->setItem(row, 4, new QTableWidgetItem(query.value("skills").toString()));
        resumeTable->setItem(row, 5, new QTableWidgetItem(query.value("languages").toString()));
    }
}

void AdminWidget::loadJobs() {
    QSqlQuery query(db);
    query.exec("SELECT job_id, title, company, salary_min, salary_max, tags, description FROM jobs");

    jobTable->setRowCount(0);
    while (query.next()) {
        int row = jobTable->rowCount();
        jobTable->insertRow(row);
        jobTable->setItem(row, 0, new QTableWidgetItem(query.value("job_id").toString()));
        jobTable->setItem(row, 1, new QTableWidgetItem(query.value("title").toString()));
        jobTable->setItem(row, 2, new QTableWidgetItem(query.value("company").toString()));
        jobTable->setItem(row, 3, new QTableWidgetItem(query.value("salary_min").toString()));
        jobTable->setItem(row, 4, new QTableWidgetItem(query.value("salary_max").toString()));
        jobTable->setItem(row, 5, new QTableWidgetItem(query.value("tags").toString()));
        jobTable->setItem(row, 6, new QTableWidgetItem(query.value("description").toString()));
    }
}

void AdminWidget::logOperation(const QString &operation) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO logs (operation, created_at) VALUES (:operation, NOW())");
    query.bindValue(":operation", operation);
    query.exec();
    loadLogs();
}

void AdminWidget::loadLogs() {
    QSqlQuery query(db);
    query.exec("SELECT log_id, operation, created_at FROM logs");

    logTable->setRowCount(0);
    while (query.next()) {
        int row = logTable->rowCount();
        logTable->insertRow(row);
        logTable->setItem(row, 0, new QTableWidgetItem(query.value("log_id").toString()));
        logTable->setItem(row, 1, new QTableWidgetItem(query.value("operation").toString()));
        logTable->setItem(row, 2, new QTableWidgetItem(query.value("created_at").toDateTime().toString("yyyy-MM-dd hh:mm")));
    }
}