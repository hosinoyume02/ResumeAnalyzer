#ifndef RESUME_H
#define RESUME_H

#include <QString>
#include <QDateTime>

class Resume {
public:
    int resume_id;
    int user_id;
    QString education;
    QString experience;
    QString skills;
    QString languages;
    QDateTime created_at;

    Resume(int rid, int uid, const QString& edu, const QString& exp, const QString& skl,
           const QString& lang, const QDateTime& created)
            : resume_id(rid), user_id(uid), education(edu), experience(exp),
              skills(skl), languages(lang), created_at(created) {}
};

#endif // RESUME_H
