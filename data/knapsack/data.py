import os
import random
import re

root = "F:\\Desktop\\AlgorithmExperiment\\data"
name = "knapsack"
root = os.path.join(root, name)

def find_next_index():
    """
    检查当前目录下所有以 '.in' 结尾的文件，找出最大的数字编号，并返回下一个编号。
    例如，如果存在 1.in, 3.in，将返回 4。
    """
    max_index = 0
    # 正则表达式匹配 '数字.in'
    pattern = re.compile(r"(\d+)\.in$")

    for filename in os.listdir(root):
        match = pattern.match(filename)
        if match:
            current_index = int(match.group(1))
            if current_index > max_index:
                max_index = current_index
    
    return max_index + 1

def knapsack_dp(weights, values, capacity):
    """
    使用动态规划解决0-1背包问题，返回最大价值
    """
    n = len(weights)
    if n == 0 or capacity == 0:
        return 0
    
    dp = [0] * (capacity + 1)
    
    for i in range(n):
        for w in range(capacity, weights[i] - 1, -1):
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i])
    
    return dp[capacity]

def generate_sample(scale_type, current_index):
    """
    生成一个0-1背包问题的测试样例
    scale_type: 表示规模的元组 (capacity, num_items)
    """
    capacity, num_items = scale_type
    in_filename = f"{current_index}.in"
    out_filename = f"{current_index}.out"
    in_filename = os.path.join(root, in_filename)
    out_filename = os.path.join(root, out_filename)
    print(f"正在生成样例: {in_filename} (容量: {capacity}, 物品数: {num_items})...")

    try:
        # 1. 生成随机权重和价值
        weights = []
        values = []
        
        # 根据容量大小调整权重范围，确保有解
        max_weight = max(1, capacity // 2)
        min_weight = max(1, max_weight // 10)
        
        for _ in range(num_items):
            weight = random.randint(min_weight, max_weight)
            value = random.randint(1, 100)  # 价值范围1-100
            weights.append(weight)
            values.append(value)
        
        # 2. 计算最大价值
        max_value = knapsack_dp(weights, values, capacity)
        
        # 3. 写入输入文件 (.in)
        with open(in_filename, 'w') as f_in:
            # 第一行：容量 物品数量
            f_in.write(f"{capacity} {num_items}\n")
            # 后续每行：权重 价值
            for i in range(num_items):
                f_in.write(f"{weights[i]} {values[i]}\n")
        
        # 4. 写入输出文件 (.out)
        with open(out_filename, 'w') as f_out:
            f_out.write(f"{max_value}")
        
        print(f"成功生成文件: {in_filename} 和 {out_filename}")
        print(f"  最大价值: {max_value}")
        
    except Exception as e:
        print(f"生成样例失败: {e}")
        return

def main():
    # 定义需要生成的规模列表，每个元素为 (capacity, num_items)
    SCALES = [
        (10, 5),      # 小规模测试
        (50, 10),     # 小规模测试
        (100, 20),    # 中等规模
        (200, 30),    # 中等规模
        (500, 50),    # 较大规模
        (1000, 100),  # 较大规模
        (2000, 200),  # 大规模
        (5000, 300),  # 大规模
        (10000, 500), # 超大规模
        (20000, 800)  # 超大规模
    ]
    
    # 确保目录存在
    if not os.path.exists(root):
        os.makedirs(root)
        print(f"创建目录: {root}")
    
    current_index = find_next_index()
    
    for scale in SCALES:
        # 对于每个选定的规模，生成一个样例
        generate_sample(scale, current_index)
        current_index += 1

    print("\n所有0-1背包问题的样例生成完毕。")

if __name__ == "__main__":
    main()