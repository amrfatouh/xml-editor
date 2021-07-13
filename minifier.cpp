#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
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

void testMinify()
{
  string s;

  cout << "new line between opening and closing tags\n";
  s = "<body>\n</body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body></body>" << endl;
  cout << "actual output: " << minify(s) << "\n\n";

  cout << "space between opening and closing tags\n";
  s = "<body> </body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body></body>" << endl;
  cout << "actual output: " << minify(s) << "\n\n";

  cout << "space inside opening tag\n";
  s = "< body ></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body></body>" << endl;
  cout << "actual output: " << minify(s) << "\n\n";

  cout << "spaces inside closing tags\n";
  s = "<body>< / body >";
  cout << "string: " + s + "\n";
  cout << "expected output: <body></body>" << endl;
  cout << "actual output: " << minify(s) << "\n\n";

  cout << "new lines and inner tags\n";
  s = "<body>\n<div></div>\n</body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body><div></div></body>" << endl;
  cout << "actual output: " << minify(s) << "\n\n";

  cout << "spaces and text\n";
  s = "<body> hello world </body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body>hello world</body>" << endl;
  cout << "actual output: " << minify(s) << "\n\n";

  cout << "five spaces in text\n";
  s = "<body>hello     world</body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body>hello     world</body>" << endl;
  cout << "actual output: " << minify(s) << "\n\n";

  cout << "spaces in comment\n";
  s = "<!--   hello   -->";
  cout << "string: " + s + "\n";
  cout << "expected output: <!-- hello -->" << endl;
  cout << "actual output: " << minify(s) << "\n\n";

  cout << "space between inner tags\n";
  s = "<body><div></div> <div></div></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body><div></div><div></div></body>" << endl;
  cout << "actual   output: " << minify(s) << "\n\n";

  cout << "tabs and new lines\n";
  s = "<body>\n\t<div>\n\t</div>\n</body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body><div></div></body>" << endl;
  cout << "actual   output: " << minify(s) << "\n\n";
}