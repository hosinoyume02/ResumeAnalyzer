#ifndef TEST_DATA_GENERATOR_H
#define TEST_DATA_GENERATOR_H

#include <vector>
#include "Resume.h"

class TestDataGenerator {
public:
    static std::vector<Resume> generate(int count);
};

#endif // TEST_DATA_GENERATOR_H
