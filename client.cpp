#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    clientSocket = new QTcpSocket(this);
    in.setDevice(clientSocket);
    connect(ui->btn_close, &QAbstractButton::clicked, this, &QWidget::close);
    connect(ui->btn_connect, &QAbstractButton::clicked, this, &Client::requestMessage);
    connect(clientSocket, &QIODevice::readyRead, this, &Client::readMessage);
}

Client::~Client()
{
    delete ui;
}

void Client::requestMessage()
{
    qInfo() << "requestMessage()...";
    QString ipAddress = ui->le_ip->text();
    QString port = ui->le_port->text();
    qInfo() << "ip: " + ipAddress + ", port: " + port;
    clientSocket->connectToHost(ipAddress, port.toInt());
}

void Client::readMessage()
{
    qInfo() << "readMessage()...";
    in.startTransaction();
    QString message;
    in >> message;
    if (!in.commitTransaction())
    {
        qInfo() << "Error in data stream";
        return;
    }
    ui->lbl_message->setText(message);
}

