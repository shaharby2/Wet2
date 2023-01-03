#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
    this->teams = new AVL<team>(compare_team_id);
    this->team_by_ability = new AVL<team>(compare_team_ability);
    this->players = new Union_Find(7,3);
}

world_cup_t::~world_cup_t()
{
    delete teams;
    delete players;
    delete team_by_ability;
}

StatusType world_cup_t::add_team(int teamId)
{
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try{

        shared_ptr<team> added_team(new team(teamId));

        if(teams->find(this->teams->get_root(),*added_team) != nullptr){
            //Found the team in the teams tree:
            return StatusType::FAILURE;
        }
        teams->set_root(teams->insert(nullptr, teams->get_root(),added_team));
        team_by_ability->set_root(team_by_ability->insert(nullptr, teams->get_root(),added_team));
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return StatusType::SUCCESS;

}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try{

        shared_ptr<team> to_remove_team(new team(teamId));

        if(teams->find(this->teams->get_root(),*to_remove_team) != nullptr){
            //Found the team in the teams tree:
            return StatusType::FAILURE;
        }
        Node<player>* cur_source = to_remove_team->get_team_Players();
        if(cur_source!=nullptr){
            cur_source->data->set_is_legal(false);
        }

        teams->set_root(teams->remove(to_remove_team));
        team_by_ability->set_root(team_by_ability->remove(to_remove_team));
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if(playerId <= 0|| teamId <= 0 || gamesPlayed || !spirit.isvalid())
    {
        return StatusType::INVALID_INPUT;
    }
    try {
        shared_ptr<team> team_data(new team(teamId));
        Node<team> *cur_team = teams->find(teams->get_root(), *team_data);
        if (cur_team == nullptr)
        {
            return StatusType::FAILURE;
        }
        chain_Node *chain_player = players->get_hashed_array().get_player(playerId);
        if (chain_player != nullptr)
        {
            return StatusType::FAILURE;
        }
        shared_ptr<player> player_data(new player(playerId,gamesPlayed,ability,cards,goalKeeper));
        Node<player>* new_player = new Node<player>();
        new_player->data = player_data;

        if(cur_team->data->get_team_Players() == nullptr)
        {
            new_player->data->set_is_legal(true);
            new_player->data->set_partial_spirit(spirit);
        }
        else
        {
            Node<player>* temp_root = cur_team->data->get_team_Players();
            players->Union(temp_root,new_player);
            permutation_t m_partial_spirit;
            temp_root->data->set_size_of_team(1);
            temp_root->data->set_goal_keeper(new_player->data->get_goal_keeper());
            new_player->data->set_partial_spirit()


        }
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }
    int num;
    try{
        shared_ptr<team> team1(new team(teamId1));
        shared_ptr<team> team2(new team(teamId2));

        Node<team>* Node_1 = teams->find(this->teams->get_root(),*team1);
        Node<team>* Node_2 = teams->find(this->teams->get_root(),*team2);

        if(Node_1 == nullptr || Node_2 == nullptr){
            //Didn't find the team in the teams tree:
            return StatusType::FAILURE;
        }
        if(Node_1->data->get_goalkeeper()==0 || Node_2->data->get_goalkeeper()==0){
            return StatusType::FAILURE;
        }
        num = compare_play_match(team1, team2);
        if(num == 0){ // tie
            team1->set_points(team1->get_points()+1);
            team2->set_points(team2->get_points()+1);
        }
        if(num == 1 || num == 2){
            team1->set_points(team1->get_points()+3);
        }
        if(num == 3 || num == 4){
            team2->set_points(team2->get_points()+3);
        }
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}

    return num;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId<=0){
        return StatusType::FAILURE;
    }
    int sum_games_played = 0;
    try{
        chain_Node* cur_player = players->get_hashed_array().get_player(playerId);
        if(cur_player != nullptr){
            //Didn't find the player
            return StatusType::FAILURE;
        }
        sum_games_played+=cur_player->m_data->data->get_games_played(); // pink in the drawing
        Node<player>* iterator = cur_player->m_data;
        while(iterator->parent!=nullptr){
            sum_games_played+=iterator->data->get_team_games(); // yellows in the drawing
            iterator = iterator->parent; //Reach to the old parent
        }
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return sum_games_played;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId<=0 || cards<0){
        return StatusType::FAILURE;
    }
    try{
        chain_Node* cur_player = players->get_hashed_array().get_player(playerId);
        if(cur_player == nullptr){
            //Didn't find the player
            return StatusType::FAILURE;
        }
        Node<player>* source = players->Find(playerId);
        if(!source->data->get_is_legal()){
            //Player removed from the competition
            return StatusType::FAILURE;
        }
        cur_player->m_data->data->set_cards(cards);
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if(playerId<=0){
        return StatusType::FAILURE;
    }
    int player_cards;
    try{
        chain_Node* cur_player = players->get_hashed_array().get_player(playerId);
        if(cur_player == nullptr){
            //Didn't find the player
            return StatusType::FAILURE;
        }
        player_cards = cur_player->m_data->data->get_cards();
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return player_cards;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId<=0){
        return StatusType::INVALID_INPUT;
    }
    int points;
    try{
        shared_ptr<team> p_team(new team(teamId));

        Node<team>* Node_team = teams->find(this->teams->get_root(),*p_team);
        if(Node_team == nullptr){
            //Didn't find the team
            return StatusType::FAILURE;
        }
        points = Node_team->data->get_points();
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return points;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    // TODO: Your code goes here
    return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    // TODO: Your code goes here
    return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}
