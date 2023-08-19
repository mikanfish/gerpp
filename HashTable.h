/*
 *  HashTable.h
 *  Gabby Fischberg, Nathan Moreno
 *  4/30/2023
 *
 *  CS 15 Proj4
 *
 *  Purpose: Implementation and interface for HashTable class. Includes relevant
 *          functions such as insert, contains, and rehashing. Note that the 
 *          implementation and interface were not able to be serarated because
 *          templates were used, and they only work per file 
 *
 */

#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include "HashNode.h"
#include <functional>
#include <iostream>

template <typename keyType, typename valueType>
class HashTable {
public: 
    HashTable();
    ~HashTable();
    void insert(keyType key, valueType value);
    bool contains(keyType key);
    valueType *getNodeValue(keyType key); 
    int getIndex(keyType key); 
    

private: 
    void calcLoad();
    void rehash();
    void desHelper(HashNode<keyType, valueType> *currnode);
    void rehashHelper(HashNode<keyType, valueType> *node);
    void printTable();
    int size;
    int capacity; 
    const float lf_max = 0.73; 
    std::vector<HashNode<keyType, valueType>> *table; 
};

/*
 * name:      constructor 
 * purpose:   initializes hash table with capacity 10, size 0
 * arguments: none
 * returns:   none
 * effects:   creates a new vector on heap that acts as table
 */
template <typename keyType, typename valueType>
HashTable<keyType, valueType>::HashTable(){
    capacity = 10;   
    size = 0;
    table = new std::vector<HashNode<keyType, valueType>>
            (capacity, HashNode<keyType, valueType>());
}

/*
 * name:      destructor 
 * purpose:   deletes nodes and hashtable
 * arguments: none
 * returns:   none
 * effects:   deletes allocated memory
 */
template <typename keyType, typename valueType>
HashTable<keyType, valueType>::~HashTable(){
    for (int i = 0; i < capacity; i++){
        HashNode<keyType, valueType> *currnode = &table->at(i);
        if (currnode->getNext() != nullptr) {
            desHelper(currnode->getNext());
        }
    }
    delete table;
}
/*
 * name:      desHelper
 * purpose:   helps recursively delete nodes
 * arguments: Pointer to HashNode that acts as root in linked list for chaining
 * returns:   none
 * effects:   deletes nodes allocated on heap
 */
template <typename keyType, typename valueType>
void HashTable<keyType, valueType>::desHelper
                                    (HashNode<keyType, valueType> *currnode){
    // if not a real node recursion done
    if (currnode == nullptr) {
        return;
    }
    //pass the next node
    desHelper(currnode->getNext());
    delete currnode;
}

/*
 * name:      calcLoad
 * purpose:   calculates load factor and rehashes if above max load
 * arguments: none
 * returns:   none
 * effects:   rehashes table if above max load factor (0.73)
 */
template <typename keyType, typename valueType>
void HashTable<keyType, valueType>::calcLoad(){
    float cap = capacity; 
    float load_factor = size/cap;
    if (load_factor > lf_max){
        rehash();
    }
}

/*
 * name:      rehash
 * purpose:   rehashes table
 * arguments: none
 * returns:   none
 * effects:   doubles capacity of table and puts nodes in new buckets
 */
template <typename keyType, typename valueType>
void HashTable<keyType, valueType>::rehash(){
    capacity = capacity * 2; 
    std::vector<HashNode<keyType, valueType>> *old_table = table; 
    table = new std::vector<HashNode<keyType, valueType>> 
                    (capacity, HashNode<keyType, valueType>());

    //traverse entire table
    size = 0;
    HashNode<keyType, valueType> *currnode; 
    for (int i = 0; i < capacity / 2; i++){
        currnode = &old_table->at(i);
        if (currnode->isFull() == true) { //if not empty node
            rehashHelper(currnode);
            desHelper(currnode->getNext());
        }
    }
    delete old_table;  
}

/*
 * name:      rehashHelper
 * purpose:   helps recursively insert nodes into new table
 * arguments: Pointer to hash node that needs to be copied to new table
 * returns:   none
 * effects:   inserts nodes into new hash table
 */
template <typename keyType, typename valueType>
void HashTable<keyType, valueType>::rehashHelper(HashNode<keyType, 
                                                valueType> *node){
    if (node == nullptr) {
        return;
    }
    keyType k = node->getKey(); 
    valueType v = *node->getValue();
    insert(k, v);
    
    rehashHelper(node->getNext());
}

/*
 * name:      insert
 * purpose:   inserts node into hash table, handles collisions by chaining
 * arguments: keyType key, valueType value
 * returns:   none
 * effects:   inserts node into table
 */
template <typename keyType, typename valueType>
void HashTable<keyType, valueType>::insert(keyType key, valueType value){
    int index = getIndex(key);
    HashNode<keyType, valueType> *node_ptr = &table->at(index); 
    HashNode<keyType, valueType> node(key, value);
    //if node is uninitialized
    if (not node_ptr->isFull()) {
        node_ptr->setValue(value);
        node_ptr->setKey(key);
        node_ptr->setFull(true);
        size++; 
    } else if (node_ptr->getKey() == key) {
        node_ptr->setValue(value);
    } else {
        bool replaced = false;
        while (node_ptr->getNext() != nullptr) {
            if (node_ptr->getKey() == key) {
                node_ptr->setValue(value);
                replaced = true;
                break;
            } else {
                node_ptr = node_ptr->getNext();
            }
        }
        if (replaced == false) {
            HashNode<keyType, valueType> *new_node = 
                new HashNode<keyType, valueType>(key, value);
            node_ptr->setNext(new_node);
            size++; 
        }
    } calcLoad();
}

/*
 * name:      contains
 * purpose:   determins whether a key is contained in table
 * arguments: keyType key
 * returns:   true if key is contained, false otherwise
 * effects:   none
 */
template <typename keyType, typename valueType>
bool HashTable<keyType, valueType>::contains(keyType key){
    if (getNodeValue(key) == nullptr){
        return false; 
    }
    return true;
}

/*
 * name:      getIndex
 * purpose:   gets index of a key in the hash table
 * arguments: keyType key
 * returns:   int index
 * effects:   none
 */
template <typename keyType, typename valueType>
int HashTable<keyType, valueType>::getIndex(keyType key){
    int index = std::hash<keyType>{}(key) % capacity;
    return index; 
}

/*
 * name:      getNodeValue
 * purpose:   gets node value of given key
 * arguments: keyType key
 * returns:   valueType value
 * effects:   none
 */
template <typename keyType, typename valueType>
valueType* HashTable<keyType, valueType>::getNodeValue(keyType key){
    int index = std::hash<keyType>{}(key) % capacity;
    
    keyType potentialKey = table->at(index).getKey();
    HashNode<keyType, valueType> *potentialNode = &table->at(index); 
    if (potentialKey == key){
        return table->at(index).getValue();
    } else {
        // traverse linked list of chained nodes
        while (potentialNode->getNext() != nullptr){
            potentialNode = potentialNode->getNext(); 
            potentialKey = potentialNode->getKey();

            if (potentialKey == key) {
                return potentialNode->getValue(); 
            }
        }
    }
    return nullptr;
}

/*
 * name:      printTable
 * purpose:   prints table
 * arguments: none
 * returns:   none
 * effects:   prints table
 */
template <typename keyType, typename valueType>
void HashTable<keyType, valueType>::printTable() {
    HashNode<keyType, valueType> *currnode; 
    for (int i = 0; i < capacity; i++){
        currnode = &table->at(i);
        std::cout << "Index [" << i << "] " << currnode->getKey() <<"\n";
        //traverse linked list of collided nodes
        while (currnode->next != nullptr) {
            std::cout << "|\n" << "v\n"; 
            currnode = currnode->next;
            std::cout << currnode->getKey() << endl;
        }
        std::cout << "|\n" << "v\n"; 
        std::cout << "NULL\n\n";
    }
}

#endif

