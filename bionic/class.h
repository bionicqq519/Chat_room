#ifndef CLASS_H
#define CLASS_H
//----------------------------------
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

//==================================
class Temp_msn_chat_data{
   public:
       /*1代表使用者輸入階段即存到變數
         2代表要匯入XML檔的時候才處理*/
       string speaker_name;
       vector <string> receiver_name;
       string chat_message;  //傳送訊息的內容
       string chat_time;
};
class Msn_chat_data{
   public:
       vector<Temp_msn_chat_data*> all;

};
//==================================
//==================================
#endif // CLASS_H
