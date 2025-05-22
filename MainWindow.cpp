#include "MainWindow.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

MainWindow::MainWindow(const User &user, QWidget *parent)
        : QMainWindow(parent), currentUser(user), filterWidget(new ResumeFilterWidget(this)) {
    setupDatabase();
    loadDataFromDatabase();
    filterWidget->setResumeManager(&manager);
    setupUI();
    resize(1000, 600);
    setWindowTitle("大学生就业推荐系统 - " + currentUser.username);
}

MainWindow::~MainWindow() {
    db.close();
}

void MainWindow::setupDatabase() {
    db = QSqlDatabase::addDatabase("QODBC", "mainConnection");
    db.setDatabaseName("MySQL");
    db.setUserName("root");
    db.setPassword("20020904");
    if (!db.open()) {
        QMessageBox::critical(this, "错误", "数据库连接失败: " + db.lastError().text());
    }
}

void MainWindow::loadDataFromDatabase() {
    QSqlQuery query(db);
    query.exec("SELECT resume_id, user_id, education, experience, skills, languages, created_at FROM resumes");
    while (query.next()) {
        Resume res(
                query.value(0).toInt(),
                query.value(1).toInt(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toDateTime()
        );
        manager.addResume(res);
    }
}

void MainWindow::setupUI() {
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    // 公共选项卡：简历筛选
    //   tabWidget->addTab(filterWidget, "简历筛选");

    // 根据角色显示不同选项卡
    if (currentUser.role == "student") {
        resumeWidget = new ResumeWidget(currentUser.userId, db, this);
        recommendationWidget = new RecommendationWidget(currentUser.userId, db, this);
        tabWidget->addTab(resumeWidget, "我的简历");
        tabWidget->addTab(recommendationWidget, "职位推荐");
    } else if (currentUser.role == "employer") {
        jobWidget = new JobWidget(currentUser.userId, db, this);
        tabWidget->addTab(filterWidget, "简历筛选");
        tabWidget->addTab(jobWidget, "职位管理");
    } else if (currentUser.role == "admin") {
        adminWidget = new AdminWidget(db, this);
        tabWidget->addTab(filterWidget, "简历筛选");
        tabWidget->addTab(adminWidget, "系统管理");
    }
}