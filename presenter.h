#ifndef PRESENTER_H
#define PRESENTER_H
#include "model.h"
#include "IView.h"

class Presenter : public QObject
{
    Q_OBJECT
public:
    Presenter(QObject *parent = nullptr);
    void sendMessageFromClientToServer(const QString &message);
    void connectClient(const QString &ip, int port);
signals:
    void newMessageReceived(const QString &message);
private:
    IView *view; //it's not allowed to take instance object from an abstract class
    Model *model;
};

#endif // PRESENTER_H
