#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <string>
#include <queue>
#include <unordered_map>
#include <bits/stdc++.h>
#include <QTextStream>
#include <QFile>
#include <QBitArray>
#include <QDataStream>
#include <QString>


using namespace std;

#define EMPTY_STRING ""

// A Tree node
class HuffmanNode
{
public:
    char value;
    int frequency;
    int nNodes;
    HuffmanNode* left;
    HuffmanNode* right;
};

int countSubNodes(HuffmanNode* n);
HuffmanNode* addHuffmanNode(char ch, int freq,int pri, HuffmanNode* left, HuffmanNode* right);
// Comparison object to be used to order the heap
class compare
{
public:
    bool operator()(const HuffmanNode* leftChild, const HuffmanNode* rightChild) const
    {
        // the highest priority item has the lowest frequency
        if(leftChild->frequency!=rightChild->frequency){
        if (leftChild->frequency > rightChild->frequency)
            return true;
        else
            return false;}
        else{
            if(leftChild->nNodes > rightChild->nNodes){
                return true;
            }
            else{return false;}
        }
    }
};
bool isLeaf(HuffmanNode* root);
void encode(HuffmanNode* root, string encodeString, unordered_map<char, string>& huffmanCode);
void decode(HuffmanNode* root, int& index, string str, string& decodedString);
priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> createHuffmanTree(string text ,unordered_map<char,pair<int, int>> &freqtable);
priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> createHuffmanTreeForDecoding(unordered_map<char,pair<int, int>> &freqtable);
void write_string(string path, const string &content);
string getEncodedString(HuffmanNode* root, string text, string saveToPath ,unordered_map<char, string>& huffmanCode);
string getDecodedString(HuffmanNode* root, string encodedString);
void storeHuffmanFreqTable(unordered_map<char,pair<int, int>> &freqtable, QFile &huffmanCodeFile);
void readHuffmanFreqTable(unordered_map<char,pair<int, int>> &freqtable, QFile &huffmanCodeFile);
string compress(string text, string filePath,QFile &huffmanCodeFile);
string read_string(string path);
string decompress(string strFilePath, QFile &huffmanCodeFile);
#endif // COMPRESSOR_H
