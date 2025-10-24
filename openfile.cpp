#include <iostream>
using namespace std;
#include <vector>
class Solution1
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
    static vector<int> getDivisorCount(int n)
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
int main()
{
    int a, b;
    while (cin >> a >> b)
        cout << Solution1::findMaxDivisors(a, b) << endl;
    return 0;
}