//
// Created by shahar on 24/12/2022.
//

#ifndef WET2_NEW_RANK_NODE_H
#define WET2_NEW_RANK_NODE_H

#include "Node.h"
template<class T>
class Rank_Node: public Node<T>{
    int m_rank;
public:
    explicit Rank_Node(int rank=1): Node<T>() , m_rank(rank) {};
    ~Rank_Node() = default;

};


#endif //WET2_NEW_RANK_NODE_H
