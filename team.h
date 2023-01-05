//
// Created by shahar on 01/12/2022.
//
//
#ifndef WET1_TEAM_H
#define WET1_TEAM_H

#include "player.h"

class player;
class team{
private:
    int teamId;
    int points;
    bool is_goalkeeper;
    //int num_of_players;
    //int cards;
    int team_games_played;
    int m_team_ability;
    Node<player>* m_team_Players;
    permutation_t m_team_spirit;
    //permutation_t m_multiplication_spirit;

public:
    team(int id);
    explicit team();
    ~team() = default;
    team& operator=( const team& other);
    int getId()const;
    int get_points()const;
    //int get_num_of_players()const;
    //int get_cards()const;
    int get_team_games_played()const;
    bool get_goalkeeper()const;
    int get_team_ability()const;
    Node<player>* get_team_Players()const;
    permutation_t get_team_spirit()const;
    //permutation_t get_multiplication_spirit()const;

    int calc_game_score()const;


    void set_team_id(int new_team_id);
    void set_points(int new_points);
    //void set_num_of_players(int new_num_of_players);
    //void set_cards(int new_cards);
    void set_team_games_played(int new_team_games_played);
    void set_goalkeeper(bool new_is_goalkeeper);
    void set_team_ability(int abilities);
    void set_team_Players(Node<player>* root);
    void set_team_spirit(const permutation_t& perm);
    //void set_multiplication_spirit(const permutation_t& perm);
};
int compare_play_match(shared_ptr<team> team1, shared_ptr<team> team2);
int compare_team_id(Node<team>* cur_node, team& comp);
int compare_team_ability(Node<team>* cur_node, team& comp);
void buy(shared_ptr<team> buyer, shared_ptr<team> bought);
#endif //WET1_TEAM_H