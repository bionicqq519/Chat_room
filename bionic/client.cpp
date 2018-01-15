#include <QtGui>
#include <QtNetwork>
#include <QDebug>
#include "client.h"

Client::Client(QWidget *parent)
    : QDialog(parent)
{

    request_ip = "";
    //抓localip的
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            localipAddress = ipAddressesList.at(i).toString();
            QString subString = localipAddress.mid(0,3);
            if(subString!="192"&&subString!="172"){
                break;
            }
        }
    }
    // if we did not find one, use IPv4 localhost
    if (localipAddress.isEmpty())
        localipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    //測試用
    //est_requst(localipAddress);
    //est_requst("140.124.183.62","Bionic");
    //QMessageBox::information(this, tr("ha"),localipAddress);

}

Client::~Client()
{

}
void Client::disconnect_all(string friend_name){
    for (int i=0;i<friendname_list.count();i++)
    {
        if(friendname_list.at(i).toStdString()==friend_name){
            QTcpSocket *item=iplist.at(i);
            item->close();
        }

    }
}

void Client::left_requst()
{
    for (int i=0;i<iplist.count();i++)
    {
        QTcpSocket *item=iplist.at(i);
        string tmp = "<Terminate_RequestFrom>" + localipAddress.toStdString() + "<Name>" + userName.toStdString() + "<End>";
        QString str0 = tmp.c_str();
        QByteArray  block = str0.toUtf8();
        item->write(block);
    }
}
void Client::left_response(QString ip_address,QString friend_name)
{
    for (int i=0;i<iplist.count();i++)
    {
        if(friendname_list.at(i).toStdString()==friend_name.toStdString()){
            QTcpSocket *item=iplist.at(i);
            string tmp = "<Terminate_ResponseFrom>" + localipAddress.toStdString() + "<Name>" + userName.toStdString() + "<End>";
            QString str0 = tmp.c_str();
            QByteArray  block = str0.toUtf8();
            item->write(block);
        }
    }
}

void Client::setchatui(QString userName1,QListWidget *friend_list1,Do_msn_chat *to1_chat
                       ,string *theis,string *theno,QCheckBox *timecheck1,QTextEdit *chat_text){
    userName = userName1;
    friend_list = friend_list1;
    to_chat =  to1_chat;
    t_is = theis;
    t_no = theno;
    timecheck = timecheck1;
    mainsendtext = chat_text;
    //friend_list->takeItem(i);
    //friend_list->insertItem(i,f_line[i]->text());
    //QMessageBox::information(this, tr("ha"),QString::number(iplist.count()));
}

void Client::editchatui(string qname,string hasbe){
    //得到輸出在box的字串並根據time checked輸出
    QString tmp_is;
    string stmp_is;
    stmp_is = *t_is;
    tmp_is = stmp_is.c_str();
    tmp_is = tmp_is+ "<font color=gray>" +qname.c_str()+ hasbe.c_str();
    *t_is = tmp_is.toStdString();

    QString tmp_no;
    string stmp_no;
    stmp_no = *t_no;
    tmp_no = stmp_no.c_str();
    tmp_no = tmp_no+ "<font color=gray>" + qname.c_str()+ hasbe.c_str();
    *t_no = tmp_no.toStdString();

    if(timecheck->isChecked()){
        mainsendtext->setText(tmp_is);
    }
    else{
        mainsendtext->setText(tmp_no);
    }
}

//傳送訊息
void Client::send_msg(QString msg,string thetime)
{
    //QMessageBox::information(this, tr("ha"),QString::number(iplist.count()));
    string receiver;
    for (int i=0;i<iplist.count();i++)
    {
        QTcpSocket *item=iplist.at(i);
        string tmp = "<Name>" + userName.toStdString() + "<Message>" + msg.toStdString() + "<End>";
        QString str0 = tmp.c_str();
        QByteArray  block = str0.toUtf8();
        item->write(block);
    }
    for (int i=0;i<friendname_list.count();i++)
    {
        receiver+=(friendname_list.at(i).toStdString()+",");
        //friend_list->item()
    }
    receiver = receiver.substr(0,receiver.size()-1);

    to_chat->msn_chat(userName.toStdString(),receiver,msg.toStdString(),thetime);
    //這邊是匯出all name的~ 加上userName後的字串輸出至all name檔案
    string allnamestring;
    allnamestring = userName.toStdString() + "," + receiver;
    to_chat->writeallname(allnamestring);
}


//3.建立連線 傳送requst並通知自己的server端去接收，隨即斷線 (set friendip)
void Client::est_requst(QString ip_address)
{
    if(request_ip==""){
        request_ip = ip_address;
        QTcpSocket *tcpSocket = new QTcpSocket(this);
        //connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
        connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(displayError(QAbstractSocket::SocketError)));
        tcpSocket->abort();
        //connect to host
        tcpSocket->connectToHost(ip_address,2010);
        string tmp = "<RequestFrom>" + localipAddress.toStdString() + "<Name>" + userName.toStdString() + "<End>";
        QString str0 = tmp.c_str();
        QByteArray  block = str0.toUtf8();
        tcpSocket->write(block);
        tcpSocket->disconnectFromHost();
    }
}

//1.收到request:呼叫client端(1)發送response訊息並(2)建立連線存到list裡面
void Client::rec_requset(QString ip_address,QString friend_name){
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    tcpSocket->abort();
    //connect to host
    tcpSocket->connectToHost(ip_address,2010);
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

    //(1)送出Response_Auto()
    string tmp = "<ResponseFrom>" + localipAddress.toStdString() + "<Name>" + userName.toStdString() + "<End>";
    QString str0 = tmp.c_str();
    QByteArray  block = str0.toUtf8();
    tcpSocket->write(block);
    //(2)
    iplist.append(tcpSocket);
    friendname_list.append(friend_name);
    editchatui(friend_name.toStdString()," has been joined .</font><br>");
    friend_list->insertItem(friend_list->count(),friend_name);
}

//2.收到response:呼叫client端(1)若是這個IP與之前曾發出的requst IP相同 則發出request_auto給朋友(2)建立連線存到list裡面
void Client::rec_response(QString ip_address,QString friend_name)
{
    //(1)
    if(request_ip.toStdString() == ip_address.toStdString()){
        for(int i=0;i<iplist.count();i++){
            string tmp = "<RequestFrom>" + ip_address.toStdString() + "<Name>" + friend_name.toStdString() + "<End>";
            QString str0 = tmp.c_str();
            QByteArray  block = str0.toUtf8();
            iplist.at(i)->write(block);
        }
        request_ip = "";
    }
    //(2)
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    tcpSocket->abort();
    //connect to host
    tcpSocket->connectToHost(ip_address,2010);
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    iplist.append(tcpSocket);
    //QMessageBox::information(this, tr("ha"),friend_name);
    friendname_list.append(friend_name);
    editchatui(friend_name.toStdString()," has been joined .</font><br>");
    friend_list->insertItem(friend_list->count(),friend_name);
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        ;
        //QMessageBox::information(this, tr("Fortune Client"),
        //                         tr("The following error occurred: %1.")
        //                         .arg(tcpSocket->errorString()));
    }
}

void Client::slotDisconnected()
{
    //QMessageBox::information(this, tr("ha"),QString::number(iplist.at(0)->state()));
    //QMessageBox::information(this, tr("ha"),"bb");
    for (int i=0;i<iplist.count();i++)
    {
        //QMessageBox::information(this, tr("ha"),QString::number(iplist.at(0)->state()));
        QTcpSocket *item=iplist.at(i);
        //item->isValid();
        if(item->state()==0)
        {
            //statusLabel->setText("a");
            editchatui(friendname_list.at(i).toStdString()," has been left .</font><br>");
            friend_list->takeItem(i);
            friendname_list.removeAt(i);
            iplist.removeAt(i);
            //return;
        }
    }
    //return;
}

