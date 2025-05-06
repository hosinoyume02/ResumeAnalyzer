#include <QApplication>
#include "MainWindow.h"
#include "LoginWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginWindow login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w(login.getCurrentUser());
        w.show();
        return app.exec();
    }
    return 0;
}