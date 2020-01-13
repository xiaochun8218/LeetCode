#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node * next;
    Node()
        :data(0)
        ,next(nullptr)
    {
    }
    Node(int val)
        :data(val)
        , next(nullptr)
    {
    }
};

//逆序构造单链表
void descCreatLinkList(Node * header)
{
    Node * pre = nullptr;
    int x = 0;
    while (cin >> x && x != -1)
    {
        Node * cur = new Node;
        cur->data = x;
        cur->next = pre;
        pre = cur;
    }
    header->next = pre;
}

//链表反转
void reverseLinkList(Node * header)
{
    if (header->next == nullptr || header->next->next == nullptr)
    {
        return;
    }

    Node * pre = nullptr;
    Node * cur = header->next;
    while (cur)
    {
        Node * tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    header->next = pre;
}

//链表快排
Node * partion(Node * begin, Node * end)
{
    int key = begin->data;
    Node * i = begin;
    Node * j = begin->next;

    while (j != end)
    {
        if (j->data < key)
        {
            //(i,j)区间的节点的data都是大于等于key的
            i = i->next;
            swap(i->data, j->data);
        }
        j = j->next;
    }
    swap(i->data, begin->data);

    return i;
}

void quickSortLinkList(Node * begin, Node * end)
{
    if (begin == end || begin->next == end)
    {
        return;
    }

    Node * i = partion(begin, end);
    quickSortLinkList(begin, i);
    quickSortLinkList(i->next, end);
}

//合并两个有序链表
Node * mergeLinkList(Node * head1, Node * head2)
{
    Node * headNew = new Node(0);
    Node * r = headNew;

    Node * p = head1->next;
    Node * q = head2->next;
    while (p && q)
    {
        if (p->data <= q->data)
        {
            r->next = p;
            p = p->next;
        }
        else
        {
            r->next = q;
            q = q->next;
        }
        r = r->next;
    }

    if (p)
        r->next = p;
    if (q)
        r->next = q;

    return headNew;
}

//返回链表的倒数第K个节点的值
int lastKNum(Node * head, int k)
{
    if (head == nullptr || head->next == nullptr)
    {
        return -1;
    }
    Node * p = head->next;
    Node * q = head->next;
    for (int i = 0; i < k; i++)
    {
        if (!p)
        {
            cout << "linklist length less then k" << endl;
            return -1;
        }
        p = p->next;
    }

    while (p)
    {
        p = p->next;
        q = q->next;
    }

    return q->data;
}

//链表删除某个值的节点
void delNodeVal(Node* head, int val)
{
    if ( head == nullptr || head->next == nullptr )
        return;
    Node * pre = head;
    Node * p = head->next;
    while (p)
    {
        if (p->data != val)
        {
            pre = p;
            p = p->next;
        }
        else
        {
            pre->next = p->next;
            free(p);
        }
    }
}

//链表删除指定节点pos, 要求平均时间复杂度为 O(1)
//虽然pos是最后一个节点时，时间复杂度为O(n),但pos是其他n-1个节点时，复杂度均为O(1)
//合起来的平均复杂度为：( (n-1)O(1) + O(n) ) / n, 仍然为O(1).
void delNodePos(Node * head, Node * pos)
{
    if (head == nullptr || head->next == nullptr)
        return;

    //如果pos是最后一个节点
    if (pos->next == nullptr)
    {
        Node * p = head;
        while (p->next != pos)
            p = p->next;
        p->next = nullptr;
        free(pos);
    }
    else
    {
        swap(pos->data, pos->next->data);
        pos->next = pos->next->next;
        free(pos->next);
    }
}

//找到链表中的中间节点
Node * findMidNode(Node * head)
{
    if (head == nullptr || head->next == nullptr)
        return nullptr;
    Node * slow = head->next;
    Node * fast = head->next;
    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//判断链表是否有环,如果有环，返回相遇节点
Node * isHaveLoop(Node * head)
{
    if (head == nullptr || head->next == nullptr)
        return nullptr;
    Node * slow = head->next;
    Node * fast = head->next;
    while (fast->next && fast->next->next && fast != slow)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast == slow)
        return slow;
    return nullptr;
}

//在一个有环的链表中找到环的入口节点
//1.找到环中某一节点
//2.计算出环长度n
//3.两个指针找到环入口节点
Node * findLoopEntryNode(Node * head)
{
    Node * meetNode = isHaveLoop(head);
    if (meetNode == nullptr)
        return nullptr;

    int n = 1;
    Node * p = meetNode->next;
    while (p != meetNode)
    {
        n++;
        p = p->next;
    }

    p = head->next;
    Node * q = p;
    for (int i = 0; i < n; i++)
    {
        q = q->next;
    }

    while (q->next)
    {
        if (p == q)
            return p;
        p = p->next;
        q = q->next;
    }

    return nullptr;
}

int main()
{
    return 0;
}