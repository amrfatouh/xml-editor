#ifndef CHECK_H
#define CHECK_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stack>
#include <ctype.h>
#include <locale>
using namespace std;
class CheckNode
{
    public:
    string s;
    int n;
    bool root = false;
};

static string escape =" \t\f\v\n\r";
static string legalCh = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static string legalCh2 = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890:-";
static string illegalCh = "<&";
static string apos = "apos;";
static string quot = "quot;";
static string amp = "amp;";
static string lt = "lt;";

void error(string &s,int begin,int end);

//escape sequence check.
bool essq(string attr);

bool recCheck(string &s, int i, bool ver,int &errorCode);

string tagName(string s,int begin);

string lowerCase(string &s);


//Rework
bool nameCheck(string s);

string emptyF(string s);
string tagCheck(string input,bool &isChecked, bool &errorFree, int &errorCode);


void testError();

void testFile();



#endif
