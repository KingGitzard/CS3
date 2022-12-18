//Hunter Harbison
//CSIII
//1/27/2022

#include "WordList.hpp"

int main(int argc, char* argv[]) {
	if (argc >= 1) {
		for (int i = 0; i < argc; ++i) {
			cout << argv[i] << " ";           //outputs arguments in command line
		}
		cout << endl << endl;
		cout << "Words used are:" << endl;
		cout << "==============="<< endl;

		std::ifstream textfile(argv[1]);    //opening the text file;
		string line;
		WordList wl;
		while (!textfile.eof()) {
			getline(textfile, line);
		
			wl.splitString(line);

		}	
		wl.print();
	}
	else {
		cout << "no files passed on command line"<< endl;
	}
}