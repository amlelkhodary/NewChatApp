#ifndef IVIEW_H
#define IVIEW_H
#include <QString>
class IView{
public:
    virtual ~IView() = default;
    virtual void connectButtonPressed() = 0;
    virtual void sendButtonPressed() = 0;
    virtual void userStartTyping() = 0;
    virtual void displayReceivedMessage(const QString &message) = 0;
};

#endif // IVIEW_H
