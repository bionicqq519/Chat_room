#include <QtGui>
#include <QtNetwork>
#include <qsignalmapper.h>
#include <stdlib.h>
#include <QMessageBox>

#include "server.h"

Server::Server(QWidget *parent)
    : QDialog(parent)
{
    chat_main = new Chat_main();

    tcpServer = new QTcpServer(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));

    //QMessageBox::information(this, tr("b"),QString::number(iplist.count()));
}

Server::~Server()
{
    delete chat_main;
    delete tcpServer;
}
void Server::setcount(){
    r_count = iplist.count();
}
void Server::initial_server(){
    //set the port of the server
    if (!tcpServer->listen(QHostAddress::Any, 2010)) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
}


void Server::setchatui(QTextEdit *chat_text,Client *theclient,Do_msn_chat *to1_chat
                       ,string *theis,string *theno,QString userName
                       ,QCheckBox *timecheck1,QPushButton *discon1){
    aclient = theclient;
    mainsendtext = chat_text;
    to_chat = to1_chat;
    t_is = theis;
    t_no = theno;
    bionic = userName;
    timecheck = timecheck1;
    discon = discon1;
}

void Server::sendFortune()
{
    QTcpSocket *clientConnection = new QTcpSocket(this);

    clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection, SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

    connect(clientConnection, SIGNAL(readyRead()),this, SLOT(dataReceived()));

    iplist.append(clientConnection);

    //QMessageBox::information(this, tr("b"),QString::number(iplist.count()));
    //clientConnection->disconnectFromHost();

}

void Server::slotDisconnected()
 {
     //QMessageBox::information(this, tr("ha"),"aa");
     for (int i=0;i<iplist.count();i++)
     {
         //QMessageBox::information(this, tr("ha"),QString::number(iplist.at(0)->state()));
         QTcpSocket *item=iplist.at(i);
         //item->isValid();
         if(item->state()==0)
         {
             //statusLabel->setText("a");
             iplist.removeAt(i);
             //return;
         }
     }
     //return;
}

void Server::dataReceived()
{
    //QMessageBox::information(this, tr("b"),QString::number(iplist.count()));
    int count = iplist.count();
    for (int i=0;i<count;i++){
        //QMessageBox::information(this, tr("ha"),QString::number(iplist.at(0)->state()));
        QTcpSocket *item=iplist.at(i);
        QByteArray  array = item->readAll();
        QString nextFortune = QString::fromUtf8(array.data());
        if(!array.isEmpty()){
            //mainsendtext->setText(nextFortune);
            //接收到的資料在這邊處理:
            //1.如果是response就要通知client端建立連線，若是client端有發requst還必須
            //  通知client端已經接收回應並通知好友
            //2.如果是request呼叫client端發送response訊息並建立連線存到list裡面
            //3.如果是message則要更新聊天視窗的畫面
            //statusLabel->setText(nextFortune);
            //QMessageBox::information(this, tr("b"),QString::number(iplist.count()));
            //QMessageBox::information(this, tr("a"),nextFortune);
            string tmpstr = nextFortune.toStdString();
            if(tmpstr.substr(1,7)=="Request"){
                string ip,name;
                ip = chat_main->jadz(tmpstr,"<RequestFrom>","<Name>",0);
                name = chat_main->jadz(tmpstr,"<Name>","<End>",0);

                aclient->rec_requset(ip.c_str(),name.c_str());
            }
            else if(tmpstr.substr(1,7)=="Respons"){
                string ip,name;
                ip = chat_main->jadz(tmpstr,"<ResponseFrom>","<Name>",0);
                name = chat_main->jadz(tmpstr,"<Name>","<End>",0);
                aclient->rec_response(ip.c_str(),name.c_str());
            }
            else if(tmpstr.substr(1,4)=="Name"){
                string msg,name;
                name = chat_main->jadz(tmpstr,"<Name>","<Message>",0);
                msg = chat_main->jadz(tmpstr,"<Message>","<End>",0);
                QString qmsg,qname;
                qmsg = msg.c_str();
                qname = name.c_str();
                //處理要輸出在box的time字串以及得到至檔案的time
                string thechattime = chat_main->gettime();
                QString q_just_time = "";
                string justtime;
                justtime = chat_main->get_just_time()+"<br>";
                q_just_time = justtime.c_str();
                //得到輸出在box的字串並根據time checked輸出
                QString tmp_is;
                string stmp_is;
                stmp_is = *t_is;
                tmp_is = stmp_is.c_str();
                tmp_is = tmp_is+q_just_time+qname+" says: "+qmsg+"<br>";
                *t_is = tmp_is.toStdString();

                QString tmp_no;
                string stmp_no;
                stmp_no = *t_no;
                tmp_no = stmp_no.c_str();
                tmp_no = tmp_no+qname+" says: "+qmsg+"<br>";
                *t_no = tmp_no.toStdString();

                if(timecheck->isChecked()){
                    mainsendtext->setText(tmp_is);
                }
                else{
                    mainsendtext->setText(tmp_no);
                }
                to_chat->msn_chat(name,bionic.toStdString()
                                  ,msg,thechattime);
                //這邊是匯出all name的~ 加上userName後的字串輸出至all name檔案
                string allnamestring;
                allnamestring = name + "," + bionic.toStdString();
                to_chat->writeallname(allnamestring);

            }
            else if(tmpstr.substr(1,21)=="Terminate_RequestFrom"){
                string ip,name;
                ip = chat_main->jadz(tmpstr,"<Terminate_RequestFrom>","<Name>",0);
                name = chat_main->jadz(tmpstr,"<Name>","<End>",0);
                aclient->left_response(ip.c_str(),name.c_str());
                aclient->disconnect_all(name);
            }
            else if(tmpstr.substr(1,22)=="Terminate_ResponseFrom"){
                string ip,name;
                ip = chat_main->jadz(tmpstr,"<Terminate_ResponseFrom>","<Name>",0);
                name = chat_main->jadz(tmpstr,"<Name>","<End>",0);
                //disconnect_it(name);
                aclient->disconnect_all(name);
                r_count--;
                //QMessageBox::information(this, tr("Information"),"Log Out Successfully!");
                if(r_count==0){
                    //QMessageBox::information(0, tr("Information"),"Log Out Successfully!");
                    r_count=0;
                    tcpServer->close();
                    //mainsendtext->clear();
                    discon->click();
                }
            }

        }
    }
}
