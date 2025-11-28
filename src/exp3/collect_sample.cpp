#include <bits/stdc++.h>
using namespace std;
#include <filesystem>

#include "../../include/utils.h"
namespace fs = std::filesystem;
string name = "collect_sample";
string datapath = BaseData + "\\" + name;
const int MAX_N = 100;
int dp[MAX_N+2][MAX_N+2][MAX_N+2][MAX_N+2];
int optimiezed_dp[(MAX_N+2)*2][MAX_N+2][MAX_N+2];
bool visited[20][20][20][20];
int direction[4][4] = {{1,0,1,0},{1,0,0,1},{0,1,1,0},{0,1,0,1}};
class Solution
{
public:
    static int solution(vector<vector<int>> &m)//dp，m[x1][y1][x1][y2]表示俩机器人走到俩个点p1,p2时价值之和
    {
        int n = m.size()-1;
        memset(dp, 0, sizeof(dp));
        dp[1][1][1][1] = m[1][1];
        for(int s= 3; s <= n*2; s++)
        {
            //确定边界防止越界
            int L = max(1, s - n);
            int R = min(n, s - 1);
            for (int x1 = L; x1 <= R; x1++)
            {
                for(int x2 = L; x2 <= R; x2++)
                {   
                    //取4个子问题的最优质，合并得到问题最优解
                    //俩个机器人分别有俩个子状态，组合得到4个子状态，即走s-1个格子,取最大值
                    int y1 = s-x1;
                    int y2 = s-x2;
                    dp[x1][y1][x2][y2] =
                                max({
                                    dp[x1-1][y1][x2-1][y2],
                                    dp[x1][y1-1][x2-1][y2],
                                    dp[x1-1][y1][x2][y2-1],
                                    dp[x1][y1-1][x2][y2-1]
                                    })
                                     +m[x1][y1]+m[x2][y2];

                    if(x1 == x2) dp[x1][y1][x2][y2] -= m[x1][y1];//减去重复的格子
                }
            }
        }
        return dp[n][n][n][n];
    }
    static int solution1(vector<vector<int>> m)//bfs，dp方法第一层是从小到大历遍步长s，这种思想也可以用bfs实现
    {
        int n = m.size()-1;
        memset(dp, 0, sizeof(dp));
        memset(visited, 0, sizeof(visited));
        deque<vector<int>> q;
        q.push_back({1,1,1,1});
        while(!q.empty())
        {
            auto t = q.front();
            q.pop_front();
            int x1 = t[0],y1 = t[1],x2 = t[2],y2 = t[3];
            for(int i = 0; i < 4; i++)//俩个机器人各有俩种方向选择，合起来下一步有4个可能。
            {
                int nx1 = x1+direction[i][0];
                int ny1 = y1+direction[i][1];
                int nx2 = x2+direction[i][2];
                int ny2 = y2+direction[i][3];

                if(nx1>n || nx2>n || ny1>n || ny2>n||nx1<1||ny1<1||nx2<1||ny2<1)
                    continue;//
                if(!visited[nx1][ny1][nx2][ny2])
                {
                    visited[nx1][ny1][nx2][ny2] = true;
                    q.push_back({nx1,ny1,nx2,ny2});
                }

                dp[nx1][ny1][nx2][ny2] = max(dp[nx1][ny1][nx2][ny2],
                                             dp[x1][y1][x2][y2]+m[nx1][ny1]+m[nx2][ny2]
                                             - (x1==x2?m[x1][y1]:0));//若从当前状态到下一状态的价值大于，下一状态的原价值则更新
            }
        }
        return dp[n][n][n][n];
    }
    static int solution2(vector<vector<int>> m)
    //dp空间优化，注意到状态x1,y1,x2,y2，中y1，y2可由x1,x2与步长s得到
    //故状态可用s，x1,x2表示,由4维变为3维，节省空间。
    //递推方程不变
    {
        int n = m.size() - 1;
        memset(optimiezed_dp, 0, sizeof(optimiezed_dp));
        optimiezed_dp[2][1][1] = m[1][1];
        for (int s = 3; s <= n * 2; s++)
        {
            int L = max(1, s - n);
            int R = min(n, s - 1);
            for (int x1 = L; x1 <= R; x1++)
            {
                for (int x2 = L; x2 <= R; x2++)
                {   
                    int y1 = s - x1;
                    int y2 = s - x2;
                    optimiezed_dp[s][x1][x2] =
                        max({optimiezed_dp[s-1][x1 - 1][x2 - 1],
                             optimiezed_dp[s-1][x1][x2 - 1],
                             optimiezed_dp[s-1][x1 - 1][x2],
                             optimiezed_dp[s-1][x1][x2]}) +
                        m[x1][y1] + m[x2][y2];

                    if (x1 == x2)
                        optimiezed_dp[s][x1][x2] -= m[x1][y1];
                }
            }
        }
        return optimiezed_dp[n*2][n][n];
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

        //定义数据结构
        int n,ans,res;
        iss >> n;
        vector<vector<int>> m(n+1,vector<int>(n+1,0));

        int x, y, v;
        while(iss >> x >> y >> v) 
        {
            if(x==0 && y==0 && v==0)
                break;
            m[x][y] = v;
        }


        ans_iss >> ans;
        cout << "Case " << i << ":" << endl;
        cout << "size" << n << endl;
        // 二维DP
        {
            Timer timer = Timer();
            res = Solution::solution(m);
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