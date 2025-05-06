#include "LoginWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QHeaderView>
LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent) {
    setupDatabase();

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("用户名");
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("邮箱（注册时填写）");
    roleCombo = new QComboBox(this); // 新增：角色选择下拉框
    roleCombo->addItem("学生", "student");
    roleCombo->addItem("招聘方", "employer");
    roleCombo->addItem("管理员", "admin");

    loginButton = new QPushButton("登录", this);
    registerButton = new QPushButton("注册", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(emailEdit);
    layout->addWidget(roleCombo);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::handleRegister);
}

void LoginWindow::setupDatabase() {
    db = QSqlDatabase::addDatabase("QODBC", "loginConnection");
    db.setDatabaseName("MySQL");
    db.setUserName("root");
    db.setPassword("20020904");
    if (!db.open()) {
        QMessageBox::critical(this, "错误", "数据库连接失败: " + db.lastError().text());
    }
}

void LoginWindow::handleLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        currentUser = User(
                query.value("user_id").toInt(),
                query.value("username").toString(),
                query.value("password").toString(),
                query.value("role").toString(),
                query.value("email").toString(),
                query.value("created_at").toDateTime()
        );
        accept(); // 登录成功，关闭对话框
    } else {
        QMessageBox::warning(this, "错误", "用户名或密码错误！");
    }
}

void LoginWindow::handleRegister() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString email = emailEdit->text();
    QString role = roleCombo->currentData().toString(); // 获取用户选择的角色

    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password, role, email, created_at) VALUES (:username, :password, :role, :email, NOW())");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":role", role);
    query.bindValue(":email", email);
    if (query.exec()) {
        QMessageBox::information(this, "成功", "注册成功，请登录！");
    } else {
        QMessageBox::warning(this, "错误", "注册失败：" + query.lastError().text());
    }
}

User LoginWindow::getCurrentUser() const {
    return currentUser;
}