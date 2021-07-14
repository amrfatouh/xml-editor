#ifndef CHECK_H_
#define CHECK_H_
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
string escape =" \t\f\v\n\r";
string legalCh = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
string legalCh2 = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890:-";
string illegalCh = "<&";
string apos = "apos;";
string quot = "quot;";
string amp = "amp;";
string lt = "lt;";
void error(string &s,int begin,int end)
{
    string error1 = "{{";
    string error2 = "}}";
    s.insert(begin,error1);
    s.insert(end,error2);
}
//escape sequence check.
bool essq(string attr)
{
    for (int q = 0; q<attr.length();q++)
        {   
            if(attr[q] =='<')
            {
                return false;
            }
            if(attr[q] == '&')
                {
        if(attr.substr(q+1,quot.length()) != quot && attr.substr(q+1,amp.length()) != amp&& attr.substr(q+1,apos.length()) != apos&& attr.substr(q+1,lt.length()) != lt)
                        return false;
                   


                }
        }
    return true;
}
bool recCheck(string &s, int i, bool ver)
    {   //i+1 is the tag name first character
        //end of tag name
        int e;
        if(s[i] =='<')
        {
        e = s.find_first_of(" >",i+1);
        //first character after opening tag or after attribute done either key or > or illegal
        }
        else e = i;
        //first character of key
        int n = s.find_first_not_of(' ',e);
        //character directly after key
        int ek = s.find_first_of(" =\"><\'",n) ;
        if(s[n] == '>')
        {
          return true;//No attributes or well-formated
        }
        //incase of any error do error handling and return false;
        //checking Key
        //checking first letter of key
        if(legalCh.find(s[n]) == string::npos)
            {
                
                //mark opening tag
                
                if(s[i] == '<')
                {   //checks if first character is legal or not
                    cout<<"ERROR1!!"<<endl;
                    error(s,i+1,e+2);
                    return false;

                }
                else
                {   cout<<"ERROR2!!"<<endl;
                    int d = s.find_last_of("<",n-1)+1;
                    int e = s.find_last_of("\"\'",n-1)+1;
                    error(s,d,e+2);
                    return false;
                }
                return false;

            }
        //checking if key contains illegal character
        if(s.substr(n,ek-n).find_first_not_of(legalCh2,0) != string::npos)
        {   //mark opening tag
            cout<<"ERROR3!!"<<endl;
            error(s,i+1,e+2);
            return false;
        }
        //first character after key

        i = s.find_first_not_of(' ',ek);
        if(s[i] != '=')
        {   //mark key
            cout<<"ERROR4!!"<<endl;
            error(s,n,ek+2);
            return false;
        }
        //checking quotes
        //assuming file contains only double quote attributes

        //index of first quote
        int k;
        k = s.find_first_not_of(' ',i+1);

        //missing &apos; &quot and allowing ' ' instead of " "
        if(s[k] != '\"' && s[k] !='\'')
            {   cout<<"ERROR5!!"<<endl;
                error(s,n,ek+2);
                return false;
            }

        string attr;

        switch(s[k])
        {
            //check for illegal characters
        case '\"':

            //index of end quote
            e = s.find_first_of("\"",k+1);
            //end of xml file and no more quotes
            if(e == string::npos)
                {
                    e = s.find('<',k+1);
                }

            attr = s.substr(k,e-k+1);
            if(!essq(attr))
            {
            cout<<"ERROR6!!"<<endl;
            error(s,k,e+3);
            return false;
                }
            break;
        case '\'':
        //index of end quote
            e = s.find_first_of("\'",k+1);
            //end of xml file and no more quotes
            if(e == string::npos)
                {
                    e = s.find('<',k+1);
                }

            attr = s.substr(k,e-k);
            if(!essq(attr))
            {
            cout<<"ERROR7!!"<<endl;
            error(s,k,e+3);
            return false;
                }
            break;
        }
        //check the character after quote
        if(s[e+1] == '>')
        {
          return true;//No attributes or well-formated
        }
        else if(s[e+1] == ' '||s[e+1] == '?'||s[e+1]=='/')
            {   i = s.find_first_not_of(' ',e+1);
                if((s[i] == '?' &&s[i+1] =='>'&&ver) || s[i] =='/')
                {
                    return true; //it's a version tag

                }
                return recCheck(s,e+1,ver);

            }
        else
            {   cout<<"ERROR8!!"<<endl;
                int d = s.find_last_of("<",e-1)+1;
                error(s,d,e+3);
                return false;
            }
    }

string tagName(string s,int begin)
{  //return two strings?
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

//Rework
bool nameCheck(string s)
{   if(s == "")
        return false;
    if(!isalpha(s[0]) && s[0] !='_')
        return false;
    if(s.find_first_not_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-") !=string::npos )
        {
            return false;
        }
    if(lowerCase(s) == "xml")
        return false;
    return true;
}

string emptyF(string s)
{
    int f = s.find_first_not_of(escape);
    if(f == -1)
        {   //file is empty from front
            return "empty";
        }
    else if(s[f] != '<')
    {
        return "gibberish";
    }
    return "ok";
}
string tagCheck(string input,bool &isChecked, bool &errorFree)
{
    isChecked = true;
    
    string f =emptyF(input);
    if(f =="empty")
    {  
        errorFree = false;
        return input;
    }
    else if(f == "gibberish")
    {   cout<<"ERROR9"<<endl;
        errorFree = false;
        int index = input.find_first_of('<');
        if(index == string::npos)
            index = input.length()-1;
        error(input,input.find_first_not_of(escape),index+2);
        return input;
    }

    bool root = false;
    stack <CheckNode> s;
    CheckNode temp;
    string name;
    bool ver = false;//No version tag initially
    for(int i =0 ; i <input.length();i++) //Moves character by character//O(n)?
    {
        if(input[i] =='<')
        {
            //Comment
            if(input[i+1]=='!')
                {
                    //-- not marked + end of comment
                    if(input[i+2] != '-')
                        {
                            cout<<"ERROR10!!"<<endl;
                            error(input,i+1,i+4);
                            errorFree = false;
                            return input;
                        }
                    else if(input[i+3] !='-')
                    {
                        cout<<"ERROR11!!"<<endl;
                        error(input,i+2,i+5);
                        errorFree = false;
                        return input;
                    }
                    int x = input.find("--",i+4);
                    if((x !=string::npos))
                    {   if(input[x+2] !='>')
                        {
                        cout<<"ERROR12!!"<<endl;
                        error(input,x,x+4);
                        errorFree = false;
                        return input;}
                    }
                    else
                    {   //-- don't exist
                        cout<<"ERROR13!!"<<endl;
                        error(input,i+1,i+4);
                        errorFree = false;
                        return input;

                    }
                }
            else if(input[i+1] == '/')
            {

                if(s.empty())
                {   //closing that doesn't have an opening tag
                    cout<<"ERROR14!!"<<endl;
                    error(input,i+1,i+4);
                    errorFree = false;
                    return input;
                }
                int n;
                int x = input.find_first_of(" ><",i+2);
                name = input.substr(i+2,x-(i+2));
                n = input.find_first_not_of(" ",x);
                if(input[n] !='>')
                    {
                        //closing bracket missing in a root closing tag
                        if(n==string::npos)
                            {   //
                                
                                cout<<"ERROR15!!"<<endl;
                                error(input,i+2,x+2);
                                errorFree = false;
                                return input;
                            }
                        cout<<"ERROR16!!"<<endl;
                        error(input,i+2,n+2);
                        errorFree = false;
                        return input;

                    }
                //closing tag is the opening tag
                else if(s.top().s == name)
                    s.pop();
                else
                    {  //tag mismatch
                        cout<<"ERROR17!!"<<endl;
                        int begin = s.top().n;
                        int len = s.top().s.length();
                        error(input,begin,begin+len+2);//+2 curly braces
                        errorFree = false;
                        return input;
                    }
            }
            else
            {   name = tagName(input,i+1);
                if(input[i+1]== '?' )
                {   name = tagName(input,i+2);
                    //version tag
                    if(i == 0)
                    {ver = true;
                    name = input.substr(i+2,3);
                    if(name != "xml")
                    {
                    cout<<"ERROR18!!"<<endl;
                    error(input,i,i+5);
                    errorFree = false;
                    return input;
                    }
                    }
                    else if(!nameCheck(name))
                    {
                    //tag name is illegal, xml, or starting with symbols/digits
                    cout<<"ERROR19!!"<<endl;
                    error(input,i,i+3);
                    errorFree = false;
                    return input;
                    }
                    //xml-model or any other tag

                
                }
                else if(!nameCheck(name))
                {   //tag name is illegal, xml, or starting with symbols/digits
                    cout<<"ERROR20!!"<<endl;
                    error(input,i,i+3);
                    errorFree = false;
                    return input;
                    }

                //attributecheck
                if(!recCheck(input,i,ver))
                        {   cout<<"ERROR21!!"<<endl;
                            errorFree = false;
                            return input;//exit function and return error after getting handled
                        }
               if(input[i+1] !='?')
               {
                temp.s = name;
                temp.n = i+1;
                //Root tag
                // temp.root = s.empty()?true:false;
                if(s.empty()&&root)
                {
                    //Root tag popped and something comes after it
                    cout<<"ERROR22!!"<<endl;
                    int begin = i+1;
                    int len = name.length();
                    error(input,begin,begin+len+2);
                    errorFree = false;
                    return input;
                }
                //root tag + normal tags
                 if(s.empty() && !root)
                    {
                        root = true;

                    }
                
                //pushdxx
               
                s.push(temp);
                }

            }
           


        }
         
            if(input[i] =='>'&&input[i-1] == '/')
            {   
                s.pop();//3ayl we ghlet e7na asfen

            }
    }
    if(!s.empty())
    {   cout<<"ERROR23!!"<<endl;
        int begin = s.top().n;
        int len = s.top().s.length();
        error(input,begin,begin+len+2);
        errorFree = false;
        return input;
    }   
    int d =0;
    d = input.find_last_not_of(escape);
    if(input[d] !='>')
    {   cout<<"ERROR24"<<endl;
        d=input.find_last_of('>',d)+1;
        error(input,d,input.length()+2);
        errorFree = false;
        return input;
    }
    return input;
}

void testError()
{
    string s;
    bool check;
    bool error;
  cout << "#1" << endl;
  s = "< body></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: {{<}} body></body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#2" << endl;
  s = "<body><body><body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body><body><{{body}}>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#3" << endl;
  s = "<pointer refs  \"n05200169 n05616246\">Attribute</pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <pointer {{refs}}  \"n05200169 n05616246\">Attribute</pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#4" << endl;
  s = "<pointer refs = \"n05200169 n05616246\"Attribute</pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <{{pointer refs = \"n05200169 n05616246\"}}Attribute</pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#5" << endl;
  s = "<pointer refs = \"n05200169 n05616246\" Attribute</pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <pointer refs = \"n05200169 n05616246\" {{Attribute}}</pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#6" << endl;
  s = "<pointer refs = \"n05200169 n05616246\">Attribute</pointer                      ";
  cout << "string: " + s + "\n";
  cout << "expected output: <pointer refs = \"n05200169 n05616246\">Attribute</{{pointer}}                      " << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";
  //same as #4
  cout << "#7" << endl;
  s = "<pointer refs = \"n05200169 n05616246\"<Attribute</pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <{{pointer refs = \"n05200169 n05616246\"}}<Attribute</pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#8" << endl;
  s = "<pointer refs = \"n05200169 n05616246\">Attribute</poinster>";
  cout << "string: " + s + "\n";
  cout << "expected output: <{{pointer}} refs = \"n05200169 n05616246\">Attribute</pointser>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#9" << endl;
  s = "<pointer refs = \"n05200169&quot; n05616246\">Attribute</pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <pointer refs = \"n05200169&quot; n05616246\">Attribute</pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#10" << endl;
  s = "<pointer refs = \"n05200169&quot n05616246\">Attribute</pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <pointer refs = {{\"n05200169&quot n05616246\"}}>Attribute</pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#11" << endl;
  s = "<pointer refs></pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <pointer {{refs}}></pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#12" << endl;
  s = "<pointer refs = \"n05200169 n05616246\" Attribute></pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <pointer refs = \"n05200169 n05616246\" {{Attribute}}></pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#13" << endl;
  s = "<pointer refs = \"n05200169 n05616246\" 3ttribute></pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <{{pointer refs = \"n05200169 n05616246\"}} 3ttribute></pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#14" << endl;
  s = "<pointer 3refs></pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <{{pointer}} 3refs></pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#15" << endl;
  s = "<pointer refs =\"n05 &quot; 616246 n05200169\" 3ource=\"1\" target=\"1\">Derivationally related form</pointer>";
  cout << "string: " + s + "\n";
  cout << "expected output: <{{pointer refs =\"n05 &quot; 616246 n05200169\"}} 3ource=\"1\" target=\"1\">Derivationally related form</pointer>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#16" << endl;
  s = "<! - A random selection of elements from data.xml\nSome IDREFS (refs attribute of element pointer) do not have a corresponding id in this sample-->";
  cout << "string: " + s + "\n";
  cout << "expected output: <{{!}} - A random selection of elements from data.xml\nSome IDREFS (refs attribute of element pointer) do not have a corresponding id in this sample-->" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#17" << endl;
  s = "<!- - A random selection of elements from data.xml\nSome IDREFS (refs attribute of element pointer) do not have a corresponding id in this sample-->";
  cout << "string: " + s + "\n";
  cout << "expected output: <!{{-}} - A random selection of elements from data.xml\nSome IDREFS (refs attribute of element pointer) do not have a corresponding id in this sample-->" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#18" << endl;
  s = "<!-- A random selection of elements from data.xml\nSome IDREFS (refs attribute of element pointer) do not have a corresponding id in this sample-->";
  cout << "string: " + s + "\n";
  cout << "expected output: <!-- A random selection of elements from data.xml\nSome IDREFS (refs attribute of element pointer) do not have a corresponding id in this sample-->" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#19" << endl;
  s = "<body><boi>asd</boi></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body><boi>asd</boi></body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#20" << endl;
  s = "<body><?xml version=\"1.0\" encoding=\"UTF-8\" ?></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body>{{<}}?xml version=\"1.0\" encoding=\"UTF-8\" ?></body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#21" << endl;
  s = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><body></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <?xml version=\"1.0\" encoding=\"UTF-8\" ?><body></body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#22" << endl;
  s = "<!-- Hello --> <?xml version=\"1.0\" encoding=\"UTF-8\" ?><body></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <!-- Hello --> {{<}}?xml version=\"1.0\" encoding=\"UTF-8\" ?><body></body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#23" << endl;
  s = "<!-- Hello -- --> <?xml version=\"1.0\" encoding=\"UTF-8\" ?><body></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <!-- Hello {{--}} --> <?xml version=\"1.0\" encoding=\"UTF-8\" ?><body></body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#24" << endl;
  s = "<!-- Hello <body></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <{{!}}-- Hello <body></body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#25" << endl;
  s = "<!-- Hello --> <body> a <b </body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <!-- Hello --> <body> a <{{b}} </body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#26" << endl;
  s = "<batata><batates><bombastic></bombastic></batates></batata>";
  cout << "string: " + s + "\n";
  cout << "expected output: <batata><batates></batates></batata>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#27" << endl;
  s = "<batata><batates><bombastic></batates></batata>";
  cout << "string: " + s + "\n";
  cout << "expected output: <batata><batates></batates></batata>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#28" << endl;
  s = "<body></body> asdasdasdasdasd ";
  cout << "string: " + s + "\n";
  cout << "expected output: <body></body>{{ asdasdasdasdasd }} " << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#29" << endl;
  s = " asdasdasdasdasd <body></body> asdasdasdasdasd ";
  cout << "string: " + s + "\n";
  cout << "expected output: {{ asdasdasdasdasd }}<body></body> asdasdasdasdasd " << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#30" << endl;
  s = "                                                                           ";
  cout << "string: " + s + "\n";
  cout << "expected output:                                                                            " << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";
    cout << "#31" << endl;
  s = "\n\n\n\n\n    ";
  cout << "string: " + s + "\n";
  cout << "expected output: \n" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#32" << endl;
  s = "<body></body>\n\n\n\n\n    ";
  cout << "string: " + s + "\n";
  cout << "expected output: <body></body>\n\n\n\n\n    " << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#32" << endl;
  s = "<body></body>\n<body></body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body></body>\n<{{body}}></body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";

  cout << "#6V2" << endl;
  s = "<body><pointer refs = \"n05200169 n05616246\">Attribute</pointer</body>";
  cout << "string: " + s + "\n";
  cout << "expected output: <body><pointer refs = \"n05200169 n05616246\">Attribute</{{pointer}}</body>" << endl;
  cout << "actual   output: " << tagCheck(s,check,error) << "\n\n";
}
void testFile()
{   string s;
    string y;
    ifstream input("testCheck.xml");
    ofstream output("testOutput.xml");
    while(getline(input,y))
        {
            s +=y +'\n';
        }
    bool check = false;
    bool error = true;
    s = tagCheck(s,check,error);
    output << s;
    cout<<s<<endl;
    cout<<check<<endl;
    cout<<error;

}

#endif
