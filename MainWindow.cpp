#include "MainWindow.h"
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    QLabel *label = new QLabel("输入关键词：", this);
    keywordInput = new QLineEdit(this);
    filterButton = new QPushButton("筛选简历", this);
    resultTable = new QTableWidget(this);

    resultTable->setColumnCount(4);  // 不需要显示 ID 可不写
    resultTable->setHorizontalHeaderLabels({"学历", "经历", "技能", "语言"});

    layout->addWidget(label);
    layout->addWidget(keywordInput);
    layout->addWidget(filterButton);
    layout->addWidget(resultTable);

    setCentralWidget(central);

    connect(filterButton, &QPushButton::clicked, this, &MainWindow::onFilterClicked);
}

void MainWindow::onFilterClicked() {
    QString keyword = keywordInput->text();  // 正确获取
    std::vector<Resume> results = repository.filterResumes(keyword);
    showResumes(results);
}

void MainWindow::showResumes(const std::vector<Resume>& resumes) {
    resultTable->clearContents();
    resultTable->setRowCount(static_cast<int>(resumes.size()));

    for (int i = 0; i < resumes.size(); ++i) {
        const Resume& r = resumes[i];
        resultTable->setItem(i, 0, new QTableWidgetItem(r.education));
        resultTable->setItem(i, 1, new QTableWidgetItem(r.experience));
        resultTable->setItem(i, 2, new QTableWidgetItem(r.skills));
        resultTable->setItem(i, 3, new QTableWidgetItem(r.languages));
    }

    resultTable->resizeColumnsToContents();  // 自动列宽
}
