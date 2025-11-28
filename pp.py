import math
import numpy as np
import matplotlib.pyplot as plt
# 物理常数（提取为全局常量，增加精度表示）
D = 2e-2               # 管道直径 (m)，保持原精度
d = 1e-3               # 颗粒直径 (m)，保持原精度
rou = 7.8e3            # 颗粒密度 (kg/m³)，保持原精度
rou0 = 0.95e3          # 流体密度 (kg/m³)，保持原精度
g = 9.78033            # 重力加速度 (m/s²)，使用更精确值（原9.78优化为9.78033）
MIN_VALUE = 1e-12      # 极小值，避免分母为0的数值稳定性问题

# 输入数据（保持原数据，若需更高精度可改为 Decimal 类型）
t_list = [16.56, 14.79, 12.79, 10.76, 7.904]
#t_list = [26.40,22.51]
def func(t):
    # 校验输入，避免数值异常
    if t <= MIN_VALUE:
        print(f"警告：输入时间 t={t} 过小，可能导致计算异常")
        return
    
    # 分步计算，避免嵌套导致的精度丢失
    # 1. 计算速度 v = 0.2 / t（假设0.2是位移，单位m，保持原公式）
    v = 0.2 / t
    
    # 2. 计算斯托克斯阻力系数 f（分步展开公式）
    numerator_f = (rou - rou0) * g * d * d  # 分子部分
    denominator_f = 18 * v                  # 分母部分
    f = numerator_f / denominator_f         # 避免直接嵌套计算
    
    # 3. 计算修正系数 f1（考虑颗粒与管道直径比）
    denominator_f1 = 1 + (2.4 * d) / D
    f1 = f / denominator_f1
    
    # 4. 计算修正系数 f2（考虑雷诺数影响）
    Re = (rou0 * d * v) / f  # 雷诺数（基于斯托克斯阻力系数）
    denominator_f2 = 1 + (3 * Re) / 16
    f2 = f1 / denominator_f2
    
    # 高精度输出：保留12位小数，确保精度不丢失
    print("=" * 50)
    print(f"输入时间 t = {t:.4f} s")
    print(f"速度 v = {v:.12f} m/s")
    print(f"斯托克斯阻力系数 f = {f:.12e} Pa·s")  # 科学计数法，更易读
    print(f"修正系数 f1 = {f1:.12e} Pa·s")
    print(f"雷诺数 Re = {Re:.12f}")
    print(f"最终修正系数 f2 = {f2:.12e} Pa·s")
    print("=" * 50 + "\n")
    return f1

# 遍历所有输入值计算
y_value = []

for t_val in t_list:
    kkk = func(t_val)
    y_value.append(kkk)

