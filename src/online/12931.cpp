#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    vector<vector<ll>> dp(c + 1, vector<ll>(d + 1, 0));
    dp[0][1] = a;
    dp[0][2] = b;

    for (int k = 3; k <= d; k++)//前俩项和
    {
        dp[0][k] = (dp[0][k - 1]+dp[0][k-2]) % MOD;
    }
        for (int i = 1; i <= c; i++)
        {
            vector<ll> prefix_sum(d + 1, 0);
            for (int j = 1; j <= d; j++)
            {
                prefix_sum[j] = (prefix_sum[j - 1] + dp[i - 1][j]) % MOD;
                dp[i][j] = prefix_sum[j];
            }
        }
    cout << dp[c][d] % MOD << endl;

    

}
}