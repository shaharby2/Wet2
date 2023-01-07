//
// Created by idanh on 1/1/2023.
//

#ifndef WET2_NEW_UNION_FIND_H
#define WET2_NEW_UNION_FIND_H

#include "hash_table.h"
class Union_Find
{
    hash_table m_hashed_array;
public:
    Union_Find(int size, int pow);
    ~Union_Find() = default;
    Node<player>* Find (int player_id);
    Node<player>* Union (Node<player>* group1, Node<player>* group2);
    chain_Node* get_player(int playerId);
    void set_num_of_players(int num_players);
    bool is_rehash_needed();
    void add_to_array(Node<player>* new_player, chain_Node** array);
    void rehash(Node<player>* new_player);
    chain_Node** get_array() const;
};

#endif //WET2_NEW_UNION_FIND_H
