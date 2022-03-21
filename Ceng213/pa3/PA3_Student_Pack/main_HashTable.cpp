#include "HashTable.h"
#include <iostream>
using namespace std;

int main()
{
    KeyedHashTable ht;
    ht.Insert("Val", std::vector<int>());
    ht.Insert("X", std::vector<int>());
    ht.Insert("L", std::vector<int>());

    ht.Print();
}