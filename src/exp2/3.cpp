#include <bits/stdc++.h>
using namespace std;
#include <filesystem>

#include "../../include/utils.h"
namespace fs = std::filesystem;
string BaseData = R"(F:\Desktop\AlgorithmExperiment\data)";
string name = "half_set";
string datapath = BaseData + "\\" + name;
class Solution
{
public:
    static long long solve(int n)
    {
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
        dp[1][1] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i][1] = 1;
            for (int j = 2; j <= i; j++)
            {
                if (i < j)  //集合元素个数小于划分个数，故方案数为默认值0；
                    break;
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] * j);
                //dp[i-1][j-1]：将i单独划为一个集合，再将其余i-1个元素划分为j-1个集合
                //dp[i-1][j]*j：先将除i外的元素划分为j个集合，再将i加入到这j个集合中的任意一个，有j种选择。
            }
        }
        long long sum = 0;
        for (int i = 1; i <= n; i++)
            sum += dp[n][i];//结果为所有划分方法数之和
        return sum;
    }
};

void solve()
{
    for (int i = 1; i < 100; i++)
    {
        if (!fs::exists(datapath + "\\" + to_string(i) + ".in"))
            break;

        istringstream iss = load_in(i, datapath);
        istringstream ans_iss = load_out(i, datapath);

        long long n, res,ans;

        iss >> n;
        ans_iss >> ans;
        cout << "Case " << i << ":" << endl;
   
        // 二维DP
        {
            Timer timer = Timer();
            res = Solution::solve(n);
        }
        cout<<"input n: "<<n<<endl;
        cout << "Expected Answer: " << ans << endl;
        cout << "Computed Answer: " << res << endl;
        if (res!= ans )
        {
            cout << "\033[31mWrong Answer\033[0m" << endl;
        }
        else
        {
            cout << "\033[32mAccepted\033[0m" << endl;
        }
        cout << "________________________________________________________" << endl;
    }
}

int main()
{
    solve();
    return 0;
}