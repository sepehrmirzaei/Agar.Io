//
// Created by sepehr007 on 4/3/17.
//

#ifndef CHATROOM_CLIENT_CLIENT_H
#define CHATROOM_CLIENT_CLIENT_H

#include <QObject>

#include "loginmenu.h"


class connection;
class interface;
class QHostAddress;

class client : public QObject
{
    Q_OBJECT
public:
    client();

private:
    connection *connector;
    loginmenu *logingin;

public slots:
    void loging(QHostAddress *, quint16 , QString *);
};

#endif //CHATROOM_CLIENT_CLIENT_H
