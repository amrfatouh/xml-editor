#include "minifier.h"
using namespace std;
string minify(string y)
{
    // Erases all escape sequences
    string whitespaces(" \t\f\v\n\r");
    string b("<>/!-?");
    int i = 0;
    for (int i = 0; i < y.length(); i++)
    {
        if (b.find(y[i]) != string::npos)
        {
            // Erase backward
            int j = y.find_last_not_of(whitespaces, i - 1) + 1;
            y.erase(j, i - j);
            if (b.find(y[i]) == string::npos)
                i = j - 1;
            // Erase forward
            j = y.find_first_not_of(whitespaces, i + 1) - 1;
            y.erase(i + 1, j - i);
        }
    }
    return y;
}
void testMinify()
{
    string s;
    cout << "#1" << endl;
    cout << "new line between opening and closing tags\n";
    s = "\n\n\n<body>\n</body>";
    cout << "string: " + s + "\n";
    cout << "expected output: <body></body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#2" << endl;
    cout << "space between opening and closing tags\n";
    s = "<body> </body>";
    cout << "string: " + s + "\n";
    cout << "expected output: <body></body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#3" << endl;
    cout << "space inside opening tag\n";
    s = "< body ></body>";
    cout << "string: " + s + "\n";
    cout << "expected output: <body></body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#4" << endl;
    cout << "spaces inside closing tags\n";
    s = "<body>< / body >";
    cout << "string: " + s + "\n";
    cout << "expected output: <body></body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#5" << endl;
    cout << "new lines and inner tags\n";
    s = "<body>\n<div></div>\n</body>";
    cout << "string: " + s + "\n";
    cout << "expected output: <body><div></div></body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#6" << endl;
    cout << "spaces and text\n";
    s = "<body> hello world </body>";
    cout << "string: " + s + "\n";
    cout << "expected output: <body>hello world</body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#7" << endl;
    cout << "five spaces in text\n";
    s = "<body>hello     world</body>";
    cout << "string: " + s + "\n";
    cout << "expected output: <body>hello     world</body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#8" << endl;
    cout << "spaces in comment\n";
    s = "<!--   hello   -->";
    cout << "string: " + s + "\n";
    cout << "expected output: <!-- hello -->" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#9" << endl;
    cout << "space between inner tags\n";
    s = "<body><div></div> <div></div></body>";
    cout << "string: " + s + "\n";
    cout << "expected output: <body><div></div><div></div></body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#10" << endl;
    cout << "tabs and new lines\n";
    s = "<body>\n\t<div>\n\t</div>\n</body>";
    cout << "string: " + s + "\n";
    cout << "expected output: <body><div></div></body>" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
    cout << "#11" << endl;
    cout << "preceding and following spaces, new lines, tabs\n";
    s = " \n\t<body></body> \t\nx";
    cout << "string: " + s + "\n";
    cout << "expected output: <body></body>x" << endl;
    cout << "actual   output: " << minify(s) << "\n\n";
}