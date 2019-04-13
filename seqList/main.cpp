#include <iostream>
//#include "seq.h"
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

template <class elemType>
class seqList: public list<elemType>
{
    private:
        elemType *data;
        int currentLength;
        int maxSize;
        void doubleSpace();
    public:
        seqList(int initSize = 10);
        ~seqList();
        seqList operator + (const seqList &b);
        void operator = (const seqList &tmp);
        void clear();
        int length() const;
        void insert(int i, const elemType &x);
        void remove(int i);
        int search(const elemType &x) const;
        elemType visit(int i) const;
        void traverse() const;
};

template <class elemType>
seqList<elemType>::~seqList()
{
    delete []data;
}

template <class elemType>
void seqList<elemType>::clear()
{
    currentLength = 0;
}

template <class elemType>
int seqList<elemType>::length() const
{
    return currentLength;
}

template <class elemType>
elemType seqList<elemType>::visit(int i) const
{
    return data[i];
}

template <class elemType>
void seqList<elemType>::traverse() const
{
    cout << endl;
    for(int i = 0; i < currentLength; ++i){
        cout << data[i] << ' ';
    }
}

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
int seqList<elemType>::search(const elemType &x) const
{
    int i;
    for(i = 0; i < currentLength && data[i] != x; ++i);
    if(i == currentLength) return -1;
    else return i;
}

template <class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *tmp = data;

    maxSize *= 2;
    data = new elemType[maxSize];
    for(int i = 0; i < currentLength; ++i)
        data[i] = tmp[i];
    delete []tmp;
}

template <class elemType>
void seqList<elemType>::insert(int i,const elemType &x)
{
    if(currentLength == maxSize)
        doubleSpace();
    for(int j = currentLength; j > i; j--)
        data[j] = data[j - 1];
    data[i] = x;
    ++currentLength;
}

template <class elemType>
void seqList<elemType>::remove(int i)
{
    for(int j = i; j < currentLength - 1; j++)
        data[j] = data[j + 1];
    --currentLength;
}

template <class elemType>
seqList<elemType> seqList<elemType>::operator + (const seqList &b)
{
    int i;
    int newlength = currentLength + b.length();
    seqList c = seqList(newlength);
    for(i = 0; i < currentLength; ++i){
        c.insert(i,data[i]);
    }
    for(; i < newlength; ++i){
        c.insert(i,b.visit(i-currentLength));
    }
    return c;
}

template <class elemType>
void seqList<elemType>::operator = (const seqList<elemType> &tmp)
{
    currentLength = tmp.length();
    maxSize = currentLength;
    delete []data;
    data = new elemType[maxSize];
    for(int i = 0; i < currentLength; ++i)
        data[i] = tmp.visit(i);
}

int main()
{
    seqList<int> a(3),b(4);
    seqList<int> c(0);
    a.insert(0,23);
    a.insert(1,32);
    a.insert(2,45);
    a.traverse();
    cout << endl;
    b.insert(0,77);
    b.insert(1,777);
    b.insert(2,88);
    b.insert(3,888);
    b.traverse();
    cout << endl;
    c = a + b;
    c.traverse();
    return 0;
}
