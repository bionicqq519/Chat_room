#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <iterator>
#include "search_virtual.h"
using namespace std;
Search_virtual::Search_virtual(){
    format_error=0;
    search_u = new Search_used();
    ini =new Chat_main();
}
Search_virtual::~Search_virtual(){
    delete search_u;
    delete ini;
}
void Search_virtual::setformat_error(int up_format_error){
    format_error = up_format_error;
}
int Search_virtual::getformat_error(){
    return format_error;
}
vector<int> Search_virtual::tobesearched(Msn_chat_data *small_msn_chat_data,string parameter,int level){
    vector<int> search_index;
    //msn_chat_data=small_msn_chat_data;
    //q=small_msn_chat_data;
    search_index=searchnot(small_msn_chat_data,parameter,level);
    return search_index;
}
/*!
* @brief 判斷底層 .
*        判斷是否為三大標籤的分層函式，若是time , name , message層
*        則將level值從0轉為其所代表的值 time為1,name為2 ,message
*        為3，並在傳到NOT層作一次切割，而若是已經切割過的標籤層，
*        在依她level的值傳入time , name , message的標籤處理function
*        每種的標籤處理都有獨特的不同
* @param msn_chat_data load的資料
* @param parameter 目前傳入的字串
* @param level 目前的層數
* @return search_index 目前得到的index資料
*/
vector<int> Search_virtual::searchtag(Msn_chat_data *msn_chat_data,string parameter,int level){
    vector<int> search_index;
    int pos = 0;
    if(level==0){
       int i,j,k;
       i= parameter.find("[time]:",0);
       j = parameter.find("[name]:",0);
       k = parameter.find("[message]:",0);
       //if(i != string::npos)
       if( i == 0){
          search_index =  searchnot(msn_chat_data,parameter.substr(pos+7,parameter.size()-7),1);
       }
       else if(j == 0){
          search_index =  searchnot(msn_chat_data,parameter.substr(pos+7,parameter.size()-7),2);
       }
       else if(k == 0){
          search_index =  searchnot(msn_chat_data,parameter.substr(pos+10,parameter.size()-10),3);
       }
       else{
          format_error = 1;
       }
    }
    else{
        if(parameter[0]!='\"'||parameter[parameter.size()-1]!='\"'){format_error = 1;}
        parameter = parameter.substr(pos+1,parameter.size()-2);
        search_u->dellr(&parameter," ");
        if(level==1){
            Search_virtual* src = new Dotimesearch();
            search_index =  src->search(msn_chat_data,parameter,1);
            delete src;
            //search_index =  searchtime(msn_chat_data,parameter,1);
        }
        else if(level==2){
            int i = parameter.find("]");
            string left,right;
            left = parameter.substr(0,i+1);
            search_u->delsubspace(&left);
            right = parameter.substr(i+1,parameter.size()-(i+1));
            search_u->dellr(&right," ");
            parameter = left + right;
            Search_virtual* src = new Donamesearch();
            search_index =  src->search(msn_chat_data,parameter,1);
            delete src;
            //search_index =  searchname(msn_chat_data,parameter,2);
        }
        else if(level==3){
            Search_virtual* src = new Domessagesearch();
            search_index =  src->search(msn_chat_data,parameter,1);
            delete src;
            //search_index =  searchmessage(msn_chat_data,parameter,3);
        }
    }
    //search_index.push_back(1);
    //cout<<parameter<<endl;
    return search_index;
}
/*!
* @brief 處理AND的function .
*        將參數由AND切開，並將切開後的字串往下傳遞，
*        下面傳回的資料作AND處理，return
*        在此層已經找到的訊息資料的index .
* @param msn_chat_data load的資料
* @param parameter 目前傳入的字串
* @param level 目前的層數
* @return search_index 目前得到的index資料
*/
vector<int> Search_virtual::searchand(Msn_chat_data *msn_chat_data,string parameter,int level){
    //and_switch = 1;
    vector<int> search_index;
    vector<int> and_index;

    int pos = 0;
    int i;
    int tag_lenth;
    string tag;
    if(level==0){
       tag="&&";
       tag_lenth = 2;
    }
    else{
       tag="&";
       tag_lenth = 1;
    }
    while((i = parameter.find(tag,pos))!=string::npos){
        //search_index = searchtag(msn_chat_data,parameter.substr(pos,i-pos),level);
        //cout<<parameter;
        if(search_index.size()!=0){
           //cout<<parameter.substr(pos,i-pos)<<endl;
           if(parameter.substr(pos,i-pos).size()==0){format_error=1;}
           vector<int> tmp_index = searchtag(msn_chat_data,parameter.substr(pos,i-pos),level);
           tmp_index = search_u->groupby(tmp_index);
           for(int j=0;j<search_index.size();j++){
               //search_index.push_back(tmp_index[j]);
               for(int k=0;k<tmp_index.size();k++){
                    if(search_index[j]==tmp_index[k]){
                       and_index.push_back(search_index[j]);
                    }
                }
           }
        }
        else{
            if(parameter.substr(pos,i-pos).size()==0){format_error=1;}
            and_index = searchtag(msn_chat_data,parameter.substr(pos,i-pos),level);
            and_index = search_u->groupby(and_index);
        }
        search_index = and_index;
        /*cout<<parameter.substr(pos,i-pos);
        for(int i=0;i<search_index.size();i++){
                   cout<<search_index[i]<<" ";
               }*/
        and_index.clear();
        pos = i;
        pos = i+tag_lenth;
    }
    if(parameter.find(tag,0)!=string::npos){
       //cout<<parameter.substr(pos,parameter.size()-pos);
       if(parameter.substr(pos,parameter.size()-pos).size()==0){format_error=1;}
       vector<int> tmp_index = searchtag(msn_chat_data,parameter.substr(pos,parameter.size()-pos),level);
       tmp_index = search_u->groupby(tmp_index);
       //cout<<parameter.substr(pos,parameter.size()-pos);
       /*for(int i=0;i<search_index.size();i++){
           cout<<search_index[i]<<" ";
       }
       cout<<endl;
       for(int i=0;i<tmp_index.size();i++){
           cout<<tmp_index[i]<<" ";
       }
       cout<<endl;cout<<endl;cout<<endl;*/
       for(int j=0;j<search_index.size();j++){
           //search_index.push_back(tmp_index[j]);
           for(int k=0;k<tmp_index.size();k++){
                if(search_index[j]==tmp_index[k]){
                   and_index.push_back(search_index[j]);
                }
            }
       }
    }
    else{
       if(parameter.substr(pos,parameter.size()-pos).size()==0){format_error=1;}
       and_index = searchtag(msn_chat_data,parameter.substr(pos,parameter.size()-pos),level);
       and_index = search_u->groupby(and_index);
    }
    search_index = and_index;
    /*cout<<parameter;
    for(int i=0;i<search_index.size();i++){
        cout<<search_index[i]<<endl;
    }
    cout<<endl;*/
    //if(month_count>=2||week_count>=2||hour_count>=2||year_count>=2){
    //   error = 1;
    //}
    //month_count=0;
    //week_count=0;
    //hour_count=0;
    //year_count=0;

    //and_switch = 0;

    return search_index;
}
/*!
* @brief 處理OR的function .
*        將參數由OR切開，並將切開後的字串往下傳遞，下面傳回的資料
*        作OR處理，return 在此層已經找到的訊息資料的index
* @param msn_chat_data load的資料
* @param parameter 目前傳入的字串
* @param level 目前的層數
* @return search_index 目前得到的index資料
*/
//用||拆
vector<int> Search_virtual::searchrange(Msn_chat_data *msn_chat_data,string parameter,int level){
    vector<int> search_index;
    int pos = 0;
    int i;
    int tag_lenth;
    string tag;
    if(level==0){
       tag="||";
       tag_lenth = 2;
    }
    else{
       tag="|";
       tag_lenth = 1;
    }
    while((i = parameter.find(tag,pos))!=string::npos){
        //cout<<parameter.substr(pos,i-pos)<<endl;
        if(parameter.substr(pos,i-pos).size()==0){format_error=1;}
        vector<int> tmp_index = searchand(msn_chat_data,parameter.substr(pos,i-pos),level);
        for(int j=0;j<tmp_index.size();j++){
            search_index.push_back(tmp_index[j]);
        }
        pos = i;
        pos = i+tag_lenth;

    }
    //cout<<parameter.substr(pos,parameter.size()-pos);
    if(parameter.substr(pos,parameter.size()-pos).size()==0){format_error=1;}
    vector<int> tmp_index = searchand(msn_chat_data,parameter.substr(pos,parameter.size()-pos),level);
    for(int j=0;j<tmp_index.size();j++){
        search_index.push_back(tmp_index[j]);
    }

    search_index = search_u->groupby(search_index);

    return search_index;
}
/*!
* @brief 處理NOT的function .
*        將參數由NOT切開，並將切開後的字串往下傳遞，下面傳回的資料
*        作NOT處理，return 在此層已經找到的訊息資料的index
* @param msn_chat_data load的資料
* @param parameter 目前傳入的字串
* @param level 目前的層數
* @return search_index 目前得到的index資料
*/
vector<int> Search_virtual::searchnot(Msn_chat_data *msn_chat_data,string parameter,int level){
    vector<int> search_index;
    int pos = 0;
    int i;
    int tag_lenth;
    string tag;
    if(level==0){
       tag="~~";
       tag_lenth = 2;
    }
    else{
       tag="~";
       tag_lenth = 1;
    }
    //search_index.push_back(1);
    if(parameter.substr(0,tag_lenth)==tag){
        //cout<<"!!!!!!!!!";
        for(int k=0;k<msn_chat_data->all.size();k++){
            search_index.push_back(k);
        }
        pos = tag_lenth;
        while((i = parameter.find(tag,pos))!=string::npos){
            //cout<<parameter.substr(pos,i-pos)<<endl;
            if(parameter.substr(pos,i-pos).size()==0){format_error=1;}
            vector<int> tmp_index = searchrange(msn_chat_data,parameter.substr(pos,i-pos),level);
            for(int j=0;j<search_index.size();j++){
                for(int k=0;k<tmp_index.size();k++){
                    if(search_index[j]==tmp_index[k]){
                       search_index.erase(search_index.begin()+ j);
                       j--;
                       break;
                    }
                }
            }
            pos = i;
            pos = i+tag_lenth;

        }
        //cout<<parameter.substr(pos,parameter.size()-pos);
        if(parameter.substr(pos,parameter.size()-pos).size()==0){format_error=1;}
        vector<int> tmp_index = searchrange(msn_chat_data,parameter.substr(pos,parameter.size()-pos),level);
        //for(int k=0;k<tmp_index.size();k++){
        //    cout<<tmp_index[k]<<endl;
        //}
        for(int j=0;j<search_index.size();j++){
            for(int k=0;k<tmp_index.size();k++){
                if(search_index[j]==tmp_index[k]){
                   search_index.erase(search_index.begin()+ j);
                   j--;
                   break;
                }
            }
        }
        return search_index;
    }
    else{
        //cout<<level<<endl;
        while((i = parameter.find(tag,pos))!=string::npos){
            if(pos==0){
                //cout<<parameter.substr(pos,i-pos)<<endl;
                if(parameter.substr(pos,i-pos).size()==0){format_error=1;}
                search_index = searchrange(msn_chat_data,parameter.substr(pos,i-pos),level);
                /*for(int i=0;i<search_index.size();i++){
                    cout<<search_index[i]<<endl;
                    //cout<<"!"<<search_index.size()<<"!";
                }*/
            }
            if(pos!=0){
               vector<int> tmp_index = searchrange(msn_chat_data,parameter.substr(pos,i-pos),level);
               for(int j=0;j<search_index.size();j++){
                   for(int k=0;k<tmp_index.size();k++){
                       if(search_index[j]==tmp_index[k]){
                          search_index.erase(search_index.begin()+ j);
                          j--;
                          break;
                       }
                   }
               }
            }
            pos = i;
            pos = i+tag_lenth;


        }
        if(parameter.find(tag,0)!=string::npos){
           //cout<<parameter.substr(pos,parameter.size()-pos)<<endl;
           if(parameter.substr(pos,parameter.size()-pos).size()==0){format_error=1;}
           vector<int> tmp_index = searchrange(msn_chat_data,parameter.substr(pos,parameter.size()-pos),level);
           /*for(int i=0;i<tmp_index.size();i++){
               cout<<tmp_index[i]<<endl;
           }
           cout<<endl<<endl;*/
           /*for(int i=0;i<search_index.size();i++){
               cout<<search_index[i]<<endl;
           }*/
           for(int j=0;j<search_index.size();j++){
               for(int k=0;k<tmp_index.size();k++){
                   if(search_index[j]==tmp_index[k]){
                      search_index.erase(search_index.begin()+ j);
                      j--;
                      break;
                   }
               }
           }
        }
        else{
           if(parameter.substr(pos,parameter.size()-pos).size()==0){format_error=1;}
           search_index = searchrange(msn_chat_data,parameter.substr(pos,parameter.size()-pos),level);
        }
        //cout<<endl<<endl;
        return search_index;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*!
* @brief 將message裡面的標籤作處理之後再去搜尋load的資料，看看有哪幾個Index符合後往上回傳 .
* @param msn_chat_data load的資料
* @param parameter 目前傳入的字串
* @param level 目前的層數
* @return search_index 目前得到的index資料
*/
//搜尋
vector<int> Domessagesearch::search(Msn_chat_data *msn_chat_data,string parameter,int level){
    vector<int> search_index;
    for(int i=0;i<msn_chat_data->all.size();i++){
        if(msn_chat_data->all[i]->chat_message.find(parameter,0)!= string::npos){
           search_index.push_back(i);
        }
    }
    //cout<<parameter<<level<<endl;
    /*for(int i=0;i<search_index.size();i++){
        cout<<search_index[i]<<endl;
    }*/
    return search_index;
}
/*!
* @brief 將name裡面的標籤作處理之後再去搜尋load的資料，看看有哪幾個Index符合後往上回傳 .
* @param msn_chat_data load的資料
* @param parameter 目前傳入的字串
* @param level 目前的層數
* @return search_index 目前得到的index資料
*/
vector<int> Donamesearch::search(Msn_chat_data *msn_chat_data,string parameter,int level){
    vector<int> search_index;
    //cout<<parameter<<" ";
    //cout<<parameter.substr(0,4)<<endl;
    if(parameter.substr(0,3)=="[r]"){
        for(int i=0;i<msn_chat_data->all.size();i++){
            int test_r=0;
            for(int j=0;j<msn_chat_data->all[i]->receiver_name.size();j++){
                //cout<<i<<" "<<msn_chat_data->all[i]->receiver_name[j]<<" "<<parameter.substr(3,parameter.size()-3)<<endl;
                if(msn_chat_data->all[i]->receiver_name[j]==parameter.substr(3,parameter.size()-3)){
                   test_r=1;
                   //cout<<"!!!!!";
                }
            }
            if(test_r==1){
               //cout<<i;
               search_index.push_back(i);
            }
        }
    }
    else if(parameter.substr(0,3)=="[s]"){
        for(int i=0;i<msn_chat_data->all.size();i++){
            if(msn_chat_data->all[i]->speaker_name==parameter.substr(3,parameter.size()-3)){
                    search_index.push_back(i);
            }
        }
    }
    else{
        int pos;
        if(parameter.substr(0,4)=="[sr]"||parameter.substr(0,4)=="[rs]"){
           pos = 4;
        }
        else{
           pos = 0;
        }
        for(int i=0;i<msn_chat_data->all.size();i++){
            int test_r=0;
            for(int j=0;j<msn_chat_data->all[i]->receiver_name.size();j++){
                //cout<<i<<" "<<msn_chat_data->all[i]->receiver_name[j]<<" "<<parameter.substr(3,parameter.size()-3)<<endl;

                if(msn_chat_data->all[i]->receiver_name[j]==parameter.substr(pos,parameter.size()-pos)){
                   test_r=1;
                   //cout<<"!!!!!";
                }
            }
            if(test_r==1){
               //cout<<i;
               search_index.push_back(i);
            }
        }
        //--------------------------------------------------------------------------------------------
        for(int i=0;i<msn_chat_data->all.size();i++){
            if(msn_chat_data->all[i]->speaker_name==parameter.substr(pos,parameter.size()-pos)){
                    search_index.push_back(i);
            }
        }
        search_index = search_u->groupby(search_index);
    }
    /*for(int i=0;i<search_index.size();i++){
        cout<<search_index[i]<<endl;
    }*/
    //cout<<parameter<<level<<endl;
    return search_index;
}
/*!
* @brief 將time裡面的標籤作處理之後再去搜尋load的資料，看看有哪幾個Index符合後往上回傳 .
* @param msn_chat_data load的資料
* @param parameter 目前傳入的字串
* @param level 目前的層數
* @return search_index 目前得到的index資料
*/
vector<int> Dotimesearch::search(Msn_chat_data *msn_chat_data,string parameter,int level){
    vector<int> search_index;
    int k=0,data_num_count=0,monthday=0,data_num_count_pos=0;
    while((k = parameter.find(" ",data_num_count_pos))!=string::npos){
        data_num_count++;
        //if(parameter[k+3]!=' '){cout<<"!!!!!!!!!!!!!!!!!!!!!!!";}
        if((parameter[k-1]>='a'&&parameter[k-1]<='z')
            &&(parameter[k+1]>='0'&&parameter[k+1]<='9')
            &&!(parameter[k+3]>='0'&&parameter[k+3]<='9')){
            data_num_count_pos = k+1;
            monthday=1;
        }
        else{
            parameter.replace(k,1,"\"&\"");
            data_num_count_pos = k;
        }
        //cout<<parameter[k+3];
        //cout<<parameter<<endl;
        //cout<<data_num_count_pos<<endl;
    }
    if(data_num_count==0||(monthday==1&&data_num_count==1)){
        parameter = timeparatrans(parameter);
        //cout<<parameter<<endl;
        for(int i=0;i<msn_chat_data->all.size();i++){
            if(msn_chat_data->all[i]->chat_time.find(parameter,0)!= string::npos){
               //cout<<msn_chat_data->all[i]->chat_time<<endl;
               search_index.push_back(i);
            }
        }
        //cout<<parameter<<level<<endl;
        /*for(int i=0;i<search_index.size();i++){
            cout<<search_index[i]<<endl;
        }*/
        //cout<<parameter<<level<<endl;
    }
    else{
        parameter = "\""+parameter+"\"";
        //cout<<parameter;
        search_index = searchand(msn_chat_data,parameter,level);
        /*for(int a=0;a<search_index.size();a++){
            cout<<search_index[a]<<endl;
        }*/
    }

    return search_index;
}

/*!
* @brief 將time標籤處理成符合的資料格式，讓它可以搜尋得到 .
* @param parameter 要處理的標籤
* @return parameter 將標籤處理完傳回
*/
string Dotimesearch::timeparatrans(string parameter){

    //month
    //int month_switch = 1;
    vector <string> month;
    int mon_pos = 0;
    int inm_pos = 0;
    month.push_back("jannuary");
    month.push_back("february");
    month.push_back("march");
    month.push_back("april");
    month.push_back("may");
    month.push_back("june");
    month.push_back("july");
    month.push_back("august");
    month.push_back("september");
    month.push_back("october");
    month.push_back("november");
    month.push_back("december");
    for(int i=0;i<month.size();i++){
        mon_pos = parameter.find(month[i]);
        if(mon_pos != string::npos){
           parameter.erase(mon_pos+3,month[i].size()-3);
        }
        inm_pos = parameter.find(month[i].substr(0,3));
        //~~~~~~~~~~~~~~~~~~
        if(inm_pos!=string::npos){
            //if((month_switch==1)&&(and_switch==1)){
            //    month_count++;
            //    month_switch=0;
            //}
            if((inm_pos+3)==parameter.size()){
                //parameter+=" ";
            }
            else{
                //cout<<parameter<<endl<<endl;
                if(parameter.size()!=6){
                   //cout<<"!!!!!!!";
                   parameter.insert(parameter.size()-1,"0");
                }
                //cout<<parameter<<endl<<endl;
                //parameter.insert(inm_pos+3," ");
            }
            //cout<<parameter<<endl;
        }
        //cout<<parameter<<endl;
        //~~~~~~~~~~~~~~~~~~
    }
    //week
    //int week_switch = 1;
    vector <string> week;
    int inw_pos = 0;
    int week_pos = 0;
    week.push_back("monday");
    week.push_back("tuesday");
    week.push_back("wednesday");
    week.push_back("thursday");
    week.push_back("friday");
    week.push_back("saturday");
    week.push_back("sunday");
    for(int i=0;i<week.size();i++){
        week_pos = parameter.find(week[i]);
        if(week_pos != string::npos){
           parameter.erase(week_pos+3,week[i].size()-3);
        }
        //~~~~~~~~~~~~~~~~~~
        inw_pos = parameter.find(week[i].substr(0,3));
        if(inw_pos!=string::npos){
            //if((week_switch==1)&&(and_switch==1)){
            //    week_count++;
            //    week_switch=0;
            //}
            if((inw_pos+3)==parameter.size()){
                //parameter+=" ";
            }
            else{
                //parameter.insert(inw_pos+3," ");
                //cout<<parameter;
            }
        }
        //cout<<parameter<<endl;
        //~~~~~~~~~~~~~~~~~~
    }
    //hour min sec
    if(parameter.substr(0,1) == "h"){
        //hour_count++;
        if(parameter.size()==2){
           parameter = " 0" + parameter.substr(1,parameter.size()-1)+ ":" ;
        }
        else{
            parameter = " " + parameter.substr(1,parameter.size()-1)+ ":" ;
        }
        //cout<<parameter<<endl<<endl;
    }
    if((ini->is_formatnum(parameter)==1)||parameter=="0"){
        parameter = "y"+parameter + "y";
    }
    //if(parameter.substr(0,1) == "m"){
    //    parameter = ":" + parameter.substr(1,parameter.size()-1)+ ":" ;
    //}
    //if(parameter.substr(0,1) == "s"){
    //    parameter = ":" + parameter.substr(1,parameter.size()-1)+ " " ;
    //}
    //year
    //if((parameter.size()==4)&&(is_formatnum(parameter)==1)){
       //year_count++;
       //cout<<"!!!!!!!!!!!!!"<<endl;
    //}

    return parameter;
}
//--------

