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
    this->goals = 0;
    this-> cards = 0;
    this-> team_games_played = 0;
    this-> team_top_scorer = nullptr;
    this-> team_by_id = new AVL<player>(compare_player_id);
    this-> team_by_goals = new AVL<player>(compare_player_goals);
}

team::~team() {
    delete team_by_id;
    delete team_by_goals;
}

team::team(int id, int points)
{
    this->teamId = id;
    this->points = points;
    this-> is_goalkeeper = 0;
    this->num_of_players = 0;
    this->goals = 0;
    this-> cards = 0;
    this-> team_games_played = 0;
    this-> team_top_scorer = nullptr;
    this-> team_by_id = new AVL<player>(compare_player_id);
    this-> team_by_goals = new AVL<player>(compare_player_goals);
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

int team::get_goals()const
{
    return this->goals;
}

int team::get_cards()const
{
    return this->cards;
}

int team::get_team_games_played()const
{
    return this->team_games_played;
}

shared_ptr<player> team::get_team_top_scorer()const
{
    return this->team_top_scorer;
}

AVL<player>* team::get_team_by_id()const
{
    return this->team_by_id;
}

AVL<player>* team::get_team_by_goals()const
{
    return this->team_by_goals;
}

int team::get_goalkeeper()const
{
    return this->is_goalkeeper;
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

void team::set_goals(int new_goals)
{
    this->goals = new_goals;
}

void team::set_cards(int new_cards)
{
    this->cards = new_cards;
}

void team::set_team_games_played(int new_team_games_played)
{
    this->team_games_played = new_team_games_played;
}

void team::set_team_top_scorer(shared_ptr<player> new_team_top_scorer)
{
    this->team_top_scorer = new_team_top_scorer;
}

void team::set_goalkeeper(int new_is_goalkeeper)
{
    this->is_goalkeeper = new_is_goalkeeper;
}

void team::set_team_by_id(AVL<player>* new_team_by_id)
{
    this->team_by_id = new_team_by_id;
}

void team::set_team_by_goals(AVL<player>* new_team_by_goals)
{
    this->team_by_goals = new_team_by_goals;
}

bool team::is_full_team()//
{
    if(this->get_num_of_players()>=11 && this->get_goalkeeper()>=1)
    {
        return true;
    }
    return false;
}

void team::update_members(int new_points, int new_num_of_players, int new_goals, int new_cards)
{
    this->points += new_points;
    this->num_of_players += new_num_of_players;
    this->goals += new_goals;
    this->cards += new_cards;
}

void team::set_members(int new_points, int new_num_of_players, int new_goals, int new_cards)
{
    this->points = new_points;
    this->num_of_players = new_num_of_players;
    this->goals = new_goals;
    this->cards = new_cards;
}

int team::calc_game_score() const {
    return (this->points + this->goals - this->cards);
}

void team::knockout_array(Node<team>* root, team array[], int* cell, shared_ptr<team> min, shared_ptr<team> max)
{
    if(root->left == nullptr && root->right == nullptr && compare_team_id(root, *min) == -1
       && compare_team_id(root, *max)==1)
    {
        array[*cell] = *root->data;
        (*cell)++;
        return;
    }
    if(compare_team_id(root, *min) == -1 && compare_team_id(root, *max)==1)
    {
        if(root->left != nullptr)
        {
            knockout_array(root->left, array, cell, min, max);
            array[*cell] = *root->data;
            (*cell)++;
        }
        else
        {
            array[*cell] = *root->data;
            (*cell)++;
        }
    }
    if(compare_team_id(root, *min) == 0)
    {
        array[*cell] = *root->data;
        (*cell)++;
        if(root->right == nullptr)
        {
            return;
        }
        knockout_array(root->right, array, cell, min, max);
    }
    if(compare_team_id(root, *max) == 0)
    {
        if(root->left == nullptr)
        {
            array[*cell] = *root->data;
            (*cell)++;
            return;
        }
        knockout_array(root->left, array, cell, min, max);
        array[*cell] = *root->data;
        (*cell)++;
    }
    if(compare_team_id(root, *min) == 1)
    {
        if(root->right == nullptr)
        {
            return;
        }
        knockout_array(root->right, array, cell, min, max);
    }
    if(compare_team_id(root, *min) == -1 && compare_team_id(root, *max)==1)
    {
        knockout_array(root->right, array, cell, min, max);
    }

    if(compare_team_id(root, *max) == -1)
    {
        if(root->left == nullptr)
        {
            return;
        }
        knockout_array(root->left, array, cell, min, max);
    }
}

team& team::get_winner(team &team1, team &team2)
{
    if(team1.calc_game_score() <= team2.calc_game_score())
    {
        team2.points += team1.points + 3;
        team2.goals += team1.goals;
        team2.cards += team1.cards;
        return team2;
    }
    team1.points += team2.points +3;
    team1.goals += team2.goals;
    team1.cards += team2.cards;
    return team1;
}
int compare_team_id(Node<team>* cur_node, team& comp) {
    if (cur_node->data->getId() == comp.getId()) {
        return 0;
    } else if (cur_node->data->getId() > comp.getId()) {
        return -1;
    }
    return 1;
}

int compare_team_goals(Node<team>* cur_node, team& comp){
    if(cur_node->data->get_goals() == comp.get_goals()) {
        if(cur_node->data->get_cards()<comp.get_cards()) {
            return -1;
        }
        else if(cur_node->data->get_cards()>comp.get_cards()) {
            return 1;
        }
        else{
            return compare_team_id(cur_node,comp);
        }
    }
    else if(cur_node->data->get_goals() > comp.get_goals()){
        return -1;
    }
    return 1;
}
