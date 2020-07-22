/**
* Author: Osman Buğra Aydın
* ID: 21704100
* Section: 3
* Assignment: 4
*/

#include "hashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable( const int tableSize, const CollisionStrategy option ){
 table = new int[tableSize];
 statusOftable = new StatusOfCell[tableSize];
 strategy = option;
 this->tableSize = tableSize;
 curAmountElements = 0;

 for (int i = 0; i < tableSize; i++) {
   statusOftable[i] = EMPTY;
 }
}

HashTable::~HashTable(){
  delete [] table;
  table = NULL;
}

bool HashTable::insert( const int item ){
  int numProbes;
  int location = addressCalculator( item, INSERT, numProbes);

  if ( location == -1) {
    return false;
  }

  statusOftable[location] = OCCUPIED;
  curAmountElements++;
  table[location] = item;

  return true;
}

bool HashTable::remove( const int item ){
  int numProbes;
  int location = addressCalculator( item, FIND, numProbes);

  if ( location == -1) {
    return false;
  }

  statusOftable[location] = DELETED;
  curAmountElements--;

  return true;
}

bool HashTable::search( const int item, int& numProbes ){
  int location = addressCalculator( item, FIND, numProbes);

  if ( location == -1 ) {
    return false;
  }

  return true;
}
void HashTable::display(){
  for (int i = 0; i < tableSize; i++) {
    std::cout << i << ": ";
    if ( statusOftable[i] != OCCUPIED )
      std::cout << "" << std::endl;
    else
      std::cout << table[i] << std::endl;
  }
}
void HashTable::analyze( int& numSucProbes, int& numUnsucProbes ){
  int sum = 0;
  int prob;
  int probUnsec;
  int sumForUnsuc = 0;
  numSucProbes = 0;
  numUnsucProbes = 0;

  for (int i = 0; i < tableSize; i++) {
    if ( statusOftable[i] == OCCUPIED ) {
      addressCalculator( table[i], FIND, prob);
      sum += prob;
    }
    if ( strategy != DOUBLE) {
      addressCalculator( i, FIND, probUnsec);
      sumForUnsuc += probUnsec;
    }
  }

  numSucProbes = sum / curAmountElements;

  if ( strategy == DOUBLE)
    numUnsucProbes = -1;
  else
    numUnsucProbes = sumForUnsuc / tableSize;
}


int HashTable::addressCalculator( const int item, const AddressCalculation option, int &numProbes){ //add

  if ( this->isFull() && option == INSERT ) {
    return -1;
  }

  if ( this->isEmpty() && option == FIND) {
    return -1;
  }

  int index;
  bool found = false;
  int location;
  int counter = 0;

  if ( strategy == LINEAR ) {
    while ( !found ) {
      location = (counter + ( calculateModulo( item, tableSize) )) % tableSize;
      if ( statusOftable[location] != OCCUPIED && option == INSERT ) {
        found = true;
      }else if( table[location] == item && option == FIND && statusOftable[location] == OCCUPIED) {
        found = true;
      }else if ( statusOftable[location] != OCCUPIED && option == FIND ) {
        numProbes = ++counter;
        return -1;
      }else if ( counter >= tableSize ) {
        numProbes = ++counter;
        return -1;
      }
      counter++;
    }
    index = location;
  }else if ( strategy == QUADRATIC) {
    while ( !found ) {
      location = ((counter * counter) + ( calculateModulo( item, tableSize) )) % tableSize;
      if ( statusOftable[location] != OCCUPIED && option == INSERT) {
        found = true;
      }else if( table[location] == item && option == FIND && statusOftable[location] == OCCUPIED) {
        found = true;
      }else if ( statusOftable[location] != OCCUPIED && option == FIND ) {
        numProbes = ++counter;
        return -1;
      }else if ( counter >= tableSize / 2) {
        numProbes = ++counter;
        return -1;
      }
      counter++;
    }
    index = location;
  }else if ( strategy == DOUBLE) {
    while ( !found ) {
      location = ((counter * secondHash(item) ) + ( calculateModulo( item, tableSize) )) % tableSize;
      if ( statusOftable[location] != OCCUPIED && option == INSERT) {
        found = true;
      }else if( table[location] == item && option == FIND && statusOftable[location] == OCCUPIED) {
        found = true;
      }else if ( statusOftable[location] != OCCUPIED && option == FIND ) {
        numProbes = ++counter;
        return -1;
      }else if ( counter >= tableSize ) {
        numProbes = ++counter;
        return -1;
      }
      counter++;
    }
    index = location;
  }

  numProbes = counter;

  return index;
}

int HashTable::secondHash( int item){
  int result = 0;

  while ( item != 0) {
    result = result * 10 + ( item % 10 );
    item = item / 10;
  }

  return result;
}

bool HashTable::isFull(){
  return curAmountElements == tableSize;
}

bool HashTable::isEmpty(){
  return curAmountElements == 0;
}
int HashTable::calculateModulo( const int number, const int modulo){
  return ( ( number % modulo ) + modulo ) % modulo;
}
