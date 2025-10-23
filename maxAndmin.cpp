#include<bits/stdc++.h>
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;
string BaseData = R"(F:\Desktop\AlgorithmExperiment\data)";
string name = "maxAndmin";
string datapath = BaseData + "\\" + name;
class Timer
{
private:
    chrono::high_resolution_clock::time_point start;

public:
    Timer() : start(chrono::high_resolution_clock::now()) {}

    ~Timer()
    {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "\n程序执行时间: " << duration.count() << " ms" << endl;
        cout << "------------------------------------------------------------" << endl;
    }
};
vector<int> maxAndmin(vector<int> &arr, int left, int right)
{
    // 基本情况：只有一个元素
    if (left == right)
    {
        return {arr[left], arr[left]};
    }

    // 分治：将数组分成两半
    int mid = left + (right - left) / 2;

    // 递归求解左半部分和右半部分
    vector<int> leftResult = maxAndmin(arr, left, mid);
    vector<int> rightResult = maxAndmin(arr, mid + 1, right);

    // 合并结果
    int maxVal = max(leftResult[0], rightResult[0]);
    int minVal = min(leftResult[1], rightResult[1]);

    return {maxVal, minVal};
}

// 重载函数，保持与原函数相同的接口
vector<int> maxAndmin(vector<int> &arr, int n)
{
    if (n <= 0)
        return {INT_MIN, INT_MAX};
    return maxAndmin(arr, 0, n - 1);
}
void check() {
  for(int i = 1; i < 100; i++)
  {
    
    string file_path= datapath+"\\"+to_string(i)+".in";
    string ans_file_path= datapath+"\\"+to_string(i)+".out";
    ifstream file(file_path);
    if(!file.is_open())
        break;
    Timer timer=Timer();
    ifstream ans_file(ans_file_path);
    string file_content(
        (std::istreambuf_iterator<char>(file)), // 起始迭代器（文件开头）
        std::istreambuf_iterator<char>()        // 结束迭代器（文件末尾）
    );
        string ans_file_content(
        (std::istreambuf_iterator<char>(ans_file)), // 起始迭代器（文件开头）
        std::istreambuf_iterator<char>()        // 结束迭代器（文件末尾）
    );
    file.close();
    ans_file.close();
    istringstream iss(file_content);
    istringstream ans_iss(ans_file_content);
    vector<int> arr;
    vector<int> ans;
    int a;
    while(iss >> a)
    {
        arr.push_back(a);
    }
    while(ans_iss >> a)
    {
        ans.push_back(a);
    }
    vector<int> res = maxAndmin(arr, arr.size());
    cout << "Case " << i << ": " << endl;
    if(res != ans)
    {
        cout << "Wrong Answer" << endl;
        cout << "Input:" << endl;
        cout << file_content << endl;
        cout << "Output:" << endl;
        for(auto i:res)
            cout << i << " ";
        cout << endl;
        cout << "Answer:" << endl;
        for(auto i:ans)
            cout << i << " ";
    }
    else
    {
        cout << "Accepted" << endl;
    }
  }
}
int main()
{
    check();
    return 0;
}
