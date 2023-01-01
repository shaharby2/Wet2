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

Node<player> *Union_Find::Find(int player_id) {
    int cell = m_hashed_array.get_cell(player_id);
    
    return nullptr;
}

Node<player> *Union_Find::Union(Node<player> *group1, Node<player> *group2) {
    return nullptr;
}



