#include <iostream>
#include <fstream>
#include <string>

#include "ExtHashTable.hpp"
#include "HashTableException.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  
  if(argc<2) {
    cout << "Insufficient number of arguments!\n";
    cout << "Usage: ./t14 <input_txt_file>\n" << endl;
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
        
    HashTable::Iterator it1 = table.begin(), it2=table.end();
    it1++;
    it2 = it1;
    if(it2==it1)
      cout << "it1 == it2\n";
    else
      cout << "it1 != it2\n";
    
    if(it1++==it2)
      cout << "it1++ == it2\n";
    else
      cout << "it1++ != it2\n";
    if(it1==++it2)
      cout << "it1 == ++it2\n";
    else
      cout << "it1 != ++it2\n";
  
  } catch(std::bad_alloc& ex) {
    cout << "std::bad_alloc occured!\n";
  } catch(HashTableException& ex) {
    cout << "HashTableException occured!\n";
  }
}
