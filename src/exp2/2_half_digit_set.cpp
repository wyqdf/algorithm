#include <bits/stdc++.h>
using namespace std;
#include <filesystem>

#include "../../include/utils.h"
namespace fs = std::filesystem;
string BaseData = R"(F:\Desktop\AlgorithmExperiment\data)";
string name = "half_digit_set";
string datapath = BaseData + "\\" + name;
vector<long long> memo(1000000, -1);
class Solution // dfs+记忆化搜索
{
public:
    static long long solve(int n)
    {
        if (memo[n] != -1) // 记忆化，减少重复递归。
            return memo[n];
        long long sum = 1;
        for (int i = 1; i <= n / 2; i++)
        {
            // 在n左边添加i的情况数为solve（i）
            // 因为对于i可以以同样的规则向左添加数字，相当于又一个半数集问题。
            sum += solve(i);
        }
        memo[n] = sum; // 记忆化
        return sum;
    }
};
class Solution2 // 动态规划dp+前缀和数组
{
public:
    static long long solve(int n)
    {
        vector<long long> dp(n + 1, 0);
        vector<long long> prefixSum(n + 1, 0); // 前缀和数组

        for (int i = 1; i <= n; i++)
        {
            dp[i] = prefixSum[i / 2] + 1;            // dp[i]等于前缀和数组在i/2位置的值
            prefixSum[i] = prefixSum[i - 1] + dp[i]; // 更新前缀和数组
        }

        return dp[n];
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

        long long n, res, ans;

        iss >> n;
        ans_iss >> ans;
        cout << "Case " << i << ":" << endl;

        {
            Timer timer = Timer();
            res = Solution2::solve(n);
        }
        cout << "input n: " << n << endl;
        cout << "Expected Answer: " << ans << endl;
        cout << "Computed Answer: " << res << endl;
        if (res != ans)
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
    memo[1] = 1;
    solve();
    return 0;
}