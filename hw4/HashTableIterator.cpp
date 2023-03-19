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
            return;
        }
    }
    this->position = ht->capacity;
    this->curr = NULL;
    return;

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
                return;
            }
        }
        this->position = ht->capacity;
        this->curr = NULL;
        return;
    }
    else
    {
        this->position = ht->capacity;
        this->curr = NULL;
    }
}

HashTable::Iterator::Iterator(const Iterator &it){
    ht = it.ht;
    position = it.position;
    curr = it.curr;
}

HashTable::Iterator& HashTable::Iterator::operator=(const Iterator &it){
    ht = it.ht;
    position = it.position;
    curr = it.curr;
    return *this;
}

HashTable::Iterator HashTable::Iterator::operator++(){
    if(position == ht->capacity)
    {
        return *this;
    }
    for (int i = position+1; i < ht->capacity; i++)
    {
        if (!ht->isAvailable(i)) {
            position = i;
            curr = ht->table[i];
            return *this;
        }
    }
    position = ht->capacity;
    curr = NULL;
    return *this;
}

HashTable::Iterator HashTable::Iterator::operator++(int){
    Iterator temp(*this);

    if(position == ht->capacity)
    {
        return temp;
    }

    if (ht->size == 0)
    {
        position += 1;
        curr = NULL;
        return temp;
    }

    for (int i = position+1; i < ht->capacity; i++)
    {
        if (!ht->isAvailable(i)) {
            position = i;
            curr = ht->table[i];
            return temp;
        }
    }

    position = ht->capacity;
    curr = NULL;
    return temp;
     
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