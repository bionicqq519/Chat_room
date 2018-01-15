#ifndef SEARCH_USED_H
#define SEARCH_USED_H
#include <string>
#include <vector>
#include "chat_used.h"
#include "exception.h"
using namespace std;
class Search_used{
public:
    friend class Bionic_Test;
    Search_used();
    ~Search_used();
    //在切字串的過程中處理雜物的function
    vector <int> groupby(vector <int> ori);
    void delspace(string *s);
    void delsubspace(string *s);
    void dellr(string *s,string tag);
    void testparaif(string s,int loction);
private:
    Chat_main *chat_u;
};
#endif // SEARCH_USED_H
