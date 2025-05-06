#include "User.h"

User::User() {}

User::User(int userId, const QString &username, const QString &password,
           const QString &role, const QString &email, const QDateTime &createdAt)
        : userId(userId), username(username), password(password),
          role(role), email(email), createdAt(createdAt) {}