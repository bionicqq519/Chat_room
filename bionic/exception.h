#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <string>
using namespace std;

class Errormsg {
public:
Errormsg(string msg) : errMsg(msg) {}
string what() ;

private:
string errMsg;

};

#endif // EXCEPTION_H
