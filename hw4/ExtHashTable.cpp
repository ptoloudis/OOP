#include <string>
#include <iostream>
#include "ExtHashTable.hpp"
using namespace std;

void ExtHashTable::rehash(){
    string **new_table;
    double ratio = (double)this->size / (double)this->capacity;

    if(size == 0){
        return;
    }

    if (ratio > upper_bound_ratio)
    {
        
        int new_capacity = 2*capacity;
        try
        {
            new_table = new string*[new_capacity];
            for (int i = 0; i < new_capacity; i++)
            {
                new_table[i] = NULL;
            }
        }
        catch(bad_alloc& ba)
        {
            throw ba;
        }  
        
        for (int i = 0; i < capacity; i++)
        {
            if (!isAvailable(i))
            {
                int new_pos = getHashCode(table[i]->c_str()) % new_capacity;
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
    else if (ratio < lower_bound_ratio)
    {
        int new_capacity = capacity/2;
        try
        {
            new_table = new string*[new_capacity];
            for (int i = 0; i < new_capacity; i++)
            {
                new_table[i] = NULL;
            }
        }
        catch(bad_alloc& ba)
        {
            throw ba;
        }
        
        for (int i = 0; i < capacity; i++)
        {
            if (!isAvailable(i))
            {
                int new_pos = getHashCode(table[i]->c_str()) % new_capacity;
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
    else
    {
        return;
    }

    cout << "--> Size: "<< size << ", New capacity: " << capacity << endl;
    
}

ExtHashTable::ExtHashTable( double upper_bound_ratio, double lower_bound_ratio, int size) : HashTable(size){
    this->upper_bound_ratio = upper_bound_ratio;
    this->lower_bound_ratio = lower_bound_ratio;
}

ExtHashTable::ExtHashTable(const ExtHashTable &t): HashTable(t){
    this->upper_bound_ratio = t.upper_bound_ratio;
    this->lower_bound_ratio = t.lower_bound_ratio;
    
}

bool ExtHashTable::add(const string &str){
    rehash();
    return HashTable::add(str);
}

bool ExtHashTable::add(const char *s){
    rehash();
    return HashTable::add(s);
}

bool ExtHashTable::remove(const string &str){
    bool result = HashTable::remove(str);
    
    if(result){ 
        rehash();
    }

    return result;
}

bool ExtHashTable::remove(const char *s){
    string str(s);
    return remove(str);
}

ExtHashTable &ExtHashTable::operator=(const ExtHashTable &t){
    if(this != &t){
        this->~ExtHashTable();
        this->size = t.size;
        this->capacity = t.capacity;
        this->upper_bound_ratio = t.upper_bound_ratio;
        this->lower_bound_ratio = t.lower_bound_ratio;
        
        string **new_table = nullptr;

        try
        {
            new_table = new string*[capacity];
            this->table = new_table;
        }
        catch(bad_alloc& ba)
        {
            throw ba;
        }
        
        for(int i=0; i<capacity; i++){
            if(t.table[i] != NULL){
                this->table[i] = new string(t.table[i]->c_str());
            }
            else{
                this->table[i] = NULL;
            }
        }
    }
    return *this;
}

ExtHashTable ExtHashTable::operator+(const string &str) const{
    ExtHashTable result(*this);
    result.add(str);
    return result;
}

ExtHashTable ExtHashTable::operator+(const char* s) const{
    string str(s);
    return operator+(str);
}

ExtHashTable ExtHashTable::operator-(const string &str) const{
    ExtHashTable result(*this);
    result.remove(str);
    return result;
}

ExtHashTable ExtHashTable::operator-(const char* s) const{
    string str(s);
    return operator-(str);
}

ExtHashTable &ExtHashTable::operator+=(const string &str){
    add(str);
    return *this;
}

ExtHashTable &ExtHashTable::operator+=(const char* s){
    add(s);
    return *this;
}

ExtHashTable &ExtHashTable::operator-=(const string &str){
    remove(str);
    return *this;
}

ExtHashTable &ExtHashTable::operator-=(const char* s){
    string str(s);
    return operator-=(str);
}

ExtHashTable ExtHashTable::operator+(const ExtHashTable &t) const{
    ExtHashTable result(*this);
    result += t;
    return result;
}

ExtHashTable &ExtHashTable::operator+=(const ExtHashTable &t){
    for(int i=0; i<t.capacity; i++){
        if(!t.isAvailable(i)){
            add(t.table[i]->c_str());
        }
    }
    return *this;
}