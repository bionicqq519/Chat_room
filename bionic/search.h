/*! * @file search.h 搜尋
    * @author 99598019 李宗人
*/
#ifndef SEARCH_H
#define SEARCH_H
#include "class.h"
#include "msn_chat.h"
#include "search_used.h"
#include "search_virtual.h"
class Do_search{
public:
    int format_error;      //! 檢查Parameter of Searching格式是否正確
    Do_search();
    ~Do_search();
    void searchmain(Msn_chat_data *msn_chat_data,string filename,string srh_para,string sortof_para);
    //這三個主要處理要被搜尋的資料，也在search主選單就定義好了
    void copy_load_data(Msn_chat_data *small_msn_chat_data,Msn_chat_data *msn_chat_data);
    void tosmall(Msn_chat_data *msn_chat_data,string *parameter);
    void changesmall(string *s);
    //在選單中的功能
    void sort_print(Msn_chat_data *msn_chat_data,string sort_para,vector <int> search_index);  //印出搜尋到的資料
    vector <int> sortsi(vector <int> sorted);  //將印出結果的index排序
    int sort_para_format(string sort_para);  //測試"印出順序的參數"格式是否正確
    string get_srh_chat_num();
    string get_srh_chat_result();
protected:
    Search_virtual *bre;
    Search_used *search_u;
    Do_msn_chat* tomsn_chat;  //宣告msn_chat class
    Chat_main* ini;
private:
    string srh_chat_num;
    string srh_chat_result;
};

#endif // SEARCH_H
