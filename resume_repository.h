#ifndef RESUME_REPOSITORY_H
#define RESUME_REPOSITORY_H

#include <QList>
#include "resume.h"

class ResumeRepository {
public:
    static QList<Resume> fetchAllResumes();

    // 新增：按字段筛选（fieldName: education/experience/skills/languages）
    static QList<Resume> filterResumesByField(const QString& fieldName, const QString& value);
};

#endif // RESUME_REPOSITORY_H
