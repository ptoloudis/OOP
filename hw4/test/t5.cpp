#include <iostream>
#include <fstream>
#include <string>

#include "HashTable.hpp"
#include "HashTableException.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  if(argc<3) {
    cout << "Insufficient number of arguments!\n";
    cout << "Usage: ./t6 <table_size> <input_txt_file>\n" << endl;
    return -1;
  }
    
  try {
    int table_size = atoi(argv[1]);
  
    ifstream in_stream (argv[2]);
    if (!in_stream.is_open()) {
      cout << "Unable to open file " << argv[2];
      return -1;    
    }
    
    HashTable table1(table_size), table2(12);
    
    while ( !in_stream.eof() ) {
      string word;
      in_stream >> word;
      if(table1.add(word)) 
        cout << "'" << word << "' added!" << endl;
      else
        cout << "'" << word << "' failed!" << endl;
    }
    in_stream.close();
    
    cout << " ###### HASH TABLE 1 ######" << endl;
    cout << table1.print() << endl;
    
    table2.add("coffee");
    table2.add("sugar");
    table2.add("orangejuice");
    table2.add("tea");
    table2.add("lemonade");
    
    cout << " ###### HASH TABLE 2 ######" << endl;
    cout << table2.print() << endl;
    
    table2 = table1;
    
    cout << " ###### HASH TABLE 2 after assignment ######" << endl;
    cout << table2.print() << endl;
    
  
  } catch(std::bad_alloc& ex) {
    cout << "std::bad_alloc occured!\n";
  } catch(HashTableException& ex) {
    cout << "HashTableException occured!\n";
  }
}
