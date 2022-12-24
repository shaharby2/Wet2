//
// Created by idanh on 12/2/2022.
#include "player.h"

player::player()
{
    this->m_playerId = 0;
    this->m_gamesPlayed = 0;//
    this->m_cards =0;
    this->m_goals = 0;
    this->m_goalkeeper = false;
    this->m_team_ptr = nullptr;
    this->m_closest_right = nullptr;
    this->m_closest_left = nullptr;
}

player::player(int playerId, int gamesPlayed, int cards, int goals, bool goalKeeper){
    this->m_playerId = playerId;
    this->m_gamesPlayed = gamesPlayed;
    this->m_cards =cards;
    this->m_goals = goals;
    this->m_goalkeeper = goalKeeper;
    this->m_team_ptr = nullptr;
    this->m_closest_right = nullptr;
    this->m_closest_left = nullptr;
}

player::~player()=default;

player& player::operator=(const player& other)=default;

int player::getId() const{
    return this->m_playerId;
}

int player::get_games_played() const {
    return this->m_gamesPlayed;
}

int player::get_cards() const {
    return this->m_cards;
}

int player::get_goals() const {
    return this->m_goals;
}

bool player::get_goal_keeper() const {
    return this->m_goalkeeper;
}

Node<team>* player::get_team_ptr() const{
    return this->m_team_ptr;
}
/*
Node<player>* player::get_players_tree() const{
    return this->m_Players_tree;
}

Node<player>* player::get_players_by_goals_tree() const{
    return this->m_Players_by_goals_tree;
}
 */

void player::set_player_id(int player_Id) {
    this->m_playerId = player_Id;
}

void player::set_games_played(int games_Played) {
    this->m_gamesPlayed = games_Played;
}
/*
void player::set_cards(int cards) {
    this->m_cards = cards;
}
 */

void player::set_goals(int goals) {
    this->m_goals = goals;
}

void player::set_goal_keeper(bool goal_Keeper) {
    this->m_goalkeeper = goal_Keeper;
}


void player::set_team_ptr(Node<team>* team_ptr)
{
    this->m_team_ptr = team_ptr;
}

void player::update_members(int games_played, int goals, int cards)
{
    this->m_gamesPlayed += games_played;
    this->m_goals += goals;
    this->m_cards += cards;
}


void player::set_members(int games_played, int goals, int cards)
{
    this->m_gamesPlayed = games_played;
    this->m_goals = goals;
    this->m_cards = cards;
}

Node<player>* player::get_closest_right() const
{
    return this->m_closest_right;
}

Node<player>* player::get_closest_left() const
{
    return this->m_closest_left;
}

void player::set_closest_right(Node<player> *closest)
{
    this->m_closest_right = closest;
}

void player::set_closest_left(Node<player> *closest)
{
    this->m_closest_left = closest;
}

Node<player>* player::find_left_closest(Node<player>* iterible, shared_ptr<player> node, Node<player>* current_closest,Node<player>* root)
{
    if(compare_player_goals(iterible , *node) == -1)
    {
        current_closest = find_left_closest(iterible->left, node , current_closest , root);
        return current_closest;
    }
    if(compare_player_goals(iterible , *node) == 0)
    {
        if(iterible->left == nullptr)
        {
            while(root->left != nullptr)
            {
                root = root->left;
            }
            if(iterible == root)
            {
                return nullptr;
            }
            return current_closest;
        }
        current_closest = find_left_closest(iterible->left, node, current_closest , root);
        return current_closest;
    }
    current_closest = iterible;
    if(iterible->right == nullptr)
    {
        return current_closest;
    }
    current_closest = find_left_closest(iterible->right, node, current_closest , root);
    return current_closest;
}

Node<player> *player::find_right_closest(Node<player> *iterible, shared_ptr<player> node , Node<player>* current_closest , Node<player>* root)
{
    if(compare_player_goals(iterible , *node) == 1)
    {
        current_closest = find_right_closest(iterible->right, node , current_closest , root);
        return current_closest;
    }
    if(compare_player_goals(iterible , *node) == 0)
    {
        if(iterible->right == nullptr)
        {
            while(root->right != nullptr)
            {
                root = root->right;
            }
            if(iterible == root)
            {
                return nullptr;
            }
            return current_closest;
        }
        current_closest = find_right_closest(iterible->right, node, current_closest,root);
        return current_closest;
    }
    if(compare_player_goals(iterible , *node) == -1){
        current_closest = iterible;
        if(iterible->left == nullptr)
        {
            return current_closest;
        }
        current_closest = find_right_closest(iterible->left, node, current_closest ,root);
        return current_closest;
    }
    //why come to here?
    return nullptr;
}

Node<player>* player::get_closer( Node<player>* left_p, Node<player>* right_p) const
{
    if(left_p->data == nullptr)
    {
        return right_p;
    }
    if(right_p->data == nullptr)
    {
        return left_p;
    }
    if(abs(left_p->data->get_goals() - this->m_goals) == abs(right_p->data->get_goals() - this->m_goals))
    {
        if(abs(left_p->data->get_cards() - this->m_cards) == abs(right_p->data->get_cards() - this->m_cards))
        {
            if(abs(left_p->data->getId() - this->m_playerId) == abs(right_p->data->getId() - this->m_playerId))
            {
                if(compare_player_id(left_p,*right_p->data)== -1)
                {
                    return left_p;
                }
                return right_p;
            }
            else if(abs(left_p->data->getId() - this->m_playerId) > abs(right_p->data->getId() - this->m_playerId))
            {
                return right_p;
            }
            return left_p;
        }
        else if(abs(left_p->data->get_cards() - this->m_cards) > abs(right_p->data->get_cards() - this->m_cards))
        {
            return right_p;
        }
        return left_p;
    }
    else if(abs(left_p->data->get_goals() - this->m_goals) > abs(right_p->data->get_goals() - this->m_goals))
    {
        return right_p;
    }
    return left_p;
}

int compare_player_id(Node<player>* cur_node, player& comp){
    if(cur_node->data->getId() == comp.getId()){
        return 0;
    }
    else if(cur_node->data->getId() > comp.getId()){
        return -1;
    }
    return 1;
}

int compare_player_goals(Node<player>* cur_node, player& comp){
    if(cur_node->data->get_goals() == comp.get_goals())
    {
        if(cur_node->data->get_cards() == comp.get_cards())
        {
            if(cur_node->data->getId() == comp.getId())
            {
                return 0;
            }
            else if(cur_node->data->getId() > comp.getId())
            {
                return -1;
            }

            return 1;
        }
        else if(cur_node->data->get_cards() < comp.get_cards()) {
            return -1;
        }
        return 1;
    }
    else if(cur_node->data->get_goals() > comp.get_goals()){
        return -1;
    }
    return 1;
}