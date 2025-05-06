#ifndef JOB_H
#define JOB_H

#include <QString>
#include <QDateTime>

class Job {
public:
    int jobId;
    QString title;
    QString company;
    int salaryMin;
    int salaryMax;
    QString tags;
    QString description;
    int createdBy;

    Job();
    Job(int jobId, const QString &title, const QString &company, int salaryMin, int salaryMax,
        const QString &tags, const QString &description, int createdBy);
};

#endif // JOB_H