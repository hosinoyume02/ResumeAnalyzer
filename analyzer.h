#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include <QString>
#include <map>
#include "Resume.h"

class Analyzer {
public:
    static std::map<QString, int> analyzeSkillFrequency(const std::vector<Resume>& resumes);
    static std::map<QString, double> predictSalaryDistribution(const std::vector<Resume>& resumes);
};

#endif // ANALYZER_H
