#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include <QTcpSocket>
#include <QMap>
#include "sqlite3.h"

class Server : public QObject
{
    Q_OBJECT
private:
    QTcpServer *server;
    QList<QTcpSocket*> socketList;
    QMap<QTcpSocket*, QString> users;
    void prepareDB();
    sqlite3 *db;
    void command(QString script);
    int nPort = 1024;

public:
    explicit Server(int nport, QObject *parent = 0);

signals:

public slots:
    void onConnected();
    void onReadyRead();
};

#endif // SERVER_H
