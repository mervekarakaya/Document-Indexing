#pragma once
#include<string>
#include<iostream>
#include"WordTypeNode.h"
//201514039 Merve KARAKAYA
using namespace std;
class IndexLinkedList {
private:
	WordTypeNode* head;
public:
	IndexLinkedList() :head(NULL) {}

	void addWord(const string& word, const string& fileName) {


		if (checkWord(word)) {// if the word read from the file is already in the list
			WordTypeNode* walk = head;
			while (walk != NULL) {
				if (walk->word == word) {
					FileNameNode* t = new FileNameNode(fileName);
					walk->wordFreq += 1;
					FileNameNode* prev = NULL;
					FileNameNode* w = walk->fileListHead;
					while (w != NULL) {//fileNames are added to the end of the list
						if (w->fileName == fileName)//if the same word is mentioned more than once in the same file,
							//it is sufficient to add the file name once
							return;
						prev = w;
						w = w->next;
					}
					prev->next = t;
					return;
				}
				walk = walk->next;

			}
		}
		else if (!checkWord(word)) {// if the word read from the file is not in the list
			if (head == NULL) {// if the list is empty at first
				head = new WordTypeNode();
				head->wordFreq = 1;
				head->word = word;
				head->fileListHead = new FileNameNode(fileName);
			}
			else {// the newly added word is added to the end of the list
				WordTypeNode* t = new WordTypeNode();
				t->wordFreq = 1;
				t->word = word;
				t->fileListHead = new FileNameNode(fileName);
				WordTypeNode* prev = NULL;
				WordTypeNode* w = head;
				while (w != NULL) {
					prev = w;
					w = w->next;
				}
				prev->next = t;

			}
		}
	}
	bool checkWord(const string& word) {// check if word is already in the list
		WordTypeNode* walk = head;
		bool flag = false;
		while (walk != NULL) {
			if (walk->word == word) {
				flag = true;
				break;
			}
			walk = walk->next;
		}
		return flag;
	}
	void printListOfFiles(const string& singleWordQuery)const {
		WordTypeNode* walk = head;
		while (walk != NULL) {
			if (walk->word == singleWordQuery)
				break;
			walk = walk->next;
		}
		if (walk == NULL) {
			cout << "This word is not in the list!" << endl;
			return;
		}
		FileNameNode* w = walk->fileListHead;
		cout << "The word " << singleWordQuery << " is in the following files: ";
		while (w != NULL) {
			cout << w->fileName << " - ";
			w = w->next;
		}
		cout << endl;
	}
	void printMostFrequentWords(int topWhat) {
		WordTypeNode* walk;
		WordTypeNode* t = NULL;
		IndexLinkedList print_list;
		string max_word;
		int max_count = 0;
		for (int i = 0; i < topWhat; i++) {
			walk = head;
			max_count = 0;
			max_word = "";
			while (walk != NULL) {
				if (walk->wordFreq > max_count && !print_list.checkWord(walk->word)) {
					max_word = walk->word;
					max_count = walk->wordFreq;
				}
				walk = walk->next;
			}
			if (print_list.head == NULL) {//print top 10  1(most found word)-2-3-4-5-6-7-8-9-10
				print_list.head = new WordTypeNode();
				print_list.head->word = max_word;
			}
			else {
				WordTypeNode* temp = new WordTypeNode();
				temp->word = max_word;
				WordTypeNode* prev = NULL;
				WordTypeNode* w = print_list.head;
				while (w != NULL) {
					prev = w;
					w = w->next;
				}
				prev->next = temp;

			}

		}
		walk = print_list.head;
		while (walk != NULL) {
			cout << walk->word << " - ";
			walk = walk->next;
		}
		cout << endl;
	}
	void printLeastFrequentWords(int topWhat) {
		WordTypeNode* walk;
		WordTypeNode* t = NULL;
		IndexLinkedList print_list;
		string min_word;
		int min_count = 0;
		int min_temp = 0;
		for (int i = 0; i < topWhat; i++) {
			walk = head;
			min_count = head->wordFreq;
			min_word = "";
			while (walk != NULL) {
				min_temp = walk->wordFreq;
				if (min_temp <= min_count && !print_list.checkWord(walk->word)) {
					min_word = walk->word;
					min_count = min_temp;
				}
				walk = walk->next;
			}
			if (print_list.head == NULL) {//print top 10 1 (least common word) -2-3-4-5-6-7-8-9-10
				print_list.head = new WordTypeNode();
				print_list.head->word = min_word;
			}
			else {
				WordTypeNode* temp = new WordTypeNode();
				temp->word = min_word;
				WordTypeNode* prev = NULL;
				WordTypeNode* w = print_list.head;
				while (w != NULL) {
					prev = w;
					w = w->next;
				}
				prev->next = temp;
			}

		}
		walk = print_list.head;
		while (walk != NULL) {
			cout << walk->word << " - ";
			walk = walk->next;
		}
		cout << endl;
	}
};


