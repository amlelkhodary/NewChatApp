#ifndef MODEL_H
#define MODEL_H
#include "qobject.h"
#include <QTcpSocket> //for clients

class Model  : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr); //Make the client socket on ready read
    void connectClientToServer(const QString &host, int port);
    void sendMessageToServer(const QString &message);

signals:
    void messageReceivedFromOtherClient(const QString &message); //Signals not implemented.. just emitted

private slots:
    void clientCanReceive(); // a private slot inside the model used to emit the message after connecting the client

private:
    QTcpSocket *clientSocket;

};

#endif // MODEL_H
