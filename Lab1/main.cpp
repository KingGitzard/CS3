// Hunter Harbison
// 1/24/2022

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using std::cout; using std::endl;

int main(int argc, char* argv[]){

   std::string text1, text2;
   std::ifstream file1(argv[1]);
   std::ifstream file2(argv[2]);
   int lineCount=1;

   if(argc != 3){ 
   cout << "Error! Please invoke program with 2 arguments." << endl;
   }

   else{
      //loop while both files are not finished
      while(!file1.eof() || !file2.eof()){

    
         //if either file is finished, create empty lines
         if(file1.eof()){
            text1 = "";
         }

         if(file2.eof()){
            text2 = "";
         }

         getline(file1, text1);
         getline(file2, text2);
  
         if(text1 != text2){
            cout << argv[1] << ": " << lineCount << ": " << text1 << endl;
            cout << argv[2] << ": " << lineCount << ": " << text2 << endl;

            //space count for the file names length, the line number, and four spaces to line up
            int space = (strlen(argv[1]) + (std::to_string(lineCount).length()) + 4);

            for(int i = 0; i < space; ++i){
               cout << " ";
            }

            for(int i = 0; text1[i] == text2[i]; ++i){
               cout << " ";
            }
         cout << "^" << endl;
         }
      }
  ++lineCount;
   }
return 0;
}