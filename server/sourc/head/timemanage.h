//
// Created by sepehr007 on 7/25/17.
//

#include <QtCore/QTimer>
#include "timer.h"
#include "server.h"

#ifndef SERVER_TIMEMANAGE_H
#define SERVER_TIMEMANAGE_H


class timer:QObject{
    Q_OBJECT
public:
    timer();

public slots:
    void semislot();
    void semislot2();
    void ais(int);
private:
    plan *myworld;
    Server *myserver;
    vector <int>ailist;
};
#endif //SERVER_TIMEMANAGE_H