#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QThread>
#include <QList>
#include <QTcpServer> //for the server
#include <QTcpSocket> //for clients
#include "qobject.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr);
    void startTcpServer();

signals:
    void serverStarted();
    void newMessageReceived();
    void threadCompleted();

private slots:
    void handleClientConnection();
    void forwardReceivedMessage();
    void removeTheClient();

private:
    QTcpServer *serverSocket;
    QList<QTcpSocket*> clients;
};

#endif // TCPSERVER_H
