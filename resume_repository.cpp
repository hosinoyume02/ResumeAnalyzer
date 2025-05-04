#include "resume_repository.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QList<Resume> ResumeRepository::fetchAllResumes() {
    QList<Resume> resumeList;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("MySQL"); // 修改为你自己的 DSN 名称

    if (!db.open()) {
        qDebug() << "数据库连接失败:" << db.lastError().text();
        return resumeList;
    }

    QSqlQuery query("SELECT resume_id, user_id, education, experience, skills, languages, created_at FROM resumes");
    while (query.next()) {
        Resume r(
                query.value(0).toInt(),
                query.value(1).toInt(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toDateTime()
        );
        resumeList.append(r);
    }

    db.close();
    return resumeList;
}

QList<Resume> ResumeRepository::fetchResumesByKeyword(const QString& keyword) {
    QList<Resume> resumeList;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("MySQL"); // 修改为你自己的 DSN 名称

    if (!db.open()) {
        qDebug() << "数据库连接失败:" << db.lastError().text();
        return resumeList;
    }

    QSqlQuery query;
    query.prepare("SELECT resume_id, user_id, education, experience, skills, languages, created_at "
                  "FROM resumes WHERE skills LIKE ?");
    query.addBindValue("%" + keyword + "%");

    if (!query.exec()) {
        qDebug() << "查询失败:" << query.lastError().text();
        db.close();
        return resumeList;
    }

    while (query.next()) {
        Resume r(
                query.value(0).toInt(),
                query.value(1).toInt(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toDateTime()
        );
        resumeList.append(r);
    }

    db.close();
    return resumeList;
}
