#include <iostream>
using namespace std;

template<class Type>
class set {
    friend set<Type> operator * (const set<Type> &a, const set<Type> &b){
        set<Type> c;
        for(int i = 0; i < a.size; i++){
            if(b.exist(a.elem[i]))
                c.insert(a.elem[i]);
        }
        return c;
    }
    friend set<Type> operator + (const set<Type> &a, const set<Type> &b){
        set<Type> c = a;
        for(int i = 0; i < b.size; i++){
            c.insert(b.elem[i]);
        }
        return c;
    }
    friend set<Type> operator - (const set<Type> &a, const set<Type> &b){
        set<Type> c;
        for(int i = 0; i < a.size; i++){
            if(!b.exist(a.elem[i]))
                c.insert(a.elem[i]);
        }
        return c;
    }

private:
    Type * elem;
    int size, maxSize;
    void doubleSpace();
    bool exist(Type x) const;

public:
    set();
    set(const set <Type> &a);
    ~set() {delete []elem;}

    set &operator= (const set<Type> &a);
    int getSize() {return size;}
    bool insert(Type x);
    bool erase(Type x);
    void display();
};

template <class Type>
set <Type>::set()
{
    size = 0;
    maxSize = 20;
    elem = new Type[maxSize];
}

template <class Type>
set <Type>::set(const set <Type> &a)
{
    size = a.size;
    maxSize = a.maxSize;
    elem = new Type[maxSize];
    for(int i = 0; i < size; i++) elem[i] = a.elem[i];
}

template <class Type>
void set<Type>::doubleSpace()
{
    maxSize *= 2;
    Type * tmp = new Type[maxSize];
    for(int i = 0; i < size; i++)
        tmp[i] = elem[i];
    delete []elem;
    elem = tmp;
}

template <class Type>
bool set<Type>::exist(Type x) const
{
    for(int i = 0; i < size; i++)
        if(elem[i] == x)
            return true;
    return false;
}

template <class Type>
bool set<Type>::insert(Type x)
{
    if (exist(x)) return false;
    if(size == maxSize) doubleSpace();
    elem[size++] = x;
    return true;
}

template <class Type>
bool set<Type>::erase(Type x)
{
    bool flag = false;
    int i;
    for(i = 0; i < size; i++){
        if(elem[i] == x){
            flag = true;
            break;
        }
    }
    if(flag){
        for(;i < size - 1; i++){
            elem[i] = elem[i + 1];
        }
    }
    return flag;
}

template <class Type>
void set<Type>::display()
{
    for(int i = 0; i < size; i++){
        cout << elem[i] << " ";
    }
    cout << endl;
}

template <class Type>
set<Type>& set<Type>::operator = (const set<Type> &a)
{
    size = a.size;
    maxSize = a.maxSize;
    delete []elem;
    elem = new Type[maxSize];
    for(int i = 0; i < size; i++){
        elem[i] = a.elem[i];
    }
    return *this;
}


int main()
{
    set<int> a, b, c;
    a.insert(1);
    a.insert(2);
    b.insert(2);
    b.insert(3);
    cout << "a:";
    a.display();
    cout << "b:";
    b.display();
    c = a + b;
    cout << "a + b:";
    c.display();
    c = a * b;
    cout << "a * b:";
    c.display();
    c = a - b;
    cout << "a - b:";
    c.display();
    return 0;
}
