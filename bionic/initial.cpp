/*!
* @file initial.cpp 主選單
* @author 99598019 李宗人
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "initial.h"
using namespace std;
initial_pro::initial_pro(){
    //改class
    main_tool = new Chat_main();
    toparse =new Do_parse();  //宣告parse class
    tomsn_chat =new Do_msn_chat();  //宣告msn_chat class
    tosearch =new Do_search();  //宣告search class
    tomsn_chat = new Do_msn_chat();

    read_msn_chat_data = new Msn_chat_data();
}
initial_pro::~initial_pro(){
    delete toparse; //釋放parse class
    delete tomsn_chat; //釋放msn_chat class
    delete tosearch; //釋放search class
    delete read_msn_chat_data;
}

string initial_pro::get_chat_num(){
    return chat_num;
}
string initial_pro::get_chat_result(){
    return chat_result;
}
/*!
* @brief 起初的function，所有主選單的要求從這個function開始，再去呼叫其他function以作功能 .
*/
void initial_pro::initial(string srh_para,string sortof_para)
{
    string filename;
    string allname_text;
    allname_text = main_tool->readxml("C:\\chat_record\\_AllName.xml");
    vector <string> all_name;
    all_name = tomsn_chat->parseallname(allname_text);
    int all_num = all_name.size();
    //chat_num = main_tool->int2str(aaa);
    for(int i=0;i<all_num;i++){
        string read_text = "";
        string allname_path;
        allname_path = "C:\\chat_record\\" + all_name[i] + ".xml";
        read_text = main_tool->readxml(allname_path);

        //chat_num = all_name[i];
        if(main_tool->test_format(read_text) == 1){
            toparse->parsemsn(read_msn_chat_data,read_text);

        }
        else{
           cout<<"Failed to laod"<<endl;
        }
        //string a;
        //a = main_tool->readxml("a.xml");
    }

    if(read_msn_chat_data->all.size()==0){
        cout<<"You have to load xml files first."<<endl;
    }
    else{
       //chat_num = "haha";
       tosearch->searchmain(read_msn_chat_data,filename,srh_para,sortof_para);
    }
    chat_num = tosearch->get_srh_chat_num();
    chat_result = tosearch->get_srh_chat_result();

}

