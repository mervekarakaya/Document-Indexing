#pragma once
#include<iostream>
#include<string>
#include"FileNameNode.h"

using namespace std;
class WordTypeBinaryTreeNode {
public:
	string word;
	int wordFreq;
	FileNameNode* fileListHead;
	WordTypeBinaryTreeNode* left;
	WordTypeBinaryTreeNode* right;

};
