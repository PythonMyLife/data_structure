#include <iostream>
#include <stdlib.h>

using namespace std;

template <class elemType>
class queue
{
public:
    virtual bool isEmpty() = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() = 0;
    virtual ~queue(){}
};

template <class elemType>
class seqQueue:public queue<elemType>
{
private:
    elemType *elem;
    int maxSize;
    int front,rear;

    void doubleSpace();

public:
    seqQueue(int size = 10);
    ~seqQueue();
    bool isEmpty();
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead();
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size)
{
    elem = new elemType[size];
    maxSize = size;
    front = rear = 0;
}

template <class elemType>
seqQueue<elemType>::~seqQueue()
{
    delete []elem;
}

template<class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
    if ((rear + 1) % maxSize == front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    for(int i = 1; i < maxSize; ++i)
        elem[i] = tmp[(front + i) % maxSize];

    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    delete tmp;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

template <class elemType>
elemType seqQueue<elemType>::getHead()
{
    return elem[(front + 1) % maxSize];
}

template <class elemType>
bool seqQueue<elemType>::isEmpty()
{
    return (front == rear);
}



int main()
{
    seqQueue<int> k(10);
    seqQueue<int> h(10);
    int k_min,k_max,k_num;
    cout << "请输入客车间隔的最小和最大时间：";
    cin >> k_min >> k_max;
    int h_min,h_max,h_num;
    cout << "请输入货车间隔的最小和最大时间：";
    cin >> h_min >> h_max;
    cout << "请输入客车总数：";
    cin >> k_num;
    cout << "请输入货车总数：";
    cin >> h_num;

    int tmp;
    for(tmp = k_num; tmp > 0; --tmp){
        k.enQueue((rand()%(k_max - k_min +1) + k_min));
    }
    for(tmp = h_num; tmp > 0; --tmp){
        h.enQueue((rand()%(h_max - h_min +1) + h_min));
    }
    int k_total = 0,h_total = 0,k_time = 0,h_time = 0,space;
    while(!k.isEmpty() || !h.isEmpty()){
        k_time += 10;
        h_time += 10;
        space = 10;
        if(!k.isEmpty()) k_total += 10;
        if(!h.isEmpty()) h_total += 10;
        for (int i = 0;i < 8; ++i){
            if ((!k.isEmpty()) && (k.getHead() < k_time)){
                k_time -= k.deQueue();
                space--;
            }
        }
        while((space > 0) && (!h.isEmpty()) && (h_time - h.getHead() >= 0)){
            h_time -= h.deQueue();
            space--;
        }

        while((space > 0) && (!k.isEmpty()) && (k_time - k.getHead() >= 0)){
            k_time -= k.deQueue();
            space--;
        }
    }
    cout << "客车的平均等待时间是：" << (k_total / k_num) << endl;
    cout << "货车的平均等待时间是：" << (h_total / h_num) << endl;
    return 0;
}
