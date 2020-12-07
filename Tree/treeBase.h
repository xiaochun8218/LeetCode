#pragma once
#include <iostream>

struct Node
{
    char data;
    Node *left, *right;
};

class BiTree
{
public:
    Node *root;
    BiTree();
    Node* create();
    void pre_order_rec(Node *node);
    void pre_order_non_rec();
    void in_order_rec(Node *node);
    void in_order_non_rec();
    void post_order_rec(Node *node);
    void post_order_non_rec();
    void level_order();
};
