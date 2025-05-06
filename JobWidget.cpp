#include "JobWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QHeaderView>
JobWidget::JobWidget(int userId, QSqlDatabase &db, QWidget *parent)
        : QWidget(parent), userId(userId), db(db) {
    setupUI();
    loadJobs();
}

void JobWidget::setupUI() {
    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("职位名称");
    companyEdit = new QLineEdit(this);
    companyEdit->setPlaceholderText("公司名称");
    salaryMinEdit = new QLineEdit(this);
    salaryMinEdit->setPlaceholderText("最低薪资");
    salaryMaxEdit = new QLineEdit(this);
    salaryMaxEdit->setPlaceholderText("最高薪资");
    tagsEdit = new QLineEdit(this);
    tagsEdit->setPlaceholderText("标签（以逗号分隔）");
    descriptionEdit = new QLineEdit(this);
    descriptionEdit->setPlaceholderText("职位描述");

    addButton = new QPushButton("发布职位", this);
    deleteButton = new QPushButton("删除选中职位", this);
    jobTable = new QTableWidget(this);
    jobTable->setColumnCount(7);
    jobTable->setHorizontalHeaderLabels({"ID", "职位", "公司", "最低薪资", "最高薪资", "标签", "描述"});
    jobTable->horizontalHeader()->setStretchLastSection(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(titleEdit);
    inputLayout->addWidget(companyEdit);
    inputLayout->addWidget(salaryMinEdit);
    inputLayout->addWidget(salaryMaxEdit);
    inputLayout->addWidget(tagsEdit);
    inputLayout->addWidget(descriptionEdit);
    inputLayout->addWidget(addButton);
    inputLayout->addWidget(deleteButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(jobTable);

    connect(addButton, &QPushButton::clicked, this, &JobWidget::addJob);
    connect(deleteButton, &QPushButton::clicked, this, &JobWidget::deleteJob);
}

void JobWidget::loadJobs() {
    QSqlQuery query(db);
    query.prepare("SELECT job_id, title, company, salary_min, salary_max, tags, description FROM jobs WHERE created_by = :userId");
    query.bindValue(":userId", userId);
    query.exec();

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

void JobWidget::addJob() {
    QSqlQuery query(db);
    query.prepare("INSERT INTO jobs (title, company, salary_min, salary_max, tags, description, created_by) "
                  "VALUES (:title, :company, :salaryMin, :salaryMax, :tags, :description, :createdBy)");
    query.bindValue(":title", titleEdit->text());
    query.bindValue(":company", companyEdit->text());
    query.bindValue(":salaryMin", salaryMinEdit->text().toInt());
    query.bindValue(":salaryMax", salaryMaxEdit->text().toInt());
    query.bindValue(":tags", tagsEdit->text());
    query.bindValue(":description", descriptionEdit->text());
    query.bindValue(":createdBy", userId);

    if (query.exec()) {
        // 记录日志
        QSqlQuery logQuery(db);
        logQuery.prepare("INSERT INTO logs (operation, created_at) VALUES (:operation, NOW())");
        logQuery.bindValue(":operation", "用户 " + QString::number(userId) + " 发布了职位：" + titleEdit->text());
        logQuery.exec();

        QMessageBox::information(this, "成功", "职位发布成功！");
        loadJobs();
    } else {
        QMessageBox::warning(this, "错误", "职位发布失败：" + query.lastError().text());
    }
}

void JobWidget::deleteJob() {
    int row = jobTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "错误", "请先选择一个职位！");
        return;
    }

    int jobId = jobTable->item(row, 0)->text().toInt();
    QSqlQuery query(db);
    query.prepare("DELETE FROM jobs WHERE job_id = :jobId AND created_by = :userId");
    query.bindValue(":jobId", jobId);
    query.bindValue(":userId", userId);

    if (query.exec()) {
        // 记录日志
        QSqlQuery logQuery(db);
        logQuery.prepare("INSERT INTO logs (operation, created_at) VALUES (:operation, NOW())");
        logQuery.bindValue(":operation", "用户 " + QString::number(userId) + " 删除了职位 ID：" + QString::number(jobId));
        logQuery.exec();

        QMessageBox::information(this, "成功", "职位删除成功！");
        loadJobs();
    } else {
        QMessageBox::warning(this, "错误", "职位删除失败：" + query.lastError().text());
    }
}

void JobWidget::refreshJobs() {
    loadJobs();
}