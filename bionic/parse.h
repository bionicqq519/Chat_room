/*!
* @file parse.h
* @author 99598019 李宗人
*/
#ifndef PARSE_H
#define PARSE_H
//#include "class.h"
#include "chat_used.h"
#include "msn_chat.h"
class Do_parse{
public:
    friend class Bionic_Test;
    Do_parse();
    ~Do_parse();
    void parsemsn(Msn_chat_data *msn_chat_data,string text);
private:
    string parsedate(string text,int data_num_count_pos);
    string parsefrom(string text,int data_num_count_pos);
    string parsemessage(string text,int data_num_count_pos);
    vector <string>  parseto(string text,int data_num_count_pos);

    Chat_main* ini;
    Do_msn_chat* tomsn_chat;  //宣告msn_chat class
};

#endif // PARSE_H
