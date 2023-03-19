CC = g++
CFLAGS=-Wall -g -std=c++11 -fsanitize=address

OBJ = HashTable.o HashTableIterator.o ExtHashTable.o main.o

libHashTable: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) 

HashTable.o: HashTable.cpp
	${CC} ${CFLAGS} HashTable.cpp -c 

HashTableIterator.o: HashTableIterator.cpp
	${CC} ${CFLAGS} HashTableIterator.cpp -c 

ExtHashTable.o: ExtHashTable.cpp
	${CC} ${CFLAGS} ExtHashTable.cpp -c 

main.o: main.cpp
	${CC} ${CFLAGS} main.cpp -c

.PHONY: clean
clean:
	rm -f*.o 