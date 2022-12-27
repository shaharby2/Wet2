//
// Created by shahar on 27/12/2022.
//

#ifndef WET2_NEW_CHAIN_NODE_H
#define WET2_NEW_CHAIN_NODE_H

#include <memory>
#include "player.h"
using namespace std;

struct chain_Node{
    int m_key;
    chain_Node* m_next;
    Node<player>* m_data;

    explicit chain_Node(Node<player>* p_node){
        this->m_data = p_node;
        this->m_key = p_node->data->getId();
        this->m_next = nullptr;
    };

    ~chain_Node(){
    };

};

#endif //WET2_NEW_CHAIN_NODE_H
