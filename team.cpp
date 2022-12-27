//
// Created by shahar on 01/12/2022.
//
//
#include "team.h"
class player;
team::team(){
    this->teamId = 0;
    this->points = 0;
    this-> is_goalkeeper = 0;
    this->num_of_players = 0;
    this-> cards = 0;
    this-> team_games_played = 0;
    this->m_team_ability =0;
    this->m_team_Players = nullptr;
}

team::team(int id, int points)
{
    this->teamId = id;
    this->points = points;
    this-> is_goalkeeper = 0;
    this->num_of_players = 0;
    this-> cards = 0;
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

int team::get_num_of_players()const
{
    return this->num_of_players;
}

int team::get_cards()const
{
    return this->cards;
}

int team::get_team_games_played()const
{
    return this->team_games_played;
}

int team::get_goalkeeper()const
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

permutation_t team::get_multiplication_spirit() const {
    return this->m_multiplication_spirit;
}

void team::set_team_id(int new_team_id)
{
    this->teamId = new_team_id;
}

void team::set_points(int new_points)
{
    this->points = new_points;
}

void team::set_num_of_players(int new_num_of_players)
{
    this->num_of_players = new_num_of_players;
}

void team::set_cards(int new_cards)
{
    this->cards = new_cards;
}

void team::set_team_games_played(int new_team_games_played)
{
    this->team_games_played = new_team_games_played;
}

void team::set_goalkeeper(int new_is_goalkeeper)
{
    this->is_goalkeeper = new_is_goalkeeper;
}

void team::set_team_ability(int abilities) {
    this->m_team_ability = abilities;
}

void team::set_members(int new_points, int new_num_of_players, int new_cards)
{
    this->points = new_points;
    this->num_of_players = new_num_of_players;
    this->cards = new_cards;
}

void team::set_team_Players(Node<player> *root) {
    this->m_team_Players = root;
}

void team::set_team_spirit(const permutation_t& perm) {
    this->m_team_spirit = perm;
}

void team::set_multiplication_spirit(const permutation_t &perm) {
    this->m_multiplication_spirit = perm;
}

int team::calc_game_score() const {
    return (this->points + this->m_team_ability);
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
        else if(cur_node->data->getId() == comp.getId())
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
