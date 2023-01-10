//
// Created by idanh on 12/2/2022.
#include "player.h"

player::player()
{
    this->m_playerId = 0;
    this->m_gamesPlayed = 0;
    this->m_cards =0;
    this->m_ability = 0;
    this->m_team_games =0;
    this->m_size_of_team = 1;
    this->m_is_legal = false;
    this->m_goalkeeper = false;
    this->m_root_spirit = permutation_t::neutral();
}

player::player(int playerId, int games_Played, int ability, int cards, bool goal_Keeper):
m_playerId(playerId),m_gamesPlayed(games_Played), m_cards(cards),m_ability(ability), m_team_games(0), m_size_of_team(0),
 m_goalkeeper(goal_Keeper),m_is_legal(false){
    this->m_root_spirit = permutation_t::neutral();
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

int player::get_ability() const {
    return this->m_ability;
}

int player::get_team_games() const {
    return this->m_team_games;
}

int player::get_size_of_team() const {
    return this->m_size_of_team;
}

bool player::get_is_legal() const {
    return this->m_is_legal;
}

bool player::get_goal_keeper() const {
    return this->m_goalkeeper;
}

permutation_t player::get_partial_spirit() const {
    return this->m_partial_spirit;
}

permutation_t player::get_root_spirit() const {
    return this->m_root_spirit;
}

void player::set_player_id(int player_Id) {
    this->m_playerId = player_Id;
}

void player::set_games_played(int games_Played) {
    this->m_gamesPlayed = games_Played;
}

void player::set_cards(int cards) {
    this->m_cards += cards;
}

void player::set_ability(int ability) {
    this->m_ability = ability;
}

void player::set_team_games(int games) {
    this->m_team_games += games;
}

void player::set_size_of_team(int size) {
    this->m_size_of_team += size;
}

void player::set_is_legal(bool is_legal) {
    this->m_is_legal = is_legal;
}
void player::set_goal_keeper(bool goal_Keeper) {
    this->m_goalkeeper = (goal_Keeper || this->m_goalkeeper);
}

void player::set_partial_spirit(const permutation_t &perm) {
    this->m_partial_spirit = perm;
}

void player::set_root_spirit(const permutation_t &perm) {
    this->m_root_spirit = perm;
}

void player::update_members(int games_played, int cards)
{
    this->m_gamesPlayed += games_played;
    this->m_cards += cards;
}

void player::set_members(int games_played, int cards)
{
    this->m_gamesPlayed = games_played;
    this->m_cards = cards;
}
