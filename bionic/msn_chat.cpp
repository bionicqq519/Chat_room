/*!
* @file msn_chat.cpp MSN聊天的主要function
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
#include <dir.h>
#include "msn_chat.h"
using namespace std;
Do_msn_chat::Do_msn_chat(){
    ini =new Chat_main();
    msn_chat_data1 = new Msn_chat_data();
}
Do_msn_chat::~Do_msn_chat(){
    delete ini;
    delete msn_chat_data1;
}
/*!
* @brief 將所存入的所有資訊以vector方式存入，包含了speaker ,receiver , chat message , chat time 以便之後的使用 .
* @param msn_chat_data 為欲存入的所有聊天的資料
* @param chat_time 暫存的時間變數
* @param speaker_name 暫存的speaker name變數
* @param receiver_name 暫存的receiver name變數
* @param chat_message 暫存的聊天訊息變數
*/
//存放所有資料的function
void Do_msn_chat::putinto_Msn_chat_data(Msn_chat_data *msn_chat_data
        ,string chat_time,string speaker_name,vector <string> receiver_name,string chat_message){
    int test=0;
    /**/
    for(int i=0;i<msn_chat_data->all.size();i++){
       if(msn_chat_data->all[i]->chat_time==chat_time
          &&msn_chat_data->all[i]->speaker_name==speaker_name
          &&msn_chat_data->all[i]->chat_message==chat_message){
           int re_all=0;
           for(int j=0;j<msn_chat_data->all[i]->receiver_name.size();j++){
               if(msn_chat_data->all[i]->receiver_name[j]!=receiver_name[j]){
                   re_all=1;
               }
           }
           if(re_all==0){
               test=1;
           }
       }
    }
    /**/
    if(test==0){
        Temp_msn_chat_data* temp_msn_chat_data = new Temp_msn_chat_data();
        temp_msn_chat_data->chat_time = chat_time;
        temp_msn_chat_data->speaker_name = speaker_name;
        temp_msn_chat_data->receiver_name = receiver_name;
        temp_msn_chat_data->chat_message = chat_message;
        msn_chat_data->all.push_back(temp_msn_chat_data);
    }

}


vector <string> Do_msn_chat::parseallname(string allname_text){
    int i,data_num_count= 0 ,data_num_count_pos = 0;
    vector <string> tmp_all;
    while((i = allname_text.find("<Friend_Name>",data_num_count_pos))!=string::npos){
        data_num_count++;
        data_num_count_pos = i;

        int j = allname_text.find("</Friend_Name>",data_num_count_pos);
        tmp_all.push_back(allname_text.substr(i+13,j-(i+13)));

        data_num_count_pos = i+1;
    }
    return tmp_all;
}
void Do_msn_chat::writeallname(string q_all_name){
    vector <string> receiver_name;        //o
    string receivername;

    //~~~~~~~~~~~~
    receivername = q_all_name;
    string tmp_receivername = ini->del_space(receivername , ",");
    receivername = "";
    receivername = tmp_receivername;
    //上面三行是去空白然後存起來的
    //cout<<receivername<<endl;
    //cin>>receivername;
    receiver_name.clear();
    string target = ",";
    int i=0,pos = 0,count = 0;
    while((i = receivername.find(target,pos))!=string::npos){
        count++;
        receiver_name.push_back(string(receivername,pos,i-pos));
        pos = i+1;
    }
    receiver_name.push_back(string(receivername,pos,receivername.size()));
    //開啟資料夾
    string filedire = "C:\\chat_record";
    //cout<<chdir(filedire.c_str());
    if(chdir(filedire.c_str())){
        if (mkdir(filedire.c_str()))
        {
            //開啟資料夾失敗
        }
    }
    //filedire+="\\all_name.xml";
    filedire+="\\_AllName.xml";
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    string allname_text;
    allname_text = ini->readxml(filedire);
    vector <string> all_name;
    all_name = parseallname(allname_text);

    for(int l=0;l<receiver_name.size();l++){
        int t_in=0;
        for(int k=0;k<all_name.size();k++){
            if(receiver_name[l] == all_name[k]){
               t_in = 1;
            }
        }
        if(t_in==0){
            all_name.push_back(receiver_name[l]);
        }
    }

    //將原本的資料刪除
    ifstream fin;
    fin.close();
    fin.open(filedire.c_str(), ios::out | ios::trunc);
    fin.close();

    ofstream fout(filedire.c_str(), ios::out | ios::app);

    if (!fout.is_open())
    {
        exit(EXIT_FAILURE);
    }
    //開始匯出XML檔案
    //-------------------------

    fout<<"<XML Friend_Name=\""<<all_name.size()<<"\">"<<endl;


    for(int k=0;k<all_name.size();k++){
        fout<<"\t<Friend_Name>"
                <<all_name[k]<<"</Friend_Name>"<<endl;
    }
    fout<<"</XML>";
    fout.close();

}
/*!
* @brief 處理msn chat要求功能的function .
*/
void Do_msn_chat::msn_chat(string q_speaker,string q_receiver
                           ,string q_chat_msg,string thetime)
{

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    string username;
    string speaker_name;                  //o
    vector <string> receiver_name;        //o
    string receivername;
    string chat_message;  //傳送訊息的內容   //o
    string chat_time;                     //o
    //~~~~~~~~~~~~
    //~~~~~~~~~~~~
    speaker_name = q_speaker;
    //~~~~~~~~~~~~
    receivername = q_receiver;
    string tmp_receivername = ini->del_space(receivername , ",");
    receivername = "";
    receivername = tmp_receivername;
    //上面三行是去空白然後存起來的
    //cout<<receivername<<endl;
    //cin>>receivername;
    receiver_name.clear();
    string target = ",";
    int i=0,pos = 0,count = 0;
    while((i = receivername.find(target,pos))!=string::npos){
        count++;
        receiver_name.push_back(string(receivername,pos,i-pos));
        pos = i+1;
    }
    receiver_name.push_back(string(receivername,pos,receivername.size()));
    //~~~~~~~~~~~~
    chat_message = q_chat_msg;
    string tmp_chat_message = ini->del_space(chat_message , "\\n");
    chat_message = "";
    chat_message = tmp_chat_message;
    chat_time = thetime;
    putinto_Msn_chat_data(msn_chat_data1,chat_time,speaker_name,receiver_name,chat_message);
    //~~~~~~~~~~~~
    writexml(msn_chat_data1,username);
    msn_chat_data1->all.clear();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~


}
/*!
* @brief 建立檔案並把傳入使用者的紀錄匯出xml檔 .
* @param file_name 檔案名稱
*/
//============writexml==============
//匯出參數所傳入人的檔案
void Do_msn_chat::file_out(Msn_chat_data *msn_chat_data,string file_name){
    string file = file_name+".xml";
    //const char * file = "1.txt";
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    string filedire = "C:\\chat_record";
    //cout<<chdir(filedire.c_str());
    if(chdir(filedire.c_str())){
        if (mkdir(filedire.c_str()))
        {
            //開啟資料夾失敗
        }
    }
    file = filedire + "\\" + file;

    ifstream fin;
    //fin.open(file.c_str());
    fin.open(file.c_str());
    string tmp_line,uanyo;
    int test_if_file_exit = 0;
    if (fin.is_open())
    {
        //cout<<"!!!!";
        /*
        cout << "File is created , please save it to other directory first .\n";
        fin.close();
        system("pause");
        exit(EXIT_FAILURE);
        */
        string line;

        getline(fin,line);
        while(fin.good())
        {
            tmp_line = line;
            if((tmp_line.find("<MSN>")==string::npos)&&(tmp_line.find("</MSN>")==string::npos)){
                uanyo =uanyo+line+"\n";
            }
            getline(fin,line);
        }
        //cout<<uanyo;
        test_if_file_exit = 1;
    }
    fin.close();
    fin.open(file.c_str(), ios::out | ios::trunc);
    fin.close();
    fin.open(file.c_str());

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ofstream fout(file.c_str(), ios::out | ios::app);

    if (!fout.is_open())
    {
        cerr << "Can't open " << file << " file for output.\n";
        system("pause");
        exit(EXIT_FAILURE);
    }
    //開始匯出XML檔案
    //-------------------------

    fout<<"<MSN>"<<endl;
    if(test_if_file_exit == 1){
        fout<<uanyo;
    }
    /*
      for (int i=0;i<msn_chat_data_cout;i++){
           fout<<"\t<date>"<<msn_chat_data->all[i]->chat_time<<"</date>";

    }*/
    //entity(msn_chat_data,file_name);
    for(int i=0;i<msn_chat_data->all.size();i++){
        int test = 0;
        if(msn_chat_data->all[i]->speaker_name == file_name){
           test = 1;
        }
        else{
            for(int j=0;j<msn_chat_data->all[i]->receiver_name.size();j++){
                if(msn_chat_data->all[i]->receiver_name[j] == file_name){
                   test = 1;
                }
            }
        }
        if(test==1){
           fout<<"\t<Chat>"<<endl;
           fout<<"\t<date>"<<msn_chat_data->all[i]->chat_time<<"</date>"<<endl;
           fout<<"\t<From>"<<msn_chat_data->all[i]->speaker_name<<"</From>"<<endl;
           fout<<"\t<To Friend_Name=\""<<msn_chat_data->all[i]->receiver_name.size()<<"\">"<<endl;
           for(int k=0;k<msn_chat_data->all[i]->receiver_name.size();k++){
                fout<<"\t<Friend_Name>"<<msn_chat_data->all[i]->receiver_name[k]<<"</Friend_Name>"<<endl;
           }
           fout<<"\t</To>"<<endl;
           fout<<"\t<message>"<<msn_chat_data->all[i]->chat_message<<"</message>"<<endl;
           fout<<"\t</Chat>"<<endl;
        }
    }
    fout<<"</MSN>";
    //msn_chat_data->all.clear();
    cout<<file<<" has been saved."<<endl;
    fout.close();

}
/*!
* @brief 將傳入的字串vector以alphabetical sort排序 .
*        sorted vector中有speaker name不需要排序所以將其找出並以存入位置往最上面丟，
*        而receiver name則是排序後放在所有speaker的下面 .
* @param sorted 所有要被排序的字串vector
* @param speaker_name 存speaker name的vector，用以檢查不需要排序的字串 .
*/
//Hw2 Save(Sort) the name of receiver(s) should be placed in alphabetical order
//這個陣列把speakername放在第一個以先印出，其他receiver作排序
vector <string> Do_msn_chat::sort_alphabet(vector <string> sorted,vector <string> speaker_name){
     //vector<string>::iterator iter = sorted.begin();
     vector <string> order;
     string temp_biggest = "";
     int biggest_index;

     for(int i=0;i<sorted.size();i++){
         //cout<<sorted.size()<<endl;
         for(int j=0;j<speaker_name.size();j++){
            if(speaker_name[j] == sorted[i]){
               //cout<<"!!!!!!!";
               //cout<<a[i]<<speaker_name<<endl;
               order.push_back(sorted[i]);
               /*for(int z=0;z<sorted.size();z++){
                   cout<<"!"<<sorted[z]<<"!"<<endl;
               }*/
               sorted.erase(sorted.begin()+ i);
               /*for(int z=0;z<sorted.size();z++){
                   cout<<"!"<<sorted[z]<<"!"<<endl;
               }*/
               i--;
               break;
            }
         }
         //cout<<sorted.size()<<endl;
     }
     //cout<<sorted.size()<<endl;
     while(sorted.size()!=0){
        for(int i=0;i<sorted.size();i++){
            if(sorted[i]<temp_biggest || temp_biggest==""){
               temp_biggest = sorted[i];
               biggest_index = i;
            }
        }
        order.push_back(temp_biggest);
        temp_biggest = "";
        sorted.erase(sorted.begin()+biggest_index);
        //cout<<sorted.size()<<endl;
        //cout<<biggest_index;
     }
     //-------------------------------------
     //for(int i=0;i<order.size();i++){
         //cout<<order[i]<<endl;
     //}
     //---------------------------------------
     return order;
}
/*!
* @brief 對資料做判斷並用迴圈call flie_out匯出檔案 .
* @param msn_chat_data 為所有聊天的資料
*/
//對資料做判斷並用迴圈call flie_out匯出檔案
void Do_msn_chat::writexml(Msn_chat_data *msn_chat_data,string username){
    /*cout<<msn_chat_data->all[0]->speaker_name<<endl<<username;
    if(msn_chat_data->all[0]->speaker_name==username){
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    }*/
/*
    cout<<msn_chat_data->all[0]->speaker_name<<endl;
    cout<<msn_chat_data->all[0]->receiver_name[0]<<"!"<<msn_chat_data->all[0]->receiver_name[1]<<endl;
    cout<<msn_chat_data->all[0]->chat_message<<endl;
    cout<<msn_chat_data->all[0]->chat_time<<endl;

    cout<<msn_chat_data->all[1]->speaker_name<<endl;
    cout<<msn_chat_data->all[1]->receiver_name[0]<<endl;
    cout<<msn_chat_data->all[1]->chat_message<<endl;
    cout<<msn_chat_data->all[1]->chat_time<<endl;
*/
    //!!!!!!!!!!!!!!!!這一段是抽出所有有參與的人!!!!!!!!!!!!!!!!!!!!!!
    vector <string> all_the_people;
    int yo_speaker = 0,yo_receiver = 0;
    //第一個迴圈是跑一整個內容
    for(int i=0;i<msn_chat_data->all.size();i++){
        //查詢speaker有沒有在暫存的all_the_people裡面
        yo_speaker = 0;
        for(int q=0;q<all_the_people.size();q++){
            //cout<<msn_chat_data->all[i]->speaker_name<<endl<<i<<endl<<username;
            if(all_the_people[q]==msn_chat_data->all[i]->speaker_name){
               yo_speaker =1;
            }
        }
        if(yo_speaker == 0){
            all_the_people.push_back(msn_chat_data->all[i]->speaker_name);
        }

        //查詢receiver有沒有在暫存的all_the_people裡面
        for(int j=0;j<msn_chat_data->all[i]->receiver_name.size();j++){
            yo_receiver = 0;
            for(int q=0;q<all_the_people.size();q++){
                if(all_the_people[q]==msn_chat_data->all[i]->receiver_name[j]){
                   yo_receiver =1;
                }
            }
            if(yo_receiver == 0){
                all_the_people.push_back(msn_chat_data->all[i]->receiver_name[j]);
            }
        }
    }
    /*for(int b=0;b<all_the_people.size();b++){
        cout<<all_the_people[b]<<endl;
    }*/
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    vector <string> speakername;
    for(int i=0;i<msn_chat_data->all.size();i++){
        speakername.push_back(msn_chat_data->all[i]->speaker_name);
    }
    /*
    for(int i=0;i<speakername.size();i++){
        cout<<speakername[i];
    }*/
    //sort
    all_the_people = sort_alphabet(all_the_people,speakername);
    for(int i=0;i<msn_chat_data->all.size();i++){
        vector <string> speaker;
        speaker.push_back(msn_chat_data->all[i]->speaker_name);
        //cout<<msn_chat_data->all.size()<<endl;
        //這邊傳的speakername就根本沒用到了
        msn_chat_data->all[i]->receiver_name
                = sort_alphabet(msn_chat_data->all[i]->receiver_name,speaker);
    }

    for(int b=0;b<all_the_people.size();b++){
        file_out(msn_chat_data,all_the_people[b]);
    }
}


