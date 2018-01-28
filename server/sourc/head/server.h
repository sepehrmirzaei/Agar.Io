//
// Created by mareal on 3/16/16.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <QUdpSocket>
#include <vector>
#include "timer.h"

using namespace std;
class QTimer;
class QHostAddress;
class QDialog;
class QTcpSocket;
class QTcpServer;
class Server : public QObject{
    Q_OBJECT
public:
    Server(QHostAddress * = new QHostAddress("127.0.0.1"), quint16 = 8888);
    void read(QTcpSocket*,int);
    QList<QTcpSocket*> *clients;
    QTcpServer *server;

public slots:
    void createConnection();
    void read();
    void sendback2(QByteArray,int);
    void shit();
    //void deletingusr(int);
private:
    QHostAddress *serverAddress;
    quint16 serverPort;


signals:
    void whichclient(QString,int);
    void shit2();
    void aicreate(int);


};
#endif //SERVER_SERVER_H
