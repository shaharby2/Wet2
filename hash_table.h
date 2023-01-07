//
// Created by shahar on 01/01/2023.
//

#ifndef WET2_NEW_HASH_TABLE_H
#define WET2_NEW_HASH_TABLE_H

#include "chain_Node.h"
#include "team.h"

#define MAX_WEIGHT_FACTOR 1

class hash_table{
    int m_pow;
    int m_num_of_players;
    chain_Node** m_array;
public:
    hash_table(int size, int pow);
    hash_table() = default;

    hash_table& operator=(const hash_table & other);

    ~hash_table();
    chain_Node* get_player(int playerId);

    bool is_rehash_needed();
    void add_to_array(Node<player>* new_player, chain_Node** array);
    void rehash(Node<player>* new_player);
    int get_cell(int id);
    void set_num_of_players(int num_players);
    chain_Node** get_array()const;
    void new_nullptr_array(int size , int pow);


};

#endif //WET2_NEW_HASH_TABLE_H
