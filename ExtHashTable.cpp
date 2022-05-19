#include <string>
#include <iostream>
#include "ExtHashTable.hpp"
using namespace std;

void ExtHashTable::rehash(){
    if (size/capacity >= upper_bound_ratio)
    {
        int new_capacity = 2*capacity;
        string **new_table = new string*[new_capacity];
        for (int i = 0; i < capacity; i++)
        {
            if (!isEmpty(i))
            {
                int new_pos = getHashCode(table[i]->c_str());
                while (new_table[new_pos] != NULL)
                {
                    new_pos = (new_pos + 1) % new_capacity;
                }
                new_table[new_pos] = table[i];
            }
        }
        delete[] table;
        table = new_table;
        capacity = new_capacity;
    }
    else if (size/capacity <= lower_bound_ratio)
    {
        int new_capacity = capacity/2;
        string **new_table = new string*[new_capacity];
        for (int i = 0; i < capacity; i++)
        {
            if (!isEmpty(i))
            {
                int new_pos = getHashCode(table[i]->c_str());
                while (new_table[new_pos] != NULL)
                {
                    new_pos = (new_pos + 1) % new_capacity;
                }
                new_table[new_pos] = table[i];
            }
        }
        delete[] table;
        table = new_table;
        capacity = new_capacity;
    }
    
}

ExtHashTable::ExtHashTable( double upper_bound_ratio, double lower_bound_ratio, int size){
    this->size = 0;
    this->capacity = size;
    this->upper_bound_ratio = upper_bound_ratio;
    this->lower_bound_ratio = lower_bound_ratio;
    this->table = new string*[capacity];
}

ExtHashTable::ExtHashTable(const ExtHashTable &t){
    this->size = t.size;
    this->capacity = t.capacity;
    this->upper_bound_ratio = t.upper_bound_ratio;
    this->lower_bound_ratio = t.lower_bound_ratio;
    this->table = new string*[capacity];
    for(int i=0; i<capacity; i++){
        if(t.table[i] != NULL){
            this->table[i] = new string(t.table[i]->c_str());
        }
        else{
            this->table[i] = NULL;
        }
    }
}

bool ExtHashTable::add(const string &str){
    if(size/capacity >= upper_bound_ratio || size/capacity <= lower_bound_ratio){
        rehash();
    }

    return HashTable::add(str);
}

bool ExtHashTable::add(const char *s){
    string str(s);
    return add(str);
}

bool ExtHashTable::remove(const string &str){
    bool result = HashTable::remove(str);
    
    if(result){ 
        if(size/capacity >= upper_bound_ratio || size/capacity <= lower_bound_ratio){
            rehash();
        }
    }

    return result;
}

bool ExtHashTable::remove(const char *s){
    string str(s);
    return remove(str);
}

// TODO: implement the following functions