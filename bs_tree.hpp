#ifndef SENG1120_BSTREE_HPP
#define SENG1120_BSTREE_HPP

#include "bs_tree.h"

//constructor initializes root to null and sets count to 0
template <typename T>
BSTree<T>::BSTree() : 
    root(nullptr), 
    count(0) {}

//deallocates memory 
template <typename T>
BSTree<T>::~BSTree() {
    clear(root);
}

//data is inserted in the correct location and count increases by 1
template <typename T>
void BSTree<T>::insert(const T& data) {
    root = insert(data, root);
    ++count;
}

//item with the specidied key has been removed
template <typename T>
void BSTree<T>::remove(const std::string& key) {
    root = remove(key, root);
}

//checks if the item with the specified key exists starting from the root
template <typename T>
bool BSTree<T>::contains(const std::string& key) const {
    return contains(key, root);
}

//removes all nodes from the tree and memory is deallocated and root is set to null and count is set to 0
template <typename T>
void BSTree<T>::clear() {
    clear(root);
    root = nullptr;
    count = 0;
}

//finds the node with the specified key if it exists otherwise a nullptr is returned
template <typename T>
T* BSTree<T>::find(const std::string& key) const {
    BTNode<T>* result = find(key, root);
    return (result ? &(result->get_data()) : nullptr);
}

//returns teh data with minimum value and if tree is empty then excpetion is thrown
template <typename T>
T& BSTree<T>::find_min() const {
    if (empty()) {
        throw empty_collection_exception("The tree is empty.");
    }
    return find_min(root)->get_data();
}

//returns the data with maximum value and if tree is empty then exception is thrown
template <typename T>
T& BSTree<T>::find_max() const {
    if (empty()) {
        throw empty_collection_exception("The tree is empty.");
    }
    return find_max(root)->get_data();
}

//checks if root is nullptr and returns true if the tree is empty
template <typename T>
bool BSTree<T>::empty() const {
    return root == nullptr;
}

//returns the number of nodes in tree
template <typename T>
int BSTree<T>::size() const {
    return count;
}

//prints the tree inorder traversal
template <typename T>
void BSTree<T>::print_inorder(std::ostream& out) const {
    print_inorder(out, root);
}

//prints the tree in preorder traversal
template <typename T>
void BSTree<T>::print_preorder(std::ostream& out) const {
    print_preorder(out, root);
}

//prints the tree in postorder traversal
template <typename T>
void BSTree<T>::print_postorder(std::ostream& out) const {
    print_postorder(out, root);
}

//all nodes from the sub-tree are removed, memory is deallocated and pointers are set to nullptr
template <typename T>
void BSTree<T>::clear(BTNode<T>* node) {
    if (node != nullptr) { //checks if the node is not null
        clear(node->get_left()); //clears the left sub-tree
        clear(node->get_right()); //clears the right sub-tree
        delete node; //deletes the node
    }
}

//data is inserted in correct location, count increases by 1
template <typename T>
BTNode<T>* BSTree<T>::insert(const T& data, BTNode<T>* node) {
    if (node == nullptr) { //checks if current node is nullptr
        return new BTNode<T>(data); //creates new node with supplied data 
    } else if (data < node->get_data()) { // checks if data is less than the current node data
        node->set_left(insert(data, node->get_left())); //recursively data is inserted in the left sub-tree
    } else if (data > node->get_data()) { //checks if data is greater than the current node data
        node->set_right(insert(data, node->get_right())); //recursively data is inserted in the right sub-tree
    }
    return node; //returns the current node
}

//removes the item with the specified key from the sub-tree if it exists, pointer to the node is returned
template <typename T>
BTNode<T>* BSTree<T>::remove(const std::string& key, BTNode<T>* node) {
    if (node == nullptr) { //checks if current node is nullptr
        return node; //returns the node
    }

    if (key < node->get_data().get_key()) { //checks if the key is les than the current node key
        node->set_left(remove(key, node->get_left())); //recursively remove the key in the left sub-tree
    } else if (key > node->get_data().get_key()) { //checks if the key is greater than the current node key
        node->set_right(remove(key, node->get_right())); //recursively remove the key in the right sub-tree
    } else {
        if (node->get_left() == nullptr) { //checks if the left child is a nullptr
            BTNode<T>* right_node = node->get_right(); //sets right child
            delete node; //delete current node
            --count; //count decreases by 1
            return right_node; //returns the right child
        } else if (node->get_right() == nullptr) { //checks if the right cild is a nullptr
            BTNode<T>* left_node = node->get_left(); //sets the left child
            delete node; //deletes current node
            --count; //decreases the count by 1
            return left_node; //returns the left child
        } else { //if the node has two children
            BTNode<T>* min_node = find_min(node->get_right()); // finds the minimum node in the right sub-tree
            node->set_data(min_node->get_data()); //sets the current node data to the minimum node data
            node->set_right(remove(min_node->get_data().get_key(), node->get_right())); //recursively  removes the minimum node
        }
    }
    return node; //returns current node
}

//checks if the item with the specified key exists in the sub-tree
template <typename T>
bool BSTree<T>::contains(const std::string& key, BTNode<T>* node) const { 
    if (node == nullptr) { //checks if current node is nullptr
        return false; // key not in tree
    } else if (key < node->get_data().get_key()) { //checks if the key is less than the current node key
        return contains(key, node->get_left()); // recursively checks the left sub-tree
    } else if (key > node->get_data().get_key()) { //checks if key is greater than current node key
        return contains(key, node->get_right()); // recursively checks the right sub-tree
    } else { // if key is equal to current node key
        return true; //the key is in tree
    }
}

// finds the node with item with the specified key, in the sub-tree rooted at the supplied node, if it exists
template <typename T>
BTNode<T>* BSTree<T>::find(const std::string& key, BTNode<T>* node) const {
    if (node == nullptr) { //checks if current node is nullptr
        return nullptr; //key is not in tree
    } else if (key < node->get_data().get_key()) { //checks if the key is less than the current node key
        return find(key, node->get_left()); //recursively finds in the left sub-tree
    } else if (key > node->get_data().get_key()) { //checks if the key is greater than the current node key
        return find(key, node->get_right()); // recursively finds in the right sub-tree
    } else { //if the key is equal to current node key
        return node; //returns the current node
    }
}

//returns pointer to the node with item with minimum data valuein the sub-tree at the supplied node
template <typename T>
BTNode<T>* BSTree<T>::find_min(BTNode<T>* node) const {
    if (node == nullptr || node->get_left() == nullptr) { //checks if the node is nullptr or has no left child
        return node; //returns the node
    } else {
        return find_min(node->get_left()); //recursively find the minimumin the left sub-tree
    }
}

//returns pointer to the node with item with minimum data valuein the sub-tree at the supplied node
template <typename T>
BTNode<T>* BSTree<T>::find_max(BTNode<T>* node) const {
    if (node == nullptr || node->get_right() == nullptr) { //checks if the node is a nullptr or has no right child
        return node; // returns the node
    } else {
        return find_max(node->get_right()); //recursively finds the maximum in the right sub-tree
    }
}

//appends the value of each node in the sub-tree using an inorder traversal
template <typename T>
void BSTree<T>::print_inorder(std::ostream& out, BTNode<T>* node) const {
    if (node != nullptr) { //checks if the node is not nullptr
        print_inorder(out, node->get_left()); // recursively prints the left sub-tree
        out << node->get_data() << " "; //outs current node data
        print_inorder(out, node->get_right()); //recursively prints the right sub-tree
    }
}

//appends the value of each node in the sub-tree using a preorder traversal 
template <typename T>
void BSTree<T>::print_preorder(std::ostream& out, BTNode<T>* node) const {
    if (node != nullptr) { //checks if the node is not nullptr
        out << node->get_data() << " "; //outs the current node data
        print_preorder(out, node->get_left()); // recursively prints the left sub-tree
        print_preorder(out, node->get_right()); //recursively printd the right sub-tree
    }
}

//appends the value of each node in the sub-tree using a postorder traversal
template <typename T>
void BSTree<T>::print_postorder(std::ostream& out, BTNode<T>* node) const {
    if (node != nullptr) { // checks if the current node is not nullptr
        print_postorder(out, node->get_left()); //recursively prints the left sub-tree
        print_postorder(out, node->get_right()); //recursively prints the right sub-tree
        out << node->get_data() << " "; //outs current node data
    }
}

//appends the value of each node in the sub-tree rooted at the supplied node, by default the tree should be printed inorder traversal
template <typename T>
std::ostream& operator<<(std::ostream& out, const BSTree<T>& tree) {
    tree.print_inorder(out); //prints the tree by inirder traversal
    return out; //returns the out stream
}

#endif 
