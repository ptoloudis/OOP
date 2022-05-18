#include <iostream>
#include "HashTableException.hpp"
using namespace std;

#ifndef __H_TABLE_H__
#define __H_TABLE_H__

class HashTable {
  
    protected:
        int size;
        int capacity;
        string **table;
        static int getHashCode(const char *str);

        bool isEmpty(int pos) const;
        bool isTomb(int pos) const;
        bool isAvailable(int pos) const;
  
    public:  
        HashTable(int capacity=8);
        HashTable(const HashTable &ht);
        int getSize() const;
        int getCapacity() const;
        
        bool contains(const string &s) const;
        bool contains(const char *s) const;
        string print() const;

        virtual bool add(const string &s);
        virtual bool add(const char *s);
        virtual bool remove(const string &s);
        virtual bool remove(const char *s);
        
        HashTable& operator=(const HashTable &ht);
        
        HashTable& operator += (const string &str);
        HashTable& operator += (const char* s);
        HashTable& operator -= (const string &str);
        HashTable& operator -= (const char *s);
        
        HashTable operator + (const string &str) const;
        HashTable operator + (const char* s) const;
        HashTable operator - (const string &str) const;
        HashTable operator - (const char *s) const;

        HashTable operator+(const HashTable &t) const;
        HashTable &operator+=(const HashTable &t);
        
        friend std::ostream& operator<<(std::ostream &stream, HashTable &t);
};

#endif