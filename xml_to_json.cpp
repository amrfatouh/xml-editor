#include "classes.cpp"
#include "parsing.cpp"
#include <vector>

using namespace std;

void toJson(TreeNode n, int rankOfChild = 0)
{
    if (n.isText)
    // print text
    {
        cout << "\"" << n.value << "\"";
        if (n.children.size() == 1 || (n.children.size() == rankOfChild))
            cout << "\n";
        else
            cout << ",\n";
    }
    else if (n.isComment)
    // print comment
    {
        cout << "<!-- " << n.value << " -->";
    }
    else
    {
        // print tag
        cout << "\"" << n.value << "\""
             << ": ";
        if (n.children.size() != 1)
            cout << "{\n";
        else
            cout << "";
        // print key value pairs
        for (int i = 0; i < n.keys.size(); i++)
        {
            cout << " " << n.keys[i] << "=\"" << n.values[i] << "\"";
        }
        for (int i = 0; i < n.children.size(); i++)
        {
            toJson(n.children[i], i + 1);
        }
        if (n.children.size() != 1)
            cout << "}\n";
        else
            cout << "";
    }
}