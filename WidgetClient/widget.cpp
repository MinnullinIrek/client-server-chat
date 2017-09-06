#include "widget.h"
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      socket(new QTcpSocket),
      nameEdit(new QLineEdit),
      sendName(new QPushButton("send name")),
      messageEdit(new QTextEdit),
      lineEdit(new QLineEdit),
      send(new QPushButton("send"))
{
    QGridLayout *layout = new QGridLayout(this);
    this->setLayout(layout);

    layout->addWidget(nameEdit, 0, 0);
    layout->addWidget(sendName, 0, 1);

    layout->addWidget(messageEdit, 1, 0, 1, 2);

    layout->addWidget(lineEdit, 2, 0);
    layout->addWidget(send, 2, 1);
    lineEdit->setEnabled(false);
    send->setEnabled(false);

    connect(sendName, &QPushButton::clicked, [=]()
    {
        if (nameEdit->text() != ""){
            socket->connectToHost("localhost", nPort);
            write(nameEdit->text());
            nameEdit->setEnabled(false);
            sendName->setEnabled(false);

            lineEdit->setEnabled(true);
            send->setEnabled(true);
        }
    });

    connect(send, &QPushButton::clicked, [=]()
    {
        if (lineEdit->text() != "") {
            write(lineEdit->text());
            lineEdit->clear();
        }
    });

    connect(socket, &QTcpSocket::readyRead, this, attemptReading);

}

void Widget::attemptReading()
{
    QByteArray bt = socket->readAll();
    messageEdit->insertPlainText(bt);
}

void Widget::write(const QString &message)
{
    socket->write(message.toUtf8().data(), message.length());
}

Widget::~Widget()
{

}
