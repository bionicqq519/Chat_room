/*
   1.
   2.and進去以後switch打開，計算年月日時的次數，兩次以上則error，timeparatrans也要有switch
   3.
*/
/*!
* @file search.cpp 搜尋功能
* @author 99598019 李宗人
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <iterator>
#include "search.h"
using namespace std;
//測試有沒有不合理的語句暫存變數
//int and_switch;
//int error =0;
//int year_count;
//int month_count;
//int week_count;
//int hour_count;
//--------------------
Do_search::Do_search(){
    format_error=0;
    search_u = new Search_used();
    bre = new Dotimesearch();
    tomsn_chat =new Do_msn_chat();  //宣告msn_chat class
    ini =new Chat_main();
}
Do_search::~Do_search(){
    delete search_u;
    delete bre;
    delete tomsn_chat;
    delete ini;
}

/*!
* @brief 判斷Parameter of Sorting Result的格式是否正確 .
* @param sort_para 為Parameter of Sorting Result
* @return e 格式正確傳0，錯誤傳1
*/
int Do_search::sort_para_format(string sort_para){
    int e=0;
    if((sort_para.size()%2)==1){
        for(int i=0;i<sort_para.size();i++){
            if(((i%2==0)&&(sort_para[i]>='1')&&(sort_para[i]<='4'))||((i%2==1)&&(sort_para[i]==','))){
               //格式正確
            }
            else{
               e=1;
            }
        }
    }
    else{
       e=1;
    }
    return e;
}
/*!
* @brief 將load的資料先copy一份，並在某些地方加入我要比對的格式 .
* @param small_msn_chat_data 新copy的被比較的資料，且轉成我要的格式
* @param msn_chat_data load的資料
*/
void Do_search::copy_load_data(Msn_chat_data *small_msn_chat_data,Msn_chat_data *msn_chat_data){

    for(int j=0;j<msn_chat_data->all.size();j++){
        string time;
        int i,pos=0,count=0;
        time = msn_chat_data->all[j]->chat_time;

        while((i = time.find(" ",pos))!=string::npos){
            count++;
            if(count==2||count==3){
                if(time[i+2]>='0'&&time[i+2]<='9'){}
                else{
                   time.insert(i+1,"0");
                }
            }
            else if(count==4){
                time.insert(i+1,"y");
            }
            pos = i+1;
        }
        time += "y";
        //cout<<time<<endl;
        tomsn_chat->putinto_Msn_chat_data(small_msn_chat_data,time
                                                 ,msn_chat_data->all[j]->speaker_name
                                                 ,msn_chat_data->all[j]->receiver_name
                                                 ,msn_chat_data->all[j]->chat_message);
    }
}
/*!
* @brief 將字串從大寫轉小寫 .
* @param s 傳入的字串
*/
void Do_search::changesmall(string *s){
    string msg;
    msg = *s;
    for(size_t index=0;index!=msg.size();++index){
        msg[index]=tolower(msg[index]);
    }
    *s = msg;
}
/*!
* @brief 將所有資料從大寫轉小寫 .
* @param msn_chat_data 為copy的load資料
* @param parameter 為Parameter of Sorting Result
*/
void Do_search::tosmall(Msn_chat_data *msn_chat_data,string *parameter){
     //paramter
     string para;
     para = *parameter;
     changesmall(&para);
     *parameter = para;
     //-------------------------
     for(int j=0;j<msn_chat_data->all.size();j++){
         changesmall(&msn_chat_data->all[j]->chat_time);
         changesmall(&msn_chat_data->all[j]->speaker_name);
         for(int l=0;l<msn_chat_data->all[j]->receiver_name.size();l++){
             changesmall(&msn_chat_data->all[j]->receiver_name[l]);
         }
         changesmall(&msn_chat_data->all[j]->chat_message);
     }
}

/*!
* @brief 將資料由小到大排序 .
* @param sorted 要排序的資料
* @return order 排序完的資料
*/
vector <int> Do_search::sortsi(vector <int> sorted){
      vector <int> order;
      int temp_biggest = -1,biggest_index;
      while(sorted.size()!=0){
        for(int i=0;i<sorted.size();i++){
            if(sorted[i]<temp_biggest || temp_biggest==-1){
               temp_biggest = sorted[i];
               biggest_index = i;
            }
        }
        order.push_back(temp_biggest);
        temp_biggest = -1;
        sorted.erase(sorted.begin()+biggest_index);
        //cout<<sorted.size()<<endl;
        //cout<<biggest_index;
     }
     return order;
}
/*!
* @brief 印出search完的資料 .
* @param msn_chat_data load的資料
* @param sort_para 排序的參數
* @param search_index 被搜尋的index存的資料
*/
void Do_search::sort_print(Msn_chat_data *msn_chat_data,string sort_para,vector <int> search_index){
    srh_chat_num = "";
    srh_chat_result = "";
    string target = ",";
    int i=0,pos = 0;
    vector <int> sort_pa;

    while((i = sort_para.find(target,pos))!=string::npos){
        string number = string(sort_para,pos,i-pos);
        sort_pa.push_back(atoi(number.c_str()));
        pos = i+1;
    }
    string number = string(sort_para,pos,i-pos);
    sort_pa.push_back(atoi(number.c_str()));
    /*for(int k=0;k<sort_pa.size();k++){
        cout<<sort_pa[k]<<endl;
    }*/
    //將歷史紀錄依存入檔案的順序排序
    search_index = sortsi(search_index);
    cout<<"Total Chat : "<<search_index.size()<<endl;
    int the_chat_size = search_index.size();
    srh_chat_num = ini->int2str(the_chat_size);

    if(search_index.size()==0){
       cout<<"Nothing to be searched!"<<endl;
    }
    else{
        for(int j=0;j<search_index.size();j++){
            cout<<"Chat "<<j+1<<endl;
            int ja1 = j+1;
            srh_chat_result += ("Chat " + ini->int2str(ja1) + "\n");
            for(int k=0;k<sort_pa.size();k++){
                if(sort_pa[k]==1){
                   cout<<"<Time>"<<endl;
                   cout<<msn_chat_data->all[search_index[j]]->chat_time<<endl;
                   srh_chat_result += ("<Time>\n"+msn_chat_data->all[search_index[j]]->chat_time+"\n");
                }
                else if(sort_pa[k]==2){
                   cout<<"<Speaker>"<<endl;
                   cout<<msn_chat_data->all[search_index[j]]->speaker_name<<endl;
                   srh_chat_result += ("<Speaker>\n"+msn_chat_data->all[search_index[j]]->speaker_name+"\n");
                }
                else if(sort_pa[k]==3){
                    cout<<"<Receiver>"<<endl;
                    srh_chat_result += ("<Receiver>\n");
                    for(int l=0;l<msn_chat_data->all[search_index[j]]->receiver_name.size();l++){
                        cout<<msn_chat_data->all[search_index[j]]->receiver_name[l]<<endl;
                        srh_chat_result += (msn_chat_data->all[search_index[j]]->receiver_name[l]+"\n");
                    }
                }
                else if(sort_pa[k]==4){
                   cout<<"<Message>"<<endl;
                   srh_chat_result += ("<Message>\n");
                   //ini->print_message(msn_chat_data->all[search_index[j]]->chat_message);
                   srh_chat_result += (msn_chat_data->all[search_index[j]]->chat_message);
                   cout<<endl;
                   srh_chat_result += ("\n");
                   //cout<<msn_chat_data->all[search_index[j]]->chat_message<<endl;
                }
            }
            srh_chat_result += ("\n");
        }
        srh_chat_result += ("\n");
    }


    cout<<endl;

}


string Do_search::get_srh_chat_num(){
    return srh_chat_num;
}
string Do_search::get_srh_chat_result(){
    return srh_chat_result;
}
/*!
* @brief 搜尋功能主要的函式，所有搜尋的功能由此function呼叫 .
* @param msn_chat_data load的原始資料
* @param filename讀入的檔案
*/
void Do_search::searchmain(Msn_chat_data *msn_chat_data,string filename,string srh_para,string sortof_para){
     Msn_chat_data* small_msn_chat_data = new Msn_chat_data();
     copy_load_data(small_msn_chat_data,msn_chat_data);

     string parameter ;
     parameter = srh_para;
     string sort_para = "1,2,3,4";
     sort_para = sortof_para;

     search_u->delspace(&parameter);   //這邊裡面有順便檢查格式
     tosmall(small_msn_chat_data,&parameter);
     vector<int> search_index;
     bre->setformat_error(format_error);
     search_index = bre->tobesearched(small_msn_chat_data,parameter,0);
     format_error = bre->getformat_error();
     if(format_error==0&&sort_para_format(sort_para)==0){
        search_u->delsubspace(&sort_para);
        sort_print(msn_chat_data,sort_para,search_index);
     }
     else if(format_error==1){
        format_error = 0;
     }
     else if(sort_para_format(sort_para)==1){
     }
     delete small_msn_chat_data;


}





