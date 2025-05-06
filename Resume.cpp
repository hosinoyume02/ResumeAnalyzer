#include "Resume.h"

Resume::Resume() {}

Resume::Resume(int resumeId, int userId, const QString &education, const QString &experience,
               const QString &skills, const QString &languages, const QDateTime &createdAt)
        : resumeId(resumeId), userId(userId), education(education), experience(experience),
          skills(skills), languages(languages), createdAt(createdAt) {}

bool Resume::matchesSkill(const QString &skill) const {
    return skills.contains(skill, Qt::CaseInsensitive);
}

bool Resume::matchesLanguage(const QString &language) const {
    return languages.contains(language, Qt::CaseInsensitive);
}

bool Resume::matchesExperienceKeyword(const QString &keyword) const {
    return experience.contains(keyword, Qt::CaseInsensitive);
}
