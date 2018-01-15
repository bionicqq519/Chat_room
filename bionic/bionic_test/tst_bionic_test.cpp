#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QDebug>
#include <string.h>
/*
#include "../chat_used.h"
#include "../class.h"
#include "../exception.h"
#include "../msn_chat.h"
#include "../parse.h"
#include "../search.h"
#include "../search_used.h"
#include "../search_virtual.h"
*/
#include "../initial.h"

using namespace std;

class Bionic_Test : public QObject
{
    Q_OBJECT

public:
    Bionic_Test();
    ~Bionic_Test();

private Q_SLOTS:

    //chat_used.h
    void test_int2str();
    void test_jadz();
    void test_readxml();
    void test_is_formatnum();
    void test_test_format();
    void test_gettime();
    void test_get_just_time();
    void test_del_space();
    //initial.h
    void test_initial();
    //msn_chat.h
    void test_putinto_Msn_chat_data();
    void test_parseallname();
    void test_sort_alphabet();
    //parse.h
    void test_parsemsn();
    void test_parsedate();
    void test_parsefrom();
    void test_parsemessage();
    void test_parseto();
    //search.h
    void test_copy_load();
    void test_tosmall();
    void test_changesmall();
    void test_sortsi();
    void test_sort_para_format();
    //search_used.h
    void test_groupby();
    void test_delspace();
    void test_delsubspace();
    void test_dellr();

private:
    Chat_main *chat_main;
    initial_pro *ini;
    Do_msn_chat *msn_chat;
    Do_parse *par;
    Do_search *sea;
    Search_used *used;
    Search_virtual* src1;
    Search_virtual* src2;
    Search_virtual* src3;
};

Bionic_Test::Bionic_Test()
{
    chat_main = new Chat_main();
    ini = new initial_pro();
    msn_chat = new Do_msn_chat();
    par = new Do_parse();
    sea = new Do_search();
    used = new Search_used();

    src1 = new Donamesearch();
    src2 = new Dotimesearch();
    src3 = new Domessagesearch();
}
Bionic_Test::~Bionic_Test()
{
    delete chat_main;
    delete ini;
    delete msn_chat;
    delete par;
    delete sea;
    delete used;

    delete src1;
    delete src2;
    delete src3;
}


void Bionic_Test::test_int2str()
{
    int i = 5;
    string i2s = "5";
    QVERIFY2(chat_main->int2str(i)==i2s, "Failure");
}
void Bionic_Test::test_jadz()
{
    string text = "<hello>";
    string b = "<";
    string c = ">";

    QVERIFY2(chat_main->jadz(text,b,c,0)=="hello", "Failure");
}
void Bionic_Test::test_readxml()
{
    QVERIFY2(chat_main->readxml("")=="", "Failure");
}
void Bionic_Test::test_is_formatnum(){
    QVERIFY2(chat_main->is_formatnum("1"), "Failure");
}
void Bionic_Test::test_test_format(){
    QVERIFY2(chat_main->test_format(""), "Failure");
}
void Bionic_Test::test_gettime(){
    string time = chat_main->gettime();
    QVERIFY2(time.substr(3,1) == " ", "Failure");
}
void Bionic_Test::test_get_just_time(){
    //cout<<chat_main->get_just_time();
    string ju = chat_main->get_just_time().substr(0,1);
    QVERIFY2(ju == "&"||ju=="", "Failure");
}
void Bionic_Test::test_del_space(){
    string r = chat_main->del_space("aaa   ,   aaa",",");
    QVERIFY2(r == "aaa,aaa", "Failure");
}
void Bionic_Test::test_initial(){
    ini->initial("[time]:\"0\"","1");
    QVERIFY2(ini->get_chat_result() == "", "Failure");
}
void Bionic_Test::test_putinto_Msn_chat_data(){
    Msn_chat_data *a = new Msn_chat_data();
    vector <string> r;
    r.push_back("1");
    msn_chat->putinto_Msn_chat_data(a,"1","1",r,"1");
    QVERIFY2(a->all.size() == 1, "Failure");
    delete a;
}
void Bionic_Test::test_parseallname(){
    vector <string> a;
    a=msn_chat->parseallname("<Friend_Name>a</Friend_Name>");
    QVERIFY2(a.size() == 1, "Failure");
}
void Bionic_Test::test_sort_alphabet(){
    vector <string> result;
    vector <string> sorted;
    vector <string> speaker_name;
    sorted.push_back("b");
    sorted.push_back("a");
    sorted.push_back("c");
    speaker_name.push_back("c");
    result =  msn_chat->sort_alphabet(sorted,speaker_name);
    QVERIFY2(result[0] == "c", "Failure");
    QVERIFY2(result[1] == "a", "Failure");
    QVERIFY2(result[2] == "b", "Failure");
}
void Bionic_Test::test_parsemsn(){
    Msn_chat_data *a = new Msn_chat_data();
    string test =
            "<Chat><date>Fri</date><From>a</From><To Friend_Name=\"1\"><Friend_Name>Bi</Friend_Name><Friend_Name>b</Friend_Name></To><message></message></Chat>";
    par->parsemsn(a,test);
    QVERIFY2(a->all.size() == 1, "Failure");
    delete a;

}
void Bionic_Test::test_parsedate(){
    QVERIFY2(par->parsedate("<date>a</date>",0) == "a", "Failure");
}
void Bionic_Test::test_parsefrom(){
    QVERIFY2(par->parsefrom("<From>a</From>",0) == "a", "Failure");
}
void Bionic_Test::test_parsemessage(){
    QVERIFY2(par->parsemessage("<message>a</message>",0) == "a", "Failure");
}
void Bionic_Test::test_parseto(){
    vector <string> b;
    b = par->parseto("<To Friend_Name=\"1\"><Friend_Name>a</Friend_Name>",0);
    QVERIFY2( b[0] == "a", "Failure");
}
void Bionic_Test::test_copy_load(){

    Msn_chat_data *a = new Msn_chat_data();
    Msn_chat_data *b = new Msn_chat_data();
    vector <string> c;
    c.push_back("1");
    msn_chat->putinto_Msn_chat_data(a,"1","1",c,"1");
    sea->copy_load_data(b,a);

    QVERIFY2( a->all.size() == b->all.size(), "Failure");

    delete a;
    delete b;
}
void Bionic_Test::test_tosmall(){
    Msn_chat_data *a = new Msn_chat_data();
    string p;
    p = "A";
    vector <string> r;
    r.push_back("A");
    msn_chat->putinto_Msn_chat_data(a,"A","A",r,"A");
    sea->tosmall(a,&p);

    QVERIFY2(a->all[0]->speaker_name == "a", "Failure");
    QVERIFY2(a->all[0]->receiver_name[0] == "a", "Failure");
    QVERIFY2(a->all[0]->chat_message == "a", "Failure");
    QVERIFY2(a->all[0]->chat_time == "a", "Failure");
    QVERIFY2(p == "a", "Failure");
    delete a;
}
void Bionic_Test::test_changesmall(){
    string a = "A";
    sea->changesmall(&a);
    QVERIFY2(a == "a", "Failure");
}
void Bionic_Test::test_sortsi(){
    vector <int> sorted;
    sorted.push_back(3);
    sorted.push_back(1);
    sorted.push_back(2);
    sorted = sea->sortsi(sorted);
    QVERIFY2(sorted[0] == 1, "Failure");
    QVERIFY2(sorted[1] == 2, "Failure");
    QVERIFY2(sorted[2] == 3, "Failure");
}
void Bionic_Test::test_sort_para_format(){
    QVERIFY2(sea->sort_para_format("1,2") == 0, "Failure");
}
void Bionic_Test::test_groupby(){
    vector <int> ori;
    ori.push_back(1);
    ori.push_back(1);
    ori = used->groupby(ori);
    QVERIFY2(ori.size() == 1, "Failure");
}
void Bionic_Test::test_delspace(){
    string q = "    \"aa \"" ;
    used->delspace(&q);
    QVERIFY2(q == "\"aa \"", "Failure");
}
void Bionic_Test::test_delsubspace(){
    string q = "aa bb ";
    used->delsubspace(&q);
    QVERIFY2(q == "aabb", "Failure");
}
void Bionic_Test::test_dellr(){
    string q = "  ab  ";
    used->dellr(&q," ");
    QVERIFY2(q == "ab", "Failure");

}
QTEST_APPLESS_MAIN(Bionic_Test);

#include "tst_bionic_test.moc"
