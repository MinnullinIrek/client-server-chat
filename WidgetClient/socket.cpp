#include "socket.h"
#include <QIODevice>

Socket::Socket(QObject *parent) : QObject(parent), socket(new QTcpSocket()), stream(stdin)
{
    int nPort = 1024;

    QObject::connect(socket, &QIODevice::readyRead, this, &Socket::attemptReading);

    qDebug() << "username:";

    username = stream.readLine();

    socket->connectToHost("localhost", nPort);
    write(username);

    while(true){
        write(stream.readAll());
    }


}

void Socket::attemptReading()
{
    qDebug() << "attempt reading";

    QByteArray bt = socket->readAll();

    qDebug() << "attempt reading" << bt;

    qDebug()<< "line readed";






}

void Socket::write(const QString &message)
{
    qDebug() << "write " << message;
    socket->write(message.toUtf8().data(), message.length());
}

