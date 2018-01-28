//
// Created by sepehr007 on 4/1/17.
//

#ifndef CHATROOM_CLIENT_CHATDESIGN_H
#define CHATROOM_CLIENT_CHATDESIGN_H
#include <QtWidgets/QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QShortcut>
#include <QFileInfo>
#include <QObject>
#include <QMediaPlayer>


class chatdesign : public  QWidget {

Q_OBJECT

public:
    explicit chatdesign(QString , QWidget *parent =0);

private:
    QTextEdit *screen, *typearea;
    QPushButton *send;
    QString name;

public slots:

    void receive(QString);

    void creating();

signals :
    void sending(QString);

};
#endif
