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
};

void error(string &s,int begin,int end)
{
   
    string error1 = "{{";
    string error2 = "}}";
    s.insert(begin,error1);
    s.insert(end,error2);

}
string tagName(string s,int begin)
{  
    s = s.substr(begin,s.find_first_of(" >",begin)-begin);  
   return s;
}
string lowerCase(string &s)
{   int i = 0;
    while(s[i])
    {   s[i] = tolower(s[i]);
        i++;
    }
    return s;
}
bool nameCheck(string s)
{   if(s == "")
        return false;
    if(!isalpha(s[0]) && s[0] !='_'&&s[0] !='/')
        return false;
    if(lowerCase(s) == "xml")
        return false;
    return true; 
}
bool bracketCheck(string &s)
{   stack <int> y;
    for(int i = 0;i<s.length();i++)
    {
       if(s[i] == '<')
        {
             if(!y.empty())
            {   error(s,y.top()+1,i+2);
                return true;
            }
             y.push(i);
        }
        else if(s[i] == '>')
        if(y.empty())
            {
                return false;
            }
        else{y.pop();}
    }
    if(!y.empty())
        {
            error(s,y.top()+1,s.length()+2);
            return true;
        }
    return false;
}
string tagCheck(string input, bool &errorFree,bool &isChecked)
{       isChecked = true;
       if(bracketCheck(input))
        {
            return input;
        }
    stack <CheckNode> s;
    string name;
    for(int i = 0; i <input.length();i++) //Moves character by character//O(n)?
    {   
        if(input[i] =='<')
        {   name = tagName(input,i+1);
            if(!nameCheck(name))
             {
                error(input,i,i+3);
                errorFree = false;
                return input;
                }
            //Closing Tag
            else if(input[i+1] =='/') 
            {   if(s.empty())
                {   error(input,i+1,i+4);
                    errorFree = false;
                    return input;

                }
                name = tagName(input,i+2);
                if(s.top().s == name)
                    s.pop();
                else
                    {   int begin = s.top().n;
                        int len = s.top().s.length();
                        error(input,begin,begin+len+2);//+2 curly braces
                        errorFree = false;
                        return input;
                    }
            }
            else
            {   //Opening Tag
                CheckNode temp;
                temp.s = name;
                temp.n = i+1;
                s.push(temp);  
            }      
        }       
    }
    if(!s.empty()) //not balanced
    {
        int begin = s.top().n;
        int len = s.top().s.length();
        error(input,begin,begin+len+2);
        errorFree = false;
        return input;
    }
    return input;
}
