#include "treeBase.h"
#include <stack>
#include <queue>
using namespace std;

BiTree::BiTree()
{
    root = create();
}

Node* BiTree::create()
{
    Node *p = nullptr;
    char ch;
    cin >> ch;
    if (ch == '.')
    {
        p = nullptr;
    }
    else
    {
        p = new Node;
        p->data = ch;
        p->left = create();
        p->right = create();
    }

    return p;
}

void BiTree::pre_order_rec(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        cout << node->data << endl;
        pre_order_rec(node->left);
        pre_order_rec(node->right);
    }
}

void BiTree::pre_order_non_rec()
{
    stack<Node*> S;
    Node *p = root;

    while (p || !S.empty())
    {
        while (p)
        {
            cout << p->data << endl;
            S.push(p);
            p = p->left;
        }

        if (!S.empty())
        {
            p = S.top()->right;
            S.pop();
        }
    }
}

void BiTree::in_order_rec(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        in_order_rec(node->left);
        cout << node->data << endl;
        in_order_rec(node->right);
    }
}

void BiTree::in_order_non_rec()
{
    stack<Node*> S;
    Node *p = root;
    while (p || !S.empty())
    {
        while (p)
        {
            S.push(p);
            p = p->left;
        }

        if (!S.empty())
        {
            p = S.top();
            cout << p->data << endl;
            p = p->right;
            S.pop();
        }
    }
}

void BiTree::post_order_rec(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        post_order_rec(node->left);
        post_order_rec(node->right);
        cout << node->data << endl;
    }
}

void BiTree::post_order_non_rec()
{
    if (root == nullptr)
    {
        return;
    }

    stack<Node*> S;
    Node *pre = nullptr;
    Node *cur = root;
    S.push(cur);

    while (!S.empty())
    {
        cur = S.top();
        if ( (cur->left == nullptr && cur->right == nullptr)
            || (pre && (pre == cur->left || pre == cur->right)) )
        {//当前节点没有左右子树，或者左右子树均已输出
            cout << cur->data << endl;
            pre = cur;
            S.pop();
        }
        else
        {
            //先进后出，先压栈右子树
            if (cur->right)
            {
                S.push(cur->right);
            }
            if (cur->left)
            {
                S.push(cur->left);
            }
        }
    }
}

void BiTree::level_order()
{
    if (root == nullptr)
    {
        return;
    }

    queue<Node*> Q;
    Node * p = root;
    Q.push(p);

    while (!Q.empty())
    {
        p = Q.front();
        cout << p->data << endl;
        Q.pop();

        if (p->left)
        {
            Q.push(p->left);
        }
        if (p->right)
        {
            Q.push(p->right);
        }
    }
}