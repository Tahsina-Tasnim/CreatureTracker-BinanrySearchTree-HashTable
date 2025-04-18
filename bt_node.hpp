#ifndef SENG1120_BT_NODE_HPP
#define SENG1120_BT_NODE_HPP

#include "bt_node.h"

//default constructor initialized with left and rifht set to null
template <typename T>
BTNode<T>::BTNode() : 
    left(nullptr), 
    right(nullptr) {}

//constructor intializes data with the supplied value and left and right are set to null
template <typename T>
BTNode<T>::BTNode(const T& new_data) :
    data(new_data), 
    left(nullptr), 
    right(nullptr) {}

//empty destructor
template <typename T>
BTNode<T>::~BTNode() {
    
}

//data has been set to the supplied value
template <typename T>
void BTNode<T>::set_data(const T& new_data) {
    data = new_data;
}

//left child has been set to the supplied data
template <typename T>
void BTNode<T>::set_left(BTNode<T>* new_left) {
    left = new_left;
}

//right child has been set to the supplied data
template <typename T>
void BTNode<T>::set_right(BTNode<T>* new_right) {
    right = new_right;
}

//returns a reference to the data
template <typename T>
T& BTNode<T>::get_data() {
    return data;
}

//returns the pointer to the left child
template <typename T>
BTNode<T>* BTNode<T>::get_left() const {
    return left;
}

//returns the pointer to the right child
template <typename T>
BTNode<T>* BTNode<T>::get_right() const {
    return right;
}

//outputs the data 
template <typename T>
std::ostream& operator<<(std::ostream& out, const BTNode<T>& node) {
    out << node.get_data();
    return out;
}

#endif 
