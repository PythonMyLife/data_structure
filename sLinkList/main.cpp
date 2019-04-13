#include <iostream>
#include "sLinkList.h"

/*template <class elemType>
sLinkList<elemType>::node *sLinkList<elemType>::move(int i) const
{
    node *p = head;
    while(i-- >= 0) p = p->next;
    return p;
}*/

template <class elemType>
sLinkList<elemType>::sLinkList()
{
    head = new node;
    currentLength = 0;
}

template <class elemType>
void sLinkList<elemType>::clear()
{
    node *p = head->next,*q;
    head->next = NULL;
    while(p != NULL){
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

template <class elemType>
void sLinkList<elemType>::insert(int i,const elemType &x)
{
    node *pos;

    pos = move(i - 1);
    pos->next = new node(x,pos->next);
    ++currentLength;
}

template <class elemType>
void sLinkList<elemType>::remove(int i)
{
    node *pos,*delp;

    pos = move(i - 1);
    delp = pos->next;
    pos->next = delp->next; //ÈÆ¹ýdelp
    delete delp;
    --currentLength;
}

template <class elemType>
int sLinkList<elemType>::search(const elemType &x) const
{
    node *p = head->next;
    int i = 0;

    while(p != NULL && p->data != x){p = p->next;++i;}
    if(p ==NULL) return -1;else return i;
}

template <class elemType>
elemType sLinkList<elemType>::visit(int i) const
{
    return move(i)->data;
}

template <class elemType>
void sLinkList<elemType>::traverse()const
{
    node *p = head->next;
    cout <<endl;
    while(p != NULL){
        cout << p->data <<" ";
        p = p->next;
    }
    cout << endl;
}

template <class elemType>
void sLinkList<elemType>::reverse()
{
    node *origin,*q,*r;

    origin = head->next;
    q = r = NULL;

    while(origin)
    {
        q = origin->next;
        origin->next = r;
        r = origin;
        origin = q;
    }
    head->next = r;
}

int main()
{
    sLinkList<int> li = sLinkList<int>();
    li.insert(0,1);
    li.insert(1,2);
    li.insert(2,3);
    li.insert(3,4);
    li.insert(4,5);
    li.traverse();
    li.reverse();
    li.traverse();
    return 0;
}
