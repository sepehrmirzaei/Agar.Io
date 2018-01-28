//
// Created by sepehr007 on 7/12/17.
//
#include <iostream>

#include <ctime>
#include <time.h>
#include <QObject>
#include <sys/socket.h>
#include "../head/timer.h"
#include <math.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <sstream>

using namespace std;



void plan::planfood()
{
    srand(time(0));
    foods.push_back(rand()%500);
    foods.push_back(rand()%500);
    foods.push_back(8);
    foods.push_back(rand()%16);

}
void plan::planvirus()
{
    srand(time(0));
    viruses.push_back(rand()%500);
    viruses.push_back(rand()%500);
    viruses.push_back(50);
    viruses.push_back(6);

}
void plan::plancircle()
{
    srand(time(0));
    circles.push_back(rand()%500);
    circles.push_back(rand()%500);
    circles.push_back(30);
    circles.push_back(rand()%16);
    speeds.push_back(0);
    speeds.push_back(0);
}
void plan::mousecalc(QString order,int k) {

    stringstream mousedata(order.toStdString());
    float mousex,mousey,type;
    mousedata>>mousex>>mousey>>type;
    if(type==1){
        float sin,cos;
        cos=sqrt(1/(1+pow(mousey/mousex,2)));
        sin=sqrt(1/(1+pow(mousex/mousey,2)));
        speeds[2*k]=150*cos;
        speeds[2*k+1]=150*sin;
        if(mousex<0)
            speeds[2*k]=-speeds[2*k];
        if(mousey<0)
            speeds[2*k+1]=-speeds[2*k+1];

    }
    else if(type==2)
    {
        if(circles[4*k+2]>50) {
            mass.push_back(circles[4 * k]);
            mass.push_back(circles[4 * k + 1]);
            mass.push_back(20);
            mass.push_back(0);
            mass.push_back(0);
            speedmass.push_back(2*speeds[2*k]);
            speedmass.push_back(2*speeds[2*k+1]);
            speedmass.push_back(circles[4 * k]);
            speedmass.push_back(circles[4 * k + 1]);
            speedmass.push_back(circles[4 * k + 2]);
            //cout<<"speed x ="<<speedmass[5*k]<<"speed y = "<<speedmass[5*k+1]<<endl;
            circles[4*k+2]=sqrt(pow(circles[4*k+2],2)-400);
        }
    }
    else if(type==3)
    {
        if(circles[4*k+2]>60) {
            subcircles.push_back(circles[4 * k]);
            subcircles.push_back(circles[4 * k + 1]);
            subcircles.push_back(float(sqrt(2)) * circles[4 * k + 2] / 2);
            subcircles.push_back(float(k));
            subcircles.push_back(0);
            speedsubs.push_back(5 * speeds[2 * k]/2);
            speedsubs.push_back(5 * speeds[2 * k + 1]/2);
            speedsubs.push_back(circles[4 * k]);
            speedsubs.push_back(circles[4 * k + 1]);
            speedsubs.push_back(circles[4 * k + 2]);
            circles[4 * k + 2] = circles[4 * k + 2] * float(sqrt(2)) / 2;
        }
    }

}

void plan::next(int sizee){

    // speed calculate

    for(int i=0;i<speeds.size();i+=2){
        if(0<circles[2*i]+speeds[i]/circles[2*i+2] and circles[2*i]+speeds[i]/circles[2*i+2]<500)
            circles[2*i]+=speeds[i]/circles[2*i+2];
        if(0<circles[2*i+1]+speeds[i+1]/circles[2*i+2] and circles[2*i+1]+speeds[i+1]/circles[2*i+2]<500)
            circles[2*i+1]+=speeds[i+1]/circles[2*i+2];
        //cout<<"circl x ="<<circles[2*i]<<"   "<<"circle y ="<<"  "<<circles[2*i+1]<<endl;

    }
    for(int i=0;i<subcircles.size();i+=5)
    {
        if(subcircles[i+4]==0)
            movesubs(i);
        else if(subcircles[i+4]==1)
        {
            if(0<subcircles[i]+speeds[2*subcircles[i+3]]/circles[4*subcircles[i+3]+2] and subcircles[i]+speeds[2*subcircles[i+3]]/circles[4*subcircles[i+3]+2]<500)
                subcircles[i]+=speeds[2*subcircles[i+3]]/subcircles[i+2];
            if(0<subcircles[i+1]+speeds[2*subcircles[i+3]+1]/circles[4*subcircles[i+3]+2] and subcircles[i+1]+speeds[2*subcircles[i+3]+1]/circles[4*subcircles[i+3]+2]<500)
                subcircles[i+1]+=speeds[2*subcircles[i+3]+1]/subcircles[i+2];
        }
    }
    for(int i=0;i<circles.size();i+=4)
    {
        if(circles[i+2]==0) {
            circles[i]=-500;
            circles[i+1]=-500;
        }
    }

    // eating foods

    for(int i=0;i<circles.size();i+=4){
        for(int j=0;j<foods.size();j+=4)
        {
            if(pow(circles[i]-foods[j],2)+pow(circles[i+1]-foods[j+1],2)<pow(circles[i+2]/2+foods[j+2]/2,2)){
                circles[i+2]=sqrt(pow(circles[i+2],2)+pow(foods[j+2],2));
                foods.erase(foods.begin()+j,foods.begin()+j+4);
                j-=4;
            }
        }
    }
    for(int i=0;i<subcircles.size();i+=5){
        for(int j=0;j<foods.size();j+=4)
        {
            if(pow(subcircles[i]-foods[j],2)+pow(subcircles[i+1]-foods[j+1],2)<pow(subcircles[i+2]/2+foods[j+2]/2,2)){
                subcircles[i+2]=sqrt(pow(subcircles[i+2],2)+pow(foods[j+2],2));
                foods.erase(foods.begin()+j,foods.begin()+j+4);
                j-=4;
            }
        }
    }
    for(int i=0;i<circles.size();i+=4){
        for(int j=0;j<mass.size();j+=5)
        {
            if(pow(circles[i]-mass[j],2)+pow(circles[i+1]-mass[j+1],2)<pow(circles[i+2]/2+mass[j+2]/2,2) and mass[j+4]==1){
                circles[i+2]=sqrt(pow(circles[i+2],2)+400);
                mass.erase(mass.begin()+j,mass.begin()+j+5);
                speedmass.erase(speedmass.begin()+j,speedmass.begin()+j+5);
                j-=5;
            }
        }
    }
    for(int i=0;i<subcircles.size();i+=5){
        for(int j=0;j<mass.size();j+=5)
        {
            if(pow(subcircles[i]-mass[j],2)+pow(subcircles[i+1]-mass[j+1],2)<pow(subcircles[i+2]/2+mass[j+2]/2,2) and mass[j+4]==1){
                subcircles[i+2]=sqrt(pow(subcircles[i+2],2)+400);
                mass.erase(mass.begin()+j,mass.begin()+j+5);
                speedmass.erase(speedmass.begin()+j,speedmass.begin()+j+5);
                j-=5;
            }
        }
    }

    eatcircle();
    sendingdata(sizee);
    movemass();

}
void plan::sendingdata(int sizeee){
    string holedata="";
    for(int j = 0;j<sizeee;j ++)
    {
        holedata+=to_string(int(circles[4*j]))+' '+to_string(int(circles[4*j+1]))+' '+to_string(int(circles[4*j+2]))+' '+to_string(int(circles[4*j+3]))+' ';
        for(int i=0;i<subcircles.size();i+=5)
        {
            if(subcircles[i+3]==j and abs(circles[4*j]-subcircles[i])<250 and abs(circles[4*j+1]-subcircles[i+1])<250)
                holedata+=to_string(int(subcircles[i]-circles[4*j]+250))+' '+to_string(int(subcircles[i+1]-circles[4*j+1]+250))+' '+to_string(int(subcircles[i+2]))+' '+to_string(int(5000))+' ';
        }
        holedata+=to_string(-100000)+' ';
        for(int i=0;i<foods.size();i+=4)
        {

            if(abs(circles[4*j]-foods[i])<250 and abs(circles[4*j+1]-foods[i+1])<250)
            {
                holedata+=to_string(int(foods[i]-circles[4*j]+250))+' '+to_string(int(foods[i+1]-circles[4*j+1]+250))+' '+to_string(int(foods[i+2]))+' '+to_string(int(foods[i+3]))+' ';

            }
        }
        holedata+=to_string(-100000)+' ';
        for(int i=0;i<circles.size();i+=4)
        {
            if(i!=4*j and abs(circles[4*j]-circles[i])<250 and abs(circles[4*j+1]-circles[i+1])<250)
            {
                holedata+=to_string(int(circles[i]-circles[4*j]+250))+' '+to_string(int(circles[i+1]-circles[4*j+1]+250))+' '+to_string(int(circles[i+2]))+' '+to_string(int(circles[i+3]))+' ';

            }
        }

        holedata+=to_string(-100000)+' ';
        for(int i=0;i<mass.size();i+=5)
        {
            if(abs(circles[4*j]-mass[i])<250 and abs(circles[4*j+1]-mass[i+1])<250)
            {
                holedata+=to_string(int(mass[i]-circles[4*j]+250))+' '+to_string(int(mass[i+1]-circles[4*j+1]+250))+' '+to_string(int(mass[i+2]))+' '+to_string(int(mass[i+3]))+' ';

            }
        }
        holedata+=to_string(-100000)+' ';
        for(int i=0;i<viruses.size();i+=4)
        {

            if(abs(circles[4*j]-viruses[i])<250 and abs(circles[4*j+1]-viruses[i+1])<250)
            {
                holedata+=to_string(int(viruses[i]-circles[4*j]+250))+' '+to_string(int(viruses[i+1]-circles[4*j+1]+250))+' '+to_string(int(viruses[i+2]))+' '+to_string(int(viruses[i+3]))+' ';

            }
        }
        holedata+=to_string(-100000);
        QString sepehr=QString::fromStdString(holedata);
        QByteArray data=&sepehr.toStdString()[0];
        emit(sendback(data,j));
        holedata="";
    }

}



void plan::eatcircle() {
    for(int i=0;i<circles.size();i+=4)
    {
        for(int j=0;j<circles.size();j+=4) {
            if (i!=j and pow(circles[i] - circles[j], 2) + pow(circles[i + 1] - circles[j + 1], 2) < pow(circles[i + 2] / 2, 2) and circles[i + 2] / 2> 7 * (circles[j + 2]) / 10) {
                circles[i + 2] = sqrt(pow(circles[i+ 2], 2) + pow(circles[j + 2], 2));
                circles[j + 2] = 0;
            }
        }
    }
    for(int i=0;i<circles.size();i+=4)
    {
        for(int j=0;j<subcircles.size();j+=5) {
            if (i/4!=subcircles[j+3] and pow(circles[i] - subcircles[j], 2) + pow(circles[i + 1] - subcircles[j + 1], 2) < pow(circles[i + 2] / 2, 2) and circles[i + 2] / 2> 7 * (circles[j + 2]) / 10) {
                circles[i + 2] = sqrt(pow(circles[i+ 2], 2) + pow(subcircles[j + 2], 2));
                subcircles.erase(subcircles.begin()+j,subcircles.begin()+j+5);
                speedsubs.erase(speedsubs.begin()+j,speedsubs.begin()+j+5);
                j-=5;
            }
            else if(i/4==int(subcircles[j+3]) and pow(circles[i] - subcircles[j], 2) + pow(circles[i + 1] - subcircles[j + 1], 2) < pow(circles[i + 2] / 2, 2) and subcircles[j+4]==1)
            {
                circles[i + 2] = sqrt(pow(circles[i+ 2], 2) + pow(subcircles[j + 2], 2));
                subcircles.erase(subcircles.begin()+j,subcircles.begin()+j+5);
                speedsubs.erase(speedsubs.begin()+j,speedsubs.begin()+j+5);
                j-=5;
            }
        }
    }
    for(int i=0;i<subcircles.size();i+=5)
    {
        for(int j=0;j<circles.size();j+=4) {
            if (j/4!=int(subcircles[i+3]) and pow(subcircles[i] - circles[j], 2) + pow(subcircles[i + 1] - circles[j + 1], 2) < pow(subcircles[i + 2] / 2, 2) and subcircles[i + 2] / 2> 7 * (circles[j + 2]) / 10) {
                subcircles[i + 2] = sqrt(pow(subcircles[i+ 2], 2) + pow(circles[j + 2], 2));
                circles[j + 2] = 0;
            }
        }
    }
    for(int i=0;i<subcircles.size();i+=5)
    {
        for(int j=0;j<subcircles.size();j+=5) {
            if (pow(subcircles[i] - subcircles[j], 2) + pow(subcircles[i + 1] - subcircles[j + 1], 2) < pow(subcircles[i + 2] / 2, 2) and subcircles[i + 2] / 2> 7 * (subcircles[j + 2]) / 10) {
                subcircles[i + 2] = sqrt(pow(subcircles[i+ 2], 2) + pow(subcircles[j + 2], 2));
                subcircles.erase(subcircles.begin()+j,subcircles.begin()+j+5);
                speedsubs.erase(speedsubs.begin()+j,speedsubs.begin()+j+5);
                j-=5;
            }
        }
    }

}


void plan::movemass() {

    for(int i=0;i<mass.size();i+=5) {
        if(pow(abs(mass[i]-speedmass[i+2]),2)+pow(abs(mass[i+1]-speedmass[i+3]),2)<pow(speedmass[i+4]+40,2))
        {
            mass[i]+=speedmass[i]/20;
            mass[i+1]+=speedmass[i+1]/20;
            if(mass[i]<0)
                mass[i]=0;
            else if(mass[i]>500)
                mass[i]=500;
            if(mass[i+1]<0)
                mass[i+1]=0;
            else if(mass[i+1]>500)
                mass[i+1]=500;

        }
        else
            mass[i+4]=1;
    }
}

void plan::movesubs(int i) {

    if(pow(abs(subcircles[i]-speedsubs[i+2]),2)+pow(abs(subcircles[i+1]-speedsubs[i+3]),2)<pow(speedsubs[i+4]+60,2))
    {
        subcircles[i]+=speedsubs[i]/subcircles[2];
        subcircles[i+1]+=speedsubs[i+1]/subcircles[2];
        if(subcircles[i]<0)
            subcircles[i]=0;
        else if(subcircles[i]>500)
            subcircles[i]=500;
        if(subcircles[i+1]<0)
            subcircles[i+1]=0;
        else if(subcircles[i+1]>500)
            subcircles[i+1]=500;
    }
    else
        subcircles[i+4]=1;
}

void plan::AI(int usr) {
    float x=-1,y=-1,num=-1,distance=2000;
    //cout<<"nubbber"<<"  "<<usr<<endl;
    for(int i=0;i<circles.size();i+=4)
    {
        if(4*usr!=i and 7*circles[i+2]<5*circles[4*usr+2] and sqrt(pow(circles[4*usr]-circles[i],2)+pow(circles[4*usr+1]-circles[i+1],2)<distance))
        {
            string chek="yes";
            for (int k=0;k<circles.size();k+=4)
            {
                if(4*usr!=k and abs(circles[k]-circles[i])<50 and abs(circles[k+1]-circles[i+1])<50 and circles[k+2]>circles[4*usr+2]) {
                    chek = "no";
                    break;
                }
            }
            if(chek=="yes") {
                distance = sqrt(pow(circles[4 * usr] - circles[i], 2) + pow(circles[4 * usr + 1] - circles[i + 1], 2));
                x = circles[i]-circles[4*usr];
                y = circles[i + 1]-circles[4*usr+1];
            }
        }
    }
    if(x!=-1 or y!=-1){
        QString offer;
        offer=QString::fromLocal8Bit((to_string(x) + ' ' + to_string(y) + ' ' + std::to_string(1)).c_str());
        emit(aioffer(offer,usr));
    }
    else {
        for (int i = 0; i < subcircles.size(); i += 5) {
            if (usr != subcircles[i + 4] and 7 * subcircles[i + 2] < 5 * circles[4 * usr + 2] and
                sqrt(pow(circles[4 * usr] - subcircles[i], 2) + pow(circles[4 * usr + 1] - subcircles[i + 1], 2) <
                     distance)) {
                string chek = "yes";
                for (int k = 0; k < circles.size(); k += 4) {
                    if (abs(circles[k] - subcircles[i]) < 50 and abs(circles[k + 1] - subcircles[i + 1]) < 50 and
                        circles[k + 2] > circles[4 * usr + 2]) {
                        chek = "no";
                        break;
                    }
                }
                if (chek == "yes") {
                    distance = sqrt(pow(circles[4 * usr] - subcircles[i], 2) + pow(circles[4 * usr + 1] - subcircles[i + 1], 2));
                    x = subcircles[i]-circles[4*usr];
                    y = subcircles[i + 1]-circles[4*usr+1];
                }
            }
        }
        if(x!=-1 or y!=-1) {
            QString offer;
            offer = QString::fromLocal8Bit((to_string(x) + ' ' + to_string(y) + ' ' + std::to_string(1)).c_str());
            emit(aioffer(offer, usr));
        }
        else{
            for (int i = 0; i < foods.size(); i += 4) {
                if (sqrt(pow(circles[4 * usr] - foods[i], 2) + pow(circles[4 * usr + 1] - foods[i + 1], 2) < distance)) {
                    string chek = "yes";
                    for (int k = 0; k < circles.size(); k += 4) {
                        if (4*usr!=k and abs(circles[k] - foods[i]) < 50 and abs(circles[k + 1] - foods[i + 1]) < 50 and circles[k + 2] > circles[4 * usr + 2]) {
                            chek = "no";
                            break;
                        }
                    }
                    if (chek == "yes") {
                        distance = sqrt(pow(circles[4 * usr] - foods[i], 2) + pow(circles[4 * usr + 1] - foods[i + 1], 2));
                        x = foods[i]-circles[4*usr];
                        y = foods[i + 1]-circles[4*usr+1];
                    }
                }
            }
            if(x!=-1 or y!=-1) {
                QString offer;
                offer = QString::fromLocal8Bit((to_string(x) + ' ' + to_string(y) + ' ' + std::to_string(1)).c_str());
                emit(aioffer(offer, usr));
            }
        }
    }


}
