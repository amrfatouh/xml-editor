#ifndef CLASSES_H_
#define CLASSES_H_

#include <string>
#include <vector>
#include <iostream>



using namespace std;
class TreeNode
{
public:
  string value;     // tagName | text | comment
  /*xxx*/ TreeNode *parent; //deprecated
  vector<TreeNode> children;
  vector<string> keys;   //for attributes
  vector<string> values; //for attributes
  bool isText;
  bool isComment;

  TreeNode()
  {
    isComment = isText = false;
    value = "";
    parent = NULL;
  }
  TreeNode(string type, string val)
  {
    isComment = isText = false;
    if (type == "comment")
      isComment = true;
    else if (type == "text")
      isText = true;
    value = val;
    parent = NULL;
  }

  void addChild(string type, string val)
  {
    TreeNode n(type, val);
    n.isComment = n.isText = false;
    if (type == "comment")
      n.isComment = true;
    else if (type == "text")
      n.isText = true;
    n.parent = this;
    children.push_back(n);
  }

  bool addAttribute(string k, string v)
  {
    if (isComment || isText)
      return false;
    keys.push_back(k);
    values.push_back(v);
  }

  void print()
  {
    if (!isComment && !isText)
      cout << "<" << value << "></" << value << ">" << endl;
    else if (isComment)
      cout << "<!-- " << value << " -->" << endl;
    else if (isText)
      cout << value << endl;
  }

  void printRecursively(TreeNode n)
  {
    if (n.isText)
      cout << n.value;
    else if (n.isComment)
      cout << "<!-- " << n.value << " -->";
    else
    {
      cout << "<" << n.value;
      for (int i = 0; i < n.keys.size(); i++)
      {
        cout << " " << n.keys[i] << "=\"" << n.values[i] << "\"";
      }
      cout << ">";
      for (int i = 0; i < n.children.size(); i++)
      {
        printRecursively(n.children[i]);
      }
      cout << "</" << n.value << ">";
    }
  }

  void printAll()
  {
    printRecursively(*this);
  }
};

//testing the creation of a tag, text, comment TreeNode
//also testing print() function
//void testBasics()
//{
//  TreeNode n1("tag", "head");
//  n1.print();
//  TreeNode n2("text", "hello world");
//  n2.print();
//  TreeNode n3("comment", "this is a comment");
//  n3.print();
//}

//void testPrintAll()
//{
//  TreeNode n("tag", "body");
//  n.addChild("tag", "div");
//  n.children[0].addChild("text", "hello world");
//  n.children[0].addAttribute("class", "red");
//  n.children[0].addAttribute("id", "my-div");
//  n.addChild("tag", "span");
//  n.addChild("comment", "this is a comment");

//  n.printAll();
//}

class Tree
{
public:
  TreeNode root;

  //make the root an empty TreeNode
  Tree()
  {
    root = TreeNode();
  }
  Tree(TreeNode n)
  {
    root = n;
  }

  void print()
  {
    root.printAll();
  }
};

//void testingTreePrint()
//{
//  Tree t(TreeNode("tag", "body"));
//  t.root.addChild("tag", "div");
//  t.root.children[0].addChild("text", "hello world");
//  t.print();
//}

class ProcessedFile
{
public:
  Tree tree;
  vector<string> declarations;
  vector<string> upperComments;
  vector<string> lowerComments;

  ProcessedFile()
  {
    tree = Tree();
  }

  void print()
  {
    cout << "declarations:\n";
    for (int i = 0; i < declarations.size(); i++)
      cout << declarations[i] << endl;
    cout << "\nupper comments:\n";
    for (int i = 0; i < upperComments.size(); i++)
      cout << upperComments[i] << endl;
    cout << "\ntree:\n";
    tree.print();
    cout << "\nlower comments:\n";
    for (int i = 0; i < lowerComments.size(); i++)
      cout << lowerComments[i] << endl;
  }
};

class InputFile
{
public:
  string fileContent;
  bool isChecked;
  bool errorFree;
  int errorNum;
  InputFile()
  {
    fileContent = "";
    isChecked = false;
    errorFree = true;
  }
};

class OutputFile
{
public:
  string fileContent;
  string fileType = "xml";

  OutputFile()
  {
    fileContent = "";
    fileType = "xml";
  }
};

#endif
