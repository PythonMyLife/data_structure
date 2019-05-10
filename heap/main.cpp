#include <iostream>
using namespace std;

template<class Type>
class priorityQueue
{
private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSize();
    void buildHeap();
    void percolateDown(int hole);
public:
    priorityQueue();
    priorityQueue(int capacity);
    priorityQueue(const Type data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
    int findMin(int x);
    int findMinImpl(int x, int i);
    void show();
};

template<class Type>
priorityQueue<Type>::priorityQueue()
{
    array = new Type[10];
    maxSize = 10;
    currentSize = 0;
}

template<class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
    array = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template<class Type>
priorityQueue<Type>::~priorityQueue()
{
    delete []array;
}

template<class Type>
bool priorityQueue<Type>::isEmpty() const
{
    return currentSize == 0;
}

template<class Type>
Type priorityQueue<Type>::getHead() const
{
    return array[1];
}

template<class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
    if(currentSize == maxSize - 1) doubleSize();

    int hole = ++currentSize;
    for(;hole > 1 && x < array[hole/2]; hole /= 2)
        array[hole] = array[hole/2];
    array[hole] = x;
}

template<class Type>
Type priorityQueue<Type>::deQueue()
{
    Type minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}
template<class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
    int child;
    Type tmp = array[hole];

    for(; hole * 2 < currentSize; hole = child){
        child = hole * 2;
        if(child != currentSize && array[child + 1] < array[child])
            child++;
        if(array[child] < tmp) array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
}

template<class Type>
void priorityQueue<Type>::buildHeap()
{
    for(int i = currentSize/2; i > 0; i--)
        percolateDown(i);
}

template<class Type>
priorityQueue<Type>::priorityQueue(const Type *items, int size):maxSize(size + 10), currentSize(size)
{
    array = new Type[maxSize];
    for(int i = 0; i < size; i++){
        array[i + 1] = items[i];
    }
    buildHeap();
}

template<class Type>
void priorityQueue<Type>::doubleSize()
{
    maxSize *= 2;
    Type *newarray = new Type[maxSize];
    for(int i = 1; i <= currentSize; i++){
        newarray[i] = array[i];
    }
    delete []array;
    array = newarray;
}

template<class Type>
void priorityQueue<Type>::show()
{
    cout << "currentsize:" << currentSize <<endl;
    for(int i = 1; i <= currentSize; i++){
        cout << array[i] << ' ';
    }
}

template<class Type>
int priorityQueue<Type>::findMin(int x)
{
    int min = findMinImpl(x, 1);
    cout << "min:" << min << endl;
    for(int i = 1; i <= currentSize; i++){
        if(array[i] == min) return i;
    }
}

template<class Type>
int priorityQueue<Type>::findMinImpl(int x, int i)
{
    if(array[i] > x){
        cout << "get_one:" << array[i] <<endl;
        return array[i];
    }
    if(2 * i > currentSize) return -1;
    if(2 * i == currentSize) return findMinImpl(x, 2*i);
    int tmp1,tmp2;
    tmp1 = findMinImpl(x, 2*i);
    tmp2 = findMinImpl(x, 2*i+1);
    if(tmp1 == -1 && tmp2 != -1) return tmp2;
    if(tmp2 == -1 && tmp1 != -1) return tmp1;
    return (tmp1 > tmp2)?tmp2:tmp1;
}




int main()
{
    int items[] = {3,6,7,12,8,21,14,15,37,18,24,23,33,18,17,26};
    priorityQueue<int> a(items,16);
    a.show();
    cout << '\n' << "find min 9:";
    cout << a.findMin(9)<< endl;
    return 0;
}
