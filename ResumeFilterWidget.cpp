#include "ResumeFilterWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QHeaderView>

ResumeFilterWidget::ResumeFilterWidget(QWidget *parent)
        : QWidget(parent), resumeManager(nullptr) {
    skillsEdit = new QLineEdit(this);
    skillsEdit->setPlaceholderText("输入技能关键词，多个以逗号分隔");

    languagesEdit = new QLineEdit(this);
    languagesEdit->setPlaceholderText("输入语言关键词，多个以逗号分隔");

    experienceEdit = new QLineEdit(this);
    experienceEdit->setPlaceholderText("输入经验关键词，多个以逗号分隔");

    filterButton = new QPushButton("筛选简历", this);
    resultTable = new QTableWidget(this);
    resultTable->setColumnCount(6);
    resultTable->setHorizontalHeaderLabels({"ID", "教育", "经验", "技能", "语言", "创建时间"});
    resultTable->horizontalHeader()->setStretchLastSection(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(skillsEdit);
    inputLayout->addWidget(languagesEdit);
    inputLayout->addWidget(experienceEdit);
    inputLayout->addWidget(filterButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(resultTable);

    connect(filterButton, &QPushButton::clicked, this, &ResumeFilterWidget::applyFilter);
}

void ResumeFilterWidget::setResumeManager(ResumeManager *manager) {
    resumeManager = manager;
}

void ResumeFilterWidget::applyFilter() {
    if (!resumeManager) return;

    QStringList skillList = skillsEdit->text().split(",", Qt::SkipEmptyParts);
    QStringList languageList = languagesEdit->text().split(",", Qt::SkipEmptyParts);
    QStringList experienceList = experienceEdit->text().split(",", Qt::SkipEmptyParts);

    QList<Resume> results = resumeManager->filterResumes(skillList, languageList, experienceList);
    displayResults(results);
}

void ResumeFilterWidget::displayResults(const QList<Resume> &results) {
    resultTable->setRowCount(results.size());
    for (int i = 0; i < results.size(); ++i) {
        const Resume &res = results[i];
        resultTable->setItem(i, 0, new QTableWidgetItem(QString::number(res.resumeId)));
        resultTable->setItem(i, 1, new QTableWidgetItem(res.education));
        resultTable->setItem(i, 2, new QTableWidgetItem(res.experience));
        resultTable->setItem(i, 3, new QTableWidgetItem(res.skills));
        resultTable->setItem(i, 4, new QTableWidgetItem(res.languages));
        resultTable->setItem(i, 5, new QTableWidgetItem(res.createdAt.toString("yyyy-MM-dd hh:mm")));
    }
}
