#include "resume_repository.h"

ResumeRepository::ResumeRepository() {
    // 初始化简历数据
}

std::vector<Resume> ResumeRepository::filterResumes(const QString& keyword) {
    std::vector<Resume> filtered;
    for (const auto& resume : resumes) {
        if (resume.education.contains(keyword, Qt::CaseInsensitive) ||
            resume.experience.contains(keyword, Qt::CaseInsensitive) ||
            resume.skills.contains(keyword, Qt::CaseInsensitive) ||
            resume.languages.contains(keyword, Qt::CaseInsensitive)) {
            filtered.push_back(resume);
        }
    }
    return filtered;
}
