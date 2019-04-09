#include <iostream>
//最坏情况下有n/2+2次比较
//该程序的时间复杂度为O(n)
using namespace std;

bool prime(int n)
{
    if(n <= 1) return false;
    if(n <= 3) return true;
    int mid = n/2;
    for(int i = 2;i <= mid;i++)
    {
        if(n % i == 0) return false;
    }
    return true;
}

int main()
{
    int n;
    cout << "please input the number you want to test!" << endl;
    cin >> n;
    if(prime(n)) cout << "The number is a prime." << endl;
    else cout << "The number is not a prime." << endl;
    return 0;
}

