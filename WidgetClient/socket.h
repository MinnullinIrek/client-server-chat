#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
class Socket : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    bool inited = false;
    QTextStream stream;
    QString username;
public:
    explicit Socket(QObject *parent = 0);
    void write(const QString &message);
signals:

public slots:
    void attemptReading();
};

#endif // SOCKET_H
