simulator_Q1: driver.o hashTable.o
	g++ driver.o hashTable.o -o simulator_Q1
driver.o: driver.cpp
	g++ -c driver.cpp
hashTable.o: hashTable.cpp hashTable.h
	g++ -c hashTable.cpp hashTable.h
clean:
	rm *.o simulator_Q1
