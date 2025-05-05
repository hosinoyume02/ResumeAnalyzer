#ifndef RESUME_ANALYZER_MAINWINDOW_H
#define RESUME_ANALYZER_MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "resume_repository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onFilterClicked();  // 这个槽函数我们已经绑定过了

private:
    ResumeRepository repository;
    QLineEdit *keywordInput;
    QPushButton *filterButton;
    QTableWidget *resultTable;

    void showResumes(const std::vector<Resume>& resumes);

};