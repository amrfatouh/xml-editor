#ifndef PRETTIFYING_H
#define PRETTIFYING_H
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "parsing.h"

using namespace std;

string tabs(int tabsCount, string tab = "\t");
void testTabs();
string printPrettyXmlTree(TreeNode n, int depth, string tab = "\t");
void testPrintPrettyXmlTree();
string prettify(string text);
void testPrettify();
#endif // PRETTIFYING_H
