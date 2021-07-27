#include<iostream>
#include<string>
#include"IndexBinaryTreeList.h"
#include"FileNameNode.h"
#include"WordTypeBinaryTreeNode.h"
#include <fstream>
using namespace std;
void getValidOption(int& option) {
	do {
		cin >> option;
	} while (!(option < 5 && option>0));
}
int  printDecoratedMenu(const string& indexCreationDuration) {
	cout << "\n------------------------------------------------------------------" << endl;
	cout << "                 Simple Document Restrieval System                   " << endl;
	cout << indexCreationDuration << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	cout << "1.	Enter a single keyword to list the document(s)(file names)" << endl;
	cout << "2.	Print the top 10 words that appeared most frequently" << endl;
	cout << "3.	Print the top 10 words that appeared least frequently" << endl;
	cout << "4.	Exit" << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	cout << "Option:";
	int option;
	getValidOption(option);
	return option;
}
void createIndex(IndexBinaryTreeList& index, const string directoryOfFiles) {
	string fname = "";
	string temp;
	string word;
	int j = 0;
	for (int i = 1; i <10000; i++) {
		string str = to_string(i);
		string fname = str + ".txt";
		char fileName[25];
		strcpy(fileName, fname.c_str());
		fstream f;
		f.open(fileName, ios::in);
		while (!f.eof()) {
			j = 0;
			string line;
			getline(f, line);
			while (j < line.size()) {
				if (line[j] > 32 && line[j] < 65)//check for non - letter characters
					j++;
				if (line[j] > 90 && line[j] < 97)//check for non - letter characters
					j++;
				if (line[j] == ' ' && temp != "") {
					word = temp;
					index.addWord(word, fileName);
					temp = "";
					word = "";
					j++;
				}

				if (line[j] != ' ' && line[j] > 64 && line[j] < 91)//convert capital letters to lowercase then add to word
					temp += line[j] + ' ';
				else if (line[j] != ' ' && line[j] > 96 && line[j] < 123)//for lower case adding to word
					temp += line[j];
				j++;

				if (j == line.size()) {//check at the end of the line
					word = temp;
					index.addWord(word, fileName);
					temp = "";
					word = "";
				}
			}
		}
		f.close();

	}
}
void main() {
	string dirName = "AllDocs";
	IndexBinaryTreeList index;
	string idxCreationTime;
	/*Start timer to measure duriation of index creation*/
	createIndex(index, dirName);
	/*stop the timer*/
	/*convert time into string and store in idxCreationTime*/
	int opt;
	do {
		opt = printDecoratedMenu(idxCreationTime);
		switch (opt) {
		case 1: {
			string queryWord;
			cout << "\nEnter single query word: ";
			cin >> queryWord;
			index.printListOfFiles(queryWord);
			break;
		}
		case 2: index.printMostFrequentWords(10); break;
		case 3: index.printLeastFrequentWords(10); break;
		}
	} while (opt != 4);
}
