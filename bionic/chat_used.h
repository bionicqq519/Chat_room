#ifndef CHAT_USED_H
#define CHAT_USED_H
#include <iostream>
#include "class.h"
#include "exception.h"
//#include "msn_chat.h"
//using namespace std;

class Chat_main{
public:
    friend class Bionic_Test;
    string int2str(int &i);
    string jadz(string text,string b,string c,int data_num_count_pos);
    string readxml(string filename);
    int is_formatnum(string friend_num);
    int test_format(string read_text);

    string gettime();
    string get_just_time();

    string del_space(string s , string t);
private:
    string just_time;
};
#endif // CHAT_USED_H
