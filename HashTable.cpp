#include <iostream>
#include <string>
#include <cstring>
#include <iterator>
#include "HashTable.hpp"
#include "HashTableException.hpp"
using namespace std;

#define TOMB (string *)0xFFFF; // tombstone

unsigned long HashTable::getHashCode(const char *str){
    unsigned long hash = 97;
    int c;

    while((c = *(str++)) != '\0')
        hash = ((hash << 5) + hash) + c;

    return hash;
}

HashTable::HashTable(int capacity){
    if (capacity < 8) {
        
        throw bad_alloc();
    }
    this->size = 0;
    this->capacity = capacity;
    try
    {
        this->table = new string*[capacity];
        for (int i = 0; i < capacity; i++)
        {
            this->table[i] = NULL;
        }
        
    }
    catch(bad_alloc& ba)
    {
        throw ba;
    }   
}

HashTable::HashTable(const HashTable &ht){
    this->size = ht.size;
    this->capacity = ht.capacity;
    try
    {
        this->table = new string*[capacity];
        for (int i = 0; i < capacity; i++)
        {
            this->table[i] = NULL;
        }
    }
    catch(bad_alloc& ba)
    {
        throw ba;
    }
    for (int i = 0; i < capacity; i++) {
        if (!ht.isAvailable(i)) {
            this->table[i] = new string(*(ht.table[i]));
        }
        if (ht.isTomb(i)) {
            this->table[i] = TOMB;
        }

        
    }
}

HashTable::~HashTable(){
    if (size > 0) {
        for (int i = 0; i < capacity; i++) {
            if (!isAvailable(i)) {

                delete table[i];
            }
        }
    }
    
    delete[] table;
}

int HashTable::getSize() const {
    return size;
}

int HashTable::getCapacity() const {
    return capacity;
}

bool HashTable::isEmpty(int pos) const {
    if (pos >= capacity) {
        return false;
    }
    if (table[pos] == NULL) {
        return true;
    }
    return false;
}

bool HashTable::isTomb(int pos) const {
    if (pos >= capacity) {
        return false;
    }
    if (table[pos] == (string *)0xFFFF )
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

bool HashTable::isAvailable(int pos) const {
    if (pos >= capacity) {
        return false;
    }
    return isEmpty(pos) || isTomb(pos);
}

bool HashTable::contains(const string &s) const{
    if (size == 0) {
        return false;
    }

    char *str = new char[s.length() + 1];
    strncpy(str, s.c_str(), s.length() + 1);
    int pos = getHashCode(str) % capacity;
    delete [] str;

    for (int i = 0; i < capacity; i++)
    {
        if (!isAvailable(pos) && *table[pos] == s) {
            return true;
        }
        pos = (pos + 1) % capacity;
    }
    
    return false;
}

bool HashTable::contains(const char *s) const{
    string str(s);
    return contains(str);
}

string HashTable::print() const{
    string str;
    char buf[128];

    for (int i = 0; i < capacity; i++)
    {
        if (!isAvailable(i))
        {
            sprintf(buf, "%2d. -%s-\n", i, (*table[i]).c_str());
            str.append(buf);
        }
    }
    
    sprintf(buf, " --- CAPACITY: %d, SIZE: %d ---\n", capacity, size);
    str.append(buf);
    return str;
}

bool HashTable::add(const string &s) {
    if (contains(s)) {
        return false;
    }
    
    if (size > capacity) {
        
        HashTableException e;
        throw e;
    }

    char *str = new char[s.length() + 1];
    strncpy(str, s.c_str(), s.length() + 1);
    int pos = getHashCode(str)%capacity;
    delete [] str;

    for (int i = 0; i < capacity; i++)
    {
        if (isAvailable(pos)) {
            try
            {
                table[pos] = new string(s);
            }
            catch(bad_alloc& ba)
            {
                throw ba;
            }
            
            size++;
            return true;
        }

        pos = (pos + 1) % capacity;
    }
    
    return false;
}

bool HashTable::add(const char *s) {
    string str(s);
    return add(str);
}

bool HashTable::remove(const string &s){
    if (!contains(s)) {
        return false;
    }
    
    char *str = new char[s.length() + 1];
    strncpy(str, s.c_str(), s.length() + 1);
    int pos = getHashCode(str)%capacity;
    
    delete [] str;

    for (int i = 0; i < capacity; i++)
    {
        if (!isAvailable(pos)) {
            if (*table[pos] == s) {
                delete table[pos];
                table[pos] = TOMB;
                size--;
                return true;
            }
        }
        pos = (pos + 1) % capacity;
    }
    
    return false;
}

bool HashTable::remove(const char *s){
    string str(s);
    return remove(str);
}

HashTable& HashTable::operator = (const HashTable &ht){
    if (this != &ht) {
        for (int i = 0; i < capacity; i++) {
            if (!isAvailable(i)) {
                delete table[i];
            }
        }
        delete[] table;

        this->size = ht.size;
        this->capacity = ht.capacity;
        
        try
        {
            this->table = new string*[capacity];
        }
        catch(bad_alloc& ba)
        {
            throw ba;
        }
        
        for (int i = 0; i < capacity; i++) {
            if (!ht.isAvailable(i)) {
                try
                {                    
                    this->table[i] = new string(*(ht.table[i]));
                }
                catch(bad_alloc& ba)
                {
                    throw ba;
                }
            }
            else if (ht.isTomb(i)) {
                this->table[i] = TOMB;
            }
            else {
                this->table[i] = NULL;
            }           
            
        }
        
    }
    return *this;
}

HashTable& HashTable::operator += (const string &str){
    add(str);
    return *this;
}

HashTable& HashTable::operator += (const char *s){
    add(s);
    return *this;
}

HashTable& HashTable::operator -= (const string &str){
    remove(str);
    return *this;
}

HashTable& HashTable::operator -=( const char *s){
    remove(s);
    return *this;
}

HashTable HashTable::operator + (const string &str) const{
    HashTable ht(*this);
    ht += str;
    return ht;
}

HashTable HashTable::operator + (const char *s) const{
    HashTable ht(*this);
    ht += s;
    return ht;
}

HashTable HashTable::operator - (const string &str) const{
    HashTable ht(*this);
    ht -= str;
    return ht;
}

HashTable HashTable::operator - (const char *s) const{
    HashTable ht(*this);
    ht -= s;
    return ht;
}

std::ostream& operator<<(std::ostream &stream, HashTable &t){
    stream << t.print();
    return stream;
};

HashTable::Iterator HashTable::begin() const{
    return HashTable::Iterator(this, true);
}

HashTable::Iterator HashTable::end() const{
    return HashTable::Iterator(this, false);
}
