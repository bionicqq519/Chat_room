#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include <string>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //,ui(new Ui::MainWindow)
{
    discon = new QPushButton;
    connect(discon, SIGNAL(clicked()), this, SLOT(out()));
    theno = new string();
    theis = new string();
    //ui->setupUi(this);
    switch_simu = 0;
    //theno = new string();
    //theis = new string();
    chat_use = new Chat_main();
    to_chat = new Do_msn_chat();
    initi = new initial_pro();
    setupUI();
    //網路
    aClient = new Client();
    aServer = new Server();


}

MainWindow::~MainWindow()
{
    delete theno;    //這個logout裡面也有
    delete theis;

    delete initi;
    delete to_chat;
    delete chat_use;
    //delete ui;
    delete aClient;
    delete aServer;
}

//void MainWindow::logoutfunc()
void MainWindow::out(){
    //discon->click();
    //QMessageBox::information(this, tr("b"),"aa");
    *theno = "";
    *theis = "";

    userName = "";
    chat_text->clear();
    friend_list->clear();

    login->setDisabled(false);
    logout->setDisabled(true);
    simulate->setDisabled(true);

    friendip->setDisabled(true);
    search_chat->setDisabled(true);

    send_text->setDisabled(true);
    submit->setDisabled(true);

}

void MainWindow::setupUI(){
    //label = new QLabel("Hello!World! Orz...",this);
    //this->setWindowTitle("First Qt!");
    //this->resize(200, 50);
    //this->setWindowTitle("Signal & Slot");
    //this->setFont(QFont("Courier", 18, QFont::Bold));
    //this->resize(250, 50);

    this->setWindowTitle("Chat");
    this->setMinimumHeight(450);
    this->setMinimumWidth(550);
    this->setMaximumSize(1600,800);
    //this->resize(550, 450);
    this->resize(650, 500);

    //QWidget* widget = new QWidget(this);
    //widget->setLayout(gridLayout);
    //this->setCentralWidget(widget);

    set_the_menu();   //製作上排選單
    set_chat();

    QVBoxLayout *winall = new QVBoxLayout;
    winall->setMenuBar(chatmenuBar);
    winall->addLayout(windown);

    QWidget* widget = new QWidget(this);
    widget->setLayout(winall);
    this->setCentralWidget(widget);
}
void MainWindow::set_chat(){
    QVBoxLayout *winleft = new QVBoxLayout;
    chat_text = new QTextEdit();
    chat_text->setReadOnly(true);
    chat_text->setMinimumSize(480,300);
    //chat_text->setGeometry(QRect(10,30,480,300));
    send_text = new QTextEdit();
    send_text->setDisabled(true);
    send_text->setMinimumWidth(480);
    send_text->setMaximumHeight(100);
    //send_text->setGeometry(QRect(10,340,480,100));
    winleft->addWidget(chat_text);
    winleft->addWidget(send_text);

    QVBoxLayout *winright = new QVBoxLayout;
    friend_list = new QListWidget();
    friend_list->setMinimumSize(130,270);
    //friend_text->setGeometry(QRect(500,30,130,270));
    submit = new QPushButton("Submit");
    submit->setDisabled(true);
    connect(submit, SIGNAL(clicked()), this, SLOT(submit_btn()));
    submit->setMinimumSize(130,100);
    //submit->setGeometry(QRect(500,340,130,100));
    timecheck = new QCheckBox("Time");
    connect(timecheck, SIGNAL(clicked()), this, SLOT(timecheck_click()));
    //timecheck->setGeometry(QRect(500,300,50,50));
    winright->addWidget(friend_list);
    winright->addWidget(timecheck);
    winright->addWidget(submit);

    windown = new QHBoxLayout;
    windown->addLayout(winleft);
    windown->addLayout(winright);
}
void MainWindow::timecheck_click(){
    if(timecheck->isChecked()){
        QString tmp_is;
        string stmp_is;
        stmp_is = *theis;
        tmp_is = stmp_is.c_str();
        chat_text->setText(tmp_is);
    }
    else{
        QString tmp_no;
        string stmp_no;
        stmp_no = *theno;
        tmp_no = stmp_no.c_str();
        chat_text->setText(tmp_no);
    }
}
void MainWindow::submit_btn(){
    string thechattime = chat_use->gettime();
    q_speaker = userName;
    q_chat = send_text->toPlainText();
    if(switch_simu==0){
        aClient->send_msg(q_chat,thechattime);  //傳送
    }
    else{
        to_chat->msn_chat(q_speaker.toStdString(),q_receiver.toStdString()
                          ,q_chat.toStdString(),thechattime);
    }
    QString q_just_time = "";
    string justtime;
    justtime = chat_use->get_just_time()+"<br>";
    q_just_time = justtime.c_str();

    QString tmp_is;
    string stmp_is;
    stmp_is = *theis;
    tmp_is = stmp_is.c_str();
    chat_text->setText(tmp_is);
    tmp_is = tmp_is+q_just_time+q_speaker+" says: "+send_text->toPlainText()+"<br>";
    *theis = tmp_is.toStdString();

    QString tmp_no;
    string stmp_no;
    stmp_no = *theno;
    tmp_no = stmp_no.c_str();
    tmp_no = tmp_no+q_speaker+" says: "+send_text->toPlainText()+"<br>";
    *theno = tmp_no.toStdString();

    if(timecheck->isChecked()){
        chat_text->setText(tmp_is);
    }
    else{
        chat_text->setText(tmp_no);
    }
    send_text->clear();

}
void MainWindow::set_the_menu(){
    chatmenuBar = new QMenuBar;
    //File主選單
    login = new QAction(tr("&Login"),this);
    connect(login, SIGNAL(triggered()), this, SLOT(loginfunc()));
    logout = new QAction(tr("&Logout"),this);
    connect(logout, SIGNAL(triggered()), this, SLOT(logoutfunc()));
    logout->setDisabled(true);
    simulate= new QAction(tr("&Simulate"),this);
    simulate->setDisabled(true);
    connect(simulate, SIGNAL(triggered()), this, SLOT(simulate_window()));
    menuexit= new QAction(tr("&Exit"),this);
    connect(menuexit, SIGNAL(triggered()), this, SLOT(exitprogram()));
    menuFile = chatmenuBar->addMenu(tr("&File"));
    menuFile->addAction(login);
    menuFile->addAction(logout);
    menuFile->addAction(simulate);
    menuFile->addSeparator();
    menuFile->addAction(menuexit);


    //Edit主選單
    friendip = new QAction(tr("&Set FriendIP"),this);
    friendip->setDisabled(true);
    connect(friendip, SIGNAL(triggered()), this, SLOT(set_friend_ip()));
    search_chat = new QAction(tr("&Search Chat"),this);
    search_chat->setDisabled(true);
    connect(search_chat, SIGNAL(triggered()), this, SLOT(search_chat_func()));
    menuEdit = chatmenuBar->addMenu(tr("&Edit"));
    menuEdit->addAction(friendip);
    menuEdit->addSeparator();
    menuEdit->addAction(search_chat);

    //Help
    about_the_homework = new QAction(tr("&About the homework"),this);
    connect(about_the_homework, SIGNAL(triggered()), this, SLOT(helphw()));
    about_the_autor = new QAction(tr("&About the autor"),this);
    connect(about_the_autor, SIGNAL(triggered()), this, SLOT(helpautor()));
    menuHelp = chatmenuBar->addMenu(tr("&Help"));
    menuHelp->addAction(about_the_homework);
    menuHelp->addSeparator();
    menuHelp->addAction(about_the_autor);
}
void MainWindow::set_friend_ip(){
    QString friendIp;
    friendIp = "";
    friendIp = QInputDialog::getText(this,
    tr("Set Friend IP"),
    tr("FriendIP:"),QLineEdit::Normal,tr("223.141.254.189"));

    if(friendIp!=""){
        aClient->est_requst(friendIp);
        //aClient->setchatui();
    }

    //est_requst("140.124.183.62",userName);
}

//search chat選單
void MainWindow::search_chat_func(){
    search_window = new QWidget;
    search_window->setWindowTitle("Search Chat");
    QVBoxLayout *search_all = new QVBoxLayout;

    QGridLayout *tag_glayout = new QGridLayout;
    //tag_glayout->setSpacing(1);
    //tag_glayout->setMargin(1);
    s_name = new QLabel(tr("Name"));
    s_time = new QLabel(tr("Time"));
    s_message = new QLabel(tr("Message"));
    tagsrh_tex[0] = new QLineEdit();
    tagsrh_tex[1] = new QLineEdit();
    tagsrh_tex[2] = new QLineEdit();
    tag_glayout->addWidget(s_name,0,0);
    tag_glayout->addWidget(s_time,1,0);
    tag_glayout->addWidget(s_message,2,0);
    tag_glayout->addWidget(tagsrh_tex[0],0,1);   //name
    tag_glayout->addWidget(tagsrh_tex[1],1,1);   //time
    tag_glayout->addWidget(tagsrh_tex[2],2,1);   //message
    search_all->addLayout(tag_glayout);

    tagchecked[0] = new QCheckBox("Time");
    tagchecked[1] = new QCheckBox("Speaker");
    tagchecked[2] = new QCheckBox("Receiver");
    tagchecked[3] = new QCheckBox("Message");
    QHBoxLayout *tag_checked = new QHBoxLayout;
    for(int i = 0;i<Numoftag;++i){
        connect(tagchecked[i], SIGNAL(clicked()), this, SLOT(set_btn()));
        tag_checked->addWidget(tagchecked[i]);
    }
    search_all->addLayout(tag_checked);

    QHBoxLayout *seto = new QHBoxLayout;
    search_btn = new QPushButton("Search");
    connect(search_btn, SIGNAL(clicked()), this, SLOT(search_allname()));
    search_btn->setDisabled(true);
    search_default = new QPushButton("Default");
    connect(search_default, SIGNAL(clicked()), this, SLOT(set_search_default()));
    total_la = new QLabel(tr("Total:"));
    num_la = new QLabel(tr(""));
    chat_la = new QLabel(tr("chat"));
    seto->addWidget(search_btn);
    seto->addWidget(search_default);
    seto->addWidget(total_la);
    seto->addWidget(num_la);
    seto->addWidget(chat_la);
    search_all->addLayout(seto);
    search_result = new QTextEdit();
    search_result->setReadOnly(true);

    search_all->addWidget(search_result);

    search_window->setLayout(search_all);
    search_window->show();
}
void MainWindow::search_allname(){
    string para_srh;
    for(int i=0;i<Numoftagsrh;i++){
        if(tagsrh_tex[i]->text()!=""){
            string tagid;
            if(i==0){
                tagid = "[Name]:";
            }
            else if(i==1){
                tagid = "[Time]:";
            }
            else if(i==2){
                tagid = "[Message]:";
            }
            para_srh+=(tagid+tagsrh_tex[i]->text().toStdString()+"&&");
        }

    }
    para_srh = para_srh.substr(0,para_srh.size()-2);
    //search_window->setWindowTitle(para_srh.c_str());
    string para_sortre;
    for(int i = 0;i<Numoftag;++i){
        if(tagchecked[i]->isChecked()){
            int ia1 = i+1;
            para_sortre += (chat_use->int2str(ia1)+",");
        }
    }
    para_sortre = para_sortre.substr(0,para_sortre.size()-1);
    //search_window->setWindowTitle(para_sortre.c_str());
    initi->initial(para_srh,para_sortre);
    search_result->setText(initi->get_chat_result().c_str());
    num_la->setText(initi->get_chat_num().c_str());
    //search_result->setText(initi->get_chat_num().c_str());
}
void MainWindow::set_btn(){
    //total_la->setDisabled(true);
    int test=0;
    for(int i = 0;i<Numoftag;++i){
        if(tagchecked[i]->isChecked()){
            test = 1;
        }
    }
    if(test==1){
        search_btn->setDisabled(false);
    }
    else{
        search_btn->setDisabled(true);
    }
}
void MainWindow::set_search_default(){
    tagsrh_tex[0]->clear();
    tagsrh_tex[1]->clear();
    tagsrh_tex[2]->clear();
    search_result->clear();
    for(int i = 0;i<Numoftag;++i){
        tagchecked[i]->setChecked(false);
    }
    search_btn->setDisabled(true);
    num_la->setText("");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//simulate選單
void MainWindow::simulate_window(){
    simu_window = new QWidget;
    QVBoxLayout *simulate_all = new QVBoxLayout;
    QGridLayout *glayout = new QGridLayout;
    //QTextEdit *f_text[Numfriend];
    simu_window->setWindowTitle("Simulate");
    for (int i = 0; i < Numfriend; ++i) {
        f_labels[i] = new QLabel(tr("Friend %1:").arg(i + 1));
        glayout->addWidget(f_labels[i],i,0);
        f_line[i] = new QLineEdit();
        connect(f_line[i], SIGNAL(textChanged(const QString &)), this, SLOT(set_radio()));
        glayout->addWidget(f_line[i],i,1);
        f_radio[i] = new QRadioButton();
        f_radio[i]->setDisabled(true);
        glayout->addWidget(f_radio[i],i,2);
    }
    simulate_all->addLayout(glayout);

    friend_say = new QTextEdit();
    simulate_all->addWidget(friend_say);

    //sim_ok = new QPushButton();
    //sim_can = new QPushButton();
    //glayoutbot->addWidget(sim_ok,0,0);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                          | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    simulate_all->addWidget(buttonBox);

    simu_window->setLayout(simulate_all);
    simu_window->show();

}
void MainWindow::accept(){
    switch_simu = 1;
    //<font color=blue>has joined</font>
    //處理box裡面的has joined字串
    QString join_all;
    for (int i = 0; i < Numfriend; ++i) {
        if(f_line[i]->text()!=""){
           join_all+=("<font color=gray>"+f_line[i]->text()+" has joined</font> <br>");
           friend_list->insertItem(i,f_line[i]->text());
        }
    }
    //f_radio[0]->isChecked();
    //處理輸出至檔案的speaker,receiver以及要印出在box的speaker
    for (int i = 0; i < Numfriend; ++i) {
        if(f_radio[i]->isChecked()){
           q_speaker = f_line[i]->text();
        }
        else{
            if(f_line[i]->text()!=""){
                q_receiver+=(f_line[i]->text()+",");
            }
        }
    }
    //處理要輸出在box的time字串以及得到至檔案的time
    string thechattime = chat_use->gettime();
    QString q_just_time = "";
    string justtime;
    justtime = chat_use->get_just_time()+"<br>";
    q_just_time = justtime.c_str();
    //得到輸出在box的字串並根據time checked輸出
    QString tmp_is;
    string stmp_is;
    stmp_is = *theis;
    tmp_is = stmp_is.c_str();
    tmp_is = join_all+q_just_time+q_speaker+": "+friend_say->toPlainText()+"<br>";
    *theis = tmp_is.toStdString();

    QString tmp_no;
    string stmp_no;
    stmp_no = *theno;
    tmp_no = stmp_no.c_str();
    tmp_no = join_all+q_speaker+": "+friend_say->toPlainText()+"<br>";
    *theno = tmp_no.toStdString();

    if(timecheck->isChecked()){
        chat_text->setText(tmp_is);
    }
    else{
        chat_text->setText(tmp_no);
    }
    q_receiver+=userName;
    q_chat = friend_say->toPlainText();
    to_chat->msn_chat(q_speaker.toStdString(),q_receiver.toStdString()
                      ,q_chat.toStdString(),thechattime);
    //存到XML檔後就清空
    q_speaker = "";
    q_receiver = "";
    q_chat = "";

    //friend_say->setDisabled(true);
    //將receiver改為全部friend 待回到chat視窗後speaker則變為login的那位
    for (int i = 0; i < Numfriend; ++i) {
        if(f_line[i]->text()!=""){
            q_receiver+=(f_line[i]->text()+",");
        }
    }
    string re_tmp;
    re_tmp = q_receiver.toStdString();
    //這邊是匯出all name的~ 加上userName後的字串輸出至all name檔案
    to_chat->writeallname(re_tmp+userName.toStdString());
    //不加userName的檔案則存到q_receiver
    re_tmp = re_tmp.substr(0,re_tmp.size()-1);
    q_receiver = re_tmp.c_str();
    //this->setWindowTitle(q_receiver);


    simu_window->close();
}
void MainWindow::reject(){
    simu_window->close();
    //friend_say->setDisabled(true);
}
void MainWindow::set_radio(){
    for(int i = 0;i<Numfriend; ++i){
        if(f_line[i]->text()==""){
            f_radio[i]->setDisabled(true);
        }
        else{
            f_radio[i]->setDisabled(false);
        }
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MainWindow::logoutfunc(){
    aClient->left_requst();
    aServer->setcount();
}
void MainWindow::loginfunc(){
    userName = QInputDialog::getText(this,
    tr("Log In"),
    tr("Enter your name:"),QLineEdit::Normal,tr("Bionic"));

    if(userName != ""){
        login->setDisabled(true);
        logout->setDisabled(false);
        simulate->setDisabled(false);

        friendip->setDisabled(false);
        search_chat->setDisabled(false);

        send_text->setDisabled(false);
        submit->setDisabled(false);
    }
    //登入後才開放監聽連線
    aServer->initial_server();
    //aServer->setchatui(chat_text,aClient,to_chat);
    aServer->setchatui(chat_text,aClient,to_chat,
                       theis,theno,userName,
                       timecheck,discon);
    aClient->setchatui(userName,friend_list,to_chat,theis,theno,timecheck,chat_text);

}
void MainWindow::helphw(){
    QMessageBox hwmsgBox;
    hwmsgBox.setWindowTitle("About the homework");
    hwmsgBox.setText("Homework 4");
    hwmsgBox.exec();
}
void MainWindow::helpautor(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("About the autor");
    msgBox.setText("Name : Tsung-Jen Li\n\nStudent_id : 99598019");
    msgBox.exec();

}
void MainWindow::exitprogram(){
     exit(0);
}
