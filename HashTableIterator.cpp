#include <iostream>
#include <string>
#include <cstring>
#include <iterator>
#include "HashTable.hpp"
using namespace std;

HashTable::Iterator::Iterator(const HashTable *t){
    this->ht = t;
    for (int i = 0; i < ht->capacity; i++)
    {
        if(!ht->isAvailable(i))
        {
            this->position = i;
            this->curr = ht->table[i];
            break;
        }
    }
}

HashTable::Iterator::Iterator(const HashTable *t, bool start){
    this->ht = t;
    if (start)
    {
        for (int i = 0; i < ht->capacity; i++)
        {
            if(!ht->isAvailable(i))
            {
                this->position = i;
                this->curr = ht->table[i];
                break;
            }
        }
    }
    else
    {
        for (int i = ht->capacity - 1; i >= 0; i--)
        {
            if(!ht->isAvailable(i))
            {
                this->position = i;
                this->curr = ht->table[i];
                break;
            }
        }
    }
}

HashTable::Iterator::Iterator(const Iterator &it){
    this->ht = it.ht;
    this->position = it.position;
    this->curr = it.curr;
}

HashTable::Iterator& HashTable::Iterator::operator=(const Iterator &it){
    this->ht = it.ht;
    this->position = it.position;
    this->curr = it.curr;
    return *this;
}

HashTable::Iterator HashTable::Iterator::operator++(){
    if(position == ht->capacity)
    {
        return *this;
    }
    for (int i = position; i < ht->capacity; i++)
    {
        if (!ht->isAvailable(i)) {
            position = i;
            curr = ht->table[i];
            return *this;
        }
    }
    
    position = ht->capacity;
    curr = ht->table[position];
    return *this;
}

HashTable::Iterator HashTable::Iterator::operator++(int){
    Iterator it(*this);
    ++(*this);
    return it;
}

bool HashTable::Iterator::operator==(const Iterator &it) const{
    return (this->position == it.position && this->ht == it.ht && this->curr == it.curr);
}

bool HashTable::Iterator::operator!=(const Iterator &it) const{
    return (!(*this == it));
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