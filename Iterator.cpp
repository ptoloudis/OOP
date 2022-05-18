#include <iostream>
#include <iterator>
#include "Iterator.hpp"
using namespace std;

HashTable::Iterator::Iterator(const HashTable *t){
    this->ht = t;
    this->curr = t->table.begin();
}

HashTable::Iterator::Iterator(const HashTable *t, bool end){
    this->ht = t;
    if(end){
        this->curr = t->table.end();
    }
    else{
        this->curr = t->table.begin();
    }
}

HashTable::Iterator::Iterator(const Iterator &it){
    this->ht = it.ht;
    this->curr = it.curr;
}

// ToDo: emplamet the Iterator class