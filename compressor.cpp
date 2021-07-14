#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_
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
    HuffmanNode* left;
    HuffmanNode* right;
};

// Function to allocate a new tree node
HuffmanNode* addHuffmanNode(char ch, int freq, HuffmanNode* left, HuffmanNode* right)
{
    HuffmanNode* addedNode = new HuffmanNode();

    addedNode->value = ch;
    addedNode->frequency = freq;
    addedNode->left = left;
    addedNode->right = right;

    return addedNode;
}

// Comparison object to be used to order the heap
class compare
{
public:
    bool operator()(const HuffmanNode* leftChild, const HuffmanNode* rightChild) const
    {
        // the highest priority item has the lowest frequency
        if (leftChild->frequency > rightChild->frequency)
            return true;
        else
            return false;
    }
};

// Utility function to check if Huffman Tree contains only a single node
bool isLeaf(HuffmanNode* root) {
    if (root->left == nullptr && root->right == nullptr)
        return true;
    else
        return false;
}

// Traverse the Huffman Tree and store Huffman Codes in a map.
void encode(HuffmanNode* root, string encodeString, unordered_map<char, string>& huffmanCode)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (isLeaf(root)) {
        huffmanCode[root->value] = (encodeString != EMPTY_STRING) ? encodeString : "1";
    }

    encode(root->left, encodeString + "0", huffmanCode);
    encode(root->right, encodeString + "1", huffmanCode);
}

// Traverse the Huffman Tree and decode the encoded string
void decode(HuffmanNode* root, int& index, string str, string& decodedString)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (isLeaf(root))
    {
        decodedString += root->value;
        return;
    }

    index++;

    if (str[index] == '0') {
        decode(root->left, index, str, decodedString);
    }
    else {
        decode(root->right, index, str, decodedString);
    }
}

// Builds Huffman Tree
priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> createHuffmanTree(string text ,unordered_map<char, int> &freqtable)
{
  
    // count the frequency of appearance of each character
    // and store it in a map
//    unordered_map<char, int> table;
//    long long textLength = text.length();
//    for (int i = 0; i < textLength; i++) {
  
//        //if not found in table insert it
//        if (table[text[i]]==0) {
//            char c = text[i];
//            int icount = count(text.begin(), text.end(), c);
//            table.insert({ c, icount });
//        }
//    }

    for (char ch: text) {
        freqtable[ch]++;
    }


    // Create a priority queue to store live nodes of the Huffman tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> priorityQue;

    // Create a leaf node for each character and add it
    // to the priority queue.
    for (auto pair : freqtable) {
        priorityQue.push(addHuffmanNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (priorityQue.size() != 1)
    {
        // Remove the two nodes of the highest priority
        // (the lowest frequency) from the queue

        HuffmanNode* left = priorityQue.top();
        priorityQue.pop();
        HuffmanNode* right = priorityQue.top();
        priorityQue.pop();

        // create a new internal node with these two nodes as children and
        // with a frequency equal to the sum of the two nodes' frequencies.
        // Add the new node to the priority queue.

        int sum = left->frequency + right->frequency;
        priorityQue.push(addHuffmanNode('\0', sum, left, right));
    }

    return priorityQue;
}
//priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> createHuffmanTreeForDecoding(unordered_map<char, int> &freqtable)
//{
//    // Create a priority queue to store live nodes of the Huffman tree
//    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> priorityQue;
//    for (auto pair : freqtable) {
//        priorityQue.push(addHuffmanNode(pair.first, pair.second, nullptr, nullptr));
//    }

//    // do till there is more than one node in the queue
//    while (priorityQue.size() != 1)
//    {
//        // Remove the two nodes of the highest priority
//        // (the lowest frequency) from the queue

//        HuffmanNode* left = priorityQue.top();
//        priorityQue.pop();
//        HuffmanNode* right = priorityQue.top();
//        priorityQue.pop();

//        // create a new internal node with these two nodes as children and
//        // with a frequency equal to the sum of the two nodes' frequencies.
//        // Add the new node to the priority queue.

//        int sum = left->frequency + right->frequency;
//        priorityQue.push(addHuffmanNode('\0', sum, left, right));
//    }

//    return priorityQue;
//}
string getEncodedString(HuffmanNode* root, string text, QFile &file ,unordered_map<char, string>& huffmanCode) {


    // Traverse the Huffman Tree and store Huffman Codes
   // in a map. Also, print them

    encode(root, EMPTY_STRING, huffmanCode);


     // Print encoded string
    string encodedString;
    for (char ch : text) {
//        QBitArray converted(huffmanCode[ch].length());
//        for(int i=0;i< huffmanCode[ch].length();i++){
//            if(huffmanCode[ch][i]=='1'){
//                converted.setBit(i);
//            }
//        }

        encodedString += huffmanCode[ch];
//        QDataStream streamx(&file);
//        streamx << converted;
    }
    auto lengt =encodedString.length();
    QBitArray converted(lengt);
            for(int i=0;i< lengt;i++){
                if(encodedString[i]=='1'){
                    converted.setBit(i);
                }
            }
   QDataStream streamx(&file);
   streamx << converted;
//            quint32 len = converted.size();
//                streamx << len;
//                if (len > 0)
//                    streamx.writeRawData(converted.bits(), converted.size() - 1);
    return encodedString;

}
string getDecodedString(HuffmanNode* root, string encodedString) {
    string funcOutput = "";
    //decoding
    if (isLeaf(root))
    {
        // Special case: For input like a, aa, aaa, etc.
        while (root->frequency--) {
            funcOutput+=root->value;
        }
    }
    else {
        // Traverse the Huffman Tree again and this time,
        // decode the encoded string
        int index = -1;
        while (index < (int)encodedString.size() - 1) {
            decode(root, index, encodedString, funcOutput);
        }
    }
    return funcOutput;
}
void storeHuffmanFreqTable(unordered_map<char, int> &freqtable, QFile &huffmanCodeFile){
    //unordered_map<char,string>::iterator it =huffmanCode.begin();
    unordered_map<char,int>::iterator it =freqtable.begin();
    QTextStream streamh(&huffmanCodeFile);
   // while(it!=huffmanCode.end())
    while(it!=freqtable.end()){
        string intermed =to_string(it->first);
        streamh<<QString::fromStdString(intermed)<<"\n"<<QString::fromStdString(to_string(it->second))<<"\n";
       // streamh<<QString::fromStdString(intermed)<<"\n"<<QString::fromStdString(it->second)<<"\n";
        it++;
    }

}

//void readHuffmanFreqTable(unordered_map<char, int> &freqtable, QFile &huffmanCodeFile){
//    QTextStream streamh(&huffmanCodeFile);
//    while(streamh.atEnd()){
//    QString readedChar = streamh.readLine();
//    string convertedReadedChar= readedChar.toStdString();
//    int token =stoi(convertedReadedChar);
//    char hc =(char)token;
//    QString readedStr = streamh.readLine();
//    string convertedReadedStr= readedStr.toStdString();
//    int counter=stoi(convertedReadedStr);
//    //huffmanCode.insert({hc,convertedReadedStr});
//    freqtable.insert({hc,counter});
//    }
//}
//you must ensure that the text isn't empty
string compress(string text, QFile &file,QFile &huffmanCodeFile) {
    string funcOutput;
    unordered_map<char, string> huffmanCode;
    if (text != "") {
        unordered_map<char, int> freqtable;
        auto huffmanTree = createHuffmanTree(text,freqtable);
        // `root` stores pointer to the root of Huffman Tree
        HuffmanNode* root = huffmanTree.top();
        funcOutput= getEncodedString(root, text, file,huffmanCode);
        storeHuffmanFreqTable(freqtable,huffmanCodeFile);
        return funcOutput;
    }
    return text;
}
//string decompress(QFile &file, QFile &huffmanCodeFile){
//    string funcOutput;
//   //HuffmanNode* newRoot = new HuffmanNode();
//    //unordered_map<char, string> huffmanCode;
//    unordered_map<char, int> freqtable;
//    readHuffmanFreqTable(freqtable,huffmanCodeFile);
//    auto huffmanTree = createHuffmanTreeForDecoding(freqtable);
//    // `root` stores pointer to the root of Huffman Tree
//    HuffmanNode* root = huffmanTree.top();
//    QTextStream streamx(&file);
//    QString enc=streamx.readAll();
//    string encodedString = enc.toStdString();
//    funcOutput=getDecodedString(root,encodedString);

//    return funcOutput;
//}
#endif
