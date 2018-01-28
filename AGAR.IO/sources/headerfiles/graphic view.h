//
// Created by sepehr007 on 7/6/17.
//

#ifndef AGAR_IO_GRAPHIC_VIEW_HQ_OBJECT
#define AGAR_IO_GRAPHIC_VIEW_H

#include <QMouseEvent>
#include <QtWidgets/QWidget>
#include <QDesktopWidget>
#include <QWidget>
#include <QPaintEvent>
#include <QGraphicsWidget>
#include <sstream>
#include <QtWidgets/QTextEdit>

using namespace std;
class graphic : public QWidget {
    Q_OBJECT
public:
    graphic(QWidget * = 0);

    void paintEvent(QPaintEvent * event);
    void mousePressEvent( QMouseEvent* ev );
    stringstream finalsitu;
private:
    //string situation;
    //int circles[100]={0},viruses[48]={0},foods[1000]={0};
    QPaintEvent *event;
    QMouseEvent *ev;
    QString situa;
    QTextEdit *result;
public slots:
    void decode(QString);
    void sendData(QPoint ,int);

signals:
    void mousePressed(QPoint,int);
    void sendout(QString);

};
#endif //AGAR_IO_GRAPHIC_VIEW_H
