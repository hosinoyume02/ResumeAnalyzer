#include "resume_parser.h"

Resume ResumeParser::parseFromRawText(const QString& text) {
    Resume resume;
    resume.education = text.contains("本科") ? "本科" : "未知";
    resume.experience = text.contains("开发") ? "软件开发经验" : "无经验";
    resume.skills = text.contains("C++") ? "C++" : "无技能";
    resume.languages = text.contains("英语") ? "英语" : "未知";
    return resume;
}
