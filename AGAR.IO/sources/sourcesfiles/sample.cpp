//
// Created by sepehr007 on 4/12/17.
//
#include "../headerfiles/sample.h"

samp::samp(QWidget *parent): QWidget(parent)
{
    setFixedSize(100, 50);
    send=new QPushButton("hello",this);
    send->setGeometry(10, 10, 80, 30);
}
