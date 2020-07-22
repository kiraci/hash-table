/**
* Author: Osman Buğra Aydın
* ID: 21704100
* Section: 3
* Assignment: 4
*/

#include <iostream>
#include "hashTable.h"
#include <fstream>
#include <stdlib.h>     /* atoi */
#include <string>

using namespace std;

#include <iostream>

int main(int argc, char* argv[])
{

    CollisionStrategy strategy;

    cout << endl;

    string arg2(argv[2]);

    if( arg2 == "LINEAR" ){
        strategy = LINEAR;
        cout << endl << "CollisionStrategy: " << argv[2] << endl;
    }else if( arg2 == "DOUBLE" ){
        strategy = DOUBLE;
        cout << endl << "CollisionStrategy: " << argv[2] << endl;
    }else if( arg2 == "QUADRATIC" ){
        strategy = QUADRATIC;
        cout << endl << "CollisionStrategy: " << argv[2] << endl;
    }else{
        cout << "The Strategy That You Enter Is Wrong. So, LINEAR Selected." << endl;
        strategy = LINEAR;
    }

    int size = atoi (argv[3]);

    HashTable* hashTable = new HashTable( size, strategy );

    ifstream input( argv[1] );

    char operation;
	  int item;


    cout << "Table Size: " << size << endl;

    cout << endl;

	  while( input >> operation >> item ){
  		int numProbes;

      switch ( operation )
      {
         case 'I':
            cout << item;
            cout << (hashTable->insert(item) ? " inserted" : " not inserted") << endl;
            break;
         case 'R':
            cout << item;
            cout << (hashTable->remove(item) ? " removed" : " not removed") << endl;
            break;
         case 'S':
            cout << item;
            cout << (hashTable->search(item, numProbes) ? " found after " : " not found after ") ;
            cout << numProbes <<" probe(s)"<< endl;
            break;
         default:
            cout<<"Illegal Operation"<<endl;
      }
  	}

    cout << endl;

    hashTable->display();

    int suc,unSuc;

    hashTable->analyze( suc, unSuc );

    cout << endl;
    cout << "Average of Successful Searchs: " << suc << endl;
    cout << "Average of Unsuccessful Searchs: " << unSuc << endl;
    cout << endl;

    return 0;
}
