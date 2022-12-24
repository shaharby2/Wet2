//
// Created by shahar on 01/12/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include "AVL.h"
class team;
class player{
private:
    int m_playerId;
    int m_gamesPlayed;//
    int m_goals;
    int m_cards;
    bool m_goalkeeper;
    Node<team>* m_team_ptr;
    Node<player>* m_closest_right;
    Node<player>* m_closest_left;
public:
    player();
    player(int playerId, int games_Played, int cards, int goals, bool goal_Keeper);
    ~player();
    player& operator=(const player& other);
    int getId() const;
    //int get_team_id() const;
    int get_games_played() const;
    int get_goals() const;
    int get_cards() const;
    bool get_goal_keeper() const;
    Node<team>* get_team_ptr() const;
    //Node<player>* get_players_tree() const;
    //Node<player>* get_players_by_goals_tree() const;

    void set_player_id(int player_id);
    void set_games_played(int gamesPlayed);

    void set_goals(int goals);
    //void set_cards(int cards);

    void set_goal_keeper(bool goal_keeper);
    void set_team_ptr(Node<team>* team_ptr);

    void update_members(int games_played, int goals, int cards);
    void set_members(int games_played, int goals, int cards);

    Node<player>* get_closest_right() const;
    Node<player>* get_closest_left() const;
    void set_closest_left(Node<player>* closest) ;
    void set_closest_right(Node<player>* closest) ;
    Node<player>* find_left_closest(Node<player>* iterible, shared_ptr<player> node, Node<player>* current_closest,Node<player>* root);
    Node<player>* find_right_closest(Node<player>* iterible, shared_ptr<player> node, Node<player>* current_closest,Node<player>* root);
    Node<player>* get_closer(Node<player>* left_p, Node<player>* right_p) const;

};
int compare_player_id(Node<player>* cur_node,player& comp);
int compare_player_goals(Node<player>* cur_node,player& comp);
#endif //WET1_PLAYER_H