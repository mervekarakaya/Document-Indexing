#pragma once
#include<string>
#include<iostream>
#include"FileNameNode.h"
//Merve KARAKAYA
using namespace std;
class WordTypeNode {
public:
	string word;
	int wordFreq;
	FileNameNode* fileListHead;
	WordTypeNode* next;
};

