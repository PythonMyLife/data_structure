#include <iostream>
using namespace std;

template <class Type>
void binarySort(Type *array, int length)
{
    for(int i = 1; i < length; i++){
        Type tmp = array[i];
        int j = 0, k = i - 1, mid, pos;
        while(j < k){
            mid = (j + k)/2;
            if(tmp == array[mid]){
                pos = mid;
                break;
            }else if(tmp <= array[mid]){
                k = mid - 1;
            }else {
                j = mid + 1;
            }
        }
        pos = array[j] < tmp ? (j + 1):j;

        for(int l = i; l > pos; l--){
            array[l] = array[l - 1];
        }
        array[pos] = tmp;
    }
}

int main()
{
    int array[] = {1,2,4,9,5,3,6,7,8,0};
    int length = 10;
    binarySort(array, length);
    for(int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    return 0;
}
