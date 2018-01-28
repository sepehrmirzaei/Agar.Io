//
// Created by sepehr007 on 4/1/17.
//

#ifndef CHATROOM_CLIENT_LOGINMENU_H
#define CHATROOM_CLIENT_LOGINMENU_H

#include <QWidget>
#include <QtWidgets/QCheckBox>

class QHostAddress;
class QPushButton;
class QLineEdit;
class QSpinBox;
class loginmenu : public QWidget {
Q_OBJECT
public:
    loginmenu(QWidget * = 0);
private:
    QPushButton *login, *exit;
    QLineEdit *user, *address, *port;
    QCheckBox *chekbox;
    int i=0;
    QString situ="";
signals:
    void loginrequested(QHostAddress *, quint16, QString *);
    void AI(QString);
public slots:
    void requestlogin();
};
#endif //CHATROOM_CLIENT_LOGINMENU_H
