#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "IView.h"
#include "presenter.h"
#include "tcpserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectButtonPressed() override;
    void sendButtonPressed() override;
    void userStartTyping() override;
    void displayReceivedMessage(const QString &message) override;

private slots:
    void onServerStarted();

private:
    Ui::MainWindow *ui;
    Presenter *presenter;
    QThread *serverThread;
    TcpServer *server;
};
#endif // MAINWINDOW_H
