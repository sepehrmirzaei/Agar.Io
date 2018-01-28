//
// Created by sepehr007 on 7/25/17.
//

#include "../head/timemanage.h"
#include "../head/timer.h"
#include "../head/server.h"

timer::timer() {
    QTimer *foodtimer=new QTimer(this);
    QTimer *virustimer=new QTimer(this);
    QTimer *action=new QTimer(this);
    QTimer *aiaction=new QTimer(this);

    myworld=new plan();
    myserver=new Server();
    connect(myworld,SIGNAL(aioffer(QString,int)),myworld,SLOT(mousecalc(QString,int)));
    connect(myserver,SIGNAL(whichclient(QString,int)),myworld,SLOT(mousecalc(QString,int)));
    connect(myserver, SIGNAL(shit2()), myworld, SLOT(plancircle()));
    connect(myworld, SIGNAL(sendback(QByteArray,int)), myserver, SLOT(sendback2(QByteArray,int)));
    connect(myserver, SIGNAL(aicreate(int)), this, SLOT(ais(int)));

    connect(foodtimer, SIGNAL(timeout()),myworld, SLOT(planfood()));
    connect(virustimer, SIGNAL(timeout()), myworld, SLOT(planvirus()));
    connect(action, SIGNAL(timeout()), this, SLOT(semislot()));
    connect(aiaction, SIGNAL(timeout()), this, SLOT(semislot2()));
    foodtimer -> start(500);
    virustimer ->start(30000);
    action ->start(30);
    aiaction ->start(1000);


}
void timer::semislot()
{
    myworld -> next(myserver-> clients ->size());

}
void timer::semislot2() {
    for(int i=0;i<ailist.size();i++)
        myworld -> AI(ailist[i]);
}
void timer::ais(int j){
    ailist.push_back(j);
}