// Hunter Harbison
// CSIII
// 1/25/2022

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

#ifndef WORDLIST_HPP_
#define WORDLIST_HPP_
using std::string; using std::cout; using std::endl;

class WordOccurrence {
public:
	WordOccurrence(const string& word = "", int num = 0);
	bool matchWord(const string&); // returns true if word matches stored
	void increment(); // increments number of occurrences
	string getWord() const;
	int getNum() const;

private:
	string word_;
	int num_;
};

class WordList {
public:
	// add copy constructor, destructor, overloaded assignment
	WordList(const WordList&);
	WordList(); 
	~WordList();

	WordList& operator=(const WordList&); // overload assignment


	// implement comparison as friend
	friend bool equal(const WordList&, const WordList&);

	void addWord(const string&);
	void print();
	void splitString(const string&);
private:
	WordOccurrence* wordArray_; // a dynamically allocated array of WordOccurrences
								// may or may not be sorted
	int size_;
};

#endif