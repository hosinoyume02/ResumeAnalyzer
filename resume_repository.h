#ifndef RESUME_REPOSITORY_H
#define RESUME_REPOSITORY_H

#include "Resume.h"
#include <QList>
#include <QString>

class ResumeRepository {
public:
    static QList<Resume> fetchAllResumes();
    static QList<Resume> fetchResumesByKeyword(const QString& keyword);
};

#endif // RESUME_REPOSITORY_H
