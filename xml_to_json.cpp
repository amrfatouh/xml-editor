#include "xml_to_json.h"


using namespace std;

vector<vector<TreeNode>> concatinate_childrens(vector<TreeNode> children)
{
    vector<vector<TreeNode>> final_vector(children.size());
    int current_index = 0;
    for (int i = 0; i < children.size(); i++)
    {
        TreeNode current = children[i];
        final_vector[current_index].push_back(current);
        children.erase(children.begin() + i);

        for (int j = 0; j < children.size(); j++)
        {
            if ((children[j].value == current.value) ||
                (children[j].isText && current.isText) ||
                (children[j].isComment && current.isComment))
            {
                final_vector[current_index].push_back(children[j]);
                children.erase(children.begin() + j);
                j = -1;
            }
        }
        current_index++;
        i = -1;
    }
    for (int i = 0; i < final_vector.size(); i++)
    {
        if (final_vector[i].size() == 0)
        {
            final_vector.erase(final_vector.begin() + i);
            i = -1;
        }
    }
    return final_vector;
}

string s = "";
string tab = "  ";

string toJson(TreeNode n, int rankOfChild , int tabs , int times , bool first , bool last )
{
    if (n.isText)
    // print text
    {
        // list if needed
        if (times > 1)
        {
            if (first)
            {
                for (int i = 0; i < tabs; i++)
                {
                    s += tab;
                }
                s += "\"#text\": ";
                s += "[\n";
            }
            for (int i = 0; i < tabs + 1; i++)
            {
                s += tab;
            }
            s += "\"" + n.value + "\"";
            if (n.children.size() == 1 || (n.children.size() == rankOfChild))
                s += +"\n";
            else
                s += ",\n";
            if (last)
            {
                for (int i = 0; i < tabs; i++)
                {
                    s += tab;
                }
                s += "],\n";
            }
        }
        else
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
    }

    else if (n.isComment)
    // print comment
    {
        if (first)
        {
            for (int i = 0; i < tabs; i++)
            {
                s += tab;
            }
            s += "\"#comments\": ";
            s += "[\n";
        }
        for (int i = 0; i < tabs + 1; i++)
        {
            s += tab;
        }
        s += "\"" + n.value + "\"";
        if (n.children.size() == 1 || (n.children.size() == rankOfChild))
            s += +"\n";
        else
            s += ",\n";
        if (last)
        {
            for (int i = 0; i < tabs; i++)
            {
                s += tab;
            }
            s += "],\n";
        }
    }

    else
    {
        if (times > 1)
        {
            if (rankOfChild == 0)
                s += "{\n";
            // print tag
            for (int i = 0; i < tabs; i++)
            {
                s += tab;
            }
            if (first)
            {
                s += "\"" + n.value + "\"" + ": ";
            }
            else
            {
                for (int i = 0; i < tabs - 2; i++)
                {
                    s += tab;
                }
                s += "{\n";
            }

            if (n.children.size() != 1 || n.keys.size() != 1)
            {
                if (first)
                    s += "[\n";
                else
                    s += "";
            }
            tabs++;

            if (first)
            {
                for (int i = 0; i < tabs; i++)
                {
                    s += tab;
                }
                s += "{\n";
            }
            else
                s += "";
        }
        else
        {
            if (rankOfChild == 0)
                s += "{\n";

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
        }

        // print key value pairs
        for (int i = 0; i < n.keys.size(); i++)
        {
            for (int i = 0; i < tabs + 1; i++)
            {
                s += tab;
            }
            s += "\"@" + n.keys[i] + "\"" + ": \"" + n.values[i] + "\"" + ",\n";
        }
        tabs++;
        vector<vector<TreeNode>> final_vector = concatinate_childrens(n.children);

        for (int i = 0; i < final_vector.size(); i++)
        {
            for (int j = 0; j < final_vector[i].size(); j++)
            {
                toJson(final_vector[i][j], i + 1,
                       tabs, final_vector[i].size(),
                       j == 0,
                       j == final_vector[i].size() - 1);
            }
        }
        // closing brackets
        if (times > 1)
        {
            if (n.children.size() != 1 || n.keys.size() != 1)
            {
                tabs--;
                for (int i = 0; i < tabs; i++)
                {
                    s += tab;
                }
                s += rankOfChild != 0 ? "},\n" : "}\n}";

                if (last)
                {
                    tabs--;
                    for (int i = 0; i < tabs; i++)
                    {
                        s += tab;
                    }
                    s += "],\n";
                }
            }
            else
                s += "";
        }
        else
        {
            if (n.children.size() != 1 || n.keys.size() != 1)
            {
                tabs--;
                for (int i = 0; i < tabs; i++)
                {
                    s += tab;
                }
                s += rankOfChild != 0 ? "},\n" : "}\n}";
            }
            else
                s += "";
        }
    }

    return s;
}

string string_to_json(string text)
{
    return toJson(parse(text).tree.root,0,1,1,true,true);
}


