#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QTcpSocket>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:

    int nPort = 1024;
    QTcpSocket *socket;

    QLineEdit *nameEdit;
    QPushButton *sendName;

    QTextEdit *messageEdit;
    QLineEdit *lineEdit;

    QPushButton *send;
    void write(const QString &message);

public slots:
    void attemptReading();


};

#endif // WIDGET_H
