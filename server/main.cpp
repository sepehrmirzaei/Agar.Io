#include <iostream>
#include "sourc/head/server.h"
#include "sourc/head/timemanage.h"
#include <QApplication>



using namespace std;

int main(int argc, char **argv) {
    QApplication *app = new QApplication(argc, argv);

    timer *timemachine=new timer;
    app -> exec();
    return 0;
}