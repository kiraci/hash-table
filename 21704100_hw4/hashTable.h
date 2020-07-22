/**
* Author: Osman Buğra Aydın
* ID: 21704100
* Section: 3
* Assignment: 4
*/

#ifndef hashTable_h
#define hashTable_h

enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
enum AddressCalculation { INSERT, FIND };
enum StatusOfCell { EMPTY, DELETED, OCCUPIED };

class HashTable{
public:
  HashTable( const int tableSize, const CollisionStrategy option );
  ~HashTable();
  bool insert( const int item );
  bool remove( const int item );
  bool search( const int item, int& numProbes );
  void display();
  void analyze( int& numSucProbes, int& numUnsucProbes );
  int addressCalculator( const int item, const AddressCalculation option, int &numProbes);
  int secondHash( int item);
  bool isFull();
  bool isEmpty();
  int calculateModulo( const int number, const int modulo);
private:
  int *table;
  StatusOfCell *statusOftable;
  int tableSize;
  CollisionStrategy strategy;
  int curAmountElements;
};

#endif /* hashTable_h */
