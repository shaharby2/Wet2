//
// Created by idanh on 1/1/2023.
//
#include "Union_Find.h"

Union_Find::Union_Find(int size, int pow) {
    m_hashed_array = hash_table(size,pow);
}
/*
Node<player> *Union_Find::MakeSet(int playerId) {

    return nullptr;
}
*/

Node<player>* Union_Find::Find(int player_id) {
    chain_Node* cur_player = m_hashed_array.get_player(player_id);
    if(cur_player == nullptr){
        return nullptr;
    }
    //Reach to the last parent - the source of the upside-down tree:
    Node<player>* source_iterator = cur_player->m_data;
    Node<player>* iterator = cur_player->m_data;
    Node<player>* next_p = cur_player->m_data;
    while(source_iterator->parent!=nullptr){
        source_iterator = source_iterator->parent;
    }
    //Sets the new parent to be the source of the upside-down tree:
    while(iterator->parent!=source_iterator){
        next_p = iterator->parent; //Saves the old parent
        iterator->parent = source_iterator; // Change the parent
        iterator = next_p; //Reach to the old parent
    }

    return cur_player->m_data;
}

Node<player> *Union_Find::Union(Node<player> *group1, Node<player> *group2) {
    return nullptr;
}


