#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int n;
    while(cin>>n)
    {
        if(n==0) break;
        int res = 0;
        while(n%2==0){
            n /= 2;
            res++;
        }
        cout << (1 << res) << endl;
    }
}