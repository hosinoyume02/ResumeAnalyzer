#include <QCoreApplication>
#include <QDebug>
#include "resume_repository.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // 1）先输出所有简历
    QList<Resume> all = ResumeRepository::fetchAllResumes();
    qDebug() << "=== 全部简历 ===";
    for (const Resume& r : all) {
        qDebug() << r.resume_id << r.user_id << r.education << r.skills;
    }

    // 2）交互式筛选
    QTextStream in(stdin);
    QString field, value;
    qDebug() << "\n请输入筛选字段 (education/experience/skills/languages):";
    field = in.readLine().trimmed();
    qDebug() << "请输入筛选关键词:";
    value = in.readLine().trimmed();

    QList<Resume> filtered = ResumeRepository::filterResumesByField(field, value);
    qDebug() << "\n=== 筛选结果 ===";
    if (filtered.isEmpty()) {
        qDebug() << "没有找到符合条件的简历。";
    } else {
        for (const Resume& r : filtered) {
            qDebug() << r.resume_id << r.user_id << r.education << r.skills;
        }
    }

    return 0;
}