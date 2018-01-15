#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "chat_used.h"
using namespace std;

/*!
* @brief int轉string的函式 .
* @param i 傳入的int reference
* @return ss.str() 轉成的string
*/
//================Class of gettime()================
//int轉string的副函式
string Chat_main::int2str(int &i) {
  string s;
  stringstream ss(s);
  ss << i;

  return ss.str();
}
//取得系統時間並轉成XML範例所要的樣子的字串
string Chat_main::gettime()
{
    string systemtime_wday;
    string systemtime_month;
    string systemtime_mday;
    string systemtime_hour;
    string systemtime_min;
    string systemtime_sec;
    string systemtime_year;
    //~~~~~~~~~~~~~~~~~~~~~
    time_t long_time;
    time(&long_time);
    struct tm date;
    date = *localtime(&long_time);
    //wday
    if(date.tm_wday == 1){
       systemtime_wday = "Mon";
    }
    else if(date.tm_wday == 2){
       systemtime_wday = "Tus";
    }
    else if(date.tm_wday == 3){
       systemtime_wday = "Wed";
    }
    else if(date.tm_wday == 4){
       systemtime_wday = "Thu";
    }
    else if(date.tm_wday == 5){
       systemtime_wday = "Fri";
    }
    else if(date.tm_wday == 6){
       systemtime_wday = "Sat";
    }
    else if(date.tm_wday == 0){
       systemtime_wday = "Sun";
    }
    //wday
    //============================
    //month
    if(date.tm_mon == 0){
       systemtime_month = "Jan";
    }
    else if(date.tm_mon == 1){
       systemtime_month = "Feb";
    }
    else if(date.tm_mon == 2){
       systemtime_month = "Mar";
    }
    else if(date.tm_mon == 3){
       systemtime_month = "Apr";
    }
    else if(date.tm_mon == 4){
       systemtime_month = "May";
    }
    else if(date.tm_mon == 5){
       systemtime_month = "Jun";
    }
    else if(date.tm_mon == 6){
       systemtime_month = "Jul";
    }
    else if(date.tm_mon == 7){
       systemtime_month = "Aug";
    }
    else if(date.tm_mon == 8){
       systemtime_month = "Sep";
    }
    else if(date.tm_mon == 9){
       systemtime_month = "Oct";
    }
    else if(date.tm_mon == 10){
       systemtime_month = "Nov";
    }
    else if(date.tm_mon == 11){
       systemtime_month = "Dec";
    }
    //month
    //============================
    //mday
    systemtime_mday = int2str(date.tm_mday);
    //mday
    //============================
    //hour
    systemtime_hour = int2str(date.tm_hour);
    if(systemtime_hour.size()==1){
       systemtime_hour = "0"+ systemtime_hour;
    }
    //hour
    //============================
    //min
    systemtime_min = int2str(date.tm_min);
    if(systemtime_min.size()==1){
       systemtime_min = "0"+ systemtime_min;
    }
    //min
    //============================
    //sec
    systemtime_sec = int2str(date.tm_sec);
    if(systemtime_sec.size()==1){
       systemtime_sec = "0"+ systemtime_sec;

    }
    //sec
    //============================
    //year
    int real_year = date.tm_year + 1900;
    systemtime_year = int2str(real_year);
    //year
    //============================
    //systemtime.wday = int2str(date.tm_wday);
    /*
    string wday;
    string month;
    string mday;
    string hour;
    string min;
    string sec;
    string year;
    */
    just_time = "&lt;" + systemtime_hour+":"+systemtime_min+":"
                +systemtime_sec+"&gt;";

    return systemtime_wday+" "+systemtime_month+" "+systemtime_mday+" "
           +systemtime_hour+":"+systemtime_min+":"
           +systemtime_sec+" "+systemtime_year;

}
string Chat_main::get_just_time(){
    return just_time;
}
/*!
* @brief 傳入全部字串以及左右邊的字串，還有欲開始搜尋的位置，function傳回第一次搜尋到的左右邊字串中間所夾的字串 .
* @param test 要被找的字串
* @param b 被夾的字串的左邊
* @param c 被夾的字串的右邊
* @param data_num_count_pos 目前搜尋到的位置
* @return jads 傳回夾到的字串
*/
//把夾起來的中間字串return
string Chat_main::jadz(string text,string b,string c,int data_num_count_pos){
     int i,j;
     string jad;
     int first_size = b.size();
     i = text.find(b,data_num_count_pos);
     j = text.find(c,i+first_size);
     jad = text.substr(i+first_size,j-(i+first_size));
     //cout<<jad;
     return jad;
}


/*!
* @brief 將所存入的所有資訊以vector方式存入，包含了speaker ,receiver , chat message , chat time 以便之後的使用 .
* @param msn_chat_data 為欲存入的所有聊天的資料
* @param chat_time 暫存的時間變數
* @param speaker_name 暫存的speaker name變數
* @param receiver_name 暫存的receiver name變數
* @param chat_message 暫存的聊天訊息變數
*/
//將傳入字串左右的空白消去 s為所有字串 t為欲消除其旁邊空白的字串
string Chat_main::del_space(string s , string t){
    //string s = "d  , dd ,a";
    //cin>>s;
    //cout<<(int)s[2];
    //string t = ",";
    string space = " ";
    string del_left,del_right;
    del_left = space + t;
    del_right = t + space;
    while(1){
       int i = s.find(del_left);
       int j = s.find(del_right);
       if(i != string::npos){
          //cout<<i;
          s.erase(i,1);
          //cout<<s<<endl;
       }
       else if(j != string::npos){
          int del_right_space = t.size() + j;
          s.erase(del_right_space,1);
       }
       else{
          break;
       }
    };
    return s;
}
/*!
* @brief 讀入輸入的xml檔案 .
* @param filename 輸入的檔案名稱
* @param text 將所有讀入的資料存入字串
*/
//3.loadxml
//讀檔
//C:\Qt\2010.04\qt\bionic-build-desktop
string Chat_main::readxml(string filename){
    //Do_msn_chat *m =new Do_msn_chat();
    string temp;  //讀進一個token的暫存檔
    string text;  //所有讀進的資料

    ifstream  inputfile;
    inputfile.open(filename.c_str(), ifstream::in);
    if (inputfile.is_open())
    {
        //int test_msg = 0;
        while(!inputfile.eof())
        {
           inputfile >> temp;

           temp += " " ;
           text += temp;

        }
        text = del_space(text,">");
        //cout<<text;
    }
    inputfile.close();
    return text;
    //parsemsn(msn_chat_data,text);

}
/*!
* @brief 判斷字串是否為1以上的數字，若否則格式錯誤 .
* @param friend_num 字串型態的數字
* @return is_formatnum 若是1以上的數字傳回1，否則為0
*/
//判斷receiver數字是不是0以上 不是就錯 沒有0個人的
int Chat_main::is_formatnum(string friend_num){
    int is_formatnum = 1;
    for(int i=0;i<friend_num.size();i++){
        if((friend_num[i]>='0')&&(friend_num[i]<='9')){
           //cout<<
        }
        else{
           is_formatnum = 0;
        }
    }
    if(friend_num=="0"){
        is_formatnum = 0;
    }
    return is_formatnum;
}
/*!
* @brief 判斷讀入的xml檔案格式是否正確 .
* @param read_text 讀入的所有檔案(字串型態)
* @return test 若格式正確傳回1，否則為0
*/
int Chat_main::test_format(string read_text){
    int test = 1;
    int num_count_pos = 0,i,j;
    int friend_num_int;
    int count_insert;
    int tag_count=0;
    //cout<<read_text<<endl;
    int msn=0,chat=0,date=0,from=0,to=0,friend_n=0,message=0;
    int what_tag;

    while(1){
        //以<為目標 一個一個往下找 找到就判斷<後面與>夾起來的資料
        //是屬於哪一個part，每個標籤都有用part來分順序，大致分別為
        //date-->From-->To-->message
        //而To又有自己特別的格式，像是receiver的數量，傳由另外一個function
        //判斷，若某個部分發現隔式錯誤馬上break傳回0
        //--------------------------------
        i = read_text.find("<",num_count_pos);
        if(i == string::npos){
           break;
        }
        else{
            tag_count++;
        }
        //cout<<i<<"---";
        //j = read_text.find(">",i);
        //cout<<read_text.substr(i,j-i)<<endl;
        //--------------------------------

        //cout<<jadz(read_text,"<",">",i)<<endl;
        //起頭
        string tagvalue = jadz(read_text,"<",">",i);
        count_insert = 0;
        int wt;
        if(date==1){
            count_insert++;
            wt = 1;
        }
        if(from==1){
            count_insert++;
            wt = 2;
        }
        if(to==1){
            count_insert++;
            wt = 3;
        }
        if(friend_n==1){
            count_insert++;
            wt = 4;
        }
        if(message==1){
            count_insert++;
            wt = 5;
        }
       try{
           //避免tag還沒結束就有新的tag產生
           if(count_insert>1){
               string e_tag = "";
               if(what_tag==1){
                   e_tag += "</date> ";
               }
               if(what_tag==2){
                   e_tag += "</From> ";
               }
               if(what_tag==3){
                   e_tag += "</To Friend_Name> ";
               }
               if(what_tag==4){
                   e_tag += "</Friend_Name> ";
               }
               if(what_tag==5){
                   e_tag += "</message> ";
               }
               test = 0;
               //throw Errormsg(e_tag+ "!tag lost");
               //cout<<"17";
           }
           else{
               what_tag = wt;
           }
       }
       catch(Errormsg e){
             cerr<<"Something error is happended about No."<<tag_count
                     <<" tag"<<endl<<e.what()<<endl;
       }
       try{
           if(tagvalue=="MSN"){
               if(msn==0){
                  msn=1;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"1";
                   throw Errormsg("</MSN> tag lost");
               }
           }
           else if (tagvalue=="Chat"){
               if(msn==1 && chat==0 ){
                  chat = 1;
                  //初始各個tag
                  date=0,from=0,to=0,friend_n=0,message=0;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"2";
                   if(chat==1){
                      throw Errormsg("</Chat> tag lost");
                   }
               }
           }
           //date
           else if (tagvalue=="date"){
               if(chat == 1 && date == 0){
                  date = 1;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"3";
                   if(chat==0&&msn==1){
                      throw Errormsg("<Chat> tag lost");
                   }
               }
           }
           else if (tagvalue=="/date"){
               if(date == 1){
                  date = -1;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"4";
                   if(date==0&&chat==1){
                      throw Errormsg("<date> tag lost");
                   }
               }
           }
           //From
           else if (tagvalue=="From"){
               if(chat == 1 && from == 0){
                  from = 1;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"5";
               }
           }
           else if (tagvalue=="/From"){
               if(from == 1){
                  from = -1;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"6";
                   if(from==0&&chat==1){
                      throw Errormsg("<From> tag lost");
                   }
               }
           }
           //To
           else if ((tagvalue.find("To Friend_Name=\"")!= string::npos) && (tagvalue[tagvalue.size()]='"')){
               if(chat == 1 && to == 0){
                  to = 1;
                  string friend_num;
                  friend_num = jadz(tagvalue,"<To Friend_Name=\"","\"",0);
                  //若數字中確實是1以上的數字則轉回int，讓Friend_Name的parse知道要幾次
                  if(is_formatnum(friend_num)==1){
                     friend_num_int=atoi(friend_num.c_str());
                  }
                  else{
                      //格式錯誤
                      test = 0;
                      //cout<<"7";
                  }
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"8";
               }

           }
           else if ( (tagvalue=="Friend_Name") || (tagvalue=="/Friend_Name") ){
               if(tagvalue=="Friend_Name"){
                   if((tagvalue=="Friend_Name")&& ( (to > 0) && (to <= friend_num_int) ) ){
                      friend_n = 1;
                      to++;
                   }
                   else{
                       //格式錯誤
                       test = 0;
                       //cout<<"9";
                   }
               }
               else if(tagvalue=="/Friend_Name"){
                   if(friend_n == 1 ){
                       if(to>friend_num_int){
                           friend_n = -1;
                       }
                       else{
                           friend_n = 0;
                       }
                   }
                   else{
                       //格式錯誤
                       test = 0;
                       //cout<<"10";
                       if(friend_n==0&&chat==1&&to==1){
                           throw Errormsg("<Friend_Name> tag lost");
                       }
                   }
               }

           }
           else if (tagvalue=="/To"){
               if(to!=0 ){
                  to = -1;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"11";
                   if(to==0&&chat==1){
                      throw Errormsg("<To Friend_Name> tag lost");
                   }
               }
           }
           else if (tagvalue=="message"){
               if(chat == 1 && message == 0){
                  message = 1;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"12";
               }
           }
           else if (tagvalue == "/message"){
               if(message == 1){
                  message = -1;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"13";
                   if(message==0&&chat==1){
                      throw Errormsg("<message> tag lost");
                   }
               }
           }
           else if (tagvalue == "/Chat"){
               if(chat == 1){
                  chat = 0;
                  if(date>=0||from>=0||to>=0||friend_n>=0||message>=0){
                      string e_tag = "";
                      if(date>0){
                          e_tag += "</date> ";
                      }
                      if(from>0){
                          e_tag += "</From> ";
                      }
                      if(to>0){
                          e_tag += "</To> ";
                      }
                      if(friend_n>0){
                          e_tag += "</Friend_Name> ";
                      }
                      if(message>0){
                          e_tag += "</message> ";
                      }
                      test = 0;
                      if(e_tag!=""){
                         throw Errormsg(e_tag+ "tag lost");
                      }

                      //cout<<"18";
                  }
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"14";
                   //if(chat==0){
                     // throw Errormsg("<Chat> tag lost");

                   //}
               }
           }
           else if ((tagvalue=="/MSN")){
               if(msn == 1){
                  msn = 0;
               }
               else{
                   //格式錯誤
                   test = 0;
                   //cout<<"15";
                   if(msn==0){
                      throw Errormsg("<MSN> tag lost");
                   }
               }
           }
           else{
               //未定義的tag
               test = 0;
               //cout<<"16";
               throw Errormsg("<"+tagvalue+"> is the error tag . ");

           }

       }
       catch(Errormsg e){
           cerr<<"Something error is happended about No."<<tag_count
                   <<" tag"<<endl<<e.what()<<endl;
       }
       num_count_pos = i+1;



    }
    try{
        if(msn==1||chat==1){
           test = 0;
           if(msn==1){
               throw Errormsg("</MSN> tag lost");
           }
           else if(chat==1){
               throw Errormsg("</Chat> tag lost");
           }
        }
    }
    catch(Errormsg e){
        cerr<<"Something error is happended about No."<<tag_count
                <<" tag"<<endl<<e.what()<<endl;
    }

    return test;
}


