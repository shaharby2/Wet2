//
// Created by idanh on 1/1/2023.
//
#include "hash_table.h"

hash_table::hash_table(int size, int pow) {
    this->m_array = new chain_Node*[size];
    this->m_num_of_players = 0;
    this->m_pow = pow;
}

hash_table::~hash_table()
{
    delete[] m_array;
}

int power(int num, int pow){
    int i=0;
    while(i<pow){
        num*=num;
        i++;
    }
    return num;
}

bool hash_table::is_rehash_needed() {
    int two_powered = power(2,m_pow+1);
    if(MAX_WEIGHT_FACTOR <= (m_num_of_players/two_powered-1)){
        return true;
    }
    return false;
}

void hash_table::add_to_array(Node<player>* new_player, chain_Node** array) {
    chain_Node cur_chain(new_player);
    int cell = get_cell(new_player->data->getId());
    if(m_array[cell] == nullptr)
    {
        m_array[cell] = &cur_chain;
    }
    else
    {
        (&cur_chain)->m_next = array[cell]->m_next;
        array[cell]->m_next = (&cur_chain);
    }
    m_num_of_players++;
}

void hash_table::rehash(Node<player>* new_player) {
    int two_powered = power(2,m_pow);
    m_pow++;
    chain_Node** new_array= new chain_Node*[(two_powered*2)-1];
    chain_Node* iterate;
    for(int i=0;i<two_powered-1;i++)
    {
        iterate = new_array[i];
        while(iterate != nullptr){
            add_to_array(iterate->m_data, new_array);
            iterate = iterate->m_next;
        }
    }
    iterate = m_array[0];
    m_array = new_array;
    delete[] iterate;
}

int hash_table::get_cell(int id) {
    return id % (power(2,m_pow)-1);
}

chain_Node* hash_table::get_player(int playerId) {
    int cell = get_cell(playerId);
    chain_Node* iterator = m_array[cell];
    while(iterator != nullptr){
        if(iterator->m_data->data->getId() == playerId){
            return iterator;
        }
    }
}
