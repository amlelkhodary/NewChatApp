#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // uint32_t x=0x2E5BF271;
    // uint8_t* ptr = (uint8_t*) &x;
    // qDebug() <<* ptr;
    // int y= 6;
    // ptr++;
    // *ptr = 7;
    // ptr = nullptr;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
