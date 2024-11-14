#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent) {
    serverSocket = new QTcpServer(this); //QTcp instance
    connect(serverSocket, &QTcpServer::newConnection, this, &TcpServer::handleClientConnection);  //Function to handle new client conection

    QString ipAddress = "127.0.0.1"; // Replace with your desired IP address
    QHostAddress hostAddress(ipAddress);
    quint16 port = 1235;
    if (!serverSocket->listen(hostAddress, port)) {
        qCritical() << "Server failed to start!";
        return;
    }
    qDebug() << "Server started on IP" << ipAddress << "and port "<<port;

}
void TcpServer::startTcpServer(){
    serverSocket = new QTcpServer(this); //QTcp instance
    connect(serverSocket, &QTcpServer::newConnection, this, &TcpServer::handleClientConnection);  //Function to handle new client conection

    QString ipAddress = "127.0.0.1"; // Replace with your desired IP address
    QHostAddress hostAddress(ipAddress);
    quint16 port = 1235;
    if (!serverSocket->listen(hostAddress, port)) {
        qCritical() << "Server failed to start!";
        return;
    }
    qDebug() << "Server started on IP" << ipAddress << "and port "<<port;
}
void TcpServer::handleClientConnection(){
    QTcpSocket *clientSocket = serverSocket->nextPendingConnection();
    // Add the new client socket to the clients list
    clients.append(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServer::forwardReceivedMessage);  //Reading messages from clients
    connect(clientSocket, &QTcpSocket::disconnected, this, &TcpServer::removeTheClient);


    qDebug() << "New client connected";
}
void TcpServer::forwardReceivedMessage(){
    // Identify which client sent the message
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender()); //To know who is the sender and forward messages to other clients
    if (!senderSocket) return;

    QByteArray data = senderSocket->readAll();

    // Broadcast the message to all clients except the sender
    for (QTcpSocket *client : clients) {
        if (client != senderSocket && client->state() == QTcpSocket::ConnectedState) {
            client->write(data); // Send the message to the client
        }
    }
    // qDebug() << "Message is forwarded to other clients";
}
void TcpServer::removeTheClient(){
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        // Remove the client from the clients list when it disconnects
        clients.removeAll(clientSocket);
        clientSocket->deleteLater();
        qDebug() << "Client disconnected";
    }
}
