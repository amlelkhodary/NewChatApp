#include "presenter.h"

Presenter::Presenter(QObject *parent) : QObject(parent){
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
    // connect(clientSocket,&QTcpSocket::readAll,this,&Presenter::messageReceivedFromOtherClient);
    emit messageReceivedFromOtherClient(receivedMessage);
}

void Presenter::createThreadForServer(){
    serverThread = new QThread(this);
    server = new TcpServer(); //No viable overloaded error when it's not a pointer
    server->moveToThread(serverThread);
    serverThread->start();
    connect(serverThread,&QThread::started,this,&Presenter::serverStarted);

    // emit serverStarted();
    // std::thread serverThread(&TcpServer::startTcpServer, &server);
    // serverThread.join();
}
