//Hunter Harbison
//CS III
//1/30/2022

#include "WordList.hpp"

//WordOccurrence
WordOccurrence::WordOccurrence(const string& word, int num) : word_(word), num_(num) {}

bool WordOccurrence::matchWord(const string& word) {
	if (word == word_) {
		return true;
	}
	else {
		return false;
	}
}

void WordOccurrence::increment() {
	++num_;
}

string WordOccurrence::getWord() const {
	return word_;
}

int WordOccurrence::getNum() const {
	return num_;
};

WordList::WordList(const WordList& rhs) {
	size_ = rhs.size_;
	wordArray_ = new WordOccurrence[size_];

	for (int i = 0; i < size_; ++i) {
		wordArray_[i] = rhs.wordArray_[i];
	}
}

WordList::~WordList() {            // destructor
	delete[] wordArray_;
}

WordList::WordList() {
	size_ = 0;
	wordArray_ = new WordOccurrence[size_];
}
WordList& WordList::operator=(const WordList& rhs) {  //overloaded assignment
	if (this != &rhs) {
		size_ = rhs.size_;
		delete[] wordArray_;
		wordArray_ = new WordOccurrence[size_];
		for (int i = 0; i < size_; ++i) {
		wordArray_[i] = rhs.wordArray_[i];
		}	
	}
	return *this;
}

void WordList::addWord(const string& word) {
	int arrayPos = 0;  
	bool check = false;
	for (int i = 0; i < size_; ++i) {
		if (wordArray_[i].matchWord(word)) {
			check = true;	
			break;
		}
		++arrayPos;
	}
	if (!check) {
		WordOccurrence* temp = new WordOccurrence[size_ + 1];
		for (int i = 0; i < size_; ++i) {
			temp[i] = wordArray_[i];
		}
		temp[size_] = word;
		delete[] wordArray_;
		wordArray_ = temp;
		++size_;
	}
	else {
		wordArray_[arrayPos].increment();      // increments  by one if word is already stored in array
	}

	for (int i = 0; i < size_; ++i) {
		if (wordArray_[i].getNum() == 0) {         
			wordArray_[i].increment();       // increments a single time if word is stored once 
		}
	}
}

bool equal(const WordList& rhs, const WordList& lhs) {       // checks to see if two wordlist are equal
	if (rhs.size_ != lhs.size_) {
		return false;
	}
	else {
		int check = 0;

		for (int i = 0; i < rhs.size_; ++i) {
			if (rhs.wordArray_[i].getWord() == lhs.wordArray_[i].getWord()) {
				++check;
			}
		}
	
		if (check == rhs.size_) {
			return true;
		}
	}
	return false;
}

void WordList::print() {
	for (int i = 0; i < size_; i++) {       
		for (int j = i + 1; j < size_; j++)
		{
			if (wordArray_[j].getNum() < wordArray_[i].getNum()) {
				WordOccurrence* temp = new WordOccurrence[size_];
				 temp[i] = wordArray_[i];
				wordArray_[i] = wordArray_[j];
				wordArray_[j] = temp[i];
			}
		}
	}
	for (int i = 0; i < size_; ++i) {
		cout <<wordArray_[i].getNum() <<":"<< wordArray_[i].getWord() << endl;
	}
}

void WordList::splitString(const string& line) {
	string word = "";
	for (auto x : line) {
		if (x == ' ') {
			addWord(word);    // adds word when the end positions is = ' '
			word = "";
		}
		else if (!ispunct(x)) {            // if the end positon != any punction  
			word += x;                     
		}
	}
	if(word != ""){
	addWord(word);
	}


}