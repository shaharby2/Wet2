//
// Created by shahar on 27/12/2022.
//

#ifndef WET2_NEW_CHAIN_NODE_H
#define WET2_NEW_CHAIN_NODE_H

#include <memory>
#include "player.h"
using namespace std;

struct chain_Node{
    chain_Node* m_next;
    Node<player>* m_data;

    explicit chain_Node(Node<player>* p_node){
        m_data = p_node;
        m_next = nullptr;
    };
    chain_Node(){
        m_next= nullptr;
        m_data = nullptr;
    };

    ~chain_Node(){
        delete m_next;
        delete this;
    };

};

#endif //WET2_NEW_CHAIN_NODE_H
