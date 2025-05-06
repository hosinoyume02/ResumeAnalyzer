#include "analyzer.h"

std::map<QString, int> Analyzer::analyzeSkillFrequency(const std::vector<Resume>& resumes) {
    std::map<QString, int> skillMap;
    for (const Resume& r : resumes) {
        for (const auto& skill : r.skills.split("/")) {
            QString trimmed = skill.trimmed();
            if (!trimmed.isEmpty())
                skillMap[trimmed]++;
        }
    }
    return skillMap;
}

std::map<QString, double> Analyzer::predictSalaryDistribution(const std::vector<Resume>& resumes) {
    std::map<QString, double> salaryMap;
    for (const Resume& r : resumes) {
        QString edu = r.education;
        if (edu.contains("本科")) salaryMap["本科"] += 8000;
        else if (edu.contains("硕士")) salaryMap["硕士"] += 12000;
        else salaryMap["其他"] += 6000;
    }

    for (auto& [key, val] : salaryMap) {
        val /= resumes.size();  // 求均值
    }

    return salaryMap;
}
