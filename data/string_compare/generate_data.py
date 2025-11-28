import os
import random
import re
import string

root = r"F:\Desktop\AlgorithmExperiment\data"
name = "string_compare"
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

def generate_sample(scale, current_index):
    in_filename = f"{current_index}.in"
    out_filename = f"{current_index}.out"
    in_filename = os.path.join(root, in_filename)
    out_filename = os.path.join(root, out_filename)

    len1 = random.randint(scale // 2, scale)
    len2 = random.randint(scale // 2, scale)
    
    chars = string.ascii_letters + string.digits
    
    str1 = ''.join(random.choice(chars) for _ in range(len1))
    str2 = ''.join(random.choice(chars) for _ in range(len2))
    
    k = random.randint(1, 100)

    try:
        with open(in_filename, 'w') as f_in:
            f_in.write(f"{str1}\n{str2}\n{k}")
    except Exception as e:
        return

    try:
        result = calculate_string_distance(k, str1, str2)
        
        with open(out_filename, 'w') as f_out:
            f_out.write(str(result))
    except Exception as e:
        return

def calculate_string_distance(k, str1, str2):
    n, m = len(str1), len(str2)
    
    
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    

    for i in range(1, n + 1):
        dp[i][0] = i * k
    for j in range(1, m + 1):
        dp[0][j] = j * k
    
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            replace_cost = dp[i-1][j-1] + abs(ord(str1[i-1]) - ord(str2[j-1]))
            delete_cost1 = dp[i-1][j] + k
            delete_cost2 = dp[i][j-1] + k
            
            dp[i][j] = min(replace_cost, delete_cost1, delete_cost2)
    
    return dp[n][m]

def main():
    SCALES = [10,50, 500, 1000,2000,5000,10000,50000,100000]
    
    current_index = find_next_index()
    
    for scale in SCALES:
        for _ in range(3):
            generate_sample(scale, current_index)
            current_index += 1

if __name__ == "__main__":
    main()