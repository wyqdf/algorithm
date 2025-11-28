import os
import random
import re
root = "F:\Desktop\AlgorithmExperiment\data"
name = "mergeSort"
root = os.path.join(root, name)
def find_next_index():
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
    in_filename = f"{current_index}.in"
    out_filename = f"{current_index}.out"
    in_filename = os.path.join(root, in_filename)
    out_filename = os.path.join(root, out_filename)

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
        return


    # 4. 写入输出文件 (.out)
    try:
        with open(out_filename, 'w') as f_out:
            # 格式: 最大值 空格 最小值
            random_array.sort()
            f_out.write(" ".join(map(str, random_array)))
    except Exception as e:
        return


def main():
    # 需要生成的规模列表
    #[5,10,50,100,1000,5000,10000,50000,100000,500000] 正数
    SCALES = [5,10,50,100,1000,5000,10000,50000,100000,500000]
    current_index = find_next_index()
    for scale in SCALES:
        generate_sample(scale, current_index)
        current_index += 1

    print("\n所有选定的样例生成完毕。")


if __name__ == "__main__":
    main()