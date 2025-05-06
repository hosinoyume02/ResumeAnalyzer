#ifndef RESUME_PARSER_H
#define RESUME_PARSER_H

#include <QString>
#include <vector>
#include "Resume.h"

class ResumeParser {
public:
    static Resume parseFromRawText(const QString& text);
};

#endif // RESUME_PARSER_H
