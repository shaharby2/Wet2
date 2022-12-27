//
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #1.
//
// Recommended TAB size to view this file: 8.
//
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
//


#include "worldcup23a2.h"
#include <string>
#include "team.h"

using namespace std;


int main()
{
    AVL<team>* a = new AVL<team>(compare_team_id);
    shared_ptr<team> added_team(new team(1, 1));
    shared_ptr<team> added_team1(new team(3, 1));
    shared_ptr<team> added_team2(new team(2, 1));
    shared_ptr<team> added_team3(new team(7, 1));
    shared_ptr<team> added_team4(new team(1, 1));
    shared_ptr<team> added_team5(new team(5, 1));
    shared_ptr<team> added_team6(new team(1, 1));
    shared_ptr<team> added_team7(new team(1, 1));
    shared_ptr<team> added_team8(new team(1, 1));
    shared_ptr<team> added_team9(new team(10, 1));
    shared_ptr<team> added_teama(new team(1, 1));
    shared_ptr<team> added_teamb(new team(14, 1));
    shared_ptr<team> added_teamc(new team(1, 1));
    shared_ptr<team> added_teamd(new team(13, 1));
    shared_ptr<team> added_teame(new team(1, 1));
    shared_ptr<team> added_teamf(new team(1, 1));
    shared_ptr<team> added_teamg(new team(11, 1));
    shared_ptr<team> added_teamh(new team(1, 1));
    shared_ptr<team> added_teami(new team(10, 1));

    a->set_root(a->insert(nullptr, a->get_root(),added_team));
    a->set_root(a->insert(nullptr, a->get_root(),added_team1));
    a->set_root(a->insert(nullptr, a->get_root(),added_team2));
    a->set_root(a->insert(nullptr, a->get_root(),added_team3));
    a->set_root(a->insert(nullptr, a->get_root(),added_team4));
    a->set_root(a->insert(nullptr, a->get_root(),added_team5));
    a->set_root(a->insert(nullptr, a->get_root(),added_team6));
    a->set_root(a->insert(nullptr, a->get_root(),added_team7));
    a->set_root(a->insert(nullptr, a->get_root(),added_team8));
    a->set_root(a->insert(nullptr, a->get_root(),added_team9));
    a->set_root(a->insert(nullptr, a->get_root(),added_teama));
    a->set_root(a->insert(nullptr, a->get_root(),added_teamb));
    a->set_root(a->insert(nullptr, a->get_root(),added_teamc));
    a->set_root(a->insert(nullptr, a->get_root(),added_teamd));
    a->set_root(a->insert(nullptr, a->get_root(),added_teame));
    a->set_root(a->insert(nullptr, a->get_root(),added_teamf));
    a->set_root(a->insert(nullptr, a->get_root(),added_teamg));
    a->set_root(a->insert(nullptr, a->get_root(),added_teamh));
    a->set_root(a->insert(nullptr, a->get_root(),added_teami));


    a->print2D(a->get_root());
    return 0;
}



/*
#include "worldcup23a2.h"
#include <string>
#include <iostream>

using namespace std;

istream& operator>>(istream &in, permutation_t &obj)
{
    string str;
    in >> str;
    obj = permutation_t::read(str.c_str());
    return in;
}

void print(string cmd, StatusType res);

template<typename T>
void print(string cmd, output_t<T> res);

int main()
{
    cin >> std::boolalpha;

    int pid, tid, tid2;
    int d1, d2, d3;
    permutation_t p1;
    bool b1;

    // Init
    world_cup_t *obj = new world_cup_t();

    // Execute all commands in file
    string op;
    while (cin >> op)
    {
        if (!op.compare("add_team"))
        {
            cin >> tid;
            print(op, obj->add_team(tid));
        }
        else if (!op.compare("remove_team"))
        {
            cin >> tid;
            print(op, obj->remove_team(tid));
        }
        else if (!op.compare("add_player"))
        {
            cin >> pid >> tid >> p1 >> d1 >> d2 >> d3 >> b1;
            print(op, obj->add_player(pid, tid, p1, d1, d2, d3, b1));
        }
        else if (!op.compare("play_match"))
        {
            cin >> tid >> tid2;
            print(op, obj->play_match(tid, tid2));
        }
        else if(!op.compare("num_played_games_for_player"))
        {
            cin >> pid;
            print(op, obj->num_played_games_for_player(pid));
        }
        else if(!op.compare("add_player_cards"))
        {
            cin >> pid >> d1;
            print(op, obj->add_player_cards(pid, d1));
        }
        else if(!op.compare("get_player_cards"))
        {
            cin >> pid;
            print(op, obj->get_player_cards(pid));
        }
        else if(!op.compare("get_team_points"))
        {
            cin >> tid;
            print(op, obj->get_team_points(tid));
        }
        else if(!op.compare("get_ith_pointless_ability"))
        {
            cin >> d1;
            print(op, obj->get_ith_pointless_ability(d1));
        }
        else if(!op.compare("get_partial_spirit"))
        {
            cin >> pid;
            print(op, obj->get_partial_spirit(pid));
        }
        else if(!op.compare("buy_team"))
        {
            cin >> tid >> tid2;
            print(op, obj->buy_team(tid, tid2));
        }
        else
        {
            cout << "Unknown command: " << op << endl;
            return -1;
        }

        // Verify no faults
        if (cin.fail())
        {
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit
    delete obj;
    return 0;
}

// Helpers
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

template<typename T>
void print(string cmd, output_t<T> res)
{
    if (res.status() == StatusType::SUCCESS)
    {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    }
    else
    {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}
*/