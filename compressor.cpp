#include "compressor.h"

int countSubNodes(HuffmanNode* n) {
    if (n == nullptr)
      return 0;
    return countSubNodes(n->left) + countSubNodes(n->right) + 1;
  }
// Function to allocate a new tree node
HuffmanNode* addHuffmanNode(char ch, int freq,int pri, HuffmanNode* left, HuffmanNode* right)
{
    HuffmanNode* addedNode = new HuffmanNode();

    addedNode->value = ch;
    addedNode->frequency = freq;
    addedNode->left = left;
    addedNode->right = right;
    addedNode->nNodes =pri;
    return addedNode;
}


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
priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> createHuffmanTree(string text ,unordered_map<char,pair<int, int>> &freqtable)
{
  
    for (char ch: text) {
        freqtable[ch].first++;
    }

     int index=0;
    for(auto &pair:freqtable){
        pair.second.second=index;
        index=index+1;
    }

    // Create a priority queue to store live nodes of the Huffman tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> priorityQue;

    // Create a leaf node for each character and add it
    // to the priority queue.

    for (auto pair : freqtable) {
        priorityQue.push(addHuffmanNode(pair.first, pair.second.first,pair.second.second, nullptr, nullptr));

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
        int sumPri=left->nNodes+right->nNodes;
        priorityQue.push(addHuffmanNode('\0', sum,sumPri, left, right));
    }

    return priorityQue;
}
priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> createHuffmanTreeForDecoding(unordered_map<char,pair<int, int>> &freqtable)
{
    // Create a priority queue to store live nodes of the Huffman tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> priorityQue;
    for (auto pair : freqtable) {
        priorityQue.push(addHuffmanNode(pair.first, pair.second.first,pair.second.second, nullptr, nullptr));
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
        int sumPri=left->nNodes+right->nNodes;
        priorityQue.push(addHuffmanNode('\0', sum,sumPri, left, right));
    }

    return priorityQue;
}
void write_string(string path, const string &content) {
  char byte = 0;
  int counter = 0;

  ofstream output_file(path, ios::binary);

  long long input_size = content.length();
  output_file.write((char *)&input_size, 8);

  for (auto input : content) {
    input -= '0';
    byte |= (input << (7 - counter));

    counter++;

    if (counter == 8) {
      output_file.put(byte);

      byte = 0;
      counter = 0;
    }
  }

  if (counter != 0) {
    output_file.put(byte);
  }
}
string getEncodedString(HuffmanNode* root, string text, string saveToPath ,unordered_map<char, string>& huffmanCode) {


    // Traverse the Huffman Tree and store Huffman Codes
   // in a map. Also, print them

    encode(root, EMPTY_STRING, huffmanCode);


     // Print encoded string
    string encodedString;
    for (char ch : text) {
        encodedString += huffmanCode[ch];
    }
    write_string(saveToPath,encodedString);
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
void storeHuffmanFreqTable(unordered_map<char,pair<int, int>> &freqtable, QFile &huffmanCodeFile){
    unordered_map<char,pair<int, int>>::iterator it =freqtable.begin();
    QTextStream streamh(&huffmanCodeFile);
    while(it!=freqtable.end()){
        string intermed =to_string(it->first);
        streamh<<QString::fromStdString(intermed)<<"\n"<<QString::fromStdString(to_string(it->second.first))<<"\n"<<QString::fromStdString(to_string(it->second.second))<<"\n";

        it++;
    }

}

void readHuffmanFreqTable(unordered_map<char,pair<int, int>> &freqtable, QFile &huffmanCodeFile){
    QTextStream streamh(&huffmanCodeFile);
    while(!streamh.atEnd()){
    QString readedChar = streamh.readLine();
    string convertedReadedChar= readedChar.toStdString();
    int token =stoi(convertedReadedChar);
    char hc =(char)token;
    QString readedStr = streamh.readLine();
    string convertedReadedStr= readedStr.toStdString();
    int counter=stoi(convertedReadedStr);
    QString readedPri = streamh.readLine();
    string convertedReadedPri=readedPri.toStdString();
    int prio=stoi(convertedReadedPri);
    freqtable.insert({hc,{counter,prio}});
    }
}

//you must ensure that the text isn't empty
string compress(string text, string filePath,QFile &huffmanCodeFile) {
    string funcOutput;
    unordered_map<char, string> huffmanCode;
    if (text != "") {
        unordered_map<char,pair<int, int>> freqtable;
        auto huffmanTree = createHuffmanTree(text,freqtable);
        // `root` stores pointer to the root of Huffman Tree
        HuffmanNode* root = huffmanTree.top();
        funcOutput= getEncodedString(root, text, filePath,huffmanCode);
        storeHuffmanFreqTable(freqtable,huffmanCodeFile);
        return funcOutput;
    }
    return text;
}

string read_string(string path) {
  string buf;
  char byte;

  ifstream input_file(path, ios::binary);

  long long input_size;
  input_file.read((char *)&input_size, 8);

  int extra_bits = input_size % 8;
  int limit = input_size / 8;

  for (auto i = 0; i < limit; i++) {
    input_file.get(byte);

    for (auto counter = 0; counter < 8; counter++) {
      buf.push_back('0' + ((byte >> (7 - counter)) & 1));
    }
  }

  if (extra_bits != 0) {
    input_file.get(byte);

    for (auto counter = 0; counter < extra_bits; counter++) {
      buf.push_back('0' + ((byte >> (7 - counter)) & 1));
    }
  }

  return buf;
}
string decompress(string strFilePath, QFile &huffmanCodeFile){
    string funcOutput ="";
    unordered_map<char,pair<int, int>> freqtable;

   readHuffmanFreqTable(freqtable,huffmanCodeFile);
 auto huffmanTree = createHuffmanTreeForDecoding(freqtable);
    // `root` stores pointer to the root of Huffman Tree
   HuffmanNode* root = huffmanTree.top();
    string enc=read_string(strFilePath);
funcOutput=getDecodedString(root,enc);
    return funcOutput;
}


