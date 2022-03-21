#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    int i, hash = 0;

    for(i = 0; i < key.size(); i++) hash += key[i] * PRIME_LIST[i];

    hash = hash % tableSize;

	return hash;
}

void KeyedHashTable::ReHash()
{
    int i, index, oldSize = tableSize;

    tableSize = FindNearestLargerPrime(tableSize * 2);
    
    HashData empty_data;
    HashData *new_table = new HashData[tableSize];

    for(i = 0; i < tableSize; i++) new_table[i] = empty_data;

    for(i = 0; i < oldSize; i++)
    {
    	if(table[i].key != "")
    	{
    		index = Hash(table[i].key);
    		new_table[index] = table[i];
    	}
    }

    delete[] table;
    table = new_table;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    int i = 0;

    while(PRIME_LIST[i] <= requestedCapacity) i++;

    return PRIME_LIST[i];
}

KeyedHashTable::KeyedHashTable()
{
	HashData empty_data;

    table = new HashData[2];
    table[0] = table[1] = empty_data;
    tableSize = 2;
    occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    HashData empty_data;
    int size = FindNearestLargerPrime(requestedCapacity), i;

    table = new HashData[size];
    for(i = 0; i < size; i++) table[i] = empty_data;

    tableSize = size;
    occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    HashData empty_data;
    int i;

    tableSize = other.tableSize;
    table = new HashData[tableSize];
    for(i = 0; i < tableSize; i++) table[i] = empty_data;
    occupiedElementCount = other.occupiedElementCount;

    for(i = 0; i < tableSize; i++) if(other.table[i].key != "" || other.table[i].key != "_DELETED_") table[i] = other.table[i];
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    HashData empty_data;
    int i;

    delete[] table;
    tableSize = other.tableSize;
    table = new HashData[tableSize];
    for(i = 0; i < tableSize; i++) table[i] = empty_data;
    occupiedElementCount = other.occupiedElementCount;

    for(i = 0; i < tableSize; i++) if(other.table[i].key != "") table[i] = other.table[i];

    return *this;
}

KeyedHashTable::~KeyedHashTable()
{
    delete[] table;
    tableSize = 0;
    occupiedElementCount = 0; 
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    int index = Hash(key), j = 0;
    HashData empty_data, new_data;
    new_data.key = key;
    new_data.intArray = intArray;

    while(table[index + (j * j)].key != "")
    {
    	if(table[index + (j * j)].key == key) return false;
    	j++;
    }

    table[index + (j * j)] = new_data;
    occupiedElementCount++;

    if(occupiedElementCount * EXPAND_THRESHOLD >= tableSize) ReHash();

    return true;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    int i, index;
    bool found = false;

    for(i = 0; i < tableSize; i++)
    {
    	if(table[i].key == key)
    	{
    		found = true;
    		index = i;
    		break;
    	}
    }

    if(!found) return false;

    table[index].key = "_DELETED_";
    table[index].intArray.clear();
    occupiedElementCount--;

    return true;
}

void KeyedHashTable::ClearTable()
{
	int i;

	for(i = 0; i < tableSize; i++)
	{
		if(table[i].key != "")
		{
			table[i].key = "";
			table[i].intArray.clear();
		}
	}

	occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    int i;

    for(i = 0; i < tableSize; i++)
    {
    	if(table[i].key == key)
    	{
    		valueOut = table[i].intArray;
    		return true;
    	}
    }

    return false;
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}