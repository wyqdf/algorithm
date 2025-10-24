import os
import random
import re
root = "F:\Desktop\AlgorithmExperiment\data\maxAndmin"
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

def generate_sample(scale, current_index):
    """
    生成一个规模为 scale 的随机数组作为输入文件 (N.in)，
    并计算最大最小值作为输出文件 (N.out)。
    """
    in_filename = f"{current_index}.in"
    out_filename = f"{current_index}.out"
    in_filename = os.path.join(root, in_filename)
    out_filename = os.path.join(root, out_filename)
    print(f"正在生成样例: {in_filename} (规模: {scale})...")

    # 1. 生成随机数组
    random_array = []
    # 随机数的范围设定在 [0, 1000000)
    for _ in range(scale):
        random_array.append(random.randint(-100000000, 100000000 - 1))

    # 2. 写入输入文件 (.in)
    try:
        with open(in_filename, 'w') as f_in:
            # 将数组元素以空格分隔的形式写入文件
            f_in.write(" ".join(map(str, random_array)))
    except Exception as e:
        print(f"写入文件 {in_filename} 失败: {e}")
        return

    # 3. 计算最大值和最小值
    max_val = max(random_array)
    min_val = min(random_array)

    # 4. 写入输出文件 (.out)
    try:
        with open(out_filename, 'w') as f_out:
            # 格式: 最大值 空格 最小值
            f_out.write(f"{max_val} {min_val}\n")
    except Exception as e:
        print(f"写入文件 {out_filename} 失败: {e}")
        return

    print(f"成功生成文件: {in_filename} 和 {out_filename}")


def main():
    # 定义需要生成的规模列表
    #[5,10,50,100,1000,5000,10000,50000,100000,500000] 正数
    SCALES = [10000,50000,100000,500000]
    current_index = find_next_index()
    for scale in SCALES:
        # 对于每个选定的规模，生成一个样例
        generate_sample(scale, current_index)
        current_index += 1

    print("\n所有选定的样例生成完毕。")


if __name__ == "__main__":
    main()