#include <iostream>
#include <string>
#include <cstring>
#include "HashTable.hpp"
#include "HashTableException.hpp"
using namespace std;

#define TOMB (string *)0xFFFF; // tombstone

static int HashTable::getHashCode(const char *str){
    string s(str);
    int hash = 0;

    for (size_t i = 0; i < s.length(); i++)
    {
        hash += s[i];
    }

    return hash;
}

HashTable::HashTable(int capacity=8){
    if (capacity < 8) {
        throw bad_alloc();
    }
    this->size = 0;
    this->capacity = capacity;
    this->table = new (nothrow) string*[capacity];
    if (table == NULL) {
        throw bad_alloc();
    }
}

HashTable::HashTable(const HashTable &ht){
    this->size = ht.size;
    this->capacity = ht.capacity;
    this->table = new (nothrow) string*[this->capacity];
    if (table == NULL) {
        throw bad_alloc();
    }
    for (int i = 0; i < capacity; i++) {
        if (ht.table[i] != NULL) {
            table[i] = new string;
            if (table[i] == NULL) {
                throw bad_alloc();
            }
            *table[i] = *ht.table[i];
        }
    }
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
    return table[pos] == NULL;
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
    char *str = new char[s.length() + 1];
    strcpy(str, s.c_str());
    int pos = getHashCode(str)%capacity;
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

virtual bool HashTable::add(const string &s) {
    if (contains(s)) {
        return false;
    }
    
    if (size >= capacity) {
        HashTableException e;
        throw e.what();
    }

    char *str = new char[s.length() + 1];
    strcpy(str, s.c_str());
    int pos = getHashCode(str)%capacity;
    pos = pos % capacity;
    int x;
    x = pos;

    for (int i = 0; i < capacity; i++)
    {
        
        if (isAvailable(pos)) {
            table[pos] = new string;
            if (table[pos] == NULL) {
                throw bad_alloc();
            }
            *table[pos] = s;
            size++;
            return true;
        }

        pos = (pos + 1) % capacity;
    }
    
    return false;
}

virtual bool HashTable::add(const char *s) {
    string str(s);
    return add(str);
}

virtual bool HashTable::remove(const string &s){
    if (!contains(s)) {
        return false;
    }
    
    char *str = new char[s.length() + 1];
    strcpy(str, s.c_str());
    int pos = getHashCode(str)%capacity;
    int x;
    x = pos;
    
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

virtual bool HashTable::remove(const char *s){
    string str(s);
    return remove(str);
}

// TODO: implement the rest of the methods