//
// Created by sepehr007 on 4/12/17.
//

#ifndef CHATROOM_CLIENT_SAMPLE_H
#define CHATROOM_CLIENT_SAMPLE_H

#include <QtWidgets/QWidget>
#include <QPushButton>
class samp : public QWidget
{
Q_OBJECT
public:
    explicit samp(QWidget *parent=0);

private:
    QPushButton *send;
};

#endif //CHATROOM_CLIENT_SAMPLE_H
