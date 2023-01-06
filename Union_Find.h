//
// Created by idanh on 1/1/2023.
//

#ifndef WET2_NEW_UNION_FIND_H
#define WET2_NEW_UNION_FIND_H

#include "hash_table.h"
class Union_Find
{
    hash_table m_hashed_array;
public:
    Union_Find(int size, int pow);
    ~Union_Find() = default;
    Node<player>* Find (int player_id);
    Node<player>* Union (Node<player>* group1, Node<player>* group2);
    hash_table get_hashed_array() const;
};

#endif //WET2_NEW_UNION_FIND_H
