#include <QCoreApplication>

#include <QTcpSocket>
#include <qtcpserver.h>
#include <iostream>
#include <qdatastream.h>
#include <qstring.h>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QTcpServer * server = new QTcpServer();
    //server->listen(QHostAddress::Any, 1024);
    Server serv(1024);
 /*   QByteArray block;
    block.append("hello");


    QTcpServer * server = new QTcpServer();

    QObject::connect(server, &QTcpServer::newConnection, [=]()
    {
        QTcpSocket *clientConnection = server->nextPendingConnection();
        clientConnection->write(block);
        clientConnection->disconnectFromHost();
    });

    server->listen(QHostAddress::Any, 1024);

*/

    return a.exec();
}
