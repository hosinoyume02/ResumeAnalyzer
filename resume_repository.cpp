#include "resume_repository.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// 原有：获取全部
QList<Resume> ResumeRepository::fetchAllResumes() {
    QList<Resume> list;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("MySQL");
    if (!db.open()) {
        qDebug() << "数据库连接失败:" << db.lastError().text();
        return list;
    }

    QSqlQuery query("SELECT resume_id, user_id, education, experience, skills, languages, created_at FROM resumes");
    while (query.next()) {
        list.append(Resume(
                query.value(0).toInt(),
                query.value(1).toInt(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toDateTime()
        ));
    }
    db.close();
    return list;
}

// 新增：按字段筛选
QList<Resume> ResumeRepository::filterResumesByField(const QString& fieldName, const QString& value) {
    QList<Resume> list;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "filterConn");
    db.setDatabaseName("MySQL");
    if (!db.open()) {
        qDebug() << "数据库连接失败:" << db.lastError().text();
        return list;
    }

    // 注意：传入的 fieldName 必须是表中合法字段名
    QString sql = QString(
            "SELECT resume_id, user_id, education, experience, skills, languages, created_at "
            "FROM resumes WHERE %1 LIKE '%%2%'"
    ).arg(fieldName).arg(value);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qDebug() << "筛选失败:" << query.lastError().text();
        db.close();
        return list;
    }

    while (query.next()) {
        list.append(Resume(
                query.value(0).toInt(),
                query.value(1).toInt(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toDateTime()
        ));
    }
    db.close();
    return list;
}
