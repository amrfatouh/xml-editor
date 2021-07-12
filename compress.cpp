#include <string>
#include <algorithm>
#include <sstream>
#include <bitset>

using namespace std;
string compress(string y)
{
    stringstream a(y);
    y ="";
    string x;
    while(getline(a,x))
    {
        y+=x;
    }
    string str="";
       for (int i = 0; i < y.length(); ++i) {
           bitset<8> bs4(y[i]);
           str.append(bs4.to_string());
       }
    int n = str.length();
    string output="";
    for(int i =0; i<str.length()-1;i++)
    {
        
        int count = 1;
        while (i < n - 1 && str[i] == str[i + 1]) {
            count++;
            i++;
        }
        output.append(str[i] + to_string(count));
    }
    return output;
}

