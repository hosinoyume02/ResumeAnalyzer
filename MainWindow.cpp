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

    resultTable->setColumnCount(5);
    resultTable->setHorizontalHeaderLabels({"ID", "学历", "经历", "技能", "语言"});

    layout->addWidget(label);
    layout->addWidget(keywordInput);
    layout->addWidget(filterButton);
    layout->addWidget(resultTable);

    setCentralWidget(central);

    connect(filterButton, &QPushButton::clicked, this, &MainWindow::onFilterClicked);
}

void MainWindow::onFilterClicked() {
    QString keyword = ui->keywordInput->text();  // 获取输入框内容
    std::vector<Resume> results = repository.filterResumes(keyword);  // 数据库查询
    showResumes(results);  // 显示
}



// MainWindow.cpp
void MainWindow::displayResumes(const std::vector<Resume>& resumes) {
    resultTable->setRowCount(resumes.size());
    for (int i = 0; i < resumes.size(); ++i) {
        const Resume& r = resumes[i];
        resultTable->setItem(i, 0, new QTableWidgetItem(QString::number(r.resume_id)));
        resultTable->setItem(i, 1, new QTableWidgetItem(r.education));
        resultTable->setItem(i, 2, new QTableWidgetItem(r.experience));
        resultTable->setItem(i, 3, new QTableWidgetItem(r.skills));
        resultTable->setItem(i, 4, new QTableWidgetItem(r.languages));
    }
}

void MainWindow::showResumes(const std::vector<Resume>& resumes) {
    ui->resumeTable->clear();
    ui->resumeTable->setRowCount(static_cast<int>(resumes.size()));
    ui->resumeTable->setColumnCount(4);  // 你有几个字段就写几个
    QStringList headers = {"Education", "Experience", "Skills", "Languages"};
    ui->resumeTable->setHorizontalHeaderLabels(headers);

    for (int row = 0; row < resumes.size(); ++row) {
        const Resume& r = resumes[row];
        ui->resumeTable->setItem(row, 0, new QTableWidgetItem(r.education));
        ui->resumeTable->setItem(row, 1, new QTableWidgetItem(r.experience));
        ui->resumeTable->setItem(row, 2, new QTableWidgetItem(r.skills));
        ui->resumeTable->setItem(row, 3, new QTableWidgetItem(r.languages));
    }

    ui->resumeTable->resizeColumnsToContents();  // 自动调整列宽
}

