#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QListWidget>
#include <string.h>
#include <QCheckBox>
#include <QTextEdit>
#include <QMessageBox>
#include "msn_chat.h"

using namespace std;

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;

class Client : public QDialog
{
    friend class Server;
    Q_OBJECT

public:
    Client(QWidget *parent = 0);
    ~Client();
    //離線要求
    void left_requst();
    void left_response(QString ip_address,QString friend_name);
    //將所有Socket斷線
    void disconnect_all(string friend_name);

    //3.建立連線 傳送requst並通知自己的server端去接收，隨即斷線 (set friendip)
    void est_requst(QString ip_address);
    //2.收到response:呼叫client端(1)若是這個IP與之前曾發出的requst IP相同 則發出request_auto給朋友(2)建立連線存到list裡面
    void rec_response(QString ip_address,QString friend_name);
    //1.收到request:呼叫client端(1)發送response訊息並(2)建立連線存到list裡面
    void rec_requset(QString ip_address,QString friend_name);
    //取得聊天介面的物件---> friend list
    void setchatui(QString userName1,QListWidget *friend_list1,Do_msn_chat *to1_chat
                   ,string *theis,string *theno,QCheckBox *timecheck1,QTextEdit *chat_text);
    //傳送訊息，send button呼叫
    void send_msg(QString msg,string thetime);

    void editchatui(string qname,string hasbe);

private slots:

    void slotDisconnected();

    void displayError(QAbstractSocket::SocketError socketError);

private:

    string *t_is
            ,*t_no;
    QCheckBox *timecheck;
    QTextEdit *mainsendtext;

    QString request_ip;          //發送request ip後暫存等代response

    QList<QTcpSocket*> iplist;   //client端已經建立好的socket
    QList<QString> friendname_list;

    QString localipAddress;      //local的ip

    //-------聊天介面-------

    QListWidget *friend_list;

    QString userName;

    Do_msn_chat *to_chat;

};

/*
     建立連線 存到LIST (由server端收到response或request時呼叫) 這邊要更新friend list
  o  1.收到request:呼叫client端(1)發送response訊息並(2)建立連線存到list裡面
  o  2.收到response:呼叫client端(1)若是這個IP與之前曾發出的requst IP相同 則發出request_auto給朋友(2)建立連線存到list裡面

  o  3.建立連線 傳送requst並通知自己的server端去接收，隨即斷線 (set friendip)
  o  4.專門傳送訊息的function，參數為send_text裡面的字串轉成題目的格式 (由main去呼叫，事實上是按send時呼叫)
*/

#endif // CLIENT_H
