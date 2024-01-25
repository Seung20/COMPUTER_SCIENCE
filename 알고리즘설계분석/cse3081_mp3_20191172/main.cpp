#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <queue>
using namespace std;

typedef struct Node
{
    char character;
    int frequency;
    struct Node *left;
    struct Node *right;
} HuffmanNode;

struct NodeComparator
{
    bool operator()(HuffmanNode *a, HuffmanNode *b)
    {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* buildHuffmanTree(priority_queue<HuffmanNode *, vector<HuffmanNode *>, NodeComparator>& pq) {
    while (pq.size() != 1) {
        HuffmanNode *node1 = pq.top();
        pq.pop();
        HuffmanNode *node2 = pq.top();
        pq.pop();

        HuffmanNode * temp;

        if (node1->frequency > node2->frequency) {
            temp = node1;
            node1 = node2;
            node2 = temp;
        }
        HuffmanNode *node3 = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        node3->character = '0';
        node3->left = node1;
        node3->right = node2;
        node3->frequency = node1->frequency + node2->frequency;
        pq.push(node3);
    }
    return pq.top();
}



int main(int argc, char **argv)
{
    char *command = argv[1];
    char *inputFile = argv[2];
    FILE *input = fopen(inputFile, "r");
    if (input == NULL)
    {
        cout << "File error!\n";
        return 0;
    }
    const int outputFileNameMax = 100;
    char outputFile[outputFileNameMax] = "";
    int flag = 0;
    if (strcmp(command, "-c") == 0){
        flag = 1;
        strcat(outputFile, inputFile);
        strcat(outputFile, ".zz");    
    }
    else if(strcmp(command, "-d") == 0){
        flag = 2;
        strcat(outputFile, inputFile);
        strcat(outputFile, ".yy");
    }


    //compress
    if (flag == 1)
    {
        map<char, int> frequencyMap;
        map<char, int>::iterator iter;

        while (true)
        {
            char temp = fgetc(input);
            if (temp != EOF)
            {
                auto result = frequencyMap.emplace(temp, 1);
                if (!result.second)
                {
                    result.first->second++;
                }
            }
            else
                break;

        }
        fclose(input);

        priority_queue<HuffmanNode *, vector<HuffmanNode *>, NodeComparator> priorityQueue;
        for (iter = frequencyMap.begin(); iter != frequencyMap.end(); iter++)
        {
            HuffmanNode *newNode = (HuffmanNode *)malloc(sizeof(HuffmanNode));
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->character = iter->first;
            newNode->frequency = iter->second;
            priorityQueue.push(newNode);
        }

        HuffmanNode *tree = buildHuffmanTree(priorityQueue);
        
        string huffmanCode = "";
        map<char, string> codeMap;
        map<char, string>::iterator iter2;

        pair<HuffmanNode *, string> nodeArray[1024];
        int top = -1;

        nodeArray[++top] = {tree, ""};

        while (top >= 0)
        {
            HuffmanNode *current = nodeArray[top].first;
            string s = nodeArray[top].second;
            top--;

            if (current->left != NULL)
                nodeArray[++top] = {current->left, s + "0"};
            if (current->right != NULL)
                nodeArray[++top] = {current->right, s + "1"};
            if (current->left == NULL && current->right == NULL)
                codeMap[current->character] = s;
        }

        if (codeMap.size() == 1)
            codeMap[tree->character] = "0";

        input = fopen(inputFile, "r");
        int temp;
        while ((temp = fgetc(input)) != EOF)
        {
            huffmanCode += codeMap[temp];
        }

        FILE *result = fopen(outputFile, "wb");

        fprintf(result, "%ld %ld\n", huffmanCode.size(), codeMap.size());

        for (iter2 = codeMap.begin(); iter2 != codeMap.end(); iter2++)
        {
            fprintf(result, "%d %ld\n", iter2->first, iter2->second.length());
        }

        iter2 = codeMap.begin();
        while(iter2 != codeMap.end())
        {
            string s = iter2->second;
            for (int i = 0; i < s.length(); i++)
            {
                fprintf(result, "%c", s[i]);
            }
            iter2++;
        }
        unsigned char buffer = 0;
        int count = 0;
        for (int i = 0; i < huffmanCode.size(); i++)
        {
            buffer = buffer << 1;
            buffer = buffer | (huffmanCode[i] - '0');
            count++;

            if (count == 8)
            {
                fprintf(result, "%c", buffer);
                buffer = 0;
                count = 0;
            }
        }
        if (count > 0)
        {
            buffer = buffer << (8 - count);
            fprintf(result, "%c", buffer);
        }
        fclose(result);
        fclose(input);
    }

    else if (flag == 2)
    {
        int codeSize, codeCount;
        fscanf(input, "%d %d\n", &codeSize, &codeCount);

        vector<pair<pair<char, int>, string>> codeVector(codeCount);
        int sum = 0;
        for (int i = 0; i < codeCount; i++)
        {
            fscanf(input, "%hhd %d\n", &codeVector[i].first.first, &codeVector[i].first.second);

            sum += codeVector[i].first.second;
        }

        string encodedData = "";
        int j = 0;
        while (j < sum)
        {
            char temp = fgetc(input);
            encodedData += temp;
            j++;
        }

        int k = 0;
        for (int i = 0; i < codeCount; i++)
        {
            int num = codeVector[i].first.second;
            string temp = encodedData.substr(k, num);
            k += num;
            codeVector[i].second = temp;
        }

        string huffmanCode = "";
        int bufferSize = codeSize / 8;
        if (codeSize % 8 != 0)
            bufferSize++;

        for (int i = 0; i < bufferSize; i++)
        {
            char c = fgetc(input);
            unsigned char temp = (unsigned char)c;

            for (int j = 7; j >= 0; j--)
            {
                huffmanCode += ((temp >> j) & 1) ? '1' : '0';
            }
        }

        FILE *result = fopen(outputFile, "w");
        string part = "";
        int huffmanCodeIndex = 0;

        while (huffmanCodeIndex < codeSize)
        {
            part += huffmanCode[huffmanCodeIndex];

            for (int j = 0; j < codeCount; j++)
            {
                if (part == codeVector[j].second)
                {
                    fprintf(result, "%c", codeVector[j].first.first);
                    part = "";
                }
            }

            huffmanCodeIndex++;
        }

        fclose(result);
        fclose(input);
    }
    else
    {
        cout << "Error!\n";
        fclose(input);
        return 0;
    }
    return 0;
}
