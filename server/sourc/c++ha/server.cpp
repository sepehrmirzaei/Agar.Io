//
// Created by mareal on 3/16/16.
//
#include "../head/server.h"
#include <QDialog>
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
using namespace std;

Server::Server(QHostAddress *serverAddress, quint16 serverPort) : serverAddress(serverAddress), serverPort(serverPort) {
    clients = new QList<QTcpSocket*>();
    server = new QTcpServer(this);
    server -> listen(*serverAddress, serverPort);
    connect(server,SIGNAL(newConnection()),this,SLOT(shit()));
    connect(server,SIGNAL(newConnection()), this, SLOT(createConnection()));

}

void Server::createConnection(){
    QTcpSocket *client = server -> nextPendingConnection();
    clients -> append(client);
    cout<<"yooo"<<endl;
    connect(client, SIGNAL(readyRead()), this, SLOT(read()));

    //if(clients -> size()==1)
        //timer();
}

void Server::read() {
    for(int i = 0;i < clients->size();i ++)
        if(clients -> at(i) -> bytesAvailable() > 0) {
            read(clients->at(i),i);

        }
}
void Server::read(QTcpSocket * client,int i) {
    //qDebug()<<"yoooo";
    QByteArray data = client -> readAll();
    QString sepehr=data;
    string sep=sepehr.toUtf8().constData();
    if(sep=="AI") {
        emit(aicreate(i));
        cout<<i<<endl;
    }
    else if(sep!="")
        emit whichclient(sepehr,i);
    //cout<<sep<<endl;
    //for(int j = 0;j < clients -> size();j ++)
      //  clients -> at(j) -> write(data);
}
void Server::sendback2(QByteArray finall,int j){


        clients->at(j)->write(finall);
        QString payam=finall;
        string sep=payam.toUtf8().constData();
        //cout<<sep<<endl;

}

void Server::shit()
{
    emit(shit2());
}
/*void Server::deletingusr(int usr)
{
    clients -> erase(clients -> begin()+usr-1,clients -> begin()+usr);
}*/