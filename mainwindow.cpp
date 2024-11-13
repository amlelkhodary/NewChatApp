#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList userOptions;
    userOptions << "Run as Client and Server" << "Run as Client Only";
    bool okButtonPressed;
    QString userChoice = QInputDialog::getItem(this, "Dialog Window for the user", "Choose an option",userOptions,0,false,&okButtonPressed);
    if(okButtonPressed){
        ui->connectButton->setEnabled(true);
        ui->sendButton->setEnabled(false);
        ui->inputLineEdit->setEnabled(false);
        ui->inputLineEdit->setPlaceholderText("Type Something");
        ui->chatDisplay->setReadOnly(true);

        presenter = new Presenter(this);
        connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectButtonPressed);
        connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendButtonPressed);
        connect(ui->inputLineEdit, &QLineEdit::returnPressed, this, &MainWindow::sendButtonPressed);
        connect(ui->inputLineEdit, &QLineEdit::textChanged, this, &MainWindow::userStartTyping);
        connect(presenter, &Presenter::newMessageReceived, this, &MainWindow::displayReceivedMessage); //When new message arrived to the server, then forward it to the other client

        if(userChoice == "Run as Client and Server"){
            serverThread = new QThread(this);
            //server = new TcpServer(); //No viable overloaded error when it's not a pointer
            server.moveToThread(serverThread);
            connect(serverThread, &QThread::started, this, &MainWindow::onServerStarted);  //if the server thread started, create a message box and enable the connect button for clients
            serverThread->start();
        }
    }

}

void MainWindow::connectButtonPressed() {
    presenter->connectClient(ipAddress,port);
    //ui->inputLineEdit->setEnabled(true);
}
void MainWindow::sendButtonPressed() {
    QString message = ui->inputLineEdit->text();
    if(!message.isEmpty()){
        ui->chatDisplay->append("Me: "+ message);
        presenter->sendMessageFromClientToServer("User: "+message);
        ui->inputLineEdit->clear();
    }
}
void MainWindow::userStartTyping() {
    ui->sendButton->setEnabled(true);
}

void MainWindow::onServerStarted()
{
    QMessageBox::information(this, "Server Started", "Server is now running on port 1235"); //when server started, create a message box that shows information about the server
    // QMessageBox::information(this, "Server Started", QString("Server is now running on port %1").arg(port));
    ui->connectButton->setEnabled(true);
}

void MainWindow::displayReceivedMessage(const QString &message)
{
    if (!message.isEmpty() && message.startsWith("User: ")) {
        ui->chatDisplay->append(message);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
