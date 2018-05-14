/*
 * Name: Brian Orozco
 * Objective: Give file stats
 * Updated: 9/27/17
 */

#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <cstring>
#include <map>
using namespace std;

int main(int argc, char *argv[]){
	
	ifstream infile;                   //est file variable
    string lines;                      //variable to be used for reading lines in a file
    string word;                       //variable to be used for reading words in a file
    map<string, int> longestWord;      //map to store longest word in a file
    map<string, int>::iterator it;     //iterator for map 
    int linelength = 0;                //variable for current line length
    bool cflag = false;                //initialize flags
    
    if(argc < 2){   //error check for no files passed
       cerr << "NO FILES" << endl;
       return -1;
    }
   
	for(int i = 1; i <= argc; i++){ //iterates through cmd line arguments
	    
        
       
       if(argv[i][0] == '-'){ //this checks to see if the arg contains a flag
          
          if(strstr(argv[i], "-c")){

             cflag = true;
             continue;
             
                
          }
          else{ //no valid flag will result in error statement
             cerr << argv[i] << " UNRECOGNIZED FLAG" << endl;
             continue;
          }
       }
       
	   infile.open(argv[i]);
       
       if(infile.is_open() == false){ //error check for invalid file
          cerr << argv[i] << " FILE NOT FOUND" << endl;
          continue;
       }
       
       cout << argv[i] << ":" << endl; //prints file name with colon
       
      
       int maxWord = 0; //variable for storing current longest word 
       longestWord.clear(); //clearing map for use in separate files
       
       while( infile >> word){ //using stringstream for splitting file into words with a space delimiter
          
          if(word.size() >= (unsigned) maxWord){ //keeps track of longest word and stores it in map
             maxWord = word.size();
             longestWord[word]++;
          }
          
          
          
       }
       
       infile.clear();
       infile.seekg(0, ios::beg);
       
       int longestlinelen = 0; //length of longest line variable
       int linecount = 0;
                
       while(getline(infile, lines)){ //reads through file to obtain longest line
                       
          linelength = lines.length(); //length of current line variable
          
          if (longestlinelen < linelength){
             longestlinelen = linelength;
             
          }
          
          else if(longestlinelen == linelength){
             longestlinelen = linelength;
             linecount++;
          }
          
        
       }
       
       infile.clear();
       infile.seekg(0, ios::beg);
       
       getline(infile,lines);
       
       if(lines.length() == (unsigned) longestlinelen && !longestWord.empty()){ //goes back to check if the first line of a file can also be considered to be among the longest of lines
          linecount++;
       }
    
       string biggestword = "";
       
       for( it = longestWord.begin(); it != longestWord.end(); it++ ){ //iterates through map to erase key that are smaller than the largest words in a file
           
          if(it->first.size() < (unsigned) maxWord){
             
             longestWord.erase(it);
          }
          
       }
       
       for( it = longestWord.begin(); it != longestWord.end(); it++ ){ //iterates through the completed map to display output
          
         
          if(cflag){
             
             if(next(it) == longestWord.end()){
             
                cout << it->first << '(' << it->second << ')';
                break;
             }
          
             
             cout << it->first << '(' << it->second << ')' << ", ";
          
          }
          
          else{
             
             if(next(it) == longestWord.end()){

                cout << it->first;
                break;
             }


                cout << it->first << ", ";
          }
          
       }
       
       if(!longestWord.empty()){ //accounts for an empty file
          cout << endl;
       }
       else{
          linecount++;        
       }
       
       if(cflag){
          cout << longestlinelen << '(' << linecount << ')' << endl;
       }
       else{
          cout << longestlinelen << endl;
       }
       
	   infile.close();
	}
	
}