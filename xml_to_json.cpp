#include "classes.cpp"
#include "parsing.cpp"
#include <vector>

using namespace std;
string s = "";
string tab = "    ";

string toJson(TreeNode n, int rankOfChild = 0, int tabs = 0)
{
    if (n.isText)
    // print text
    {
        for (int i = 0; i < tabs; i++)
        {
            s += tab;
        }
        s += "\"#text\": ";
        s += "\"" + n.value + "\"";
        if (n.children.size() == 1 || (n.children.size() == rankOfChild))
            s += +"\n";
        else
            s += ",\n";
    }
    else if (n.isComment)
    // print comment
    {
        s += +"<!-- " + n.value + " -->";
    }
    else
    {
        // print tag
        for (int i = 0; i < tabs; i++)
        {
            s += tab;
        }
        s += +"\"" + n.value + "\"" + ": ";
        if (n.children.size() != 1 || n.keys.size() != 1)
        {
            s += "{\n";
        }
        else
            s += "";

        // print key value pairs
        for (int i = 0; i < n.keys.size(); i++)
        {
            for (int i = 0; i < tabs + 1; i++)
            {
                s += tab;
            }
            s += "\"@" + n.keys[i] + "\"" + " = \"" + n.values[i] + "\"" + ",\n";
        }
        tabs++;
        for (int i = 0; i < n.children.size(); i++)
        {
            toJson(n.children[i], i + 1, tabs);
        }
        if (n.children.size() != 1 || n.keys.size() != 1)
        {
            tabs--;
            for (int i = 0; i < tabs; i++)
            {
                s += tab;
            }
            s += "}\n";
        }
        else
            s += "";
    }
    return s;
}