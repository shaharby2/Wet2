//
// Created by shahar on 01/12/2022.
//
//
#ifndef WET1_TEAM_H
#define WET1_TEAM_H

#include "player.h"
#include "AVL.h"

class player;
class team{
private:
    int teamId;
    int points;

    int is_goalkeeper;
    int num_of_players;
    int goals;
    int cards;
    int team_games_played;
    shared_ptr<player> team_top_scorer;
    AVL<player>* team_by_id;
    AVL<player>* team_by_goals;
public:
    team(int id, int points);
    explicit team();
    ~team();
    team& operator=( const team& other);
    int getId()const;
    int get_points()const;
    int get_num_of_players()const;
    int get_goals()const;
    int get_cards()const;
    int get_team_games_played()const;
    shared_ptr<player> get_team_top_scorer()const;
    AVL<player>* get_team_by_id()const;
    AVL<player>* get_team_by_goals()const;
    int get_goalkeeper()const;
    int calc_game_score()const;

    void set_team_id(int new_team_id);
    void set_points(int new_points);
    void set_num_of_players(int new_num_of_players);
    void set_goals(int new_goals);
    void set_cards(int new_cards);
    void set_team_games_played(int new_team_games_played);
    void set_team_top_scorer(shared_ptr<player> new_team_top_scorer);
    void set_goalkeeper(int new_is_goalkeeper);
    //?
    void set_team_by_id(AVL<player>* new_team_by_id);
    void set_team_by_goals(AVL<player>* new_team_by_goals);

    bool is_full_team();

    void update_members(int new_points , int new_num_of_players, int new_goals, int new_cards);
    void set_members(int new_points , int new_num_of_players, int new_goals, int new_cards);
    void knockout_array(Node<team>* root, team array[], int* cell, shared_ptr<team> min, shared_ptr<team> max);
    team& get_winner(team& team1, team& team2);


};
int compare_team_id(Node<team>* cur_node, team& comp);//
int compare_team_goals(Node<team>* cur_node, team& comp);
#endif //WET1_TEAM_H