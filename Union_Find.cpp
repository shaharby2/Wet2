//
// Created by idanh on 1/1/2023.
//
#include "Union_Find.h"

Union_Find::Union_Find(int size, int pow):
m_hashed_array(size, pow){}

Node<player>* Union_Find::Find(int player_id) {
    chain_Node* cur_player = m_hashed_array.get_player(player_id);
    if(cur_player == nullptr){
        return nullptr;
    }
    //Reach to the last parent - the source of the upside-down tree:
    Node<player>* source_iterator = cur_player->m_data;
    Node<player>* iterator = cur_player->m_data;
    Node<player>* next_p;
    permutation_t temp = cur_player->m_data->data->get_root_spirit(); //multiplies all permutations
    permutation_t temp_partial_spirit = cur_player->m_data->data->get_partial_spirit();// specific node partial_spirit
    int sum_team_games=0;
    while(source_iterator->parent!=nullptr){
        source_iterator = source_iterator->parent;
        sum_team_games+=source_iterator->data->get_team_games();
        temp = source_iterator->data->get_root_spirit()*temp;
    }
    sum_team_games -= source_iterator->data->get_team_games(); // subtracting root team games
    temp = source_iterator->data->get_root_spirit().inv() * temp;
    //Sets the new parent to be the source of the upside-down tree:
    while(iterator->parent!= nullptr){
        next_p = iterator->parent; //Saves the old parent
        iterator->parent = source_iterator; // Change the parent
        iterator->data->set_team_games(sum_team_games);// sets the correct team games
        iterator->data->set_partial_spirit(temp*iterator->data->get_partial_spirit());//sets specific partial_spirit
        iterator->data->set_root_spirit(temp);// sets multiplication of permutations in way of the root
        iterator = next_p; //Reach to the old parent
        sum_team_games -= iterator->data->get_team_games();// subtracting the current team games
        temp = temp * temp_partial_spirit.inv();// removing current node spirit
        temp_partial_spirit = iterator->data->get_partial_spirit();// sets to spirit of new node
    }

    return source_iterator;
}

Node<player> *Union_Find::Union(Node<player> *buyer, Node<player> *bought) {
    bought->parent = buyer;
    bought->data->set_team_games(-buyer->data->get_team_games());
    buyer->data->set_size_of_team(bought->data->get_size_of_team());
    buyer->data->set_goal_keeper(bought->data->get_goal_keeper());
    permutation_t temp_spirit = buyer->data->get_root_spirit();
    buyer->data->set_root_spirit( buyer->data->get_root_spirit()*bought->data->get_root_spirit());
    bought->data->set_root_spirit(temp_spirit);
    return buyer;
}

chain_Node* Union_Find::get_player(int playerId){
    return m_hashed_array.get_player(playerId);
}

void Union_Find::set_num_of_players(int num_players)
{
    m_hashed_array.set_num_of_players(num_players);
}

bool Union_Find::is_rehash_needed(){
    return m_hashed_array.is_rehash_needed();
}

void Union_Find::add_to_array(Node<player>* new_player, chain_Node** array){
    m_hashed_array.add_to_array(new_player, array);
}

void Union_Find::rehash(Node<player>* new_player){
    m_hashed_array.rehash(new_player);
}

chain_Node** Union_Find::get_array() const {
    return m_hashed_array.get_array();
}
