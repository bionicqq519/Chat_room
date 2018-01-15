/*!
* @file initial.h
* @author 99598019 李宗人
*/
#ifndef INITIAL_H
#define INITIAL_H
//#include <iostream>
#include "class.h"
#include "msn_chat.h"
#include "parse.h"
#include "chat_used.h"
#include "search.h"
//==================================
class initial_pro{
public:
    friend class Bionic_Test;
    initial_pro();
    ~initial_pro();
    void initial(string srh_para,string sortof_para);

    string get_chat_num();
    string get_chat_result();
private:
    string chat_num;
    string chat_result;
    Do_msn_chat* tomsn_chat;
    Chat_main* main_tool;
    Do_parse* toparse;  //宣告parse class
    Do_search* tosearch;

    Msn_chat_data* read_msn_chat_data;
};




#endif // INITIAL_H
