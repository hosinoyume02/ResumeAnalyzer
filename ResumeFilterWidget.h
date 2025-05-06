#ifndef RESUMEFILTERWIDGET_H
#define RESUMEFILTERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "ResumeManager.h"

class ResumeFilterWidget : public QWidget {
Q_OBJECT

public:
    ResumeFilterWidget(QWidget *parent = nullptr);
    void setResumeManager(ResumeManager *manager);

private slots:
    void applyFilter();

private:
    QLineEdit *skillsEdit;
    QLineEdit *languagesEdit;
    QLineEdit *experienceEdit;
    QPushButton *filterButton;
    QTableWidget *resultTable;

    ResumeManager *resumeManager;

    void displayResults(const QList<Resume> &results);
};

#endif // RESUMEFILTERWIDGET_H
