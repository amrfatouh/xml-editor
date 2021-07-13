#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "classes.cpp"

using namespace std;
vector<string> getDeclarations(string &minString)
{
  vector<string> declarations;
  if (minString.empty() || minString[1] != '?')
    return declarations;
  while (!minString.empty() && minString[1] == '?')
  {
    int closeIndex = minString.find('>');
    int numOfChars = closeIndex + 1;
    string declaration = minString.substr(0, numOfChars);
    declarations.push_back(declaration);
    minString.erase(0, numOfChars);
  }
  return declarations;
}

void testGetDeclarations()
{

  string minString;
  vector<string> declarations;

  //1 declaration
  minString = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";
  cout << "minString: " << minString << endl;
  declarations = getDeclarations(minString);
  cout << "declarations:\n";
  for (int i = 0; i < declarations.size(); i++)
    cout << declarations[i] << endl;
  cout << "rest of minString: " << minString << endl
       << endl;

  //1 declaration & root tag
  minString = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><user><id>0</id></user>";
  cout << "minString: " << minString << endl;
  declarations = getDeclarations(minString);
  cout << "declarations:\n";
  for (int i = 0; i < declarations.size(); i++)
    cout << declarations[i] << endl;
  cout << "rest of minString: " << minString << endl
       << endl;

  //2 declarations & root tag
  minString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-model href=\"data.rnc\" type=\"application/relax-ng-compact-syntax\"?><user><id>0</id></user>";
  cout << "minString: " << minString << endl;
  declarations = getDeclarations(minString);
  cout << "declarations:\n";
  for (int i = 0; i < declarations.size(); i++)
    cout << declarations[i] << endl;
  cout << "rest of minString: " << minString << endl
       << endl;
}

vector<string> parseComments(string &minString)
{
  vector<string> comments;
  while (!minString.empty() && minString[1] == '!')
  {
    int closeIndex = minString.find('>');
    int numOfChars = closeIndex + 1;
    string comment = minString.substr(0, numOfChars);
    comments.push_back(comment);
    minString.erase(0, numOfChars);
  }
  return comments;
}

void testParseComments()
{

  string minString;
  vector<string> comments;

  //1 comment
  minString = "<!-- first comment -->";
  cout << "minString: " << minString << endl;
  comments = parseComments(minString);
  cout << "comments:\n";
  for (int i = 0; i < comments.size(); i++)
    cout << comments[i] << endl;
  cout << "rest of minString: " << minString << "\n\n\n";

  //3 comment
  minString = "<!-- first comment --><!-- second comment --><!-- third comment -->";
  cout << "minString: " << minString << endl;
  comments = parseComments(minString);
  cout << "comments:\n";
  for (int i = 0; i < comments.size(); i++)
    cout << comments[i] << endl;
  cout << "rest of minString: " << minString << "\n\n\n";

  //comment & tag
  minString = "<!-- first comment --><!-- second comment --><body><div>hello world</div></body>";
  cout << "minString: " << minString << endl;
  comments = parseComments(minString);
  cout << "comments:\n";
  for (int i = 0; i < comments.size(); i++)
    cout << comments[i] << endl;
  cout << "rest of minString: " << minString << "\n\n\n";
}

TreeNode parseTag(string tag)
{
  TreeNode n;
  tag = tag.substr(1, tag.size() - 2); //removing brackets
  if (tag.back() == '/')
    tag.erase(tag.length() - 1, 1); //erase '/' if found
  int spaceIndex = tag.find(' ');
  if (spaceIndex == string::npos)
  {
    n.value = tag;
    return n;
  }

  int charsCount = spaceIndex;
  string tagName = tag.substr(0, charsCount);
  tag.erase(0, charsCount + 1);
  n.value = tagName;

  while (tag.find('=') != string::npos)
  {
    int equalIndex = tag.find('=');
    charsCount = equalIndex;
    string key = tag.substr(0, charsCount);
    tag.erase(0, charsCount + 1); //erase the key & the equal sign
    n.keys.push_back(key);
    if (tag.find('=') == string::npos)
    {
      tag = tag.substr(1, tag.length() - 2);
      n.values.push_back(tag);
    }
    else
    {
      spaceIndex = tag.find(' ');
      charsCount = spaceIndex;
      string value = tag.substr(0, charsCount);
      value = value.substr(1, value.length() - 2);
      tag.erase(0, charsCount + 1); //erase the value & the space
      n.values.push_back(value);
    }
  }
  return n;
}

void testParseTag()
{
  string tag;

  //regular tag
  tag = "<div>";
  cout << "tag: " << tag << endl;
  cout << "TreeNode:\n";
  parseTag(tag).printAll();
  cout << "\n\n";

  //empty tag
  tag = "<div/>";
  cout << "tag: " << tag << endl;
  cout << "TreeNode:\n";
  parseTag(tag).printAll();
  cout << "\n\n";

  //tag with 1 attribute
  tag = "<div class=\"red\">";
  cout << "tag: " << tag << endl;
  cout << "TreeNode:\n";
  parseTag(tag).printAll();
  cout << "\n\n";

  //tag with 3 attributes
  tag = "<div class=\"red\" id=\"mi-div\" data-num=\"1\">";
  cout << "tag: " << tag << endl;
  cout << "TreeNode:\n";
  parseTag(tag).printAll();
  cout << "\n\n";
}

string getNextElementType(string &minString)
{
  if (minString.empty())
    return "empty";
  if (minString[0] != '<')
    return "text";
  if (minString[1] == '!')
    return "comment";
  if (minString[1] == '/')
    return "closing tag";
  int closingIndex = minString.find('>');
  if (minString[closingIndex - 1] == '/')
    return "empty tag";
  return "opening tag";
}

void testGetNextElementType()
{
  string minString;

  //text
  minString = "hello<body><div></div></body>";
  cout << "minString: " << minString << endl;
  cout << "next element type: " << getNextElementType(minString) << "\n\n";

  //comment
  minString = "<!-- hello --><body><div></div></body>";
  cout << "minString: " << minString << endl;
  cout << "next element type: " << getNextElementType(minString) << "\n\n";

  //empty tag
  minString = "<div/><body><div></div></body>";
  cout << "minString: " << minString << endl;
  cout << "next element type: " << getNextElementType(minString) << "\n\n";

  //closing tag
  minString = "</div><body><div></div></body>";
  cout << "minString: " << minString << endl;
  cout << "next element type: " << getNextElementType(minString) << "\n\n";

  //opening tag
  minString = "<div></div><body><div></div></body>";
  cout << "minString: " << minString << endl;
  cout << "next element type: " << getNextElementType(minString) << "\n\n";

  //empty minString
  minString = "";
  cout << "minString: " << minString << endl;
  cout << "next element type: " << getNextElementType(minString) << "\n\n";
}

TreeNode parseComment(string comment)
{
  int closeIndex = comment.find("-->");
  int charsCount = closeIndex - 4;
  comment = comment.substr(4, charsCount);
  //trimming
  while (comment[0] == ' ')
    comment.erase(0, 1);
  while (comment.back() == ' ')
    comment.erase(comment.length() - 1, 1);
  TreeNode n = TreeNode("comment", comment);
  n.isComment = true;
  return n;
}

void testParseComment()
{
  string comment;

  //with spaces
  comment = "<!-- first comment -->";
  cout << "comment: " << comment << endl;
  cout << "TreeNode:\n";
  parseComment(comment).printAll();
  cout << "\n\n";

  //without spaces
  comment = "<!--first comment-->";
  cout << "comment: " << comment << endl;
  cout << "TreeNode:\n";
  parseComment(comment).printAll();
  cout << "\n\n";
}

TreeNode getNextElement(string &minString)
{
  string nextElemType = getNextElementType(minString);
  if (nextElemType == "empty")
    return TreeNode("tag", "");
  if (nextElemType == "text")
  {
    int openIndex = minString.find('<');
    int charsCount = openIndex;
    string text = minString.substr(0, charsCount);
    minString.erase(0, charsCount);
    TreeNode n = TreeNode("text", text);
    n.isText = true;
    return n;
  }
  else if (nextElemType == "comment")
  {
    int closeIndex = minString.find('>');
    int charsCount = closeIndex + 1;
    string comment = minString.substr(0, charsCount);
    minString.erase(0, charsCount);
    TreeNode commentNode = parseComment(comment);
    return commentNode;
  }
  else if (nextElemType == "opening tag")
  {
    int closeIndex = minString.find('>');
    int charsCount = closeIndex + 1;
    string tag = minString.substr(0, charsCount);
    minString.erase(0, charsCount);
    TreeNode tagNode = parseTag(tag);
    return tagNode;
  }
  else if (nextElemType == "empty tag")
  {
    int closeIndex = minString.find('>');
    int charsCount = closeIndex + 1;
    string tag = minString.substr(0, charsCount);
    minString.erase(0, charsCount);
    tag.erase(0, 1);
    tag.erase(tag.size() - 2, 2);
    TreeNode tagNode = TreeNode("tag", tag);
    return tagNode;
  }
  //the function doesn't handle the case of "closing tag"
}

void testGetNextElement()
{
  string minString;
  TreeNode n;

  //empty minString
  minString = "";
  cout << "minString: " << minString << endl;
  n = getNextElement(minString);
  cout << "TreeNode:\n";
  n.printAll();
  cout << endl;
  cout << "remaining minString: " << minString << endl;
  cout << "\n\n";

  //text
  minString = "hello world</div>";
  cout << "minString: " << minString << endl;
  n = getNextElement(minString);
  cout << "TreeNode:\n";
  n.printAll();
  cout << endl;
  cout << "remaining minString: " << minString << endl;
  cout << "\n\n";

  //comment
  minString = "<!-- hello world -->";
  cout << "minString: " << minString << endl;
  n = getNextElement(minString);
  cout << "TreeNode:\n";
  n.printAll();
  cout << endl;
  cout << "remaining minString: " << minString << endl;
  cout << "\n\n";

  //opening tag
  minString = "<div>";
  cout << "minString: " << minString << endl;
  n = getNextElement(minString);
  cout << "TreeNode:\n";
  n.printAll();
  cout << endl;
  cout << "remaining minString: " << minString << endl;
  cout << "\n\n";

  //opening tag with attributes and closing tag
  minString = "<div class=\"red\" id=\"my-div\"></div>";
  cout << "minString: " << minString << endl;
  n = getNextElement(minString);
  cout << "TreeNode:\n";
  n.printAll();
  cout << endl;
  cout << "remaining minString: " << minString << endl;
  cout << "\n\n";

  //empty tag
  minString = "<div/>";
  cout << "minString: " << minString << endl;
  n = getNextElement(minString);
  cout << "TreeNode:\n";
  n.printAll();
  cout << endl;
  cout << "remaining minString: " << minString << endl;
  cout << "\n\n";
}

Tree parseXmlTree(string &minString)
{
  Tree tree;
  if (minString.empty())
    return tree;
  //parsing the root node
  string elemType = getNextElementType(minString);
  int closeIndex = minString.find('>');
  int numOfChars = closeIndex + 1;
  string tag = minString.substr(0, numOfChars);
  minString.erase(0, numOfChars);
  TreeNode n = parseTag(tag);
  tree.root = n;
  if (elemType == "empty tag")
    return tree;

  //parsing the xml tree
  stack<TreeNode *> openTags;
  openTags.push(&tree.root);
  while (!openTags.empty())
  {
    string nextElemType = getNextElementType(minString);
    if (nextElemType == "text" || nextElemType == "comment" || nextElemType == "empty tag")
    {
      TreeNode n = getNextElement(minString);
      openTags.top()->children.push_back(n);
    }
    else if (nextElemType == "opening tag")
    {
      TreeNode n = getNextElement(minString);
      openTags.top()->children.push_back(n);
      //pushing the tag into stack of open tags
      TreeNode *childTagAddress = &openTags.top()->children.back();
      openTags.push(childTagAddress);
    }
    else if (nextElemType == "closing tag")
    {
      openTags.pop();
      //erase closing tag
      int closeIndex = minString.find('>');
      int charsCount = closeIndex + 1;
      minString.erase(0, charsCount);
    }
  }
  return tree;
}

void testParseXmlTree()
{
  string minString;

  //empty tag (with opening and closing tags)
  minString = "<body></body>";
  cout << "minString: " << minString << endl;
  parseXmlTree(minString).print();
  cout << "\n\n";

  //empty tag (with single tag)
  minString = "<body/>";
  cout << "minString: " << minString << endl;
  parseXmlTree(minString).print();
  cout << "\n\n";

  //tag inside tag [tag(tag)]
  minString = "<body><div></div></body>";
  cout << "minString: " << minString << endl;
  parseXmlTree(minString).print();
  cout << "\n\n";

  //tag(text, tag)
  minString = "<body>hello wolrd<div></div></body>";
  cout << "minString: " << minString << endl;
  parseXmlTree(minString).print();
  cout << "\n\n";

  //tag(comment, text, tag)
  minString = "<body><!-- my comment -->hello world<div></div></body>";
  cout << "minString: " << minString << endl;
  parseXmlTree(minString).print();
  cout << "\n\n";

  //tag(text, tag(comment, tag(text), text), comment)
  minString = "<body id=\"my-body\">hello world<div class=\"red\" id=\"my-div\"><!-- first comment --><span>hello world2</span>hello world3</div><!-- second comment --></body>";
  cout << "minString: " << minString << endl;
  parseXmlTree(minString).print();
  cout << "\n\n";

  //three parellel tags inside root tag
  //tag(tag(tag(text)), tag(tag(text)), tag(tag(tag(text)), tag(tag(text))))
  minString = "<body><div><span>hello world</span></div><div><span>hello world2</span></div><div><div><span>hello world3</span></div><div><span>hello world4</span></div></div></body>";
  cout << "minString: " << minString << endl;
  parseXmlTree(minString).print();
  cout << "\n\n";
}

ProcessedFile parse(string minString)
{
  ProcessedFile processedFile;
  processedFile.declarations = getDeclarations(minString);
  processedFile.upperComments = parseComments(minString);
  processedFile.tree = parseXmlTree(minString);
  processedFile.lowerComments = parseComments(minString);
  return processedFile;
}

void testParse()
{
  string minString;

  //only 1 declaration
  minString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  cout << "minString: " << minString << endl;
  cout << "processed file:\n";
  parse(minString).print();
  cout << "\n\n\n";

  //only 1 comment
  minString = "<!-- hello world -->";
  cout << "minString: " << minString << endl;
  cout << "processed file:\n";
  parse(minString).print();
  cout << "\n\n\n";

  //one tag having attributes
  minString = "<body id=\"my-body\" class=\"red\"></body>";
  cout << "minString: " << minString << endl;
  cout << "processed file:\n";
  parse(minString).print();
  cout << "\n\n\n";

  //2 declarations & 2 comments
  minString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-model href=\"data.rnc\" type=\"application/relax-ng-compact-syntax\"?><!-- first comment --><!-- second comment -->";
  cout << "minString: " << minString << endl;
  cout << "processed file:\n";
  parse(minString).print();
  cout << "\n\n\n";

  //1 declaration & 2 comments & root tag & 1 lower comment
  minString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!-- first comment --><!-- second comment --><body></body><!-- third comment -->";
  cout << "minString: " << minString << endl;
  cout << "processed file:\n";
  parse(minString).print();
  cout << "\n\n\n";

  //1 declaration & 2 comments & root tag & 1 lower comment
  minString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!-- first comment --><!-- second comment --><body></body><!-- third comment -->";
  cout << "minString: " << minString << endl;
  cout << "processed file:\n";
  parse(minString).print();
  cout << "\n\n\n";
}
