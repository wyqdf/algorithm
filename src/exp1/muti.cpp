#include <bits/stdc++.h>
using namespace std;
#include <filesystem>

#include "../../include/utils.h"
namespace fs = std::filesystem;
string BaseData = R"(F:\Desktop\AlgorithmExperiment\data)";
string name = "muti";
string datapath = BaseData + "\\" + name;

// 数据规模
// 5 10
// 10 100
// 100 1000
// 1000 10000
// 10000 50000
// 50000 500000
// 100000 5000000
// 1000000 10000000

//[0, 0, 0, 0, 1, 22, 389, 1082]
//  solution
class Solution1//历遍每一个因子为有该因子的数+1
{
public:

    static int findMaxDivisors(int A, int B)
    {
        if (B < A)
            return 0;

        vector<int> divisors = getDivisorCount(B);

        int maxDivisors = 0;
        for (int i = A; i <= B; i++)
        {
            if (divisors[i] > maxDivisors)
            {
                maxDivisors = divisors[i];
            }
        }

        return maxDivisors;
    }
private:
    static
    vector<int> getDivisorCount(int n)
    {
        vector<int> divisors(n + 1, 0);

        // 使用筛法计算每个数的因数个数
        for (int i = 1; i <= n; i++)
        {
            for (int j = i; j <= n; j += i)
            {
                divisors[j]++;
            }
        }

        return divisors;
    }
};

class Solution2//每个数都可以分解为质数的质数幂乘积，利用dfs搜索所有可能的质数幂乘积，
{
public:
    static int findMaxDivisors(int A, int B)
    {
        if (B < A)
            return 0;
        if (A == 1 && B == 1)
            return 1;

        // 生成质数表
        vector<int> primes = generateSmartPrimes(B);

        Ans = 2;
        dfs(1, 0, calculateMaxExponent(B), 1, A, B, primes);
        return Ans;
    }

private:
    static int Ans;

    static void dfs(long long Num, int pos, int k, int Cnt, int A, int B, const vector<int> &primes)
    {
        if (pos >= primes.size())//超过质数表长度
            return;
        if (Num > B) // 超过范围
            return;

        // 检查当前数
        if (A <= Num && Num <= B)
        {
            if (Cnt > Ans)
            {
                Ans = Cnt;
            }
        }

        for (int i = 1; i <= k; i++)
        {
            if (Num > B / primes[pos])
                break;
            Num *= primes[pos];
            dfs(Num, pos + 1, i, Cnt * (i + 1), A, B, primes);
        }
    }

    // 生成质数表
    static vector<int> generateSmartPrimes(int B)
    {
        int maxPrime = sqrt(B)+1;

        vector<int> primes;
        vector<bool> isPrime(maxPrime + 1, true);

        if (maxPrime >= 2)
        {
            isPrime[0] = isPrime[1] = false;
            for (int i = 2; i <= maxPrime; i++)
            {
                if (isPrime[i])
                {
                    primes.push_back(i);
                    for (long long j = (long long)i * i; j <= maxPrime; j += i)
                    {
                        isPrime[j] = false;
                    }
                }
            }
        }

        return primes;
    }

    // 合理的最大初始指数
    static int calculateMaxExponent(int B)
    {
        // 计算以2为底的对数作为最大指数参考
        int log2B = 0;
        long long temp = 1;
        while (temp <= B)
        {
            temp *= 2;
            log2B++;
        }
        return min(64, log2B + 5); // 适当放宽
    }
};

int Solution2::Ans = 2;

class Solution3//利用质数的幂与因数个数的关系式
{
public:
    static int findMaxDivisors(int A, int B)
    {
        if (B < A)
            return 0;
        if (A == 1 && B == 1)
            return 1;

        // 预计算质数表（优化性能）
        vector<int> primes = generatePrimesUpTo(sqrt(B) + 1);

        int maxDivisors = 0;

        for (int i = A; i <= B; i++)
        {
            int divisors = countDivisorsWithPrimes(i, primes);
            if (divisors > maxDivisors)
            {
                maxDivisors = divisors;
            }
        }

        return maxDivisors;
    }

private:
    // 使用预计算质数表进行质因数分解
    static int countDivisorsWithPrimes(int n, const vector<int> &primes)
    {
        if (n == 1)
            return 1;

        int divisors = 1;
        int temp = n;

        for (int prime : primes)
        {
            if (prime * prime > temp)
                break;
            if (temp % prime != 0)
                continue;

            int count = 0;
            while (temp % prime == 0)
            {
                count++;
                temp /= prime;
            }
            divisors *= (count + 1);
        }

        // 处理剩余的质因数
        if (temp > 1)
        {
            divisors *= 2;
        }

        return divisors;
    }

    // 生成质数表
    static vector<int> generatePrimesUpTo(int limit)
    {
        if (limit < 2)
            return {};

        vector<bool> isPrime(limit + 1, true);
        vector<int> primes;

        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i <= limit; i++)
        {
            if (isPrime[i])
            {
                primes.push_back(i);
                for (long long j = (long long)i * i; j <= limit; j += i)
                {
                    isPrime[j] = false;
                }
            }
        }

        return primes;
    }
};
class Solution4 // 超暴力方法 - 对每个数单独计算因数个数
{
public:
    static int findMaxDivisors(int A, int B)
    {
        if (B < A)
            return 0;

        int maxDivisors = 0;
        for (int i = A; i <= B; i++)
        {
            int divisors = countDivisorsBruteForce(i);
            if (divisors > maxDivisors)
            {
                maxDivisors = divisors;
            }
        }

        return maxDivisors;
    }

private:
    static int countDivisorsBruteForce(int n)
    {
        if (n == 1)
            return 1;

        int count = 0;

       
        for (int i = 1; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                count++;
                if (i != n / i)
                {
                    count++;
                }
            }
        }

        return count;
    }
};
void solve()
{
    for (int i = 1; i < 100; i++)
    {
        if (!fs::exists(datapath + "\\" + to_string(i) + ".in"))
            break; // 文件不存在则结束

        istringstream iss = load_in(i, datapath);
        istringstream ans_iss = load_out(i, datapath);

        // 定义输入输出数据结构
        vector<int> arr;
        int ans;
        int res;

        // 读取输入输出数据
        int a;
        while (iss >> a)
            arr.push_back(a);
        ans_iss>>ans;
        cout << "Case " << i << ":" << endl;

        // 执行算法
        {
            cout << "Algorithm: 本算法: " ;
            Timer timer = Timer(); // 计时器
            res = Solution1::findMaxDivisors(arr[0], arr[1]);
        }
        cout << "Input: " << arr[0] << " " << arr[1] << endl;
        cout << "Output: " << res << endl;
        

        // 比较结果
        if (res != ans)
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

//[0, 0, 0, 0, 1, 22, 405, 1082]
//[0, 0, 0, 0, 0, 0, 0, 0]  dfs
//[0, 0, 0, 1, 7, 152, 3189, 7453] 
//[0, 0, 0, 1, 16, 500, 15816, (超时)] 
