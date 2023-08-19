/*
 *  HashNode.h
 *  Gabby Fischberg, Nathan Moreno
 *  4/30/2023
 *
 *  CS 15 Proj4
 *
 *  Purpose: Implementation and interface for HashNode class. Includes relevant
 *          functions such as getters and setters for nodes. Note that the 
 *          implementation and interface were not able to be serarated because
 *          templates were used, and they only work per file 
 *
 */

#ifndef _HASH_NODE_H
#define _HASH_NODE_H

#include <vector>
#include <string>

template <typename keyType, typename valueType>
class HashNode {
    public: 
    HashNode();
    HashNode(const HashNode<keyType, valueType> &other);
    HashNode(const keyType &newKey, const valueType &newValue);
    keyType getKey();
    valueType *getValue();
    void setValue(const valueType &newValue); 
    void setKey(const keyType &newKey);
    HashNode *getNext(); 
    void setNext(HashNode *newNext); 
    bool isFull();
    void setFull(bool new_value);

    private: 
    HashNode<keyType, valueType> &operator=(const 
                HashNode<keyType, valueType> &other);
    bool full;
    keyType key; 
    valueType value; 
    HashNode *next; 
};

using namespace std;
/*
 * name:      default constructor 
 * purpose:   initializes empty node, key and value use their built in 
                default constructors for given keyType and valueTyp
 * arguments: none
 * returns:   none
 * effects:   none
 */
template <typename keyType, typename valueType>
HashNode<keyType, valueType>::HashNode() : key(), value() {
    this->full = false;
    this->next = nullptr; 
}

/*
 * name:      second constructor 
 * purpose:   initializes node with given key and value
 * arguments: references to key and value
 * returns:   none
 * effects:   none
 */
template <typename keyType, typename valueType>
HashNode<keyType, valueType>::HashNode(const keyType &newKey, 
                                const valueType &newValue){
    this->key = newKey; 
    this->value = newValue; 
    this->next = nullptr; 
    this->full = true; 
}

/*
 * name:      copy constructor 
 * purpose:   initializes a HashNode that is a deep copy of another instance
 * arguments: reference to another HashNode
 * returns:   none
 * effects:   none
 */
template <typename keyType, typename valueType>
HashNode<keyType, valueType>::HashNode(const 
                HashNode<keyType, valueType> &other){
    key = other.key; 
    value = other.value; 
    next = nullptr; 
    full = other.full; 
}

/*
 * name:      overloaded operato
 * purpose:   initializes empty node, key and value use their built in 
                default constructors for given keyType and valueTyp
 * arguments: none
 * returns:   none
 * effects:   none
 */
template <typename keyType, typename valueType>
HashNode<keyType, valueType> &HashNode<keyType, valueType>::operator=(const 
        HashNode<keyType, valueType> &other) {
    if (this == &other) {
        return *this;
    }
    
    this->key = other.key; 
    this->value = other.value; 
    this->next = nullptr; 
    this->full = other.full; 

    return *this; 
}


template <typename keyType, typename valueType>
keyType HashNode<keyType, valueType>::getKey(){
    return key; 
}

template <typename keyType, typename valueType>
void HashNode<keyType, valueType>::setKey(const keyType &newKey) {
    key = newKey;
}

template <typename keyType, typename valueType>
void HashNode<keyType, valueType>::setFull(bool new_value) {
    full = new_value;
}

template <typename keyType, typename valueType>
valueType *HashNode<keyType, valueType>::getValue(){
    valueType *myp = &value; 
    return myp; 
}

template <typename keyType, typename valueType>
void HashNode<keyType, valueType>::setValue(const valueType &newValue){
    this->value = newValue; 
    //using getvalue for vectors 
}

template <typename keyType, typename valueType>
HashNode<keyType, valueType> *HashNode<keyType, valueType>::getNext(){
    return next; 
}

template <typename keyType, typename valueType>
void HashNode<keyType, valueType>::setNext(HashNode *newNext){
    this->next = newNext; 
}

template <typename keyType, typename valueType>
bool HashNode<keyType, valueType>::isFull(){
    return full; 
}

#endif