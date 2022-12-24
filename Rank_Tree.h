//
// Created by shahar on 24/12/2022.
//

#ifndef WET2_NEW_RANK_TREE_H
#define WET2_NEW_RANK_TREE_H

#include "AVL.h"
#include "Rank_Node.h"
template <class T>
class Rank_Tree: public AVL<T>{

public:
    Rank_Tree(int (*compare)(Node<T>* cur_node, T& comp)): AVL<T>{compare}{};
    ~Rank_Tree();
    Node<T>* RR(Rank_Node<T>* unbalanced) override;
    Node<T>* LR(Rank_Node<T>* unbalanced) override;
    Node<T>* LL(Rank_Node<T>* unbalanced) override;
    Node<T>* RL(Rank_Node<T>* unbalanced) override;
    Node<T>* insert(Rank_Node<T> *prev_node,Rank_Node<T> *current, shared_ptr<T>data) override;
    Node<T>* remove(shared_ptr<T> removed_Node_id) override;
    Node<T>* switch_AVL_values(Node<T>* cur_parent, Node<T>* son) override;
    Node<T>* delete_node_as_leaf (Node<T>* to_delete) override;
};
template<class T>
Node<T>* Rank_Tree<T>::insert(Rank_Node<T> *prev_node,Rank_Node<T> *current, shared_ptr<T> data){
    if(current== nullptr){
        Rank_Node<T> *New;
        New = new Rank_Node<T>();
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
    //current->rank++
    current = rotations(current);
    return current;

}
/*With all the rotations if we will go to nullptr we need to count it as rank 0 - maybe we can use a function that deals with this situation*/

template<class T>
Node<T>* Rank_Tree<T>::LL(Rank_Node<T>* unbalanced) {
    //Rank new source = rank unbalanced
    //Rank unbalanced = Rank (unbalanced->right + new_source->right+1)
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

    return new_source;
}

template<class T>
Node<T>* Rank_Tree<T>::RR(Rank_Node<T>* unbalanced) {
    //Rank new source = rank unbalanced
    //Rank unbalanced = Rank (unbalanced->left + new_source->left+1)
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

    return new_source;
}

template<class T>
Node<T>* Rank_Tree<T>::LR(Rank_Node<T>* unbalanced) {
    //rank tp2 = rank p
    //rank tp = rank tp2->left + rank tp->left + 1
    //rank p = rank p->right + rank tp2->right + 1
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

    return tp2;

}

template<class T>
Node<T>* Rank_Tree<T>::RL(Rank_Node<T>* unbalanced) {
    //rank tp2 = rank p
    //rank tp = rank tp2->right + rank tp->right + 1
    //rank p = rank p->left + rank tp2->left + 1
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

    return tp2;
}
#endif //WET2_NEW_RANK_TREE_H
