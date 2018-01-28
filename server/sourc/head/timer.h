//
// Created by sepehr007 on 7/12/17.
//

#ifndef SERVER_TIMER_H
#define SERVER_TIMER_H


#include <vector>
#include <QTimer>
#include <QtCore/QObject>
#include <cstdlib>

using namespace std;
class plan: public QObject
{
Q_OBJECT
public:
    void sendingdata(int);
    void eatcircle();
    void movemass();
    void movesubs(int);
    void AI(int);
public slots:
    void planfood();
    void planvirus();
    void plancircle();
    void mousecalc(QString,int);
    void next(int);
private:
    vector <float>foods;
    vector <float>viruses;
    vector <float>circles;
    vector <float>mass;
    vector <float>speeds;
    vector <float>speedmass;
    vector <float>subcircles;
    vector <float>speedsubs;
    vector <float>bestmove;
signals:
    void sendback(QByteArray,int);
    void aioffer(QString,int);
};





#endif //SERVER_TIMER_H

