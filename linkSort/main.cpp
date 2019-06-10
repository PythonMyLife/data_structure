#include <iostream>
using namespace std;


struct Node {
    int value;
    Node *next;
};

/*void insertSort(int *array, int length)
{
    int i, j;
    Node *head = new Node(), *nextp = new Node(), *tmp = new Node();
    nextp->next = NULL;
    nextp->value = array[0];
    head->next = nextp;
    for(i = 1; i < length; i++){
        Node *newNode = new Node();
        tmp = head;
        newNode->value = array[i];
        while(tmp->next != NULL && tmp->next->value < newNode->value){
            tmp = tmp->next;
        }
        newNode->next = tmp->next;
        tmp->next = newNode;
    }
    nextp = head->next;
    for(j = 0; j < length; j++){
        array[j] = nextp->value;
        nextp = nextp->next;
    }
}*/

Node *insertSort(Node *array)
{
    Node *origin = array;
    Node *head = new Node(), *tmp = new Node(), *nextp = new Node();
    nextp->value = array->value;
    nextp->next = NULL;
    head->next = nextp;
    while((array = array->next) != NULL){
        Node *newNode = new Node();
        tmp = head;
        newNode->value = array->value;
        while(tmp->next != NULL && tmp->next->value < newNode->value){
            tmp = tmp->next;
        }
        newNode->next = tmp->next;
        tmp->next = newNode;
    }
    array = head->next;
    while(origin != NULL){
        Node *p = origin;
        origin = origin->next;
        delete p;
    }
    return array;
}

Node *selectSort(Node *array)
{
    int size = 0;
    Node *origin = array, *o = array;
    Node *head = new Node(), *nextp = head;
    while((array = array->next) != NULL){
        size++;
    }

    for(int i = 0; i < size; i++){
        array = origin->next;
        int min = array->value;
        Node * newNode = new Node();
        while((array = array->next) != NULL){
            min = min < array->value ? min : array->value;
        }
        array = origin->next;
        if(array->value == min){
            origin = origin->next;
        }else{
            while(array->next != NULL){
                if(array->next->value == min){
                    Node *tmp = array->next;
                    array->next = array->next->next;
                    delete tmp;
                    break;
                }
                array = array->next;
            }
        }
        newNode->value = min;
        newNode->next = NULL;
        nextp->next = newNode;
        nextp = nextp->next;
    }
    while(o != NULL){
        Node *tmp = o;
        o = o->next;
        delete o;
    }
    return head;
}

int main()
{
    Node *head = new Node(),
        *a0 = new Node(),
        *a1 = new Node(),
        *a2 = new Node(),
        *a3 = new Node(),
        *a4 = new Node(),
        *a5 = new Node();
    a0->value = 3;
    a1->value = 1;
    a2->value = 2;
    a3->value = 5;
    a4->value = 4;
    a5->value = 0;

    head->next = a0;
    a0->next = a1;
    a1->next = a2;
    a2->next = a3;
    a3->next = a4;
    a4->next = a5;
    a5->next = NULL;
    //head = insertSort(head);
    head = selectSort(head);
    while(head->next != NULL)
    {
        cout << head->next->value << " ";
        head = head->next;
    }
    return 0;

}
