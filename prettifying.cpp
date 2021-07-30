#include "prettifying.h"


using namespace std;

string tabs(int tabsCount, string tab )
{
  string text = "";
  for (int i = 0; i < tabsCount; i++)
    text.append(tab);
  return text;
}

void testTabs()
{
  string text;

  //1 tab
  text = "hello";
  cout << "before: " << text << endl;
  text += tabs(1);
  text.append("hello");
  cout << "after: " << text;
  cout << "\n\n";

  //3 tabs
  text = "hello";
  cout << "before: " << text << endl;
  text += tabs(3);
  text.append("hello");
  cout << "after: " << text;
  cout << "\n\n";

  //3 tabs, each tab is 2 spaces
  text = "hello";
  cout << "before: " << text << endl;
  text += tabs(3, "  ");
  text.append("hello");
  cout << "after: " << text;
  cout << "\n\n";
}

string printPrettyXmlTree(TreeNode n, int depth, string tab)
{
  string prettyXml = "";
  if (n.isText)
  {
    prettyXml += tabs(depth, tab);
    prettyXml.append(n.value + "\n");
  }
  else if (n.isComment)
  {
    prettyXml += tabs(depth, tab);
    prettyXml.append("<!-- " + n.value + " -->\n");
  }
  else
  {
    prettyXml += tabs(depth, tab);
    prettyXml += "<" + n.value;
    for (int i = 0; i < n.keys.size(); i++)
      prettyXml += " " + n.keys[i] + "=\"" + n.values[i] + "\"";
    prettyXml += ">\n";
    for (int i = 0; i < n.children.size(); i++)
      prettyXml += printPrettyXmlTree(n.children[i], depth + 1, tab);
    prettyXml += tabs(depth, tab);
    prettyXml.append("</" + n.value + ">\n");
  }
  return prettyXml;
}

void testPrintPrettyXmlTree()
{
  string minString;
  ProcessedFile file;

  //tab(text)
  minString = "<body>hello world</body>";
  cout << "minString: " << minString << endl;
  file = parse(minString);
  cout << "prettified:\n";
  cout << printPrettyXmlTree(file.tree.root, 0) << "\n\n";

  //tag(tag(text), comment, text, tag(tag(text, comment)))
  minString = "<body><div>hello world</div><!-- first comment -->hello world2<div><div>hello world3<!-- second comment --></div></div></body>";
  cout << "minString: " << minString << endl;
  file = parse(minString);
  cout << "prettified:\n";
  cout << printPrettyXmlTree(file.tree.root, 0, "  ") << "\n\n";
}

string prettify(string text)
{
  ProcessedFile file = parse(text);
  string prettyString = "";
  string tab = "    ";
  for (int i = 0; i < file.declarations.size(); i++)
  {
    prettyString.append(file.declarations[i] + "\n");
  }
  for (int i = 0; i < file.upperComments.size(); i++)
  {
    prettyString.append(file.upperComments[i] + "\n");
  }
  prettyString += printPrettyXmlTree(file.tree.root, 0, tab);
  for (int i = 0; i < file.lowerComments.size(); i++)
  {
    prettyString.append(file.lowerComments[i] + "\n");
  }
  return prettyString;
}

void testPrettify()
{
  string minString;
  ProcessedFile file;

  //2 declaration & 2 comments & root tag (with attributes) & 1 lower comment
  minString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?xml-model href=\"data.rnc\" type=\"application/relax-ng-compact-syntax\"?><!-- first comment --><!-- second comment --><body class=\"red\" id=\"my-body\"><div>hello world</div><!-- first comment -->hello world2<div><div>hello world3<!-- second comment --></div></div></body><!-- third comment -->";
  cout << "minString: " << minString << endl;
  cout << "prettified:\n";
  cout << prettify(minString);
  cout << "\n\n\n";
}


