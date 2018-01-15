#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <iterator>
#include "search_used.h"
using namespace std;
Search_used::Search_used(){
    chat_u = new Chat_main();
}
Search_used::~Search_used(){
    delete chat_u;
}
/*!
* @brief 把字串左右的tag刪除 .
* @param s 要去左右tag的字串
* @param tag 為要去的字
*/
void Search_used::dellr(string *s,string tag){
    // *
    string bedel;
    bedel = *s;
    //-----------
    while(1){
       int isdel = 0;
       int i = bedel.find(tag);
       if(( i != string::npos )&& (i==0) ){
          //cout<<i;
          bedel.erase(i,1);
          isdel = 1;
          //cout<<s<<endl;
       }
       int j = bedel.rfind(tag);
       if(( j != string::npos )&& (j==bedel.size()-1) ){
          bedel.erase(j,1);
          isdel = 1;
       }
       if(isdel==0){
          break;
       }
    };
    *s = bedel;  //    *
    //string delspace(string s)
    //return s;
}
/*!
* @brief 將所有空白刪去 .
* @param s 要去空白的字串
*/
void Search_used::delsubspace(string *s){
    // *
    string bedel;
    bedel = *s;
    //-----------
    string space = " ";
    while(1){
       int i = bedel.find(space);
       if(i != string::npos){
          //cout<<i;
          bedel.erase(i,1);
          //cout<<s<<endl;
       }
       else{
          break;
       }
    };
    *s = bedel;  //*
    //string delspace(string s)
    //return s;
}
//hw3 error massage
void Search_used::testparaif(string s,int location){
     //chat_u->jaz();
    int i,j;
    int first_size = 1;
    i = s.find("[",0);
    j = s.find("]:",i+first_size);
    //cout<<j;
    string srange,blogic;
    //srange = chat_u->jaz(s,"[","]:",0);
    try{
        if( (i!=string::npos) && (j!=string::npos) ){
            blogic = s.substr(0,i);
            if((blogic!="~~")&&(blogic!="||")&&(blogic!="&&")&&(blogic!="")){
                //cout<<"["<<blogic<<"] is not the right notation . "<<endl;
                cout<<"Something error on about locate "<<location<<endl;
                throw Errormsg("["+blogic+"] is not the right notation . ") ;
            }
            srange = chat_u->jadz(s,"[","]:",0);
            if((srange!="time")&&(srange!="name")&&(srange!="message")){
                //cout<<"["<<srange<<"] is not search range . "<<endl;
                cout<<"Something error on about locate "<<location<<endl;
                throw Errormsg("["+srange+"] is not search range . ") ;
            }
        }
        else{
            if((s!="|\"")&&(s!="~\"")&&(s!="&\"")){
               //cout<<"["<<s.substr(0,s.size()-1)<<"] is not the right notation . "<<endl;
                cout<<"Something error before locate "<<location<<endl;
                throw Errormsg("["+s.substr(0,s.size()-1)+"] is not the right notation . ") ;
            }
        }
    }
    catch(Errormsg e){
        cerr<<e.what()<<endl;
    }

}
/*!
* @brief 將" "裡面的空白留著，其他刪去 .
* @param s 要處理的字串
*/
void Search_used::delspace(string *s){
     string bedel;
     bedel = *s;
     string tmp="";
     int i,loc=0,ll=0;
     string mau = "\"";
     //i = bedel.find(mau);
     //cout<<i;
     while(1){
       i = bedel.find(mau);
       if(i != string::npos){
           ll+=(i+1);
           if(loc==0){
             string del = bedel.substr(0,i+1);
             delsubspace(&del);
             //~~~~
             //cout<<del;
             //cout<<"!!!";
             testparaif(del,ll);
             //~~~~
             tmp+=del;
             bedel=bedel.substr(i+1,bedel.size()-(i+1));
             loc=1;
          }
          else if(loc==1){
             tmp+=bedel.substr(0,i+1);
             bedel=bedel.substr(i+1,bedel.size()-(i+1));
             loc=0;
          }
       }
       else{
          break;
       }
     };
     delsubspace(&bedel);
     tmp+=bedel;
     *s = tmp;
}
/*!
* @brief 將time標籤處理成符合的資料格式，讓它可以搜尋得到 .
* @param parameter 要處理的標籤
* @return parameter 將標籤處理完傳回
*/

/*!
* @brief 將同樣的資料刪去 .
* @param ori 目前處理出的index
* @return only 將刪除完的傳回
*/
vector <int> Search_used::groupby(vector <int> ori){

     vector <int> only;
     int test_in;

     for(int i=0;i<ori.size();i++){
         test_in = 0;
         for(int j=0;j<only.size();j++){
             if(ori[i]==only[j]){
                test_in = 1;
             }
         }
         if(test_in==0){
            only.push_back(ori[i]);
         }
     }

     return only;
}

