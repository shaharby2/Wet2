#ifndef WET1_NODE_H
#define WET1_NODE_H
#include <memory>
using namespace std;
template<class T>

struct Node{
    shared_ptr<T> data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    int height{};
    int rank{};

    explicit Node(){
        this->data = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->height = 0;
        this->rank = 1;
    };

    ~Node(){
    };

};
#endif //WET1_NODE_H
