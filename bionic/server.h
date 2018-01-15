#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>
#include <QDialog>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
#include "client.h"
#include "chat_used.h"
#include "msn_chat.h"
class QLabel;
class QPushButton;
class QTcpServer;

class Server : public QDialog
{
    Q_OBJECT

public:
    Server(QWidget *parent = 0);
    ~Server();
    void setchatui(QTextEdit *chat_text,Client *theclient,Do_msn_chat *to1_chat
                   ,string *theis,string *theno,QString userName
                   ,QCheckBox *timecheck1,QPushButton *discon1);

    void initial_server();    //呼叫Server端監聽連線

    void setcount();
private:
    int r_count;
    QPushButton *discon;

    Chat_main *chat_main;
    QTcpServer *tcpServer;
    QList<QTcpSocket*> iplist;
    //主畫面的一些元件
    QTextEdit *mainsendtext;
    Client *aclient;
    Do_msn_chat *to_chat;
    string *t_is
            ,*t_no;
    QString bionic;
    QCheckBox *timecheck;

private slots:
    void sendFortune();

    void slotDisconnected();

    void dataReceived();
};

#endif // SERVER_H
