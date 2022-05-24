CC = g++
CFLAGS=-Wall -g -std=c++11 -fsanitize=address

OBJ = HashTable.o HashTableIterator.o ExtHashTable.o

HashTable.o: HashTable.cpp
	${CC} ${CFLAGS} HashTable.cpp -c 

HashTableIterator.o: HashTableIterator.cpp
	${CC} ${CFLAGS} HashTableIterator.cpp -c 

ExtHashTable.o: ExtHashTable.cpp
	${CC} ${CFLAGS} ExtHashTable.cpp -c 

libHashTable: HashTable.o HashTableIterator.o ExtHashTable.o 
	ar cr  HashTable.o HashTableIterator.o ExtHashTable.o

.PHONY: clean
clean:
	rm -f*.o 