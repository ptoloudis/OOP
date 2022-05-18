#include <iostream>
#include<iterator>
using namespace std;

#ifndef __H_TABLE_EXCEPTION_H__
#define __H_TABLE_EXCEPTION_H__

class HashTable::Iterator {
    private:
        string *curr;
        const HashTable *ht
    
    public:    
        Iterator(const HashTable *t);
        Iterator(const HashTable *t, bool end);
        Iterator(const Iterator &it);
        Iterator& operator=(const Iterator &it);
        Iterator operator++();
        Iterator operator++(int a);
        bool operator==(const Iterator &it) const ;
        bool operator!=(const Iterator &it) const;
        const string& operator*();
        const string* operator->();
};

#endif
