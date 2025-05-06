#include "Job.h"

Job::Job() {}

Job::Job(int jobId, const QString &title, const QString &company, int salaryMin, int salaryMax,
         const QString &tags, const QString &description, int createdBy)
        : jobId(jobId), title(title), company(company), salaryMin(salaryMin), salaryMax(salaryMax),
          tags(tags), description(description), createdBy(createdBy) {}