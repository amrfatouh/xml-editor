#include <string>
#include <algorithm>
#include <sstream>
using namespace std;
string minify(string y)
{
    stringstream a(y);
    y ="";
    string x;
    while(getline(a,x))
    {
        y+=x;
    }
    for(int i =0; i<y.length()-1;i++)
    {
        if(y[i] == '>' && y[i+1] == ' ')
        {   int j = 0;
            while(y[i+1+j] ==' ')
                j++;
            y.erase(i+1,j);
        }
        else if(y[i] == '<' && y[i+1] == ' ')
        {   int j = 0;
            while(y[i+1+j] ==' ')
                j++;
            y.erase(i+1,j);
        }
        else if(y[i] =='<')
            {   int j =0;
                while(y[i-1-j] ==' ')
                    j++;
                y.erase(i-j,j);
        }
        else if(y[i] =='>')
            {   int j =0;
                while(y[i-1-j] ==' ')
                    j++;
                y.erase(i-j,j);
        }
        else if(y[i] == ' ' && y[i+1] == ' ')
            {   int j = 0;
            while(y[i+1+j] ==' ')
                j++;
            y.erase(i+1,j);
        }

    }
    return y;
    
}


