#include "model.h"
#include "qobject.h"

Model::Model(QObject *parent) : QObject(parent){
    clientSocket = new QTcpSocket(this);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Model::clientCanReceive); //connect the client to start receiving from server
}

void Model::connectClientToServer(const QString &host, int port){
    clientSocket->connectToHost(host, port);
}

void Model::sendMessageToServer(const QString &message){
    if (clientSocket->state() == QAbstractSocket::ConnectedState) {
        clientSocket->write(message.toUtf8());
    }
}

void Model::clientCanReceive(){
    QByteArray data = clientSocket->readAll();
    QString receivedMessage = QString::fromUtf8(data);
    emit messageReceivedFromOtherClient(receivedMessage);
}
