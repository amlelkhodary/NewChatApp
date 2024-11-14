#ifndef PRESENTER_H
#define PRESENTER_H
#include "IView.h"
#include <QTcpSocket> //for clients
#include <thread>
#include "tcpserver.h"

class Presenter : public QObject
{
    Q_OBJECT
public:
    Presenter(QObject *parent = nullptr);
    void connectClientToServer(const QString &host, int port);
    void sendMessageToServer(const QString &message);
    void createThreadForServer();

signals:
    void messageReceivedFromOtherClient(const QString &message); //Signals not implemented.. just emitted
    void serverStarted();

private slots:
    void clientCanReceiveMessages(); // a private slot inside the model used to emit the message after connecting the client

private:
    IView *view; //it's not allowed to take instance object from an abstract class
    QTcpSocket *clientSocket = nullptr;
    QThread *serverThread;
    TcpServer *server;
};

#endif // PRESENTER_H
