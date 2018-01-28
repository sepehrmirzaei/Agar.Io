//
// Created by sepehr007 on 4/2/17.
//

#ifndef CHATROOM_CLIENT_CONNECTION_H
#define CHATROOM_CLIENT_CONNECTION_H

#include <QObject>
#include <QHostAddress>
class QTcpSocket;
class connection :public QObject
{
    Q_OBJECT
public:
    connection(QHostAddress * =new QHostAddress("127.0.0.1"), quint16 =4444);

private:
    QTcpSocket *socket;
    QHostAddress *serveraddress;
    quint16 serverport;
public slots:
    void receivemessage();
    void sendmessage(QString);
signals:
    void newrecievemessage(QString);
};


#endif //CHATROOM_CLIENT_CONNECTION_H
