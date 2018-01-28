#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "sources/headerfiles/chatdesign.h"
#include "sources/headerfiles/loginmenu.h"
#include "sources/headerfiles/client.h"
#include<QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
using namespace std;
int main(int argc,char **argv)
{
    QApplication app(argc, argv);
    //loginmenu *dard=new loginmenu();
    //dard -> show();
    //loginmenu *logingin=new loginmenu();
    //timer();
    new client;

    //QString sss="50,50,100,2E400,200,30,1,300,100,20,3E250,400,150,1";
    //graphic front(sss);
    //front.show();



    return app.exec();

}