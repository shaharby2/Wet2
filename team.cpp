//
// Created by shahar on 01/12/2022.
//
//
#include "team.h"
class player;
team::team(){
    this->teamId = 0;
    this->points = 0;
    this-> is_goalkeeper = false;
    this-> team_games_played = 0;
    this->m_team_ability =0;
    this->m_team_Players = nullptr;
}

team::team(int id)
{
    this->teamId = id;
    this->points = 0;
    this-> is_goalkeeper = false;
    //this->num_of_players = 0;
    this-> team_games_played = 0;
    this->m_team_ability =0;
    this->m_team_Players = nullptr;
}

team& team::operator=(const team& other)=default;

int team::getId()const {
    return this->teamId;
}

int team::get_points()const
{
    return this->points;
}

/*
int team::get_num_of_players()const
{
    return this->num_of_players;
}
void team::set_num_of_players(int new_num_of_players)
{
    this->num_of_players = new_num_of_players;
}
 */

int team::get_team_games_played()const
{
    return this->team_games_played;
}

bool team::get_goalkeeper()const
{
    return this->is_goalkeeper;
}

int team::get_team_ability() const {
    return this->m_team_ability;
}

Node<player>* team::get_team_Players() const {
    return this->m_team_Players;
}

permutation_t team::get_team_spirit() const {
    return this->m_team_spirit;
}

/*permutation_t team::get_multiplication_spirit() const {
    return this->m_multiplication_spirit;
}
*/
void team::set_team_id(int new_team_id)
{
    this->teamId = new_team_id;
}

void team::set_points(int new_points)
{
    this->points += new_points;
}

void team::set_team_games_played(int new_team_games_played)
{
    this->team_games_played += new_team_games_played;
}

void team::set_goalkeeper(bool new_is_goalkeeper)
{
    this->is_goalkeeper = (this->is_goalkeeper || new_is_goalkeeper);
}

void team::set_team_ability(int abilities) {
    this->m_team_ability += abilities;
}

void team::set_team_Players(Node<player> *root) {
    this->m_team_Players = root;
}

void team::set_team_spirit(const permutation_t& perm) {
    this->m_team_spirit = perm;
}

int compare_team_id(Node<team>* cur_node, team& comp) {
    if (cur_node->data->getId() == comp.getId()) {
        return 0;
    } else if (cur_node->data->getId() > comp.getId()) {
        return -1;
    }
    return 1;
}

int compare_team_ability(Node<team>* cur_node, team& comp)
{
    if (cur_node->data->get_team_ability() == comp.get_team_ability())
    {
        if(cur_node->data->getId() == comp.getId())
        {
            return 0;
        }
        else if(cur_node->data->getId() > comp.getId())
        {
            return  -1;
        }
        else
        {
            return 1;
        }
    }
    else if (cur_node->data->get_team_ability() > comp.get_team_ability())
    {
        return -1;
    }
    else{
        return 1;
    }
}

int compare_play_match(shared_ptr<team> team1, shared_ptr<team> team2){
    int sum1 = team1->get_team_ability() + team1->get_points();
    int sum2 = team2->get_team_ability() + team2->get_points();
    if(sum1 == sum2){
        if(team1->get_team_Players()->data->get_root_spirit().strength() == team2->get_team_Players()->data->get_root_spirit().strength()){
            return 0;
        }
        else if(team1->get_team_Players()->data->get_root_spirit().strength() > team2->get_team_Players()->data->get_root_spirit().strength()){
            return 2;
        }
        else{
            return 4;
        }
    }
    else if(sum1 > sum2){
        return 1;
    }
    else{
        return 3;
    }
}

void buy(shared_ptr<team> buyer, shared_ptr<team> bought) {
    buyer->set_team_ability(bought->get_team_ability());
    buyer->set_points(bought->get_points());
    buyer->set_goalkeeper(bought->get_goalkeeper());
    buyer->set_team_games_played(bought->get_team_games_played());
    buyer->set_team_spirit(bought->get_team_spirit());
}
