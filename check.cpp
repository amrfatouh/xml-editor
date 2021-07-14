#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stack>
#include <ctype.h>
#include <locale>
using namespace std;
class InputFile
{ public:
  string fileContent;
  bool isChecked;
  bool errorFree;
  InputFile()
  {
    isChecked = false;
    errorFree = true;


  }
};
class OutputFile
{ public:
  string fileContent;
  string fileType;
  OutputFile()
  {

  }
};
class CheckNode
{
    public:
    string s;
    int n;
    bool root;
};
string legalCh = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
string legalCh2 = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-";
string illegalCh = "<&";
string apos = "apos;";
string quot = "quot;";
void error(string &s,int begin,int end)
{
    string error1 = "{{";
    string error2 = "}}";
    s.insert(begin,error1);
    s.insert(end,error2);
}
//escape sequence check.
bool essq(string attr,string comp)
{
    for (int q = 0; q<attr.length();q++)
        {
            if(attr[q] =='<')
            {
                return false;
            }
            if(attr[q] == '&')
                {
                   if(attr.substr(q+1,comp.length()) != comp)
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
                //error handling
                //mark opening tag
                if(s[i] == '<')
                {   cout<<"ERROR14!!"<<endl;
                    error(s,i+1,e+2);

                }
                else
                {   cout<<"ERROR15!!"<<endl;
                    int d = s.find_last_of("<",n-1)+1;
                    int e = s.find_last_of("\"\'",n-1)+1;
                    error(s,d,e+2);
                }
                return false;

            }
        //checking if key contains illegal character
        if(s.substr(n,ek-n).find_first_not_of(legalCh2,0) != string::npos)
        {   //mark opening tag
            cout<<"ERROR16!!"<<endl;
            error(s,i+1,e+2);
            return false;
        }
        //first character after key

        i = s.find_first_not_of(' ',ek);
        if(s[i] != '=')
        {   //mark key
            cout<<"ERROR17!!"<<endl;
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
            {   cout<<"ERROR18!!"<<endl;
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
            if(!essq(attr,quot))
            {
            cout<<"ERROR19!!"<<endl;
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
            if(!essq(attr,apos))
            {
            cout<<"ERROR20!!"<<endl;
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
        else if(s[e+1] == ' ')
            {   i = s.find_first_not_of(' ',e+1);
                if(s[i] == '?' &&s[i+1] =='>'&&ver)
                {
                    return true; //it's a version tag

                }
                recCheck(s,e+1,ver);
            }
        else
            {   cout<<"ERROR21!!"<<endl;
                int d = s.find_last_of("<",e-1)+1;
                error(s,d,e+3);
                return false;
            }
        return true;
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
bool nameCheck(string s)
{   if(s == "")
        return false;
    if(!isalpha(s[0]) && s[0] !='_')
        return false;
    if(lowerCase(s) == "xml")
        return false;
    return true;
}
string tagCheck(string input,bool &isChecked, bool &errorFree)
{   
    isChecked = true;
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
                            cout<<"ERROR1!!"<<endl;
                            error(input,i+1,i+4);
                            errorFree = false;
                            return input;
                        }
                    else if(input[i+3] !='-')
                    {
                        cout<<"ERROR2!!"<<endl;
                        error(input,i+2,i+5);
                        errorFree = false;
                        return input;
                    }
                    int x = input.find("--",i+4);
                    if((x !=string::npos))
                    {   if(input[x+2] !='>')
                        {
                        cout<<"ERROR3!!"<<endl;
                        error(input,x,x+4);
                        errorFree = false;
                        return input;}
                    }
                    else 
                    {
                        cout<<"ERROR4!!"<<endl;
                        error(input,i+1,i+4);
                        errorFree = false;
                        return input;

                    }
                }
            else if(input[i+1] == '/')
            {

                if(s.empty())
                {   //closing that doesn't have an opening tag
                    cout<<"ERROR5!!"<<endl;
                    error(input,i+1,i+4);
                    errorFree = false;
                    return input;
                }

                int n = input.find_first_of(" >",i+2);
                name = input.substr(i+2,n-(i+2));
                n = input.find_first_not_of(" ",n);
                if(input[n] !='>')
                    {
                        //closing bracket missing in a closing tag
                        
                        if(n==string::npos)
                            {   cout<<"ERROR6!!"<<endl;
                                error(input,i+2,input.length()+2);
                                errorFree = false;
                                return input;
                            }
                        cout<<"ERROR7!!"<<endl;
                        error(input,i+2,n+2);
                        errorFree = false;
                        return input;

                    }
                //ROOT TAG CHECK
                //closing tag is the opening tag
                else if(s.top().s == name)
                    s.pop();
                else
                    {  //tag mismatch
                        cout<<"ERROR8!!"<<endl;
                        int begin = s.top().n;
                        int len = s.top().s.length();
                        error(input,begin,begin+len+2);//+2 curly braces
                        errorFree = false;
                        return input;
                    }
            }
            else
            {   //version tag
                name = tagName(input,i+1);
                if(input[i+1]== '?' && i == 0)
                {   
                    ver = true;
                    name = input.substr(i+2,3);
                    if(name != "xml")
                    {
                    cout<<"ERROR9!!"<<endl;
                    error(input,i,i+5);
                    errorFree = false;
                    return input;
                    }
                }
                else if(!nameCheck(name))
                {   //tag name is illegal xml or starting with symbols/digits
                    cout<<"ERROR10!!"<<endl;
                    error(input,i,i+3);
                    errorFree = false;
                    return input;
                    }
                //attributecheck
                if(!recCheck(input,i,ver))
                        {   cout<<"ERROR11!!"<<endl;
                            errorFree = false;
                            return input;//exit function and return error after getting handled
                        } 
                
                temp.s = name;
                temp.n = i+1;
                //Root tag
                temp.root = s.empty()?true:false;

                //root tag + normal tags
                if(!s.empty()&&!(s.top().root))//root = false; therefore stack is not empty
                {   
                    //Two Opening tags right after each other
                    cout<<"ERROR12!!"<<endl;
                    while(!s.top().root)//get root tag
                        s.pop();
                    int begin = s.top().n;
                    int len = s.top().s.length();
                    error(input,begin,begin+len+2);
                    errorFree = false;
                    return input;
                }
                //pushdxx
                s.push(temp);

            }

        }
    }

    if(!s.empty()) //root tag?
    {   cout<<"ERROR13!!"<<endl;
        while(!s.top().root)
            s.pop();
        int begin = s.top().n;
        int len = s.top().s.length();
        
        error(input,begin,begin+len+2);
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
  cout << "expected output: <{{body}}><body>" << endl;
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
  s = "<pointer refs = \"n05200169 n05616246\">Attribute</pointer";
  cout << "string: " + s + "\n";
  cout << "expected output: <pointer refs = \"n05200169 n05616246\">Attribute</{{pointer}}" << endl;
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

}
void testFile()
{   string s;
    string y;
    ifstream input("testCheck.xml");
    while(getline(input,y))
        {
            s +=y +'\n';
        }
    bool check = false;
    bool error = true;
    s = tagCheck(s,check,error);
    cout<<s<<endl;
    cout<<check<<endl;
    cout<<error;

}

