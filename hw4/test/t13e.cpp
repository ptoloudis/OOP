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
  
  if(argc<4) {
    cout << "Insufficient number of arguments!\n";
    cout << "Usage: ./t13 <input_txt_file1> <input_txt_file2> <input_txt_file3>\n" << endl;
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
    
    in_stream.open(argv[2]);
    if (!in_stream.is_open()) {
      cout << "Unable to open file " << argv[2];
      return -1;    
    }
    
    while ( !in_stream.eof() ) {
      string word;
      in_stream >> word;
      table.remove(word);
    }
    in_stream.close();
    
    in_stream.open(argv[3]);
    if (!in_stream.is_open()) {
      cout << "Unable to open file " << argv[3];
      return -1;    
    }
    
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
  } catch(...) {
    cout << "An exception of unknown type occured!" << endl;
  }
}
