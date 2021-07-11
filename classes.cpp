
class TreeNode
{
public:
  string value;     // tagName | text | comment
  TreeNode *parent; //parent of root is NULL
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
void testBasics()
{
  TreeNode n1("tag", "head");
  n1.print();
  TreeNode n2("text", "hello world");
  n2.print();
  TreeNode n3("comment", "this is a comment");
  n3.print();
}

void testPrintAll()
{
  TreeNode n("tag", "body");
  n.addChild("tag", "div");
  n.children[0].addChild("text", "hello world");
  n.children[0].addAttribute("class", "red");
  n.children[0].addAttribute("id", "my-div");
  n.addChild("tag", "span");
  n.addChild("comment", "this is a comment");

  n.printAll();
}

class Tree
{
public:
  TreeNode root;

  Tree(TreeNode n)
  {
    root = n;
  }

  void print()
  {
    root.printAll();
  }
};

void testingTreePrint()
{
  Tree t(TreeNode("tag", "body"));
  t.root.addChild("tag", "div");
  t.root.children[0].addChild("text", "hello world");
  t.print();
}

class ProcessedFile
{
  Tree tree;
  string declaration;
  vector<string> upperComments;
  vector<string> lowerComments;
};

class InputFile
{
  string fileContent;
  bool isChecked;
};

class OutputFile
{
  string fileContent;
  string fileType;
};