#include "check.h"
//#include "correction.h"
using namespace std;


int getOpeningBracesIndex(string markedString)
{
  return markedString.find("{{");
}
int getClosingBracesIndex(string markedString)
{
  return markedString.find("}}");
}
void removeOpeningBraces(string &markedString)
{
  markedString.erase(getOpeningBracesIndex(markedString), 2);
}
void removeClosingBraces(string &markedString)
{
  markedString.erase(getClosingBracesIndex(markedString), 2);
}
void removeBraces(string &markedString)
{
  removeOpeningBraces(markedString);
  removeClosingBraces(markedString);
}
bool isLegal(char a)
{
  string legalChars = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-";
  return legalChars.find(a) != string::npos;
}

//error 10: <{{!}}
string correctError10(string markedString)
{
  int openBracesIndex = markedString.find("{{");
  markedString.erase(openBracesIndex, 2);
  int dashesIndex = openBracesIndex + 1;
  markedString.insert(dashesIndex, "--");
  int closeBracesIndex = markedString.find("}}");
  markedString.erase(closeBracesIndex, 2);
  return markedString;
}

void testCorrectError10()
{
  string markedString;

  cout << "#1\n";
  markedString = "<{{!}} hello world -->";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <!-- hello world -->\n";
  cout << "actual   output: " << correctError10(markedString) << endl
       << endl;

  cout << "#2\n";
  markedString = "<{{!}} - hello world -->";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <!-- - hello world -->\n";
  cout << "actual   output: " << correctError10(markedString) << endl
       << endl;
}

//error 11: <!{{-}}
string correctError11(string markedString)
{
  int openBracesIndex = markedString.find("{{");
  markedString.erase(openBracesIndex, 2);
  int dashesIndex = openBracesIndex + 1;
  markedString.insert(dashesIndex, "-");
  int closeBracesIndex = markedString.find("}}");
  markedString.erase(closeBracesIndex, 2);
  return markedString;
}

void testCorrectError11()
{
  string markedString;

  cout << "#1\n";
  markedString = "<!{{-}} hello world -->";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <!-- hello world -->\n";
  cout << "actual   output: " << correctError11(markedString) << endl
       << endl;

  cout << "#2\n";
  markedString = "<!{{-}} - hello world -->";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <!-- - hello world -->\n";
  cout << "actual   output: " << correctError11(markedString) << endl
       << endl;
}

//error 12: <!-- {{--}}
string correctError12(string markedString)
{
  int openBracesIndex = markedString.find("{{");
  markedString.erase(openBracesIndex, 2);
  int closeBracesIndex = markedString.find("}}");
  markedString.erase(closeBracesIndex, 2);
  int dashesIndex = closeBracesIndex;
  markedString.insert(dashesIndex, ">");
  return markedString;
}

void testCorrectError12()
{
  string markedString;

  cout << "#1\n";
  markedString = "<!-- hello world {{--}}";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <!-- hello world -->\n";
  cout << "actual   output: " << correctError12(markedString) << endl
       << endl;
}

//error 13: <{{!}}
string correctError13(string markedString)
{
  int openBracesIndex = markedString.find("{{");
  markedString.erase(openBracesIndex, 2);
  int closeBracesIndex = markedString.find("}}");
  markedString.erase(closeBracesIndex, 2);
  int commentCloseIndex = closeBracesIndex + 2;
  markedString.insert(commentCloseIndex, " -->");
  return markedString;
}

void testCorrectError13()
{
  string markedString;

  cout << "#1\n";
  markedString = "<{{!}}-- hello world";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <!-- --> hello world\n";
  cout << "actual   output: " << correctError13(markedString) << endl
       << endl;
}

//error 14: <{{/}}a>
string correctError14(string markedString)
{
  //getting tag name
  int closeBracesIndex = markedString.find("}}");
  int tagNameIndex = closeBracesIndex + 2;
  int closeAngleIndex = markedString.find(">");
  int charsCount = closeAngleIndex - tagNameIndex;
  string tagName = markedString.substr(tagNameIndex, charsCount);
  //adding opening tag
  int openBracesIndex = markedString.find("{{");
  int openingTagIndex = openBracesIndex - 1;
  markedString.insert(openingTagIndex, "<" + tagName + ">");
  //removing braces
  openBracesIndex = markedString.find("{{");
  markedString.erase(openBracesIndex, 2);
  closeBracesIndex = markedString.find("}}");
  markedString.erase(closeBracesIndex, 2);
  return markedString;
}

void testCorrectError14()
{
  string markedString;

  cout << "#1\n";
  cout << "closing tag\n";
  markedString = "<{{/}}tagA>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <tagA></tagA>\n";
  cout << "actual   output: " << correctError14(markedString) << endl
       << endl;

  cout << "#2\n";
  cout << "closing tag with spaces inside\n";
  markedString = "<{{/}}  tagA>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <  tagA></  tagA>\n";
  cout << "actual   output: " << correctError14(markedString) << endl
       << endl;
}

//error 15: </{{a}}
string correctError15(string markedString)
{
  int closingBracesIndex = getClosingBracesIndex(markedString);
  markedString.insert(closingBracesIndex, ">");
  removeBraces(markedString);
  return markedString;
}

void testCorrectError15()
{
  string markedString;

  cout << "#1\n";
  cout << "closing tag without closing angle bracket\n";
  markedString = "<a></{{a}}";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <a></a>\n";
  cout << "actual   output: " << correctError15(markedString) << endl
       << endl;
}

//error 16: </{{a}}
string correctError16(string markedString)
{
  int closingBracesIndex = getClosingBracesIndex(markedString);
  markedString.insert(closingBracesIndex, ">");
  removeBraces(markedString);
  return markedString;
}

void testCorrectError16()
{
  string markedString;

  cout << "#1\n";
  cout << "closing tag without closing angle bracket - with tag after it\n";
  markedString = "<b><a></{{a}}</b>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <b><a></a></b>\n";
  cout << "actual   output: " << correctError16(markedString) << endl
       << endl;

  cout << "#2\n";
  cout << "closing tag without closing angle bracket - with space after it\n";
  markedString = "<b><a></{{a}} </b>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <b><a></a> </b>\n";
  cout << "actual   output: " << correctError16(markedString) << endl
       << endl;
}

//error 17: <{{a}}>
string correctError17(string markedString)
{
  //getting tag name
  int openBracesIndex = markedString.find("{{");
  int closeBracesIndex = markedString.find("}}");
  int tagNameIndex = openBracesIndex + 2;
  int charsCount = closeBracesIndex - tagNameIndex;
  string tagName = markedString.substr(tagNameIndex, charsCount);
  //replacing closing tag name with opening tag name
  int closingTagIndex = markedString.find("</", closeBracesIndex);
  int closingAngleIndex = markedString.find(">", closingTagIndex);
  int closingTagNameIndex = closingTagIndex + 2;
  charsCount = closingAngleIndex - closingTagNameIndex;
  markedString.erase(closingTagNameIndex, charsCount);
  markedString.insert(closingTagNameIndex, tagName);
  //removing braces
  openBracesIndex = markedString.find("{{");
  markedString.erase(openBracesIndex, 2);
  closeBracesIndex = markedString.find("}}");
  markedString.erase(closeBracesIndex, 2);
  return markedString;
}

void testCorrectError17()
{
  string markedString;

  cout << "#1\n";
  cout << "not matching tags (one letter tag)\n";
  markedString = "<{{a}}>hello world</b>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <a>hello world</a>\n";
  cout << "actual   output: " << correctError17(markedString) << endl
       << endl;

  cout << "#2\n";
  cout << "not matching tags (one word tag)\n";
  markedString = "<{{tagA}}>hello world</tagB>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <tagA>hello world</tagA>\n";
  cout << "actual   output: " << correctError17(markedString) << endl
       << endl;
}

//error 18: <?{{first 3 letters after '?' symbol}}
string correctError18(string markedString)
{
  int openingBracesIndex = markedString.find("{{");
  markedString.insert(openingBracesIndex, "xml ");
  openingBracesIndex = markedString.find("{{");
  int closingBracesIndex = markedString.find("}}");
  int charsCount = closingBracesIndex - openingBracesIndex + 2;
  markedString.erase(openingBracesIndex, charsCount);
  return markedString;
}

void testCorrectError18()
{
  string markedString;

  cout << "#1\n";
  cout << "space before xml\n";
  markedString = "<?{{ xm}}l bla=\"bla\"?>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: <?xml l bla=\"bla\"?>\n";
  cout << "actual   output: " << correctError18(markedString) << endl
       << endl;
}

//error 19: {{<}}a>
string correctError19(string markedString)
{
  int closingBracesIndex = getClosingBracesIndex(markedString);
  int tagNameIndex = closingBracesIndex + 2;
  int closingAngleIndex = markedString.find(">", closingBracesIndex);
  int charsCount = closingAngleIndex - tagNameIndex;
  string tagName = markedString.substr(tagNameIndex, charsCount);

  if (tagName == "xml")
  {
    markedString.insert(tagNameIndex, "_");
    removeBraces(markedString);
    return markedString;
  }

  for (int i = tagNameIndex; i < tagNameIndex + charsCount; i++)
    if (!isLegal(markedString[i]))
      markedString[i] = '_';
  removeBraces(markedString);
  return markedString;
}

void testCorrectError19()
{
  string markedString;

  cout << "#1\n";
  cout << "tag named xml\n";
  markedString = "{{<}}xml>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: "
       << "<_xml>"
       << "\n";
  cout << "actual   output: " << correctError19(markedString) << endl
       << endl;

  cout << "#2\n";
  cout << "tag name containing illegal characters\n";
  markedString = "{{<}}tag!A>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: "
       << "<tag_A>"
       << "\n";
  cout << "actual   output: " << correctError19(markedString) << endl
       << endl;

  cout << "#3\n";
  cout << "tag name equal to \"xml\" comming after a correct tag\n";
  markedString = "<?xml version=\"1.0\"?><a></a>{{<}}xml>";
  cout << "marked string: " << markedString << endl;
  cout << "expected output: "
       << "<?xml version=\"1.0\"?><a></a><_xml>"
       << "\n";
  cout << "actual   output: " << correctError19(markedString) << endl
       << endl;
}

string correct(string text)
{
  int errNum;
  bool isChecked, errorFree;
  string markedString = tagCheck(text, isChecked, errorFree, errNum);
  while (markedString.find("{{") != string::npos)
  {
    if (markedString.find("{{") == string::npos)
      return markedString;
    /* */ if (errNum == 1)
      return markedString;
    else if (errNum == 2)
      return markedString;
    else if (errNum == 3)
      return markedString;
    else if (errNum == 4)
      return markedString;
    else if (errNum == 5)
      return markedString;
    else if (errNum == 6)
      return markedString;
    else if (errNum == 7)
      return markedString;
    else if (errNum == 8)
      return markedString;
    else if (errNum == 9)
      return markedString;
    else if (errNum == 10)
      markedString = correctError11(markedString);
    else if (errNum == 11)
      markedString = correctError11(markedString);
    else if (errNum == 12)
      markedString = correctError12(markedString);
    else if (errNum == 13)
      markedString = correctError13(markedString);
    else if (errNum == 14)
      markedString = correctError14(markedString);
    else if (errNum == 15)
      markedString = correctError15(markedString);
    else if (errNum == 16)
      markedString = correctError16(markedString);
    else if (errNum == 17)
      markedString = correctError17(markedString);
    else if (errNum == 18)
      markedString = correctError18(markedString);
    else if (errNum == 19)
      return markedString;
    else if (errNum == 20)
      return markedString;
    else if (errNum == 21)
      return markedString;
    else if (errNum == 22)
      return markedString;
    else if (errNum == 23)
      return markedString;
    else if (errNum == 24)
      return markedString;

    markedString = tagCheck(markedString, isChecked, errorFree, errNum);
  }
  return markedString;
}

void testCorrect()
{
  string text;

  cout << "#1"
       << "\n";
  cout << "error 10: missing double dashes after \'!\' in comment"
       << "\n";
  cout << "error 13: comment is not closed"
       << "\n";
  text = "<a><! hello</a>";
  cout << "marked string: " << text << endl;
  cout << "expected output: "
       << "<a><!-- --> hello</a>"
       << "\n";
  cout << "actual   output: " << correct(text) << endl
       << endl;

  cout << "#2"
       << "\n";
  cout << "error 11: missing dash after \"<!-\" in comment"
       << "\n";
  cout << "error 12: missing closing angle bracket after the double dashes in comment"
       << "\n";
  text = "<a><!-hello--</a>";
  cout << "marked string: " << text << endl;
  cout << "expected output: "
       << "<a><!--hello--></a>"
       << "\n";
  cout << "actual   output: " << correct(text) << endl
       << endl;

  cout << "#3"
       << "\n";
  cout << "error 17: mismatch between opening and closing tag"
       << "\n";
  text = "<aaa>hello world</bbb>";
  cout << "marked string: " << text << endl;
  cout << "expected output: "
       << "<aaa>hello world</aaa>"
       << "\n";
  cout << "actual   output: " << correct(text) << endl
       << endl;
}


