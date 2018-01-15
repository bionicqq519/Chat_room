#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
//#include <QLabel>
//#include <QPushButton>
//#include <QFont>
//#include <QMenu>
//#include "msn_chat.h"
#include "client.h"
#include "server.h"
#include "initial.h"
#include <QMainWindow>
#include <QAction>
#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCheckBox>
#include <qinputdialog.h>
#include <QDialog>
#include <QDialogButtonBox>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton *discon;
    int switch_simu;
    Client *aClient;
    Server *aServer;

    Do_msn_chat *to_chat;
    Chat_main *chat_use;
    initial_pro *initi;

    QString q_speaker;
    QString q_receiver;
    QString q_chat;
    //~~~~~~~主選單畫面~~~~~~
    QString userName;
    //QLabel *label;
    QMenuBar *chatmenuBar;
    QHBoxLayout *windown;
    //File選單
    QMenu *menuFile;
    QAction *login, *logout , *simulate , *menuexit;
    //Edit選單
    QMenu *menuEdit;
    QAction *friendip , *search_chat;
    //Help選單
    QMenu *menuHelp;
    QAction *about_the_homework , *about_the_autor;
    //新增chat視窗畫面元件
    QWidget *search_window;
    QTextEdit *chat_text,*send_text;
    QListWidget *friend_list;
    string *theno;
    string *theis;
    QPushButton *submit;
    QCheckBox *timecheck;
    void setupUI();
    void set_the_menu();
    void set_chat();
    //simulate~~~~~~~~~~~~~~~
    QWidget *simu_window;
    enum { Numfriend = 5 };
    QLabel *f_labels[Numfriend];
    QLineEdit *f_line[Numfriend];
    QRadioButton *f_radio[Numfriend];
    QTextEdit *friend_say;
    QDialogButtonBox *buttonBox;
    //QPushButton *buttons[NumButtons];
    //QLabel *friend1 = new QLabel("Author:",this);
    //search~~~~~~~~~~~~~~~~~
    enum { Numoftag = 4 };
    QLabel *s_name,*s_time,*s_message;
    enum { Numoftagsrh = 3 };
    QLineEdit *tagsrh_tex[Numoftagsrh];
    QCheckBox *tagchecked[Numoftag];
    QPushButton *search_btn,*search_default;
    QLabel *total_la,*num_la,*chat_la;
    QTextEdit *search_result;

private slots:
    void exitprogram();

    void helphw();
    void helpautor();

    void loginfunc();
    void logoutfunc();
    void submit_btn();
    void timecheck_click();
    //~~~~~~~~~~~~~~~~~~~~
    void simulate_window();
    void set_radio();
    void accept();
    void reject();
    //~~~~~~~~~~~~~~~~~~~~~
    void search_chat_func();
    void set_search_default();
    void set_btn();
    void search_allname();
    //~~~~~~~~~~~~~~~~~~~~~
    void set_friend_ip();
    //Ui::MainWindow *ui;
    void out();
};

#endif // MAINWINDOW_H
