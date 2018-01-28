//
// Created by sepehr007 on 7/6/17.
//
#include <iostream>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include "../headerfiles/graphic view.h"
#include <QPoint>
#include <QPalette>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <sstream>

using namespace std;
graphic::graphic(QWidget *parent) :QWidget(parent){
    connect(this,SIGNAL(mousePressed(QPoint,int)),this,SLOT(sendData(QPoint,int)));
    setGeometry(0,0,500,500);


}

void graphic::decode(QString situ) {
    //situation=situ.toStdString();
    ////////////////////
    situa=situ;
    update();
    /*int x ,y,r,c;
    finalsitu >>x>>y>>r>>c;
    cout<<x<<"  "<<y<<"  "<<r<<"  "<<c<<endl;
    update();*/

}
    /////////////////////
    /*int j=0,c=0,f=0,v=0;
    for(int i=0;i<situation.size();i++) {
        if (situation[i] != 'E' and j == 0) {
            if (situation[i] != ',')
                circles[c] = circles[c] * 10 + int(situation[i]) - 48;
            else
                c++;
        }
        else if (situation[i] == 'E' and j == 0)
            j++;
        else if (situation[i] != 'E' and j == 1) {
            if (situation[i] != ',')
                circles[c] = circles[c] * 10 + int(situation[i]) - 48;
            else
                c++;
        }
        else if (situation[i] == 'E' and j == 1)
            j++;
        else if (situation[i] != 'E' and j == 2) {
            if (situation[i] != ',')
                foods[f] = foods[f] * 10 + int(situation[i]) - 48;
            else
                f++;
        }
        else if (situation[i] == 'E' and j == 2)
            j++;
        else {
            if (situation[i] != ',')
                viruses[v]=viruses[v]*10 + int(situation[i])-48;
            else
                v++;
        }
    }
}*/
QColor color(int n)
{
    if(n==0)
        return Qt::black;
    if(n==1)
        return Qt::white;
    if(n==2)
        return Qt::darkGray;
    if(n==3)
        return Qt::gray;
    if(n==4)
        return Qt::lightGray;
    if(n==5)
        return Qt::red;
    if(n==6)
        return Qt::green;
    if(n==7)
        return Qt::blue;
    if(n==8)
        return Qt::cyan;
    if(n==9)
        return Qt::magenta;
    if(n==10)
        return Qt::yellow;
    if(n==11)
        return Qt::darkRed;
    if(n==12)
        return Qt::darkGreen;
    if(n==13)
        return Qt::darkBlue;
    if(n==14)
        return Qt::darkCyan;
    if(n==15)
        return Qt::darkMagenta;
    if(n==16)
        return Qt::darkYellow;
}
void graphic::paintEvent(QPaintEvent *) {

    stringstream finalsitu(situa.toStdString());
    int type = -1;
    while (!finalsitu.eof()) {
        // me
        if (type == -1) {
            int x, y,r,c;
            finalsitu >> x;
            if (x == -100000) {
                type++;
                continue;
            }
            finalsitu >>y>>r>>c;
            QPainter painter1(this);
            if(c<500) {
                painter1.setPen(color(c));
                painter1.setBrush(color(c));
            }
            if(r==0)
            {
                return;
            }

            if(c==5000)
                painter1.drawEllipse(x- r/2, y - r/2, r, r);
            else {
                painter1.drawEllipse(width() / 2 - r / 2, height() / 2 - r / 2, r, r);

            }
            type++;
        }
        // foods
        if (type == 0) {
            int x, y, r, c;
            finalsitu>> x;
            if (x == -100000) {
                type++;
                continue;
            }
            finalsitu >> y >> r >> c;
            QPainter painter2(this);
            //cout<<x<<"  "<<y<<"  "<<r<<"  "<<c<<endl;
            painter2.setPen(color(c));
            painter2.setBrush(color(c));
            painter2.drawEllipse(x - r/2, y - r/2, r, r);
        }
        // circles
        if (type == 1) {
            int x, y, r, c;

            finalsitu>>x;
            if (x == -100000) {
                type++;
                continue;
            }
            finalsitu >> y >> r >> c;
            QPainter painter3(this);
            painter3.setPen(color(c));
            painter3.setBrush(color(c));
            painter3.drawEllipse(x - r/2, y - r/2, r, r);
        }
        //mass
        if (type == 2) {
            int x, y, r, c;

            finalsitu>>x;
            if (x == -100000) {
                type++;
                continue;
            }
            finalsitu >> y >> r >> c;
            QPainter painter4(this);
            painter4.setPen(color(c));
            painter4.setBrush(color(c));
            painter4.drawEllipse(x - r/2, y - r/2, r, r);
        }

        // virus
        if (type == 3) {
            int x, y, r, c;
            finalsitu >> x;
            if (x == -100000) {
                return;
            }
            cout<<"yees!";
            finalsitu >> y >> r >> c;
            cout<<x<<"  "<<y<<"  "<<r<<"  "<<c<<endl;
            QPainter painter5(this);
            painter5.setBrush(Qt::CrossPattern);
            painter5.setBrush(color(c));
            painter5.drawEllipse(x - r/2, y - r/2, r, r);
        }



    }
}

void graphic::mousePressEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    int type=4;
    if(ev->buttons() == Qt::RightButton)
        type=2;
    if(ev->buttons() == Qt::LeftButton)
        type=1;
    if(ev->buttons() == Qt::MidButton)
        type=3;
    emit mousePressed(p,type );
}
void graphic::sendData(QPoint p,int type) {
    std::string sx = std::to_string(p.x()-width()/2);
    std::string sy = std::to_string(p.y()-height()/2);
    QString q = QString::fromLocal8Bit((sx + ' ' + sy + ' ' + std::to_string(type)).c_str());
    emit sendout(q);
}