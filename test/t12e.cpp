#include <iostream>
#include <fstream>
#include <string>

#include "ExtHashTable.hpp"
#include "HashTableException.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  string str; 
  char buf[128];
  
  if(argc<2) {
    cout << "Insufficient number of arguments!\n";
    cout << "Usage: ./t12 <input_txt_file>\n" << endl;
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
      table.add(word);
    }
    in_stream.close();
    
    cout << " ###### HASH TABLE ######" << endl;
    for(HashTable::Iterator it = table.begin(); it!=table.end(); ) {
      sprintf(buf, "%2d. -%s-\n", it.pos(), (*(it++)).c_str());
      str.append(buf);
    }
    sprintf(buf, " --- CAPACITY: %d, SIZE: %d ---\n", table.getCapacity(), table.getSize());
    str.append(buf);
    cout << str;
    
    str.clear();
    cout << " ###### HASH TABLE ######" << endl;
    for(HashTable::Iterator it = table.begin(); it!=table.end(); ++it) {
      sprintf(buf, "%2d. -%s-\n", it.pos(), (*it).c_str());
      str.append(buf);
    }
    sprintf(buf, " --- CAPACITY: %d, SIZE: %d ---\n", table.getCapacity(), table.getSize());
    str.append(buf);
    cout << str;
  
  } catch(std::bad_alloc& ex) {
    cout << "std::bad_alloc occured!\n";
  } catch(HashTableException& ex) {
    cout << "HashTableException occured!\n";
  }
}
