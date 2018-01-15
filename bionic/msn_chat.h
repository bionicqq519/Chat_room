#ifndef MSN_CHAT_H
#define MSN_CHAT_H

#include "class.h"
#include "chat_used.h"
//#include "initial.h"
class Do_msn_chat{
public:
    friend class Bionic_Test;
    Do_msn_chat();
    ~Do_msn_chat();
    void putinto_Msn_chat_data(Msn_chat_data *msn_chat_data
            ,string chat_time,string speaker_name,vector <string> receiver_name,string chat_message);
    void msn_chat(string q_speaker,string q_receiver,string q_chat_msg,string thetime);
    void writeallname(string q_all_name);

    vector <string> parseallname(string allname_text);
private:
    void file_out(Msn_chat_data *msn_chat_data,string file_name);
    void writexml(Msn_chat_data *msn_chat_data,string username = "");
    vector <string> sort_alphabet(vector <string> sorted,vector <string> speaker_name);
    Chat_main* ini;
    Msn_chat_data* msn_chat_data1;
};

#endif // MSN_CHAT_H
