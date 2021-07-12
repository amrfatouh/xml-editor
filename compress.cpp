#include <string>
#include <algorithm>
#include <sstream>
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
    int n = y.length();
    string output="";
    for(int i =0; i<y.length()-1;i++)
    {
        
        int count = 1;
        while (i < n - 1 && y[i] == y[i + 1]) {
            count++;
            i++;
        }
        output.append(y[i] + to_string(count));
        }
 return output;
    }

