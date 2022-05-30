#include <iostream>
#include <fstream>
#include <string>

#include "HashTable.hpp"
#include "HashTableException.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  if(argc<5) {
    cout << "Insufficient number of arguments!\n";
    cout << "Usage: ./t10 <table_size> <input_txt_file1> <input_txt_file2> <input_txt_file3>\n" << endl;
    return -1;
  }
    
  try {
    int table_size = atoi(argv[1]);
  
    ifstream in_stream (argv[2]);
    if (!in_stream.is_open()) {
      cout << "Unable to open file " << argv[2];
      return -1;    
    }
    
    HashTable table(table_size);
    
    while ( !in_stream.eof() ) {
      string word;
      in_stream >> word;
      table.add(word);
    }
    in_stream.close();
    
    cout << " ###### HASH TABLE ######" << endl;
    cout << table.print() << endl;    
    
    in_stream.open(argv[3]);
    if (!in_stream.is_open()) {
      cout << "Unable to open file " << argv[3];
      return -1;    
    }
    
    cout << " ###### Removing words ######" << endl;
    while ( !in_stream.eof() ) {
      string word;
      in_stream >> word;
      table.remove(word);
    }
    in_stream.close();
    
    cout << " ###### HASH TABLE ######" << endl;
    cout << table.print() << endl;    
    
    in_stream.open(argv[4]);
    if (!in_stream.is_open()) {
      cout << "Unable to open file " << argv[4];
      return -1;    
    }
    
    cout << " ###### Adding words ######" << endl;
    while ( !in_stream.eof() ) {
      string word;
      in_stream >> word;
      table.add(word);
    }
    in_stream.close();
    
    cout << " ###### HASH TABLE ######" << endl;
    cout << table.print() << endl;
  
  } catch(std::bad_alloc& ex) {
    cout << "std::bad_alloc occured!\n";
  } catch(HashTableException& ex) {
    cout << "HashTableException occured!\n";
  } catch(...) {
    cout << "An exception of unknown type occured!" << endl;
  }
}
