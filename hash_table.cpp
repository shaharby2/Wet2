//
// Created by idanh on 1/1/2023.
//
#include "hash_table.h"


hash_table::hash_table(int size, int pow):m_pow(pow), m_num_of_players(0),m_array(nullptr) {
    m_array = new chain_Node*[size];
    for(int i=0;i<size;i++)
    {
        m_array[i]= nullptr;
    }
}

int power(int num, int pow){
    int i=0;
    int multiplied = num;
    while(i<pow-1){
        num*=multiplied;
        i++;
    }
    return num;
}

hash_table::~hash_table()
{
    int size = power(2, m_pow)-1;
    chain_Node* temp;
    chain_Node* temp_next;
    for(int i=0;i<size;i++)
    {
        temp =  m_array[i];
        while (temp!=nullptr)
        {
            temp_next = temp->m_next;
            delete temp;
            temp = temp_next;
        }
    }
    delete[] m_array;
}

hash_table & hash_table::operator=(const hash_table &other) {
    this->m_array = other.m_array;
    this->m_num_of_players = other.m_num_of_players;
    this->m_pow = other.m_pow;
    return *this;
}


bool hash_table::is_rehash_needed() {
    int two_powered = power(2,m_pow);
    if(MAX_WEIGHT_FACTOR <= (m_num_of_players/(two_powered-1))){
        return true;
    }
    return false;
}

void hash_table::add_to_array(Node<player>* new_player, chain_Node** array) {
    chain_Node* cur_chain = new chain_Node(new_player);
    int cell = get_cell(new_player->data->getId());
    if(array[cell] == nullptr)
    {
        array[cell] = cur_chain;
    }
    else
    {
        cur_chain->m_next = array[cell]->m_next;
        array[cell]->m_next = cur_chain;
    }
    m_num_of_players++;
}

/*void hash_table::replace_node(chain_Node* node, chain_Node** array) {
    int cell = get_cell(node->m_data->data->getId());
    if(array[cell] == nullptr)
    {
        array[cell] = node;
    }
    else
    {
        node->m_next = array[cell]->m_next;
        array[cell]->m_next = node;
    }
}
*/
void hash_table::rehash(Node<player>* new_player) {
    int two_powered = power(2,m_pow);
    m_pow++;
    chain_Node** new_array= new chain_Node * [((two_powered*2)-1)];
    for(int i=0;i<((two_powered*2)-1);i++)
    {
        new_array[i]= nullptr;
    }
    chain_Node** old_array = m_array;
    chain_Node* iterate;
    chain_Node* next_chain;
    for(int i=0;i<two_powered-1;i++)
    {
        iterate = old_array[i];
        while(iterate != nullptr){
            next_chain = iterate->m_next;
            add_to_array(iterate->m_data, new_array);
            m_num_of_players--;
            delete iterate;
            iterate = next_chain;
        }
    }
    add_to_array(new_player,new_array);
    m_array = new_array;
    delete[] old_array;
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
        iterator = iterator->m_next;
    }
    return nullptr;
}

void hash_table::set_num_of_players(int num_players)
{
    m_num_of_players+= num_players;
}

chain_Node** hash_table::get_array() const {
    return m_array;
}