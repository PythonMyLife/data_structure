#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED
#include <iostream>
using namespace std;

template <class elemType>
class queue
{
public:
    virtual bool isEmpty() const = 0;            //判队空
    virtual void enQueue(const elemType &x) = 0; //进队
    virtual elemType  deQueue() = 0;             //出队
    virtual elemType getHead() const = 0;        //读队头元素
    virtual ~queue() {}                          //虚析构函数
};

template <class elemType>
class linkQueue: public queue<elemType>
 {
private:
    struct node {
        elemType  data;
        node *next;
        node(const elemType &x, node *N = NULL){data = x; next = N;}
        node():next(NULL) {}
        ~node() {}
	};
	node *front, *rear;
public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue(const elemType &x);
    elemType deQueue() ;
    elemType getHead() const;
};

template <class elemType>
linkQueue<elemType>::linkQueue()
{
   front = rear = NULL;
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear == NULL)
   	     front = rear = new node(x);
    else
	     rear = rear->next = new node(x);
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = front;
    elemType value = front->data;
    front = front->next;
    if (front == NULL) rear = NULL;
    delete tmp;
    return value;
}

template <class elemType>
bool linkQueue<elemType>::isEmpty() const
{
     return front == NULL;
}

template <class elemType>
elemType linkQueue<elemType>::getHead() const
{
     return front->data;
}


template <class elemType>
linkQueue<elemType>::~linkQueue()
{
	   node *tmp;
	   while (front != NULL) {
		      tmp = front;
		      front = front->next;
		      delete tmp;
	   }
}





#endif // LINKQUEUE_H_INCLUDED
