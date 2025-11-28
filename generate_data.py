import math
import random
import numpy as np
# 输入参数
def calculate_ln_v_slope_with_full_time_scaling(
    t_matrix: np.ndarray, 
    dt_matrix: np.ndarray, 
    l_scalar=0.01
) -> np.ndarray:
    """
    计算基于 (t * 10^-3) - ln(v) 数据的线性回归斜率。
    同时对 t 和 dt 矩阵进行 10^-3 的缩放。
    
    参数:
    t_matrix (np.ndarray): 原始时间 t (x轴)。
    dt_matrix (np.ndarray): 原始时间间隔 dt (用于计算 v)。
    l_scalar (float): 长度/位移变量 (标量)。
    
    返回:
    np.ndarray: 包含所有计算得到的斜率的一维数组。
    """
    
    # 1. 检查输入矩阵的形状是否匹配
    if t_matrix.shape != dt_matrix.shape:
        raise ValueError(
            f"输入矩阵的形状必须匹配。t_matrix 形状: {t_matrix.shape}, "
            f"dt_matrix 形状: {dt_matrix.shape}"
        )
    
    # **核心修改 1**: 对整个矩阵进行尺度变换 (t_new = t * 10^-3)
    t_scaled = t_matrix 
    
    # **核心修改 2**: 对整个 dt 矩阵进行尺度变换 (dt_new = dt * 10^-3)
    dt_scaled = dt_matrix 
    
    num_groups = t_matrix.shape[0]
    slopes = np.full(num_groups, np.nan, dtype=float)
    
    # 2. 遍历每一行 (每一组数据)
    for i in range(num_groups):
        t = t_scaled[i, :]   # 缩放后的 x 轴数据
        dt = dt_scaled[i, :] # 缩放后的 dt 数据
        
        try:
            # 2.1 检查 dt 或 l 是否会导致非正速度
            if l_scalar <= 0:
                 raise ValueError("长度 l_scalar 必须大于 0。")
            if np.any(dt <= 0):
                print(f"警告: 第 {i+1} 组缩放后的 dt 数组中包含非正值 (<= 0)，无法计算速度和对数。")
                continue
                
            # 2.2 计算速度数组 V = L / DT
            # 注意：如果 L 和 DT 的单位统一，V 的单位是 L/T 的单位（例如 m/s）
            v = l_scalar / dt
            
            # 2.3 计算 ln(v) 作为 Y 轴数据
            ln_v = np.log(v)
            # 2.4 执行线性回归 (最小二乘法拟合)
            # x=t (已缩放), y=ln_v, deg=1
            coefficients = np.polyfit(t, ln_v, 1)
            slope = coefficients[0]
            
            # 存储斜率
            slopes[i] = slope
            
        except Exception as e:
            # 处理其他拟合失败的错误
            print(f"拟合第 {i+1} 组数据时发生错误: {e}")

    return slopes
f = open("result.txt", "w", encoding="utf-8")
target = 0.0439
for k in  np.arange(target*0.995, target*1.005, 0.0000003):
    s = [0,0.0, 0.0999, 0.2344, 0.3925, 0.5357, 0.6274, 0.7640, 0.9058]
    while True:
        v0 = random.gauss(0.20, 0.03)
        if v0 > k * max(s):   # 能保证 term 永远 > 0
            break   # 初始速度加入微小随机扰动，模拟实验误差
    # 1到i光电门的累积距离 s_i
    
    n = 8  # 光电门数量

    # 计算 t1 ~ t8
    t = [0.0] * (n + 1)
    for i in range(1, n + 1):
        term = 1.0 - (k / v0) * s[i]
        t[i] = (-math.log(term) / k)*random.uniform(0.98,1.02)  # 加入微小随机扰动，模拟实验误差

    # 计算 dt_i = 0.01 * v0 * exp(-k * t_i)
    dt = [0.0] * (n + 1)
    for i in range(1, n + 1):
        dt[i] = (0.01 /(v0 * math.exp(-k * t[i])) )*random.uniform(0.98,1.02)  # 加入微小随机扰动，模拟实验误差

    # 输出结果
    print("\n===== 计算结果 =====")
    print("1到i光电门的时刻 t_i (s)：")
    for i in range(1, n + 1):
        print(f"t{i} = {t[i]*1000:.4f} ms")

    print("\n各光电门的遮光时间 dt_i (s)：")
    for i in range(1, n + 1):
        print(f"dt{i} = {dt[i]*1000:.4f}ms")
    slope = calculate_ln_v_slope_with_full_time_scaling(
        np.array([t[1:]]), 
        np.array([dt[1:]]), 
        l_scalar=0.01
    )[0]
    t_ms = [int(x * 1000) for x in t[1:]]             # 转换成整数毫秒 
    dt_ms = [round(float(x * 1000), 2) for x in dt[1:]]  # 保留 2 位小数毫秒
    print(f"k={slope:.4f}\n ")
    if all(earlier < later for earlier, later in zip(dt_ms, dt_ms[1:])) and (abs(abs(slope)-k)/k < 0.003) :
        with open("output.txt", "a") as f:
            f.write(f"k={abs(slope):.4f}\n t={t_ms}\n dt={dt_ms}\n")
    else:
        print("dt_ms 不递增，未写入文件")