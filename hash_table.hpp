#ifndef SENG1120_HASH_TABLE_HPP
#define SENG1120_HASH_TABLE_HPP

#include "hash_table.h"

//constructor initializes a hash table with the count set to 0
template <typename T>
HashTable<T>::HashTable(int table_capacity) :
    table(table_capacity), 
    capacity(table_capacity),
    count(0) {} 

//destructor to free all associated memory
template <typename T>
HashTable<T>::~HashTable() {
    clear(); 
}

//inserts the supplied data into the hash table
template <typename T>
void HashTable<T>::insert(const T& data) {
    int index = hash_function(data.get_key()); // computes the hash index for the key
    table[index].push_back(data); // inserts data at the end of the list at the computed index
    ++count; //increase count by 1
}

//removes the item with the specified key from the hash table
template <typename T>
void HashTable<T>::remove(const std::string& key) {
    int index = hash_function(key); //computes the hash index for the key
    if (list_remove(table[index], key)) { //removes the item from the list at the computed index
        --count; //decreases count by 1
    }
}

//return a pointer to the item with the specified key
template <typename T>
T* HashTable<T>::get(const std::string& key) {
    int index = hash_function(key); //computes the hash index for the key
    return list_find(table[index], key); //return a pointer to the item if it exists
}

//determine if an item with the specified key exists
template <typename T>
bool HashTable<T>::contains(const std::string& key) {
    int index = hash_function(key); //Computes the hash index for the key
    return list_contains(table[index], key); //returns true if the item exists in the list
}

//clears all items from the hash table
template <typename T>
void HashTable<T>::clear() {
    for (auto& list : table) {
        list.clear(); //clears each list in the table
    }
    count = 0; //resets the count to 0
}

//returns true if the hash table is empty
template <typename T>
bool HashTable<T>::empty() const {
    return count == 0; //returns true if count is 0
}

//returns the number of items in the hash table
template <typename T>
int HashTable<T>::size() const {
    return count; //returns the count
}

//appends the value of each cell in the hash table
template <typename T>
void HashTable<T>::print(std::ostream& os) const {
    for (int i = 0; i < capacity; ++i) {
        os << i << ": "; //prints the index
        list_print(os, table[i]); //prints the list at the current index
        os << std::endl; //end of line
    }
}

//prints the hash table
template <typename T>
std::ostream& operator<<(std::ostream& out, const HashTable<T>& table) {
    table.print(out); //prints the hash table using the print method
    return out; //returns the output stream
}

#endif
