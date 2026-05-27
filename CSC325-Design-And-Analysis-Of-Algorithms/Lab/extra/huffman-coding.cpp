#include <iostream>
#include <queue>
#include <iomanip>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = nullptr;
    }

    Node(char c,
         int f,
         Node *l,
         Node *r)
    {
        ch = c;
        freq = f;
        left = l;
        right = r;
    }
};

struct compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

void generateCodes(Node *root,
                   string code,
                   unordered_map<char, string> &huffmanCode)
{
    if (!root)
        return;

    if (!root->left && !root->right)
        huffmanCode[root->ch] = code;

    generateCodes(root->left,
                  code + "0",
                  huffmanCode);

    generateCodes(root->right,
                  code + "1",
                  huffmanCode);
}

int getHeight(Node *root)
{
    if (!root)
        return 0;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

int getNodesCount(int level)
{
    return 1 << level;
}

string nodeToString(Node *node)
{
    if (!node)
        return "";

    if (!node->left && !node->right)
    {
        return string(1, node->ch) + "(" + to_string(node->freq) + ")";
    }

    return to_string(node->freq);
}

int getSubtreeWidth(int treeHeight,
                    int level,
                    int nodeLength,
                    int spaceLength)
{
    int levelsBelow = treeHeight - level - 1;
    int nodesCount = getNodesCount(levelsBelow);
    int spacesCount = nodesCount - 1;
    return nodeLength * nodesCount + spaceLength * spacesCount;
}

void printAsciiTree(Node *root)
{
    if (!root)
        return;

    int treeHeight = getHeight(root);
    int treeNodes = getNodesCount(treeHeight) - 1;

    queue<Node *> temp;
    queue<Node *> nodes;
    temp.push(root);

    for (int i = 0; i < treeNodes; i++)
    {
        Node *current = temp.front();
        temp.pop();
        nodes.push(current);

        if (current == nullptr)
        {
            temp.push(nullptr);
            temp.push(nullptr);
        }
        else
        {
            temp.push(current->left);
            temp.push(current->right);
        }
    }

    vector<vector<string>> values(treeHeight);
    int minNodeLen = 0;

    for (int level = 0; level < treeHeight; level++)
    {
        int nodesCount = getNodesCount(level);
        values[level].resize(nodesCount);

        for (int node = 0; node < nodesCount; node++)
        {
            string value = nodes.front() == nullptr ? "" : nodeToString(nodes.front());
            values[level][node] = value;
            nodes.pop();

            int length = static_cast<int>(value.length());
            if (minNodeLen < length)
                minNodeLen = length;
        }
    }

    int nodeLength = minNodeLen > 1 ? minNodeLen : 1;
    if (nodeLength % 2 == 0)
        nodeLength++;

    int nodeType = nodeLength % 2;
    int nodeShiftFactor = nodeLength / 2;
    string emptyNode(nodeLength, ' ');

    int minSpaceLen = nodeType ? 3 : 4;
    int spaceLength = minSpaceLen - 1;
    if (spaceLength < 1)
        spaceLength = 1;
    int spaceShiftFactor = spaceLength / 2;

    int lastLevel = treeHeight - 1;

    for (int level = 0; level < treeHeight; level++)
    {
        int nodesCount = getNodesCount(level);
        int lastNode = nodesCount - 1;
        int subtreeWidth = getSubtreeWidth(treeHeight, level, nodeLength, spaceLength);
        int nodeIndentation = subtreeWidth / 2 - nodeShiftFactor;
        int nodesSpacing = subtreeWidth - 2 * (nodeShiftFactor - spaceShiftFactor);
        int branchHeight = (subtreeWidth + 1) / 4;

        cout << string(nodeIndentation, ' ');

        for (int node = 0; node < nodesCount; node++)
        {
            string nodeValue = values[level][node].empty() ? emptyNode : values[level][node];
            cout << setw(nodeLength) << setfill(' ') << nodeValue;
            cout << string(nodesSpacing * (node != lastNode), ' ');
        }

        cout << endl;

        for (int i = 0; i < branchHeight && level != lastLevel; i++)
        {
            int branchIndentation = subtreeWidth / 2 - 1 - i;
            cout << string(branchIndentation, ' ');

            for (int node = 0; node < nodesCount; node++)
            {
                bool hasLeftChild = !values[level + 1][2 * node].empty();
                bool hasRightChild = !values[level + 1][2 * node + 1].empty();
                int branchWidth = nodeType + 2 * i;
                int branchesSpacing = nodesSpacing + 2 * (nodeShiftFactor - 1 - i);

                cout << (hasLeftChild ? '/' : ' ');
                cout << string(branchWidth, ' ');
                cout << (hasRightChild ? '\\' : ' ');
                cout << string(branchesSpacing * (node != lastNode), ' ');
            }
            cout << endl;
        }
    }
}

void buildHuffmanTree(vector<char> &chars,
                      vector<int> &freq,
                      int n)
{
    priority_queue<Node *,
                   vector<Node *>,
                   compare>
        pq;
    for (int i = 0; i < n; i++)
        pq.push(
            new Node(chars[i],
                     freq[i]));

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        pq.push(
            new Node('\0',
                     sum,
                     left,
                     right));
    }

    Node *root = pq.top();
    unordered_map<char, string> huffmanCode;
    generateCodes(root,
                  "",
                  huffmanCode);
    cout << endl
         << "Huffman Codes :" << endl;
    for (auto pair : huffmanCode)
        cout << pair.first
             << " : "
             << pair.second
             << endl;

    cout << endl
         << "Huffman Tree :" << endl;

    printAsciiTree(root);
}

int main()
{
    int n;
    cout << "Enter number of characters: ";
    cin >> n;
    vector<char> chars(n);
    vector<int> freq(n);

    cout << endl
         << "Enter character and frequency:" << endl;
    for (int i = 0; i < n; i++)
        cin >> chars[i] >> freq[i];
    cout << endl
         << "---Huffman Coding---" << endl;
    buildHuffmanTree(chars, freq, n);

    return 0;
}