#ifndef SLINKLIST_H_INCLUDED
#define SLINKLIST_H_INCLUDED

#include <iostream>
using namespace std;

template <class elemType>
class list
{
    public:
        virtual void clear()=0;
        virtual int length() const = 0;
        virtual void insert(int i,const elemType &x)=0;
        virtual void remove(int i)=0;
        virtual int search(const elemType &x) const = 0;
        virtual elemType visit(int i) const = 0;
        virtual void traverse() const = 0;
        virtual ~list() {};
};

template<class elemType>
class sLinkList: public list<elemType>
{
    private:
        struct node {
            elemType data;
            node *next;

            node(const elemType &x,node *n = NULL)
                {data = x; next = n;}
            node():next(NULL){}
            ~node(){}
        };

        node *head;
        int currentLength;

        node *move(int i) const
        {
            node *p = head;
            while(i-- >= 0) p = p->next;
            return p;
        } //返回第i个结点的地址

    public:
        sLinkList();
        ~sLinkList(){clear(); delete head;}

        void clear();
        int length() const {return currentLength;}
        void insert(int i, const elemType &x);
        void remove(int i);
        int search(const elemType &x) const;
        elemType visit(int i) const;
        void traverse() const;
        void reverse();
};


#endif // SLINKLIST_H_INCLUDED
