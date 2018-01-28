//
// Created by sepehr007 on 4/3/17.
//

#include "../headerfiles/client.h"

#include "../headerfiles/connection.h"
#include "../headerfiles/graphic view.h"
#include "../headerfiles/chatdesign.h"
#include "../headerfiles/loginmenu.h"

#include <QHostAddress>
#include <QGraphicsItem>

client::client()
{
    //interfacer=new interface(this);
    logingin=new loginmenu();
    connect(logingin, SIGNAL(loginrequested(QHostAddress *, quint16 , QString *)), this, SLOT(
            loging(QHostAddress *, quint16 , QString *)));
}
void client::loging(QHostAddress *hostAddress, quint16 port, QString *nameof)
{

    //chatdesign *chatroom=new chatdesign(*nameof);
    //chatroom->show();
    graphic *gameboard=new graphic;
    gameboard -> show();
    connector=new connection(hostAddress, port);
    //connect(chatroom, SIGNAL(sending(QString)), connector, SLOT(sendmessage(QString)));
    //connect(connector, SIGNAL(newrecievemessage(QString)),chatroom, SLOT(receive(QString)));
    connect(connector, SIGNAL(newrecievemessage(QString)),gameboard, SLOT(decode(QString)));
    connect(gameboard,SIGNAL(sendout(QString)),connector,SLOT(sendmessage(QString)));
    connect(logingin,SIGNAL(AI(QString)),connector,SLOT(sendmessage(QString)));

}
