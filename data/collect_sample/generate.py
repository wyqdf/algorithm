import os
import random
import re

root = "F:\\Desktop\\AlgorithmExperiment\\data"
name = "collect_sample"
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

def generate_sample(n_size, current_index):
    in_filename = f"{current_index}.in"
    out_filename = f"{current_index}.out"
    in_filename = os.path.join(root, in_filename)
    out_filename = os.path.join(root, out_filename)

    n = n_size
    m = [[0] * (n + 1) for _ in range(n + 1)]
    
    points_count = random.randint(n, min(n * n, 1000))
    positions = set()
    
    for _ in range(points_count):
        x = random.randint(1, n)
        y = random.randint(1, n)
        if (x, y) not in positions:
            v = random.randint(1, 100)
            m[x][y] = v
            positions.add((x, y))
    
    max_value = calculate_max_value(m, n)
    
    with open(in_filename, 'w') as f_in:
        f_in.write(f"{n}\n")
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if m[i][j] > 0:
                    f_in.write(f"{i} {j} {m[i][j]}\n")
        f_in.write("0 0 0\n")
    
    with open(out_filename, 'w') as f_out:
        f_out.write(f"{max_value}")

def calculate_max_value(m, n):
    dp = [[[0] * (n + 2) for _ in range(n + 2)] for _ in range(n * 2 + 2)]
    dp[2][1][1] = m[1][1]
    
    for s in range(3, n * 2 + 1):
        for x1 in range(1, n + 1):
            for x2 in range(1, n + 1):
                y1 = s - x1
                y2 = s - x2
                if 1 <= y1 <= n and 1 <= y2 <= n:
                    dp[s][x1][x2] = max(
                        dp[s - 1][x1 - 1][x2 - 1],
                        dp[s - 1][x1 - 1][x2],
                        dp[s - 1][x1][x2 - 1],
                        dp[s - 1][x1][x2]
                    ) + m[x1][y1] + m[x2][y2]
                    if x1 == x2:
                        dp[s][x1][x2] -= m[x1][y1]
    
    return dp[n * 2][n][n]

def main():
    SCALES = [5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100]
    
    if not os.path.exists(root):
        os.makedirs(root)
    
    current_index = find_next_index()
    
    for scale in SCALES:
        generate_sample(scale, current_index)
        current_index += 1

if __name__ == "__main__":
    main()