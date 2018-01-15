/*!
* @file parse.cpp 對MSN的資料作parse
* @author 99598019 李宗人
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "parse.h"
using namespace std;
Do_parse::Do_parse(){
    ini =new Chat_main();
    tomsn_chat =new Do_msn_chat();  //宣告msn_chat class
}
Do_parse::~Do_parse(){
    delete ini;
    delete tomsn_chat;
}
/*!
* @brief 對檔案的date作parse並回傳date裡面的資料 .
* @param text 為要被parse的字串
* @param data_num_count_pos 目前parse到的位置
* @return date 回傳tag中的date資料
*/
string Do_parse::parsedate(string text,int data_num_count_pos){
     int i,j;
     string date;
     i = text.find("<date>",data_num_count_pos);
     j = text.find("</date>",data_num_count_pos);
     date = text.substr(i+6,j-(i+6));
     return date;

}
/*!
* @brief 對檔案的From作parse並回傳From裡面的資料 .
* @param text 為要被parse的字串
* @param data_num_count_pos 目前parse到的位置
* @return date 回傳tag中的From資料，即speaker
*/
string Do_parse::parsefrom(string text,int data_num_count_pos){
     int i,j;
     string date;
     i = text.find("<From>",data_num_count_pos);
     j = text.find("</From>",data_num_count_pos);
     //cout<<data_num_count_pos<<","<<i<<","<<j<<endl;
     date = text.substr(i+6,j-(i+6));
     //cout<<data_num_count_pos;
     //cout<<date;

     return date;
}
/*!
* @brief 對檔案的To格式作parse並回傳裡面Friend_Name的資料 .
* @param text 為要被parse的字串
* @param data_num_count_pos 目前parse到的位置
* @return rec_name 回傳tag中的receiver name資料
*/
vector <string>  Do_parse::parseto(string text,int data_num_count_pos){

    vector <string> rec_name;
    //vector <string> a;
    //a.push_back("aaa");
    //return a;
    //int i,j;
    //string text = "<ToFriend_Name=\"2\"";
    string friend_num;
    //i = text.find("<ToFriend_Name=\"",data_num_count_pos);
    //j = text.find("\"",i+17);
    //cout<<text;
    //cout<<endl<<i<<endl<<j;
    //friend_num = text.substr(i+17,j-(i+17));
    friend_num = ini->jadz(text,"<To Friend_Name=\"","\"",data_num_count_pos);
    //-----------------------------------------
    int friend_num_int=atoi(friend_num.c_str());
    /*for(i=0;i<friend_num_int;i++){
        cout<<endl<<"d";
    }*/

    int count = 0,i;
    while(count<friend_num_int){
        i = text.find("<Friend_Name>",data_num_count_pos);
        rec_name.push_back(ini->jadz(text,"<Friend_Name>","</Friend_Name>",data_num_count_pos));
        data_num_count_pos = i+1;
        count++;
    }

    return rec_name;
}
/*!
* @brief 對檔案的message作parse並回傳message裡面的資料 .
* @param text 為要被parse的字串
* @param data_num_count_pos 目前parse到的位置
* @return date 回傳tag中的message資料
*/
string Do_parse::parsemessage(string text,int data_num_count_pos){
    int i,j;
    string date;
    i = text.find("<message>",data_num_count_pos);
    j = text.find("</message>",data_num_count_pos);
    date = text.substr(i+9,j-(i+9));
    return date;
}
/*!
* @brief 呼叫各個parse function對檔案作parse .
* @param msn_chat_data 為所有聊天的資料
* @param test 所有讀入的資料字串
*/
//parsemsn------------------------
void Do_parse::parsemsn(Msn_chat_data *msn_chat_data,string text){
    int i,data_num_count= 0 ,data_num_count_pos = 0;
    //Temp_msn_chat_data* temp_msn_chat_data = new Temp_msn_chat_data();

    string speaker_name;                                 //1
    vector <string> receiver_name;                                //2
    string chat_message;  //傳送訊息的內容                 //2
    string chat_time;
    //cout<<text.find("<date>",data_num_count_pos);
    //cout<<text<<endl<<endl;
    while((i = text.find("<date>",data_num_count_pos))!=string::npos){
        data_num_count++;
        data_num_count_pos = i;
        //先清空

        chat_time = "";
        speaker_name = "";
        receiver_name.clear();
        chat_message = "";

        chat_time = parsedate(text,data_num_count_pos);
        //cout<<temp_msn_chat_data->chat_time<<endl;
        speaker_name = parsefrom(text,data_num_count_pos);
        //cout<<temp_msn_chat_data->speaker_name<<endl;
        //這個不知道行不行 應該可以 有用dev c打新的測試過
        receiver_name = parseto(text,data_num_count_pos);
        //cout<<temp_msn_chat_data->receiver_name[0]<<endl;
        chat_message = parsemessage(text,data_num_count_pos);
        //cout<<temp_msn_chat_data->chat_message<<endl;
        tomsn_chat->putinto_Msn_chat_data(msn_chat_data,chat_time,speaker_name,receiver_name,chat_message);


        data_num_count_pos = i+1;

        //cout<<data_num_count_pos<<endl;
    }
/*
    cout<<"~"<<msn_chat_data->all.size()<<"~"<<endl;
    cout<<"ii"<<msn_chat_data->all[0]->chat_time<<endl;
    cout<<"ii"<<msn_chat_data->all[1]->chat_time<<endl;
    cout<<"ii"<<msn_chat_data->all[0]->speaker_name<<endl;
    cout<<"ii"<<msn_chat_data->all[1]->speaker_name<<endl;
    cout<<msn_chat_data->all[0]->receiver_name[0]<<"ii"<<msn_chat_data->all[0]->receiver_name[1]<<endl;
    cout<<"ii"<<msn_chat_data->all[1]->receiver_name[0]<<endl;
    cout<<"ii"<<msn_chat_data->all[0]->chat_message<<endl;
    cout<<"ii"<<msn_chat_data->all[1]->chat_message<<endl;
*/

}



