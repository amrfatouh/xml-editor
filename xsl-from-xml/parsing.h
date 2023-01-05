#ifndef PARSING_H
#define PARSING_H
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "classes.cpp"
#include "minifier.h"

using namespace std;

vector<string> getDeclarations(string &minString);
void testGetDeclarations();
vector<string> parseComments(string &minString);
void testParseComments();
TreeNode parseTag(string tag);
void testParseTag();
string getNextElementType(string &minString);
void testGetNextElementType();
TreeNode parseComment(string comment);
void testParseComment();
TreeNode getNextElement(string &minString);
void testGetNextElement();
Tree parseXmlTree(string &minString);
void testParseXmlTree();
ProcessedFile parseXml(string text);
void testParse();

#endif // PARSING_H
