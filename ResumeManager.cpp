#include "ResumeManager.h"

void ResumeManager::addResume(const Resume &resume) {
    resumes.append(resume);
}

QList<Resume> ResumeManager::getAllResumes() const {
    return resumes;
}

QList<Resume> ResumeManager::filterResumes(const QStringList &skills,
                                           const QStringList &languages,
                                           const QStringList &experienceKeywords) const {
    QList<Resume> filtered;

    for (const Resume &resume : resumes) {
        bool skillMatch = skills.isEmpty() || std::any_of(skills.begin(), skills.end(), [&](const QString &skill) {
            return resume.matchesSkill(skill);
        });

        bool languageMatch = languages.isEmpty() || std::any_of(languages.begin(), languages.end(), [&](const QString &lang) {
            return resume.matchesLanguage(lang);
        });

        bool experienceMatch = experienceKeywords.isEmpty() || std::any_of(experienceKeywords.begin(), experienceKeywords.end(), [&](const QString &kw) {
            return resume.matchesExperienceKeyword(kw);
        });

        if (skillMatch && languageMatch && experienceMatch) {
            filtered.append(resume);
        }
    }

    return filtered;
}
