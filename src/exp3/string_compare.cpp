#include <bits/stdc++.h>
using namespace std;
#include <filesystem>

#include "../../include/utils.h"
namespace fs = std::filesystem;
string name = "string_compare";
string datapath = BaseData + "\\" + name;

class Solution
{
public:
    static int solution(int k, string str1, string str2)
    {
        int n = str1.size(), m = str2.size();
        // int dp[n + 1][m + 1];
        //   memset(dp, 0, sizeof(dp));
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++)
            dp[i][0] = i * k;
        for (int j = 1; j <= m; j++)
            dp[0][j] = j * k;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = min({dp[i - 1][j - 1] + abs(str1[i - 1] - str2[j - 1]),//以俩个非空格结尾
                                dp[i - 1][j] + k,//第一个字符串以字符结尾，第二个以空格
                                dp[i][j - 1] + k});//第一个字符串以空格结尾，第二个以字符结尾
            }
        }
        return dp[n][m];
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

        int k;
        string str1, str2;
        int ans;
        int res;

        iss >> str1 >> str2 >> k;

        ans_iss >> ans;
        cout << "Case " << i << ":" << endl;
        cout << "k:" << k << " str1:" << str1.length() << " str2:" << str2.length() << endl;
        // 二维DP
        {
            cout << "Algorithm: 二维DP: ";
            Timer timer = Timer();
            res = Solution::solution(k, str1, str2);
            cout << "res:" << res << endl;
        }

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
    solve();
    return 0;
}