#include <iostream>
#include <string>
#include <cstring>
#include <iterator>
#include "HashTable.hpp"
#include "HashTableException.hpp"
using namespace std;


// ************* Iterator **************//
HashTable::Iterator::Iterator(const HashTable *t){
    ht = t;
    curr = t->table[0];
    position = 0;
}

HashTable::Iterator::Iterator(const HashTable *t, bool start){
    ht = t;
    if(start){
        curr = t->table[0];
        position = 0;
    }
    else{
        curr = t->table[t->capacity - 1];
        position = t->capacity - 1;
    }
}

HashTable::Iterator::Iterator(const Iterator &it){
    this->ht = it.ht;
    this->curr = it.curr;
    this->position = it.position;
}

HashTable::Iterator& HashTable::Iterator::operator = (const Iterator &it){
    this->ht = it.ht;
    this->curr = it.curr;
    this->position = it.position;
    return *this;
}

HashTable::Iterator HashTable::Iterator::operator ++(){
    curr = ht->table[position + 1];
    position++;
    return *this;
}

HashTable::Iterator HashTable::Iterator::operator ++(int){
    Iterator it(*this);
    curr = ht->table[position + 1];
    position++;
    return it;
}

bool HashTable::Iterator::operator == (const Iterator &it) const{
    return (ht == it.ht && position == it.position && curr == it.curr);
}

bool HashTable::Iterator::operator != (const Iterator &it) const{
    return !HashTable::Iterator::operator == (it);
}

const string& HashTable::Iterator::operator*(){
    return *curr;
}

const string* HashTable::Iterator::operator->(){
    return curr;
}


int HashTable::Iterator::pos() const{
    return position;
}