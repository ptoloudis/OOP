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

HashTable::~HashTable(){
    for (int i = 0; i < capacity; i++)
    {
        if (!isAvailable(i))
        {
            delete table[i];
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
    
    if (size >= capacity) {
        HashTableException e;
        throw e.what();
    }

    char *str = new char[s.length() + 1];
    strncpy(str, s.c_str(), s.length() + 1);
    int pos = getHashCode(str)%capacity;
    delete [] str;

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
        this->~HashTable();
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

HashTable HashTable::operator + (const char *s)const{
    HashTable ht(*this);
    ht += s;
    return ht;
}

HashTable HashTable::operator - (const string &str)const{
    HashTable ht(*this);
    ht -= str;
    return ht;
}

HashTable HashTable::operator - (const char *s)const{
    HashTable ht(*this);
    ht -= s;
    return ht;
}

std::ostream& operator<<(std::ostream &stream, HashTable &t){
    stream << t.print();
    return stream;
};

// ************* Iterator **************//
// HashTable::Iterator(const HashTable *t){
//     ht = t;
//     curr = t->table.begin();
//     position = 0;
// }

// HashTable::Iterator(const HashTable *t, bool start){
//     ht = t;
//     if(start){
//         curr = t->table.begin();
//         position = 0;
//     }
//     else{
//         curr = t->table.end();
//         position = t->capasity
//     }
// }

// HashTable::Iterator(const Iterator &it){
//     this->ht = it.ht;
//     this->curr = it.curr;
// }

// int pos() const{
//     return position;
// }


// TODO: implement the rest of the methods
