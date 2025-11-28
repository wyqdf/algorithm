#include <bits/stdc++.h>
using namespace std;
#include <filesystem>

#include "../../include/utils.h"
namespace fs = std::filesystem;
string name = "knapsack";
string datapath = BaseData + "\\" + name;

class Solution
{
public:
    // 一维DP
    static int knapsack01_1D(vector<int> &weights, vector<int> &values, int capacity)
    {
        int n = weights.size() - 1;
        vector<int> dp(capacity + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            for (int j = capacity; j >= weights[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
            }
        }
        return dp[capacity];
    }

    // 二维DP
    static int knapsack01_2D(vector<int> &weights, vector<int> &values, int capacity)
    {
        int n = weights.size() - 1;
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= capacity; j++)
            {
                if (j < weights[i]) // 压根装不下物品i
                    dp[i][j] = dp[i - 1][j];
                else // 可以装下，故装与不装两种情况取最大值
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
            }
        }
        return dp[n][capacity];
    }

    // 给方案
    static pair<int, vector<int>> knapsack01WithItems(vector<int> &weights, vector<int> &values, int capacity)
    {
        int n = weights.size() - 1;
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= capacity; j++)
            {
                if (j < weights[i])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
            }
        }

        vector<int> selectedItems;
        int remainingCapacity = capacity;
        for (int i = n; i > 0 && remainingCapacity > 0; i--)
        {
            if (dp[i][remainingCapacity] != dp[i - 1][remainingCapacity])
            // 如果不等，说明dp[i][remainingCapacity],不是直接继承上一个状态，而是是由物品i贡献的。
            {
                selectedItems.push_back(i);
                remainingCapacity -= weights[i]; // 跳到他继承的状态
            }
        }

        reverse(selectedItems.begin(), selectedItems.end());
        return {dp[n][capacity], selectedItems};
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

        int capacity, n;
        vector<int> weights, values;
        int ans;
        int res1, res2;

        iss >> capacity >> n;
        weights.resize(n + 1);
        values.resize(n + 1);

        for (int j = 1; j <= n; j++)
            iss >> weights[j] >> values[j];

        ans_iss >> ans;
        cout << "Case " << i << ":" << endl;

        // 二维DP
        {
            cout << "Algorithm: 二维DP: ";
            Timer timer = Timer();
            res1 = Solution::knapsack01_2D(weights, values, capacity);
        }

        cout << "Input: " << n << " items, capacity " << capacity << endl;
        cout << "Output: " << res1<< endl;

        if (res1 != ans)
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