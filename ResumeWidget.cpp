#include "ResumeWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QHeaderView>
ResumeWidget::ResumeWidget(int userId, QSqlDatabase &db, QWidget *parent)
        : QWidget(parent), userId(userId), db(db) {
    setupUI();
    loadResumes();
}

void ResumeWidget::setupUI() {
    educationEdit = new QLineEdit(this);
    educationEdit->setPlaceholderText("教育背景");
    experienceEdit = new QLineEdit(this);
    experienceEdit->setPlaceholderText("工作经验");
    skillsEdit = new QLineEdit(this);
    skillsEdit->setPlaceholderText("技能（以逗号分隔）");
    languagesEdit = new QLineEdit(this);
    languagesEdit->setPlaceholderText("语言（以逗号分隔）");

    addButton = new QPushButton("添加简历", this);
    editButton = new QPushButton("编辑选中简历", this);
    resumeTable = new QTableWidget(this);
    resumeTable->setColumnCount(5);
    resumeTable->setHorizontalHeaderLabels({"ID", "教育", "经验", "技能", "语言"});
    resumeTable->horizontalHeader()->setStretchLastSection(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(educationEdit);
    inputLayout->addWidget(experienceEdit);
    inputLayout->addWidget(skillsEdit);
    inputLayout->addWidget(languagesEdit);
    inputLayout->addWidget(addButton);
    inputLayout->addWidget(editButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(resumeTable);

    connect(addButton, &QPushButton::clicked, this, &ResumeWidget::addResume);
    connect(editButton, &QPushButton::clicked, this, &ResumeWidget::editResume);
}

void ResumeWidget::loadResumes() {
    QSqlQuery query(db);
    query.prepare("SELECT resume_id, education, experience, skills, languages FROM resumes WHERE user_id = :userId");
    query.bindValue(":userId", userId);
    query.exec();

    resumeTable->setRowCount(0);
    while (query.next()) {
        int row = resumeTable->rowCount();
        resumeTable->insertRow(row);
        resumeTable->setItem(row, 0, new QTableWidgetItem(query.value("resume_id").toString()));
        resumeTable->setItem(row, 1, new QTableWidgetItem(query.value("education").toString()));
        resumeTable->setItem(row, 2, new QTableWidgetItem(query.value("experience").toString()));
        resumeTable->setItem(row, 3, new QTableWidgetItem(query.value("skills").toString()));
        resumeTable->setItem(row, 4, new QTableWidgetItem(query.value("languages").toString()));
    }
}

void ResumeWidget::addResume() {
    QSqlQuery query(db);
    query.prepare("INSERT INTO resumes (user_id, education, experience, skills, languages, created_at) "
                  "VALUES (:userId, :education, :experience, :skills, :languages, NOW())");
    query.bindValue(":userId", userId);
    query.bindValue(":education", educationEdit->text());
    query.bindValue(":experience", experienceEdit->text());
    query.bindValue(":skills", skillsEdit->text());
    query.bindValue(":languages", languagesEdit->text());

    if (query.exec()) {
        // 记录日志
        QSqlQuery logQuery(db);
        logQuery.prepare("INSERT INTO logs (operation, created_at) VALUES (:operation, NOW())");
        logQuery.bindValue(":operation", "用户 " + QString::number(userId) + " 添加了简历");
        logQuery.exec();

        QMessageBox::information(this, "成功", "简历添加成功！");
        loadResumes();
    } else {
        QMessageBox::warning(this, "错误", "简历添加失败：" + query.lastError().text());
    }
}

void ResumeWidget::editResume() {
    int row = resumeTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "错误", "请先选择一个简历！");
        return;
    }

    int resumeId = resumeTable->item(row, 0)->text().toInt();
    QSqlQuery query(db);
    query.prepare("UPDATE resumes SET education = :education, experience = :experience, "
                  "skills = :skills, languages = :languages WHERE resume_id = :resumeId AND user_id = :userId");
    query.bindValue(":education", educationEdit->text());
    query.bindValue(":experience", experienceEdit->text());
    query.bindValue(":skills", skillsEdit->text());
    query.bindValue(":languages", languagesEdit->text());
    query.bindValue(":resumeId", resumeId);
    query.bindValue(":userId", userId);

    if (query.exec()) {
        // 记录日志
        QSqlQuery logQuery(db);
        logQuery.prepare("INSERT INTO logs (operation, created_at) VALUES (:operation, NOW())");
        logQuery.bindValue(":operation", "用户 " + QString::number(userId) + " 编辑了简历 ID：" + QString::number(resumeId));
        logQuery.exec();

        QMessageBox::information(this, "成功", "简历更新成功！");
        loadResumes();
    } else {
        QMessageBox::warning(this, "错误", "简历更新失败：" + query.lastError().text());
    }
}

void ResumeWidget::refreshResumes() {
    loadResumes();
}