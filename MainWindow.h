#ifndef RESUME_ANALYZER_MAINWINDOW_H
#define RESUME_ANALYZER_MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "resume_repository.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onFilterClicked();

private:
    QLineEdit *keywordInput;
    QPushButton *filterButton;
    QTableWidget *resultTable;
    ResumeRepository repo;

    void displayResumes(const std::vector<Resume> &resumes);
};

#endif // RESUME_ANALYZER_MAINWINDOW_H
