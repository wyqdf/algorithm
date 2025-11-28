import os
import random
import re
from heapq import heappush, heappop

root = "F:\\Desktop\\AlgorithmExperiment\\data"
name = "dijkstra"
root = os.path.join(root, name)

def find_next_index():
    max_index = 0
    pattern = re.compile(r"(\d+)\.in$")

    for filename in os.listdir(root):
        match = pattern.match(filename)
        if match:
            current_index = int(match.group(1))
            if current_index > max_index:
                max_index = current_index
    
    return max_index + 1

def dijkstra(graph, start, n):
    dist = [float('inf')] * (n + 1)
    dist[start] = 0
    pq = [(0, start)]
    
    while pq:
        d, u = heappop(pq)
        if d > dist[u]:
            continue
        for v, w in graph[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heappush(pq, (dist[v], v))
    
    return dist

def generate_sample(n_size, current_index):
    in_filename = f"{current_index}.in"
    out_filename = f"{current_index}.out"
    in_filename = os.path.join(root, in_filename)
    out_filename = os.path.join(root, out_filename)

    n = n_size
    m = min(random.randint(int(n*1.6),n*3), n * (n - 1) // 2)
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
    SCALES = [10, 50, 100, 500, 1000, 2000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000]
    
    if not os.path.exists(root):
        os.makedirs(root)
    
    current_index = find_next_index()
    
    for scale in SCALES:
        generate_sample(scale, current_index)
        current_index += 1

if __name__ == "__main__":
    main()