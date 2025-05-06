#ifndef RESUME_H
#define RESUME_H

#include <QString>
#include <QDateTime>
#include <QStringList>

class Resume {
public:
    int resumeId;
    int userId;
    QString education;
    QString experience;
    QString skills;
    QString languages;
    QDateTime createdAt;

    Resume();
    Resume(int resumeId, int userId, const QString &education, const QString &experience,
           const QString &skills, const QString &languages, const QDateTime &createdAt);

    // 筛选匹配函数
    bool matchesSkill(const QString &skill) const;
    bool matchesLanguage(const QString &language) const;
    bool matchesExperienceKeyword(const QString &keyword) const;
};

#endif // RESUME_H
