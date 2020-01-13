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

//�����쵥����
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

//����ת
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

//�������
Node * partion(Node * begin, Node * end)
{
    int key = begin->data;
    Node * i = begin;
    Node * j = begin->next;

    while (j != end)
    {
        if (j->data < key)
        {
            //(i,j)����Ľڵ��data���Ǵ��ڵ���key��
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

//�ϲ�������������
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

//��������ĵ�����K���ڵ��ֵ
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

//����ɾ��ĳ��ֵ�Ľڵ�
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

//����ɾ��ָ���ڵ�pos, Ҫ��ƽ��ʱ�临�Ӷ�Ϊ O(1)
//��Ȼpos�����һ���ڵ�ʱ��ʱ�临�Ӷ�ΪO(n),��pos������n-1���ڵ�ʱ�����ӶȾ�ΪO(1)
//��������ƽ�����Ӷ�Ϊ��( (n-1)O(1) + O(n) ) / n, ��ȻΪO(1).
void delNodePos(Node * head, Node * pos)
{
    if (head == nullptr || head->next == nullptr)
        return;

    //���pos�����һ���ڵ�
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

//�ҵ������е��м�ڵ�
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

//�ж������Ƿ��л�,����л������������ڵ�
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

//��һ���л����������ҵ�������ڽڵ�
//1.�ҵ�����ĳһ�ڵ�
//2.�����������n
//3.����ָ���ҵ�����ڽڵ�
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