#pragma once
#include<iostream>
#include<string>
#include"WordTypeBinaryTreeNode.h"
#include"FileNameNode.h"
using namespace std;
int max_wordFreq = 0;
string words_max[10];//array that stores the most common word names in documents
int min_wordFreq;
string words_min[10];//array that stores the least common word names in documents
class IndexBinaryTreeList {
private:
	WordTypeBinaryTreeNode* root;

private:
	bool addNewFileName(WordTypeBinaryTreeNode*& r, const string& word, const string& fileName) {
		if (r == NULL)
			return false;
		if (r->word == word) {
			FileNameNode* t = new FileNameNode(fileName);
			r->wordFreq += 1;
			FileNameNode* prev = NULL;
			FileNameNode* w = r->fileListHead;
			while (w != NULL) {//fileNames are added to the end of the list
				if (w->fileName == fileName)//if the same word is mentioned more than once in the same file,
					//it is sufficient to add the file name once
					return true;
				prev = w;
				w = w->next;
			}
			prev->next = t;
			return true;
		}
		if (word > r->word)
			return addNewFileName(r->right, word, fileName);
		if (word < r->word)
			return addNewFileName(r->left, word, fileName);
	}
	bool addNewWord(WordTypeBinaryTreeNode*& root, const string& word, const string& fileName) {
		if (root == NULL) {
			root = new WordTypeBinaryTreeNode();
			root->wordFreq = 1;
			root->word = word;
			root->fileListHead = new FileNameNode(fileName);
			return true;
		}
		if (word < root->word && root->left == NULL) {
			root->left = new WordTypeBinaryTreeNode();
			root->left->wordFreq = 1;
			root->left->word = word;
			root->left->fileListHead = new FileNameNode(fileName);
			return true;
		}
		if (word > root->word && root->right == NULL) {
			root->right = new WordTypeBinaryTreeNode();
			root->right->wordFreq = 1;
			root->right->word = word;
			root->right->fileListHead = new FileNameNode(fileName);
			return true;
		}
		if (word < root->word)
			return addNewWord(root->left, word, fileName);
		if (word > root->word)
			return addNewWord(root->right, word, fileName);
	}
	bool checkWord(const string& word, WordTypeBinaryTreeNode*& r) {// check if word is already in the tree
		if (r == NULL)
			return false;
		if (r->word == word)
			return true;
		if (word > r->word)
			return(checkWord(word, r->right));
		if (word < r->word)
			return(checkWord(word, r->left));
	}
	bool printFiles(WordTypeBinaryTreeNode* r, const string& word)const {
		if (r == NULL)
			return false;
		if (r->word == word) {
			FileNameNode* w = r->fileListHead;
			cout << "The word " << word << " is in the following files: ";
			while (w != NULL) {
				cout << w->fileName << " - ";
				w = w->next;
			}
			cout << endl;
			return true;
		}
		if (word > r->word)
			return printFiles(r->right, word);
		if (word < r->word)
			return printFiles(r->left, word);
	}
	void findMaxWord(WordTypeBinaryTreeNode*& r, string& MaxWord) {//Finds the word with maximum wordFreq in binary search tree
		if (r == NULL)
			return;
		if (r->wordFreq > max_wordFreq && checkMaxWord(r->word)) {
			MaxWord = r->word;
			max_wordFreq = r->wordFreq;
		}
		findMaxWord(r->left, MaxWord);
		findMaxWord(r->right, MaxWord);
	}
	void findMinWord(WordTypeBinaryTreeNode*& r, string& MinWord) {//Finds the word with minimum wordFreq in binary search tree
		if (r == NULL)
			return;
		if (r->wordFreq < min_wordFreq && checkMinWord(r->word)) {
			MinWord = r->word;
			min_wordFreq = r->wordFreq;
		}
		findMinWord(r->left, MinWord);
		findMinWord(r->right, MinWord);
	}
	bool checkMaxWord(string wordName) {//check if the word with maximum wordFreq number is found and added to the words_max array before
		for (int i = 0; i < 10; i++) {
			if (wordName == words_max[i])
				return false;
		}
		return true;
	}
	bool checkMinWord(string wordName) {//check if the word with minimum wordFreq number is found and added to the words_min array before
		for (int i = 0; i < 10; i++) {
			if (wordName == words_min[i])
				return false;
		}
		return true;
	}
public:
	IndexBinaryTreeList() :root(NULL) {}

	void addWord(const string& word, const string& fileName) {
		if (checkWord(word, this->root)) {// if the word read from the file is already in the tree
			bool check = addNewFileName(root, word, fileName);//find word in the tree and insert new fileName for this word
			if (check == false)
				cout << "Adding new file name failed!" << endl;
		}
		else {// the newly added word is added to binary search tree
			bool flag = addNewWord(this->root, word, fileName);
			if (flag == false)
				cout << "Adding new words failed!" << endl;
		}
	}
	void printListOfFiles(const string& singleWordQuery)const {
		bool check = printFiles(root, singleWordQuery);//find the word and print the fileNames containing that word
		if (check == false)
			cout << singleWordQuery << " is not included in the documents!" << endl;
	}
	void printMostFrequentWords(int topWhat) {
		string MaxWord;
		int i;
		for (i = 0; i < topWhat; i++) {
			words_max[i] = "";
		}
		for (i = 0; i < topWhat; i++) {
			findMaxWord(root, MaxWord);
			words_max[i] = MaxWord;
			max_wordFreq = 0;
		}
		cout << "These words are listed starting from the most frequently mentioned word among the documents:\n" << endl;
		for (i = 0; i < topWhat; i++) {
			cout << words_max[i] << " - ";
		}
		cout << endl;
	}
	void printLeastFrequentWords(int topWhat) {
		string MinWord;
		int i;
		for (i = 0; i < topWhat; i++) {
			words_min[i] = "";
		}
		min_wordFreq = root->wordFreq;
		for (i = 0; i < topWhat; i++) {
			findMinWord(root, MinWord);
			words_min[i] = MinWord;
			min_wordFreq = root->wordFreq;
		}
		cout << "These words are listed starting from the least frequently mentioned word among the documents:\n" << endl;
		for (i = 0; i < topWhat; i++) {
			cout << words_min[i] << " - ";
		}
		cout << endl;

	}
};
