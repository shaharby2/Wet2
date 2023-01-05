/*
//
// Created by idanh on 1/1/2023.
//
#include "Union_Find.h"

Union_Find::Union_Find(int size, int pow) {
    m_hashed_array = hash_table(size,pow);
}

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
    if(group1->data->get_size_of_team()>= group2->data->get_size_of_team())
    {
        group2->parent = group1;
        group1->data->set_size_of_team(group1->data->get_size_of_team()+group2->data->get_size_of_team());
        group1->data->set_goal_keeper(group1->data->get_goal_keeper()+group2->data->get_goal_keeper());
        return group1;
    }
    else
    {
        group1->parent = group2;
        group2->data->set_size_of_team(group1->data->get_size_of_team()+group2->data->get_size_of_team());
        group2->data->set_goal_keeper(group1->data->get_goal_keeper()+group2->data->get_goal_keeper());
        return group2;
    }
}

hash_table Union_Find::get_hashed_array() const {
    return m_hashed_array;
}
*/

//
// Created by idanh on 1/1/2023.
//
#include "Union_Find.h"

Union_Find::Union_Find(int size, int pow) {
    m_hashed_array = hash_table(size,pow);
}

Node<player>* Union_Find::Find(int player_id) {
    chain_Node* cur_player = m_hashed_array.get_player(player_id);
    if(cur_player == nullptr){
        return nullptr;
    }
    //Reach to the last parent - the source of the upside-down tree:
    Node<player>* source_iterator = cur_player->m_data;
    Node<player>* iterator = cur_player->m_data;
    Node<player>* next_p;
    permutation_t temp = cur_player->m_data->data->get_partial_spirit(); //multiplies all permutations
    permutation_t temp_partial_spirit = cur_player->m_data->data->get_partial_spirit();// spesific node partial_spirit
    int sum_team_games=0;
    while(source_iterator->parent!=nullptr){
        source_iterator = source_iterator->parent;
        sum_team_games+=source_iterator->data->get_team_games();
        temp = source_iterator->data->get_root_spirit()*temp;
    }
    sum_team_games-=source_iterator->data->get_team_games(); // subtracting root team games
    temp = source_iterator->data->get_root_spirit().inv()*temp;
    //Sets the new parent to be the source of the upside-down tree:
    while(iterator->parent!=source_iterator){
        next_p = iterator->parent; //Saves the old parent
        iterator->parent = source_iterator; // Change the parent
        iterator->data->set_team_games(sum_team_games);// sets the correct team games
        iterator->data->set_partial_spirit(temp);//sets spesific partial_spirit
        iterator->data->set_root_spirit(temp);// sets multiplication of permutations in way of the root
        iterator = next_p; //Reach to the old parent
        sum_team_games-=iterator->data->get_team_games();// subtracting the current team games
        temp = temp*temp_partial_spirit.inv();// removing current node spirit
        temp_partial_spirit = iterator->data->get_partial_spirit();// sets to spirit of new node
    }

    return cur_player->m_data;
}

Node<player> *Union_Find::Union(Node<player> *group1, Node<player> *group2) {
    if(group1->data->get_size_of_team()>= group2->data->get_size_of_team())
    {
        update_Union_stats(group1, group2);
        return group1;
    }
    else
    {
        update_Union_stats(group2, group1);
        return group2;
    }
}

hash_table Union_Find::get_hashed_array() const {
    return m_hashed_array;
}

void Union_Find::update_Union_stats(Node<player> *group1, Node<player> *group2) {
    group2->parent = group1;
    group2->data->set_team_games(group2->data->get_team_games()-group1->data->get_team_games());
    group1->data->set_size_of_team(group1->data->get_size_of_team()+group2->data->get_size_of_team());
    group1->data->set_goal_keeper(group1->data->get_goal_keeper()+group2->data->get_goal_keeper());
    permutation_t temp_spirit = group1->data->get_root_spirit();
    group1->data->set_root_spirit( group1->data->get_root_spirit()*group2->data->get_root_spirit());
    group2->data->set_root_spirit(temp_spirit);
}
