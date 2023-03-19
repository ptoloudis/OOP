#include <iostream>
#include <fstream>
#include <string>

#include "HashTable.hpp"
#include "HashTableException.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  string str; 
  char buf[128];
    
  try {
    int table_size = atoi(argv[1]);
    
    HashTable table(table_size);
    
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
