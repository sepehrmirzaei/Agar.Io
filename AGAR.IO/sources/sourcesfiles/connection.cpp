//
// Created by sepehr007 on 4/2/17.
//
#include "../headerfiles/connection.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <iostream>

using namespace std;
connection::connection(QHostAddress *serveraddress, quint16 serverport)
{
    socket= new QTcpSocket;
    socket -> connectToHost(*serveraddress, serverport);
    connect(socket, SIGNAL(readyRead()), this, SLOT(receivemessage()));
}
void connection::receivemessage()
{
    QString message=socket -> readAll();
    emit newrecievemessage(message);
}
void connection::sendmessage(QString message)
{
    QByteArray data=&message.toStdString()[0];
    socket-> write(data);
}
