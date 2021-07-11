#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cctype>
//#include <bits/stdc++.h>
using namespace std;
//At the end use f stream to direct edit a file
string oneLine()
{
    ifstream xmlData("data-sample.xml");
    if(xmlData.fail())
    {cout<<"Input failed.";
        xmlData.close();
        xmlData.clear();
        }
    else{
    string s;
    string y;
    while(getline(xmlData,s))
    {
        y+=s;
    }
    xmlData.close();
    xmlData.clear();
    return y;
    }

}
int main()
{   ofstream output("whitespace2.xml");
    string x = oneLine();
    for(int i =0; i<x.length()-1;i++)
    {
        if(x[i] == '>' && x[i+1] == ' ')
        {   int j = 0;
            while(x[i+1+j] ==' ')
                j++;
            x.erase(i+1,j);
        }
        if(x[i] == '<' && x[i+1] == ' ')
        {   int j = 0;
            while(x[i+1+j] ==' ')
                j++;
            x.erase(i+1,j);
        }
        else if(x[i] =='<')
            {   int j =0;
                while(x[i-1-j] ==' ')
                    j++;
                x.erase(i-j,j);
        }
        else if(x[i] =='>')
            {   int j =0;
                while(x[i-1-j] ==' ')
                    j++;
                x.erase(i-j,j);
        }
        else if(x[i] == ' ' && x[i+1] == ' ')
            {   int j = 0;
            while(x[i+1+j] ==' ')
                j++;
            x.erase(i+1,j);
        }

    }
    output<<x;
    return 0;
}

