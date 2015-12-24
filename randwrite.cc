/////////////////////////////////////////
// Random Writing
// Muhammad Najib
// randwrite.cc
// CS 111 Data Structures
// April 2 2015
//
// The program takes an input file and produces
// an output file with characters taken randomly 
//from the input file. The program takes the length
// of seed , no of character to print to output file and 
// names of both files to produce an output. A random string
// of seed length is taken from input file and used to take
// a character that occurs next to the seed in input file.
// The program keeps on printed random characters to outfile
// upto the number specified in commandline.


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "list.h"

using namespace std;


//instruction to write command_line
void usage()
{
  cout << "Usage: randwrite Seedlength NumCharsToOutput"
          " InputFileName OutputFileName " << endl;
  exit(1); // 1 means error
}

//print out error message and exit
void error(string msg)
{
  cout<<msg<<endl;
  exit(1);
}

//returns the total characters in file
size_t file_size(ifstream & infile)
{
  
  size_t count = 0;
  while(infile.good()){
    infile.get();//gets char from file
    if(infile.good()){
	  //add count for each char read
          count++;
        }
    }
 
  return count;

}

//adds each character to the mainlist
void make_mainlist(ifstream & infile, list & mainlist)
{
  
   while(infile.good()) {
     char c = infile.get();
      if(infile.good()){
          mainlist.add(c,mainlist.size());
        }	
  }

}


void make_sublist(string & seed,const list & mainlist, list & sublist,size_t seed_length)
{
    //if first char same as seed's initial char
    //store the string of seed_length in teststring
    //then compare with seed and if equal
    //add next char to sublist
  
    string teststring;
    size_t counter;

    for(size_t length = 0; length < mainlist.size()-seed_length -1 ; length++){
       //important to have blank string at each loop
       teststring = "" ;
       char c = mainlist.get(length);
  
       //teststring only equals seed after c equals seed[0]
       //add char to teststring upto seed_length
       if(c == seed[0]) {   
           teststring += c;
	   for(size_t i = 1; i < seed_length; i++) {
               counter = length + i; 
	       c = mainlist.get(counter);
               teststring += c;                          
	     }
	 }
    
      //if string equals seed, add char to sublist
      if(teststring == seed){
           char c = mainlist.get(length+seed_length);
           sublist.add(c,sublist.size());
	  }

    }

}


void create_seed(string & seed,const list & mainlist, size_t seed_length)
{
  //randomly selects a position in mainlist
  //adds char upto seed_length to seed
   size_t index;
   char data;
 
   srand(time(NULL));
   index = rand() % mainlist.size();

   //for loop to get string upto seed_length
   //increment index to get to next node in list
   for(size_t i = 0; i < seed_length; i++) { 
       data = mainlist.get(index);
       seed += data;
       index++;
     }
}


int main(int argc, char * argv[])
{
  //check for errors
  //error 1: wrong command line 
  if(argc != 5) {
    usage();    
  }
 

  //store all command-line inputs in variables
  size_t seed_length = atoi(argv[1]);
  size_t output_length = atoi(argv[2]);
  string input_file_name = argv[3];
  string output_file_name = argv[4];

  ifstream infile(input_file_name.c_str());
  ofstream outfile(output_file_name.c_str());


  //error 2: file could not be opened
  if(!infile.good()) { 
    error(input_file_name + "could not be opened!");
  }
  
  //error 3: not enough characters in input file
  //first find the no. of characters 
  size_t count = file_size(infile);
  if(count < seed_length) {
    error("not enough characters in "+ input_file_name);
  }


  //move file pointer to beginning of file to read again
  infile.clear();
  infile.seekg(0,ios::beg);

  // create a list to store all characters from file
  list mainlist;
  make_mainlist(infile, mainlist);

  //seed to find char to be printed
  string seed;
  create_seed(seed, mainlist, seed_length);


  //for loop to find next character after seed 
  //and print to outfile up to output_length
  for(size_t length = 0; length < output_length;length++){   

    //create a sublist of all char
    //following the occurences of seed
    list sublist;
    make_sublist(seed, mainlist,sublist,seed_length); 
   
    if(sublist.size()!= 0) {

        //pick random char from sublist
        //print to outfile and update seed
        
	 srand(time(NULL));
         size_t random = rand() % sublist.size();
         char   next = sublist.get(random);
  
         outfile<<next;

         seed.erase(0,1);
         seed += next;

       }

     else { 

         // select new seed
         seed = "";// due to seed += .... in function 
	 create_seed(seed, mainlist, seed_length);
	 length -=  1;

       }
  }//end of for loop(current_length)
}

