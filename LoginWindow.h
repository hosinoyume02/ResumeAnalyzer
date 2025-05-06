#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QtSql/QSqlDatabase>
#include "User.h"

class LoginWindow : public QDialog {
Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    User getCurrentUser() const;

private slots:
    void handleLogin();
    void handleRegister();

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *emailEdit;
    QComboBox *roleCombo; // 新增：角色选择下拉框
    QPushButton *loginButton;
    QPushButton *registerButton;
    QSqlDatabase db;
    User currentUser;

    void setupDatabase();
};

#endif // LOGINWINDOW_H