#ifndef RESUME_REPOSITORY_H
#define RESUME_REPOSITORY_H

#include <vector>
#include <QString>
#include "Resume.h"

class ResumeRepository {
public:
    ResumeRepository();
    std::vector<Resume> filterResumes(const QString& keyword);
private:
    std::vector<Resume> resumes;
};

#endif // RESUME_REPOSITORY_H
