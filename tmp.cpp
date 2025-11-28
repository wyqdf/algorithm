import os import random import re from heapq import heappush, heappop

                                                              root = "F:\\Desktop\\AlgorithmExperiment\\data" name = "dijkstra" root = os.path.join(root, name)

                                                                                                                                                        def find_next_index() :max_index = 0 pattern = re.compile(r "(\d+)\.in$")

                                                                                                                                                                                                                      for filename in os.listdir(root) :match = pattern.match(filename) if match:current_index = int(match.group(1)) if current_index> max_index:max_index = current_index

                                                                                                                                                                                                                                                                                                                     return max_index + 1

                                                                                                                                                                                                                                                                                                                     def dijkstra(graph, start, n) :dist =[float('inf')] *(n + 1)
                                                                                                                                                                                                                                                                                                                                      dist[start] = 0 pq =[(0, start)]

                                                                                                                                                                                                                                                                                                                                                           while pq:d,
                                                                                                                                                                                                                                                                                                                                                           u = heappop(pq) if d> dist[u] : continue for v, w in graph[u] : if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heappush(pq, (dist[v], v))
    
    return dist

def generate_sample(n_size, current_index):
    in_filename = f"{current_index}.in"
    out_filename = f"{current_index}.out"
    in_filename = os.path.join(root, in_filename)
    out_filename = os.path.join(root, out_filename)

    n = n_size
    m = min(n * 3, n * (n - 1) // 2)
    s = 1
    
    edges = []
    graph = [[] for _ in range(n + 1)]
    
    for i in range(1, n):
        u = i
        v = i + 1
        w = random.randint(1, 1000)
        edges.append((u, v, w))
        graph[u].append((v, w))
    
    edge_set = set((u, v) for u, v, w in edges)
    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u != v and (u, v) not in edge_set:
            w = random.randint(1, 1000)
            edges.append((u, v, w))
            edge_set.add((u, v))
            graph[u].append((v, w))
    
    dist = dijkstra(graph, s, n)
    
    with open(in_filename, 'w') as f_in:
        f_in.write(f"{n} {m} {s}\n")
        for u, v, w in edges:
            f_in.write(f"{u} {v} {w}\n")
    
    with open(out_filename, 'w') as f_out:
        result = []
        for i in range(1, n + 1):
            result.append(str(dist[i]))
        f_out.write(" ".join(result))

def main():
    SCALES = [10, 50, 100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000]
    
    if not os.path.exists(root):
        os.makedirs(root)
    
    current_index = find_next_index()
    
    for scale in SCALES:
        generate_sample(scale, current_index)
        current_index += 1

if __name__ == "__main__":
    main()#include <bits/stdc++.h>
                                                                                                                                                                                                                                                                                                                                                                                                               using namespace std;
#include <filesystem>

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
        graph.reserve(n + 1);
        for (int j = 0; j <= n; j++)
        {
            graph[j].reserve(10);
        }

        int u, v, w;
        while (iss >> u >> v >> w)
        {
            graph[u].emplace_back(v, w);
        }

        string ans_line, res_line;
        getline(ans_iss, ans_line);

        cout << "Case " << i << ":" << endl;
        vector<ll> res;
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
    solve();
    return 0;
}
t提高io速度，in文件不用换行，这样就可以直接getline，其他地方严禁修改，其他地方严禁修改，其他地方严禁修改