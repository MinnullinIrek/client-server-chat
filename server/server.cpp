#include "server.h"

Server::Server(int nport, QObject *parent) : QObject(parent),
    server(new QTcpServer(this)),
    nPort(nport)
{
    connect(server, &QTcpServer::newConnection, this, &Server::onConnected);
    if (!server->listen(QHostAddress::Any, nPort)) {
        qDebug() << "server error";
    }

    prepareDB();
}

void Server::prepareDB()
{
    sqlite3_open("chat", &db);

    QString script = "CREATE TABLE IF NOT EXISTS messages ("
              "	id integer PRIMARY KEY AUTOINCREMENT,"
              "	username TEXT,"
              "	message TEXT,"
              "	FOREIGN KEY (username) REFERENCES users(username));";

    command(script);
}

void Server::onConnected()
{
    QTcpSocket *clientConnection = server->nextPendingConnection();
    socketList.push_back(clientConnection);
    connect(clientConnection, &QTcpSocket::readyRead, this, &Server::onReadyRead);
}

void Server::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (QObject::sender());
    QString text = socket->readAll();
    if (!users.contains(socket))
        users[socket] = text;
    else {
        QString script = QString("INSERT INTO messages (username, message) VALUES( '%1', '%2')")
                .arg(users[socket]).arg(text);
        command(script);


        text = QString("%1 : %2 \n").arg(users[socket]).arg(text);
        for(QTcpSocket * soc : users.keys()){
             soc->write(text.toUtf8().data());
        }
    }
}

void Server::command(QString script)
{
    sqlite3_stmt *st = NULL;
    if (SQLITE_OK != sqlite3_prepare_v2(db,script.toUtf8().data(), script.length(), &st, NULL)){
        qDebug() << (sqlite3_errmsg(db));
    }

    int res = sqlite3_step(st);

    if (res != SQLITE_DONE)
        qDebug() << (sqlite3_errmsg(db));
}
