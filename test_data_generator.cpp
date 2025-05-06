#include "test_data_generator.h"

std::vector<Resume> TestDataGenerator::generate(int count) {
    std::vector<Resume> result;
    for (int i = 0; i < count; ++i) {
        Resume r;
        r.resume_id = i;
        r.education = (i % 2 == 0) ? "本科" : "硕士";
        r.experience = "项目经验 " + QString::number(i);
        r.skills = (i % 3 == 0) ? "C++/Python" : "Java";
        r.languages = "英语";
        result.push_back(r);
    }
    return result;
}
