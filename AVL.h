//
// Created by shahar on 28/11/2022.
//
//
#ifndef WET1_AVL_H
#define WET1_AVL_H
#define UNBALANCED_PLUS 2
#define UNBALANCED_MINUS (-2)

#include <iostream>
#include "Node.h"


template <class T>
class AVL {
    Node<T>* m_root;
    Node<T>* rotations(Node<T>*node);

public:
    int (*m_compare)( Node<T>*cur_node, T& comp);
    explicit AVL(int (*compare)(Node<T>* cur_node, T& comp));
    virtual ~AVL();
    void destroy_tree(Node<T>* base);
    Node<T>* get_root() const;
    void set_root(Node<T>* new_root);
    virtual Node<T>* RR(Node<T>* unbalanced);
    virtual Node<T>* LR(Node<T>* unbalanced);
    virtual Node<T>* LL(Node<T>* unbalanced);
    virtual Node<T>* RL(Node<T>* unbalanced);
    int balance_factor(Node <T> *n) const;
    int calc_height(Node<T> *n) const ;
    int calc_rank (Node<T> *node) const;
    virtual Node<T>* insert(Node<T> *prev_node,Node<T> *current, shared_ptr<T>data);
    virtual Node<T>* remove(shared_ptr<T> removed_Node_id);
    Node<T>* find(Node<T>* cur_node, T& comp);
    virtual Node<T>* switch_AVL_values(Node<T>* cur_parent, Node<T>* son);
    virtual Node<T>* delete_node_as_leaf (Node<T>* to_delete);



    void printBT(const std::string& prefix, const Node<T>* node, bool isLeft);
    void printBT(const Node<T>* node);
    void print2DUtil(const Node<T>* root, int space);
    void print2D(const Node<T>* root);

};

//
// Created by shahar on 28/11/2022.
//

template<class T>
AVL<T>::AVL(int (*compare)(Node<T>* cur_node, T& comp))
{
    this->m_root = nullptr;
    this->m_compare = compare;
}

template<class T>
//Don't know- need to check!//
AVL<T>::~AVL()
{
    destroy_tree(m_root);
}

template<class T>
void AVL<T>::destroy_tree(Node<T>* base){
    if(base == nullptr){
        return;
    }
    destroy_tree(base->left);//
    destroy_tree(base->right);
    delete base;
}

template<class T>
//Return: Null_ptr - already in tree;
// this - if the action succeeded;
// throws exception if the allocation failed
Node<T>* AVL<T>::insert(Node<T> *prev_node,Node<T> *current, shared_ptr<T> data) {
    if(current== nullptr){
        Node<T> *New;
        New = new Node<T>();
        New->data = data;
        current = New;
        current->parent = prev_node;
        current->left = current->right = nullptr;

        if(current->parent == nullptr){
            this->m_root = current;
        }
        return current;
    }
    if(m_compare(current, *data) ==0){
        return current;
    }
    if(m_compare(current, *data) ==1){
        current->right = insert(current,current->right,data);
    }
    else{
        current->left = insert(current,current->left,data);
    }
    current->height = calc_height(current);
    current->rank = calc_rank(current);
    current = rotations(current);
    return current;


}

template<class T>
Node<T>* AVL<T>::find(Node<T>* cur_node, T& comp){
    if(cur_node == nullptr){
        return nullptr;
    }
    if(m_compare(cur_node,comp)==0) return cur_node;//found the node
    if(cur_node->left == nullptr && cur_node->right == nullptr){
        //this isn't the node, and he doesn't have right_son or left_son
        return nullptr;
    }
    if(m_compare(cur_node,comp) ==1){
        return find(cur_node->right,comp);
    }
    else{
        return find(cur_node->left,comp);
    }
}

template<class T>
int AVL<T>::balance_factor(Node <T> *n) const{
    int bf=0;
    if(n->left != nullptr) bf++;
    if(n->right != nullptr) bf--;
    bf += (calc_height(n->left) - calc_height(n->right));
    return bf;
}

template<class T>
int AVL<T>::calc_height(Node<T> *n) const {
    if(n==nullptr){
        return 0;
    }
    if (n->left ==nullptr && n->right == nullptr) return 0;
    if(n->left==nullptr) return (n->right->height + 1);
    if(n->right==nullptr) return (n->left->height + 1);
    return (max(n->right->height,n->left->height) + 1);
}

template<class T>
int AVL<T>::calc_rank(Node<T> *node) const {
    if(node==nullptr){
        return 0;
    }
    if (node->left ==nullptr && node->right == nullptr) return 1;
    if(node->left==nullptr) return (node->right->rank + 1);
    if(node->right==nullptr) return (node->left->rank + 1);
    return node->right->rank + node->left->rank + 1;
}

template<class T>
Node<T>* AVL<T>::LL(Node<T>* unbalanced) {
    Node<T>* new_source = unbalanced->left;
    unbalanced->left = new_source->right;
    if(new_source->right != nullptr)
    {
        new_source->right->parent = unbalanced;
    }
    new_source->right = unbalanced;
    //Parents:
    if(new_source->parent!=nullptr){
        new_source->parent = unbalanced->parent;
        if(unbalanced->parent!=nullptr)
        {
            if(unbalanced->parent->right == unbalanced)
            {
                unbalanced->parent->right = new_source;
            }
            else
            {
                unbalanced->parent->left = new_source;
            }
        }
    }
    unbalanced->parent = new_source;
    //Heights:
    unbalanced->height = calc_height(unbalanced);
    new_source->height = calc_height(new_source);
    new_source->left->height = calc_height(new_source->left);
    unbalanced->rank = calc_rank(unbalanced);
    new_source->rank = calc_rank(new_source);

    return new_source;
}

template<class T>
Node<T>* AVL<T>::RR(Node<T>* unbalanced) {
    Node<T>* new_source = unbalanced->right;
    unbalanced->right = new_source->left;
    if(new_source->left != nullptr)
    {
        new_source->left->parent = unbalanced;
    }
    new_source->left = unbalanced;
    //Parents :
    if(new_source->parent!=nullptr){
        new_source->parent = unbalanced->parent;
        if(unbalanced->parent!=nullptr){
            if(unbalanced->parent->right == unbalanced)
            {
                unbalanced->parent->right = new_source;
            }
            else
            {
                unbalanced->parent->left = new_source;
            }
        }
    }
    unbalanced->parent = new_source;

    //Heights:
    unbalanced->height = calc_height(unbalanced);
    new_source->height = calc_height(new_source);
    new_source->right->height = calc_height(new_source->right);
    unbalanced->rank = calc_rank(unbalanced);
    new_source->rank = calc_rank(new_source);

    return new_source;
}

template<class T>
Node<T>* AVL<T>::LR(Node<T>* unbalanced) {
    Node<T> *p;
    Node<T> *tp;
    Node<T> *tp2;
    p = unbalanced;
    tp = p->left;
    tp2 =p->left->right;

    p -> left = tp2->right;
    tp ->right = tp2->left;
    tp2 ->right = p;
    tp2->left = tp;

    //Parents:
    if(p->parent!= nullptr){
        tp2->parent = p->parent;
        if(p->parent->right == p){
            p->parent->right = tp2;
        }
        else{
            p->parent->left = tp2;
        }
    }
    else
    {
        tp2->parent = nullptr;
    }
    p->parent = tp2;
    tp->parent = tp2;
    if(p->left!= nullptr){
        p->left->parent = p;
    }
    if(tp->right != nullptr){
        tp->right->parent = tp;
    }

    //Heights:
    p->height = calc_height(p);
    tp->height = calc_height(tp);
    tp2->height = calc_height(tp2);
    p->rank = calc_rank(p);
    tp->rank = calc_rank(tp);
    tp2->rank = calc_rank(tp2);

    return tp2;

}

template<class T>
Node<T>* AVL<T>::RL(Node<T>* unbalanced) {
    Node<T> *p;
    Node<T> *tp;
    Node<T> *tp2;
    p = unbalanced;
    tp = p->right;
    tp2 =p->right->left;

    p -> right = tp2->left;
    tp ->left = tp2->right;
    tp2 ->left = p;
    tp2->right = tp;

    //Parents:
    if(p->parent!= nullptr){
        tp2->parent = p->parent;
        if(p->parent->right == p){
            p->parent->right = tp2;
        }
        else{
            p->parent->left = tp2;
        }
    }
    else
    {
        tp2->parent = nullptr;
    }
    p->parent = tp2;
    tp->parent = tp2;
    if(p->right!= nullptr){
        p->right->parent = p;
    }
    if(tp->left != nullptr){
        tp->left->parent = tp;
    }

    //Heights:
    p->height = calc_height(p);
    tp->height = calc_height(tp);
    tp2->height = calc_height(tp2);
    p->rank = calc_rank(p);
    tp->rank = calc_rank(tp);
    tp2->rank = calc_rank(tp2);

    return tp2;
}

template<class T>
Node<T>* AVL<T>::remove(shared_ptr<T> removed_Node_id)
{

    Node<T>* to_delete= find(this->m_root ,*removed_Node_id);
    if(to_delete == nullptr)
    {
        return this->m_root;
    }
    Node<T>* after_deletion_node = delete_node_as_leaf(to_delete);
    Node<T>* new_root = this->m_root;
    while (after_deletion_node != nullptr)
    {
        if(after_deletion_node->left == nullptr && after_deletion_node->right == nullptr)
        {
            after_deletion_node->height = 0;
            after_deletion_node->rank = 1;
        }
        else
        {
            after_deletion_node->height = calc_height(after_deletion_node);
            after_deletion_node->rank = calc_rank(after_deletion_node);
            if (balance_factor(after_deletion_node) == UNBALANCED_PLUS)
            {
                if(balance_factor(after_deletion_node->left) >= 0)
                {
                    after_deletion_node = LL(after_deletion_node);
                }
                else
                {
                    after_deletion_node = LR(after_deletion_node);
                }
            }
            else if (balance_factor(after_deletion_node) == UNBALANCED_MINUS)
            {
                if(balance_factor(after_deletion_node->right) <= 0)
                {
                    after_deletion_node = RR(after_deletion_node);
                }
                else
                {
                    after_deletion_node = RL(after_deletion_node);
                }
            }
        }
        new_root = after_deletion_node;
        after_deletion_node =after_deletion_node->parent;
    }
    return new_root;
}
template<class T>
Node<T>* AVL<T>::switch_AVL_values(Node<T>* cur_parent, Node<T>* son)
{
    shared_ptr<T> temp_data;

    temp_data = cur_parent->data;
    cur_parent->data = son->data;
    son->data = temp_data;

    return son;
}

//this function finds the node to be deleted, makes it a leaf and then deletes it. part of the deletion algorithm
template<class T>
Node<T>* AVL<T>::delete_node_as_leaf (Node<T>* to_delete)
{
    Node<T>* to_delete_parent = to_delete->parent;
    if(to_delete->left == nullptr&& to_delete->right== nullptr)
    {
        if(to_delete_parent == nullptr) //checking if the removed node is a leaf and a root
        {
            to_delete->data =nullptr;
            to_delete->height = 0;
            delete to_delete;
            m_root = nullptr;
            return nullptr;
        }
        if(to_delete_parent->right == to_delete)
        {
            to_delete_parent->right = nullptr;
        }
        else
        {
            to_delete_parent->left = nullptr;
        }
        delete to_delete;
        return to_delete_parent;
    }
    if (to_delete->left == nullptr && to_delete->right != nullptr)
    {
        to_delete = switch_AVL_values(to_delete, to_delete->right);
        to_delete_parent = to_delete->parent;
        to_delete_parent->right = nullptr;
        delete to_delete;
        return to_delete_parent;
    }
    if (to_delete->left!= nullptr && to_delete->right == nullptr)
    {
        to_delete = switch_AVL_values(to_delete, to_delete->left);
        to_delete_parent = to_delete->parent;
        to_delete_parent->left = nullptr;
        delete to_delete;
        return to_delete_parent;
    }
    if (to_delete->left != nullptr && to_delete->right != nullptr)
    {
        Node<T>* successor = to_delete->right;
        while (successor->left != nullptr)
        {
            successor = successor->left;
        }
        successor = switch_AVL_values(to_delete, successor);
        if (successor->right != nullptr)
        {
            successor = switch_AVL_values(successor, successor->right);
        }
        to_delete_parent = successor->parent;

        if(to_delete_parent->right == successor)
        {
            to_delete_parent->right = nullptr;
        }
        else
        {
            to_delete_parent->left = nullptr;
        }
        delete to_delete;
        return to_delete_parent;
    }
    return nullptr;
}

template<class T>
Node<T>* AVL<T>::rotations(Node<T>*node) {
    //If the tree become unbalanced,  then try the 4 cases:
    //int bf = balance_factor(node);
    if(balance_factor(node) ==UNBALANCED_PLUS && balance_factor(node->left)>=0){
        return LL(node);
    }
    if(balance_factor(node)==UNBALANCED_PLUS && balance_factor(node->left)==-1){
        return LR(node);
    }
    if(balance_factor(node)==UNBALANCED_MINUS && balance_factor(node->right)<1){
        return RR(node);
    }
    if(balance_factor(node)==UNBALANCED_MINUS && balance_factor(node->right)==1){
        return RL(node);
    }
    return node;

}

template<class T>
Node<T> *AVL<T>::get_root() const {
    return this->m_root;
}

template<class T>
void AVL<T>::set_root(Node<T>* new_root) {
    if(new_root!= nullptr) {
        this->m_root = new_root;
    }
}

//print functions. need to be deleted before we assign this project

template <class T>
void AVL<T>::printBT(const std::string& prefix, const Node<T>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->getData()->getID() << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->getLeft(), true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->getRight(), false);
    }
}
template <class T>
void AVL<T>::printBT(const Node<T>* node)
{
    printBT("", node, false);
}

#define COUNT 5

// Function to print binary tree in 2D
// It does reverse inorder traversal
template <class T>
void AVL<T>::print2DUtil(const Node<T>* root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout <<  root->data->getId()  << "\n";

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
template <class T>
void AVL<T>::print2D(const Node<T>* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

#endif //WET1_AVL_H

