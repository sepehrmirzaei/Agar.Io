//
// Created by sepehr007 on 4/1/17.
//
#include "../headerfiles/loginmenu.h"
#include "../headerfiles/chatdesign.h"
#include <QPushButton>
#include <QApplication>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QHostAddress>
#include <iostream>
#include "../headerfiles/loginmenu.h"

using namespace std;
loginmenu::loginmenu(QWidget *parent) :QWidget(parent)
{
    QRect rec = QApplication::desktop() -> screenGeometry();
    setGeometry(500,300,400,300);
    exit =new QPushButton("EXIT",this);
    login=new QPushButton("Login", this);
    QDialogButtonBox *buttonarea=new QDialogButtonBox;
    buttonarea -> addButton(exit, QDialogButtonBox::RejectRole);
    buttonarea -> addButton(login, QDialogButtonBox::ActionRole);
    user=new QLineEdit("unknown");
    QLabel *userlab = new QLabel("username : ");
    QHBoxLayout *userbox =new QHBoxLayout;
    userbox -> addWidget(userlab);
    userbox -> addWidget(user);
    address=new QLineEdit("localhost");
    QLabel *addlab = new QLabel("server IP : ");
    QHBoxLayout *addressbox =new QHBoxLayout;
    addressbox -> addWidget(addlab);
    addressbox -> addWidget(address);

    port=new QLineEdit("8888");
    QLabel *portlab = new QLabel("server port : ");
    QHBoxLayout *portbox =new QHBoxLayout;
    portbox -> addWidget(portlab);
    portbox -> addWidget(port);

    chekbox=new QCheckBox;
    QLabel *ai=new QLabel("AI ?");
    QHBoxLayout *aibox =new QHBoxLayout;
    aibox ->addWidget(ai);
    aibox ->addWidget(chekbox);


    QVBoxLayout *mainmap=new QVBoxLayout;
    mainmap -> addLayout(userbox);
    mainmap -> addLayout(addressbox);
    mainmap -> addLayout(portbox);
    mainmap -> addLayout(aibox);
    mainmap -> addWidget(buttonarea);

    setLayout(mainmap);
    connect(exit, SIGNAL(clicked()), this, SLOT(close()));
    connect(login, SIGNAL(clicked()), this, SLOT(requestlogin()));
    show();

}
void loginmenu::requestlogin()
{
    QString serveraddress=address -> text()=="localhost" ? "127.0.0.1" : address -> text();
    //this -> hide();

    if(chekbox->isChecked()) {
        situ="AI";
        emit(AI(situ));
        emit loginrequested(new QHostAddress(serveraddress), port -> text().toUShort(), new QString(user ->text()));
    }
    else {
        emit(AI(situ));
        emit loginrequested(new QHostAddress(serveraddress), port->text().toUShort(), new QString(user->text()));
    }
    //const QString usr=user ->text();
}
