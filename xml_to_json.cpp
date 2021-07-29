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

string s = "{\n";
string tab = "  ";

string toJson(TreeNode n, int rankOfChild, int rankOfNode, int tabs, int times, bool first, bool last, int maxRank)
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
			if (last)
				s += "\n";
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
			if (rankOfChild + rankOfNode == maxRank)
				s += "\n";
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
		if (last)
			s += "\n";
		else
			s += ",\n";

		if (last)
		{
			for (int i = 0; i < tabs; i++)
			{
				s += tab;
			}
			s += "]";
			if (rankOfNode + rankOfChild == maxRank)
				s += "\n";
			else
				s += ",\n";
		}
	}

	else
	{
		if (times > 1)
		{
			// print tag
			for (int i = 0; i < tabs; i++)
			{
				s += tab;
			}
			if (first)
			{
				s += "\"" + n.value + "\"" + ": [\n";
			}
			else
			{
				for (int i = 0; i < tabs - 1; i++)
				{
					s += tab;
				}
				s += "{\n";
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
			// print tag
			for (int i = 0; i < tabs; i++)
			{
				s += tab;
			}
			s += +"\"" + n.value + "\"" + ": ";

			s += "{";
			if (n.children.size() != 0)
				s += "\n";
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
				toJson(final_vector[i][j], j, i,
					tabs, final_vector[i].size(),
					j == 0,
					j == final_vector[i].size() - 1, final_vector.size() + final_vector[i].size() - 2);
			}
		}
		// closing brackets
		if (times > 1)
		{
			tabs--;
			for (int i = 0; i < tabs; i++)
			{
				s += tab;
			}
			s += (rankOfChild + 1 == times) ? "}\n" : "},\n";

			if (last)
			{
				tabs--;
				for (int i = 0; i < tabs; i++)
				{
					s += tab;
				}
				s += (rankOfChild + rankOfNode == maxRank) ? "]\n" : "],\n";
			}
		}

		else
		{
			tabs--;
			if (n.children.size() != 0)
				for (int i = 0; i < tabs; i++)
				{
					s += tab;
				}
			s += (rankOfChild + rankOfNode == maxRank) ? "}\n" : "},\n";
		}
	}

	return s + "}";
}

string string_to_json(string text)
{
	return toJson(parse(text).tree.root, 0, 0, 1, 1, true, true, 0);
}