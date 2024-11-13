#include "presenter.h"
Presenter::Presenter(QObject *parent) : QObject(parent){
    model = new Model(this);
}
void Presenter::sendMessageFromClientToServer(const QString &message){
    model->sendMessageToServer(message);
}

void Presenter::connectClient(const QString &ip, int port){
    model->connectClientToServer(ip,port);
}
