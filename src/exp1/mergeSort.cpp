#include <bits/stdc++.h>
using namespace std;
#include <filesystem>

#include "../../include/utils.h"
namespace fs = std::filesystem;
string BaseData = R"(F:\Desktop\AlgorithmExperiment\data)";
string name = "mergeSort";
string datapath = BaseData + "\\" + name;
// solution

// 数据规模[5,10,50,100,1000,5000,10000,50000,100000,500000]
//[0, 0, 0, 0, 0,   1,   2,    16,   34, 192] 分治（拷贝费时间）
//[0, 0, 0, 0, 4, 107, 418, 11436,55528,cant wait] 冒泡
//[0, 0, 0, 0, 0,   0,   1,    10,   23, 125]快排
class Solution//分治合并排序
{
public:
    static vector<int> sortArray(vector<int> nums)
    {
        if (nums.size() <= 1)
        {
            return nums;
        }
        vector<int> temp(nums.size());
        mergeSort(nums, 0, nums.size() - 1, temp);
        return nums;
    }

private:
    static void mergeSort(vector<int> &nums, int left, int right, vector<int> &temp)
    {
        if (left >= right)
        {
            return;
        }

        int mid = left + (right - left) / 2;

        // 递归排序左右两半
        mergeSort(nums, left, mid, temp);
        mergeSort(nums, mid + 1, right, temp);

        // 合并两个有序部分
        merge(nums, left, mid, right, temp);
    }

    static void merge(vector<int> &nums, int left, int mid, int right, vector<int> &temp)
    {
        int i = left, j = mid + 1, k = 0;

        // 比较并合并
        while (i <= mid && j <= right)
        {
            if (nums[i] <= nums[j])  temp[k++] = nums[i++];
            else  temp[k++] = nums[j++];
        }

        // 复制剩余元素
        while (i <= mid)    temp[k++] = nums[i++];
        while (j <= right)  temp[k++] = nums[j++];

        // 将临时数组复制回原数组
        for (int i = 0; i < k; i++)  
            nums[left + i] = temp[i];
    }
};
class Solution2 // 快速排序
{
public:
    static vector<int> sortArray(vector<int> nums)
    {
        int n = nums.size();
        quick(nums, 0, n - 1);
        return nums;
    }

private:
    static void quick(vector<int> &nums, int l, int r)
    {
        int p = nums[l];
        int i = l, j = r;
        if (l >= r)
            return;
        while (i < j)
        {
            while (i<j&&nums[j] >= p)  j--;
            while (i<j&&nums[i] <= p)  i++;  
            if (i < j) swap(nums[i], nums[j]);
        }
        swap(nums[l], nums[j]);
        quick(nums, l, j);
        quick(nums, j + 1, r);
    }
};
class Solution1//冒泡排序
{
public:
    static vector<int> sortArray(vector<int> nums)
    {
        if (nums.size() <= 1)
        {
            return nums;
        }

        bubbleSort(nums);
        return nums;
    }

private:
    static void bubbleSort(vector<int> &nums)
    {
        int n = nums.size();

        for (int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (nums[j] > nums[j + 1])
                {
                    // 交换相邻元素
                    swap(nums[j], nums[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
    }
};
void solve()
{
    for (int i = 1; i < 100; i++)
    {

        // 文件检查读取
        if (!fs::exists(datapath + "\\" + to_string(i) + ".in"))
            break; // 文件不存在则结束
        cout << "Case " << i << ": " << endl;
        istringstream iss = load_in(i, datapath);
        istringstream ans_iss = load_out(i, datapath);

        // 定义输入输出数据结构
        vector<int> arr;
        vector<int> ans;
        vector<int> res;

        // 读取输入输出数据
        int a;
        while (iss >> a)
            arr.push_back(a);
        while (ans_iss >> a)
            ans.push_back(a);

        // 执行算法
        {
            cout << "Algorithm: mergeSort: ";
            Timer timer = Timer(); // 计时器
            res = Solution::sortArray(arr);
        }

        // {
        //     cout << "Algorithm: bubbleSort: " ;
        //     Timer timer = Timer(); // 计时器
        //     res = Solution1::sortArray(arr);
        // }

        // 打印信息
        cout << "Input size:" << arr.size() << endl;
        if (arr.size() <= 20)
        {
            cout << "Input: ";
            for (auto i : arr)
                cout << i << " ";
            cout << endl;
            cout << "Output: ";
            for (auto i : res)
                cout << i << " ";
            cout << endl;
        }

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
