#include <iostream>
#include <fstream>
#include <string>

#include "HashTable.hpp"
#include "HashTableException.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    
  try {
    
    HashTable  table2(12), table3(12);
    
    table2.add("coffee");
    table2.add("sugar");
    table2.add("orangejuice");
    table2.add("tea");
    table2.add("lemonade");
    table2.add("water");
    table2.add("milk");
    table2.add("salt");
    table2.add("butter");
    
    cout << " ###### HASH TABLE 2 ######" << endl;
    cout << table2.print() << endl;
    
    table3 = table2 - "sugar";

    cout << " ###### HASH TABLE 2 after assignment ######" << endl;
    cout << table3.print() << endl;
    
    cout << " ######### FINISHED #########" << endl;
  
  } catch(std::bad_alloc& ex) {
    cout << "std::bad_alloc occured!\n";
  } catch(HashTableException& ex) {
    cout << "HashTableException occured!\n";
  }
}
