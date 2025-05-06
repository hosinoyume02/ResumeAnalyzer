#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User {
public:
    int userId;
    QString username;
    QString password;
    QString role; // student, employer, admin
    QString email;
    QDateTime createdAt;

    User();
    User(int userId, const QString &username, const QString &password,
         const QString &role, const QString &email, const QDateTime &createdAt);
};

#endif // USER_H