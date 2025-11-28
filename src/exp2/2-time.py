import matplotlib.pyplot as plt
import time
count = 0
memo = {}
def dp_with_prefix_sum(n):
    dp = [0]*(n+1)
    prefix_sum = [0]*(n+1)
    dp[0]=0
    prefix_sum[0]=dp[0]
    for i in range(1,n+1):
        dp[i]=prefix_sum[i//2]+1
        prefix_sum[i]=prefix_sum[i-1]+dp[i]
    return dp[n]
def dfs(n):
    global count
    count+=1;
    if n==1:
        return 1
    sum = 1
    for i in range(1, n // 2 + 1):
        sum += dfs(i)
    return sum
def dfs_with_memo(n):
    global count
    count+=1;
    if n in memo:
        return memo[n]
    if n==1:
        return 1
    sum = 1
    for i in range(n//2,0,-1):
        sum += dfs_with_memo(i)
    memo[n]=sum
    return sum
times = []     # 记录真实时间
counts = []    # 记录 count 次数
y = range(1, 1500000, 10000)
for n in y:
    memo.clear()
    count = 0

    start = time.time()    # 开始计时
    print(dp_with_prefix_sum(n))       # 运行
    end = time.time()      # 结束计时

    real_time = end - start

    print(f"n={n}, count={count}, time={real_time:.6f}s")

    times.append(real_time)
    counts.append(count)
plt.plot(y, times)
plt.xlabel('n')
plt.ylabel('Time Complexity Count')
plt.title('Time Complexity Analysis of dp for Half-Digit Set Problem')
plt.show()
