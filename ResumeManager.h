#ifndef RESUMEMANAGER_H
#define RESUMEMANAGER_H

#include "Resume.h"
#include <QList>
#include <QStringList>

class ResumeManager {
public:
    QList<Resume> resumes;

    void addResume(const Resume &resume);
    QList<Resume> getAllResumes() const;

    // 筛选接口
    QList<Resume> filterResumes(const QStringList &skills,
                                const QStringList &languages,
                                const QStringList &experienceKeywords) const;
};

#endif // RESUMEMANAGER_H
