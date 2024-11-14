#include "presenter.h"

Presenter::Presenter(QObject *parent) : QObject(parent), server(parent){
    clientSocket = new QTcpSocket(this);
    // Move the client socket to the current (main) thread
    // clientSocket->moveToThread(QThread::currentThread());
    connect(clientSocket, &QTcpSocket::readyRead, this, &Presenter::clientCanReceiveMessages);
}

void Presenter::connectClientToServer(const QString &host, int port){
    clientSocket->connectToHost(host, port);
}
void Presenter::sendMessageToServer(const QString &message){
    if (clientSocket->state() == QAbstractSocket::ConnectedState) {
        // QString formattedMessage = "User: " + message;
        clientSocket->write(message.toUtf8()); //Send message to server
    }
}
void Presenter::clientCanReceiveMessages(){
    QByteArray data = clientSocket->readAll();
    QString receivedMessage = QString::fromUtf8(data);
    emit messageReceivedFromOtherClient(receivedMessage);
}

void Presenter::createThreadForServer(){
    std::thread serverThread(&TcpServer::startTcpServer, &server);
    serverThread.join();
    connect(&server,&TcpServer::threadCompleted,this,&Presenter::serverStarted);
}
