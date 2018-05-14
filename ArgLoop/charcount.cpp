/*
 * Name: Brian Orozco
 * Objective: Count chars in File
 * Updated: 9/12/17
 */

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
  
   ifstream infile; //establish file variable
   int c, newlines; //charcount variable and variable for counting line breaks
   string lines;    //establish line variable to count from file later on
   
   
   
   for(int i = 1; i <= argc; i++){ //iterates through cmd line arguments
      
      infile.open(argv[i]);
      c = 0;
      newlines = 0;
      
      
      while(infile.is_open() == false){                      //checks current arg and all following args for validity
         
         cerr << argv[i] << " " << "FILE NOT FOUND" << endl; //error check for opening file
         i++;
         infile.open(argv[i]);                               //trys to open the next file
      }
      
      while( getline(infile, lines)){  //reading the line of file and assigning array of chars to "lines"
         
         c += lines.length();          //counting the chars on each line, then adding to integer c
         newlines++;                   //accounting for newline chars
      }
      
      c += newlines - 1;                   //adding the missing newline chars from the files
      cout << argv[i] << " " << c << endl; //printing the name of a file, a space, and the total chars, including line breaks
      infile.close();
   }
}
   
