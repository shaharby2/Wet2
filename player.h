//
// Created by shahar on 01/12/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include "wet2util.h"
#include "Node.h"

class team;
class player{
private:
    int m_playerId;
    int m_gamesPlayed;
    int m_cards;
    int m_ability;
    int m_team_games;
    int m_size_of_team;
    bool m_goalkeeper;
    bool m_is_legal;
    permutation_t m_partial_spirit;
    permutation_t m_root_spirit;

public:
    player();
    player(int playerId, int games_Played, int ability, int cards, bool goal_Keeper);
    ~player();
    player& operator=(const player& other);
    int getId() const;
    int get_games_played() const;
    int get_cards() const;
    int get_ability() const;
    int get_team_games() const;
    int get_size_of_team() const;
    bool get_goal_keeper() const;
    bool get_is_legal() const;
    permutation_t get_partial_spirit() const;
    permutation_t get_root_spirit() const;

    void set_player_id(int player_id);
    void set_games_played(int gamesPlayed);
    void set_cards(int cards);
    void set_ability(int ability);
    void set_team_games(int games);
    void set_size_of_team(int size);
    void set_is_legal(bool is_legal);
    void set_goal_keeper(bool goal_keeper);
    void set_partial_spirit(const permutation_t& perm);
    void set_root_spirit(const permutation_t& perm);
    void update_members(int games_played, int cards);
    void set_members(int games_played, int cards);

};
#endif //WET1_PLAYER_H
