#include "RecommendationWidget.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QHeaderView>
RecommendationWidget::RecommendationWidget(int userId, QSqlDatabase &db, QWidget *parent)
        : QWidget(parent), userId(userId), db(db) {
    setupUI();
    loadUserResumes();
}

void RecommendationWidget::setupUI() {
    recommendButton = new QPushButton("推荐职位", this);
    jobTable = new QTableWidget(this);
    jobTable->setColumnCount(7);
    jobTable->setHorizontalHeaderLabels({"ID", "职位", "公司", "最低薪资", "最高薪资", "标签", "描述"});
    jobTable->horizontalHeader()->setStretchLastSection(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(recommendButton);
    mainLayout->addWidget(jobTable);

    connect(recommendButton, &QPushButton::clicked, this, &RecommendationWidget::recommendJobs);
}

void RecommendationWidget::loadUserResumes() {
    QSqlQuery query(db);
    query.prepare("SELECT resume_id, user_id, education, experience, skills, languages, created_at "
                  "FROM resumes WHERE user_id = :userId");
    query.bindValue(":userId", userId);
    query.exec();

    userResumes.clear();
    while (query.next()) {
        Resume res(
                query.value("resume_id").toInt(),
                query.value("user_id").toInt(),
                query.value("education").toString(),
                query.value("experience").toString(),
                query.value("skills").toString(),
                query.value("languages").toString(),
                query.value("created_at").toDateTime()
        );
        userResumes.append(res);
    }
}

void RecommendationWidget::recommendJobs() {
    if (userResumes.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先创建简历！");
        return;
    }

    QStringList allSkills;
    for (const Resume &resume : userResumes) {
        allSkills.append(resume.skills.split(",", Qt::SkipEmptyParts));
    }
    allSkills.removeDuplicates();

    QSqlQuery query(db);
    query.exec("SELECT job_id, title, company, salary_min, salary_max, tags, description FROM jobs");
    jobTable->setRowCount(0);

    while (query.next()) {
        QString tags = query.value("tags").toString();
        QStringList tagList = tags.split(",", Qt::SkipEmptyParts);
        bool match = false;
        for (const QString &skill : allSkills) {
            for (const QString &tag : tagList) {
                if (skill.trimmed().compare(tag.trimmed(), Qt::CaseInsensitive) == 0) {
                    match = true;
                    break;
                }
            }
            if (match) break;
        }

        if (match) {
            int row = jobTable->rowCount();
            jobTable->insertRow(row);
            jobTable->setItem(row, 0, new QTableWidgetItem(query.value("job_id").toString()));
            jobTable->setItem(row, 1, new QTableWidgetItem(query.value("title").toString()));
            jobTable->setItem(row, 2, new QTableWidgetItem(query.value("company").toString()));
            jobTable->setItem(row, 3, new QTableWidgetItem(query.value("salary_min").toString()));
            jobTable->setItem(row, 4, new QTableWidgetItem(query.value("salary_max").toString()));
            jobTable->setItem(row, 5, new QTableWidgetItem(tags));
            jobTable->setItem(row, 6, new QTableWidgetItem(query.value("description").toString()));
        }
    }

    if (jobTable->rowCount() == 0) {
        QMessageBox::information(this, "提示", "没有匹配的职位！");
    }
}