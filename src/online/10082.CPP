#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n, k;
    while(cin>>n>>k)
    {
        cout << (n/(k-1))*k +(n%(k-1)==0?-1:n%(k-1)) << endl;
    }
}