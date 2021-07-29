#ifndef XML_TO_JSON_H
#define XML_TO_JSON_H
#include "parsing.h"
#include <vector>

using namespace std;

vector<vector<TreeNode>> concatinate_childrens(vector<TreeNode> children);


string toJson(TreeNode n, int rankOfChild , int tabs , int times , bool first , bool last );

string string_to_json(string text);

#endif // XML_TO_JSON_H
