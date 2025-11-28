#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int n, S;
    cin >> n >> S;

    vector<int> t(n + 1), f(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> t[i] >> f[i];

    vector<int> dp(n + 2, 0); // dp[i]表示从第i个任务开始到最后的最小费用
    vector<int> c(n + 2, 0);// 记录选择的批处理结束位置
    vector<int> sumT(n + 2, 0); // 后缀和数组
    vector<int> sumF(n + 2, 0);// 后缀和数组
    //sumT[i]表示从第i个任务到第n个任务的处理时间之和
    //sumF[i]表示从第i个任务到第n个任务的费用之和

    // 计算后缀和
    for (int i = n; i >= 1; i--)
    {
        sumT[i] = t[i] + sumT[i + 1];
        sumF[i] = f[i] + sumF[i + 1];
    }

    dp[n + 1] = 0;

    // 从后往前动态规划
    for (int i = n; i >= 1; i--)
    {
        dp[i] = INT_MAX;
        for (int j = i; j <= n; j++) //[i, j]作为一个批处理
        {
            // 计算从i到j的处理时间之和
            int currentBatchTime = sumT[i] - sumT[j + 1];
            int cost = dp[j + 1] + (S + currentBatchTime) * sumF[i];//[j+1,n]的费用与在前面添加[i,j]的费用之和

            if (cost < dp[i])//更新最小费用
            {
                dp[i] = cost;
                c[i] = j; // 记录以i开头的批处理结束位置
            }
        }
    }

    // 输出最小费用
    cout << dp[1] << endl;

    // 构造并输出最优批处理方案
    int i = 1;
    while (i <= n)
    {
        int j = c[i];
        printf("[%d,%d]\n", i, j);
        i = j + 1;
    }

    return 0;
}