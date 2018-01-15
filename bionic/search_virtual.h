#ifndef SEARCH_VIRTUAL_H
#define SEARCH_VIRTUAL_H
#include "class.h"
#include "msn_chat.h"
#include "search_used.h"
class Search_virtual{
public:
    friend class Bionic_Test;
    Search_virtual();
    ~Search_virtual();
    void setformat_error(int up_format_error);
    int getformat_error();
    vector<int> tobesearched(Msn_chat_data *small_msn_chat_data,string parameter,int level);
    //定義虛擬函式
    virtual vector<int> search(Msn_chat_data *msn_chat_data,string parameter,int level)=0;
protected:
    vector<int> searchnot(Msn_chat_data *msn_chat_data,string parameter,int level);    //logic not
    vector<int> searchrange(Msn_chat_data *msn_chat_data,string parameter,int level);  //logic or
    vector<int> searchand(Msn_chat_data *msn_chat_data,string parameter,int level);    //logic and
    //各種tag主要是從這裡切的，下面三個搜尋類別都是由此開始分別做搜尋
    vector<int> searchtag(Msn_chat_data *msn_chat_data,string parameter,int level);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Search_used *search_u;
    Chat_main* ini;
    //Msn_chat_data *q;
    //Msn_chat_data *msn_chat_data;
    int format_error;      //! 檢查Parameter of Searching格式是否正確
};
class Dotimesearch : public Search_virtual{
public:
    vector<int> search(Msn_chat_data *msn_chat_data,string parameter,int level);
    string timeparatrans(string parameter);
};
class Donamesearch : public Search_virtual{
public:
    vector<int> search(Msn_chat_data *msn_chat_data,string parameter,int level);
};

class Domessagesearch : public Search_virtual{
public:
    vector<int> search(Msn_chat_data *msn_chat_data,string parameter,int level);
};


#endif // SEARCH_VIRTUAL_H
