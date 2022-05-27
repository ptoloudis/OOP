#include <string>
#include <iostream>
#include "ExtHashTable.hpp"
using namespace std;

void ExtHashTable::rehash(){
    string **new_table;

    if (size/capacity >= upper_bound_ratio)
    {
        
        int new_capacity = 2*capacity;
        try
        {
            new_table = new string*[new_capacity];
        }
        catch(bad_alloc& ba)
        {
            throw ba;
        }  
        
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
        try
        {
            new_table = new string*[new_capacity];
        }
        catch(bad_alloc& ba)
        {
            throw ba;
        }
        
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
    else
    {
        return;
    }
    
}

ExtHashTable::ExtHashTable( double upper_bound_ratio, double lower_bound_ratio, int size){
    this->size = 0;
    this->capacity = size;
    this->upper_bound_ratio = upper_bound_ratio;
    this->lower_bound_ratio = lower_bound_ratio;
    
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
}

ExtHashTable::ExtHashTable(const ExtHashTable &t){
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

bool ExtHashTable::add(const string &str){
    
    bool success  = HashTable::add(str);

    if(success){
        rehash();
    }
    return success; 
}

bool ExtHashTable::add(const char *s){
    string str(s);
    return add(str);
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
    string str(s);
    return operator+=(str);
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
        else if (t.isTomb(i) && isAvailable(i)){
            remove(t.table[i]->c_str());
        }
    
        
    }
    return *this;
}