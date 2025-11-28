#include <filesystem>
using namespace std;
#include <bits/stdc++.h>
#include "../../include/utils.h"
namespace fs = std::filesystem;
string name = "dijkstra";
string datapath = BaseData + "\\" + name;

typedef long long ll;
typedef pair<ll, int> pii;

const int MAXN = 100005;
const ll INF = 1e18;

class Solution
{
public:
    static vector<ll> dijkstra(vector<vector<pii>> &graph, int start, int n)
    {
        vector<ll> dist(n + 1, INF);
        vector<bool> visited(n + 1, false);
        dist[start] = 0;

        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (visited[u])
                continue;
            visited[u] = true;

            for (auto &edge : graph[u])
            {
                int v = edge.first;
                ll weight = edge.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
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

        int n, m, s;
        iss >> n >> m >> s;
        vector<vector<pii>> graph(n + 1);
        vector<ll> res;
        graph.reserve(n + 1);

        int u, v, w;
        while (iss >> u >> v >> w)
        {
            graph[u].emplace_back(v, w);
        }

        string ans_line, res_line;
        getline(ans_iss, ans_line);

        cout << "Case " << i << ":" << endl;
        cout <<"n "<<n<<" m "<<m<<endl;
        {
            Timer timer = Timer();
            res = Solution::dijkstra(graph, s, n);
        }
        

        stringstream ss;
        for (int j = 1; j <= n; j++)
        {
            ss << res[j];
            if (j < n)
                ss << " ";
        }

        res_line = ss.str();
        bool correct = (ans_line == res_line);

        if (!correct)
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
    cin.tie(0)->sync_with_stdio(0);
    solve();
    return 0;
}