#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
    this->teams = new AVL<team>(compare_team_id);
    this->team_by_ability = new AVL<team>(compare_team_ability);
    this->players = new Union_Find(7,3);
    this->number_of_teams=0;
}

world_cup_t::~world_cup_t()
{
    delete teams;
    delete team_by_ability;
    delete players;
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
        team_by_ability->set_root(team_by_ability->insert(nullptr, team_by_ability->get_root(),added_team));
        number_of_teams++;
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
       /* if(teamId == 24086)
        {
            int u =0;
        }*/
        shared_ptr<team> to_remove_team(new team(teamId));
        Node<team>* cur_team = teams->find(this->teams->get_root(),*to_remove_team);
        if(cur_team == nullptr){
            //Didn't find the team in the teams tree:
            return StatusType::FAILURE;
        }
        to_remove_team = cur_team->data;
        Node<player>* cur_source = cur_team->data->get_team_Players();
        if(cur_source!=nullptr){
            cur_source->data->set_is_legal(false);
        }

        teams->set_root(teams->remove(to_remove_team));
        team_by_ability->set_root(team_by_ability->remove(to_remove_team));
        number_of_teams--;
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
   /* if(playerId == 55457)
    {
        int u =0;
    }
*/
    if(playerId <= 0|| teamId <= 0 || gamesPlayed<0 || !spirit.isvalid() || cards<0)
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
        chain_Node *chain_player = players->get_player(playerId);
        if (chain_player != nullptr)
        {
            return StatusType::FAILURE;
        }
        team_by_ability->set_root(team_by_ability->remove(cur_team->data)); ///new thing we added

        shared_ptr<player> player_data(new player(playerId,gamesPlayed,ability,cards,goalKeeper));
        Node<player>* new_player = new Node<player>();
        new_player->data = player_data;

        if(cur_team->data->get_team_Players() == nullptr)
        {
            new_player->data->set_is_legal(true);
            new_player->data->set_partial_spirit(spirit);
            new_player->data->set_root_spirit(spirit);
            cur_team->data->set_goalkeeper(new_player->data->get_goal_keeper());
            cur_team->data->set_team_spirit(spirit);
            cur_team->data->set_team_Players(new_player);
        }
        else
        {
            Node<player>* temp_root = cur_team->data->get_team_Players();
            new_player->parent = temp_root;
            temp_root->data->set_size_of_team(1);
            cur_team->data->set_goalkeeper(new_player->data->get_goal_keeper());
            new_player->data->set_team_games(-temp_root->data->get_team_games());
            new_player->data->set_partial_spirit(temp_root->data->get_root_spirit()*spirit);
            temp_root->data->set_root_spirit( temp_root->data->get_root_spirit()*spirit);
        }
        cur_team->data->set_team_ability(ability);

        team_by_ability->set_root(team_by_ability->insert(nullptr,team_by_ability->get_root(),cur_team->data)); ///new thing

        if (players->is_rehash_needed())
        {
            players->rehash(new_player);
        }
        else
        {
            players->add_to_array(new_player , players->get_array());
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
        num = compare_play_match(Node_1->data, Node_2->data);
        if(num == 0){ // tie
            Node_1->data->set_points(team1->get_points()+1);
            Node_2->data->set_points(team2->get_points()+1);
        }
        if(num == 1 || num == 2){//team1 won
            Node_1->data->set_points(team1->get_points()+3);
        }
        if(num == 3 || num == 4){//team2 won
            Node_2->data->set_points(team2->get_points()+3);
        }
        Node_1->data->get_team_Players()->data->set_team_games(1);
        Node_2->data->get_team_Players()->data->set_team_games(1);
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}

    return num;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
   /* if (playerId == 83314)
    {
        int u =0;
    }*/
    if(playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    int sum_games_played = 0;
    try{
        chain_Node* cur_player = players->get_player(playerId);
        if(cur_player == nullptr){
            //Didn't find the player
            return StatusType::FAILURE;
        }

        if(cur_player->m_data->parent != nullptr){
            Node<player>* source = players->Find(playerId);
            sum_games_played+=source->data->get_team_games(); // Add the source's games played
        }
        sum_games_played+=cur_player->m_data->data->get_games_played(); // pink in the drawing
        sum_games_played+=cur_player->m_data->data->get_team_games(); //yellows?

    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
    return sum_games_played;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId<=0 || cards<0){
        return StatusType::INVALID_INPUT;
    }
    try{
        chain_Node* cur_player = players->get_player(playerId);
        if(cur_player == nullptr){
            //Didn't find the player
            return StatusType::FAILURE;
        }
        Node<player>* source = cur_player->m_data;
        if(cur_player->m_data->parent!= nullptr){
            source = players->Find(playerId);
        }
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
        return StatusType::INVALID_INPUT;
    }
    int player_cards;
    try{
        chain_Node* cur_player = players->get_player(playerId);
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
   /* if (i == 11)
    {
        int u = 0;
        team_by_ability->print2D(team_by_ability->get_root());
        return 0;
    }
*/
    int sum=0;
    if(i<0 || number_of_teams==0 || i>=number_of_teams){
        return StatusType::FAILURE;
    }
    try{
        int left_rank;
        Node<team>* rec_team = team_by_ability->get_root();
        while(true){
            //Sets left rank:
            if(rec_team->left == nullptr){
                left_rank = 0;
            }
            else{
                left_rank = rec_team->left->rank;
            }
            //Check conditions:
            if((left_rank + sum) == i){
                return rec_team->data->getId();
            }

            else if(left_rank+ sum > i){
                rec_team = rec_team->left;
            }
            else{
                sum+=left_rank+1;
                rec_team = rec_team->right;
            }
        }
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    /*if (playerId == 74012)
    {
        int u =0;
    }
*/
    if(playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    try{
        chain_Node* cur_p = players->get_player(playerId);
        if(cur_p == nullptr){
            return StatusType::FAILURE;
        }
        Node<player> *source = cur_p->m_data;
        if(source->parent != nullptr) {
            source = players->Find(playerId);
        }
        if(!source->data->get_is_legal()){
            //Player removed from the competition
            return StatusType::FAILURE;
        }
        /*I want to return the team partial spirit and I don't really need the players one, so maybe we need to keep this info
        at the source in the reversed tree*/
        return cur_p->m_data->data->get_partial_spirit();
    }
    catch(...){return StatusType::ALLOCATION_ERROR;}
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
 /*   if (teamId1 == 8  && teamId2 == 7)
    {
        int u =0;
    }
*/
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }
    try{
        shared_ptr<team> buyer(new team(teamId1));
        shared_ptr<team> bought(new team(teamId2));

        Node<team>* Node_buyer = teams->find(this->teams->get_root(),*buyer);
        Node<team>* Node_bought = teams->find(this->teams->get_root(),*bought);
        if(Node_buyer == nullptr || Node_bought == nullptr){
            //Didn't find one of the teams
            return StatusType::FAILURE;
        }
        buyer = Node_buyer->data;
        Node<player>*Source_buyer = Node_buyer->data->get_team_Players();
        Node<player>*Source_bought = Node_bought->data->get_team_Players();

        team_by_ability->set_root(team_by_ability->remove(Node_bought->data));
        team_by_ability->set_root(team_by_ability->remove(Node_buyer->data));
        //Group1 is empty and Group2 isn't:
        if(Source_buyer == nullptr && Source_bought != nullptr){
            Node_buyer->data->set_team_Players(Node_bought->data->get_team_Players());
            Node_bought->data->set_team_Players(nullptr);
            buy(Node_buyer->data,Node_bought->data);

        }
        else if(Source_buyer != nullptr && Source_bought != nullptr){
            //Assert that both teams have player:
            players->Union(Source_buyer,Source_bought);
            Node_buyer->data->set_points(Node_bought->data->get_points());
            Node_buyer->data->set_team_ability(Node_bought->data->get_team_ability());
            Node_buyer->data->set_goalkeeper(Node_bought->data->get_goalkeeper()); ///New
        }
        //remove from trees:
        teams->set_root(teams->remove(Node_bought->data));
        Node<team>* after_delete_buyer = teams->find(teams->get_root(),*buyer);
        team_by_ability->set_root(team_by_ability->insert(nullptr, team_by_ability->get_root(), after_delete_buyer->data));
        number_of_teams--;

    }
    catch(...){return StatusType::ALLOCATION_ERROR;}

    return StatusType::SUCCESS;
}
