#include <iostream>
#include <fstream>
#include <string>

#include "ExtHashTable.hpp"
#include "HashTableException.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  if(argc<3) {
    cout << "Insufficient number of arguments!\n";
    cout << "Usage: ./t16 <input_txt_file>\n" << endl;
    return -1;
  }
    
  try {  
    ifstream in_stream (argv[1]);
    if (!in_stream.is_open()) {
      cout << "Unable to open file " << argv[1];
      return -1;    
    }
    
    ExtHashTable table;
    
    while ( !in_stream.eof() ) {
      string word;
      in_stream >> word;
      table += word;
      if(table.contains(word)) 
        cout << "'" << word << "' added!" << endl;
      else
        cout << "'" << word << "' failed!" << endl;
    }
    in_stream.close();
    
    cout << " ###### HASH TABLE ######" << endl;
    cout << table.print() << endl;
    
    in_stream.open(argv[2]);
    if (!in_stream.is_open()) {
      cout << "Unable to open file " << argv[2];
      return -1;    
    }
    
    while ( !in_stream.eof() ) {
      string word;
      in_stream >> word;
      table -= word;
      if(!table.contains(word))
        cout << "'" << word << "' removed!" << endl;
      else
        cout << "'" << word << "' not found!" << endl;
    }
    in_stream.close();
    
    cout << " ###### HASH TABLE ######" << endl;
    cout << table.print() << endl;
  
  } catch(std::bad_alloc& ex) {
    cout << "std::bad_alloc occured!\n";
  } catch(HashTableException& ex) {
    cout << "HashTableException occured!\n";
  }
}
