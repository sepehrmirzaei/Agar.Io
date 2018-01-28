//
// Created by sepehr007 on 4/1/17.
//
#include "../headerfiles/chatdesign.h"

#include <QAudioOutput>
#include <iostream>
#include <QPainter>
#include <QMouseEvent>
using namespace std;

chatdesign::chatdesign(QString name, QWidget *parent): QWidget(parent) , name(name)
{
    QRect rec = QApplication::desktop() -> screenGeometry();
    setGeometry(500, 100, 350, 400);
    QLabel *usrname=new QLabel(name);


//    QMouseEvent event;
  //  QPoint point= event.pos();



    screen=new QTextEdit;
    screen -> setReadOnly(true);
    screen -> setFixedHeight(300);
    typearea=new QTextEdit;
    typearea -> setFixedHeight(80);
    send=new QPushButton("send");
    send -> setFixedSize(60,30);
    connect(send, SIGNAL(clicked()),this,SLOT(creating()));
    QVBoxLayout *plan= new QVBoxLayout;
    plan -> addWidget(usrname);
    plan -> addWidget(screen);
    plan -> addWidget(typearea);
    plan -> addWidget(send);
    setLayout(plan);


}
void chatdesign::receive(QString message)
{
    screen ->append(message);
}
void chatdesign::creating()
{
    QString message=typearea -> toPlainText();
    typearea -> clear();
    if (message.size()>0)
        emit sending(name+" : "+message);
}




