#include<bits/stdc++.h>
using namespace std;
#include <filesystem>
#include "..\..\include/utils.h"
namespace fs = std::filesystem;
string BaseData = R"(F:\Desktop\AlgorithmExperiment\data)";
string name = "maxAndmin";
string datapath = BaseData + "\\" + name;

//solution

class Solution
{
public:
   static vector<int> maxAndmin(vector<int> &arr)
    {
        int n = arr.size();
        if (n <= 0)
            return {INT_MIN, INT_MAX};
        return maxAndmin(arr, 0, n - 1);
    }

private:
   static vector<int> maxAndmin(vector<int> &arr, int left, int right)
    {
        if (left == right)
        {
            return {arr[left], arr[left]};
        }

        int mid = left + (right - left) / 2;
        vector<int> leftRes = maxAndmin(arr, left, mid);
        vector<int> rightRes = maxAndmin(arr, mid + 1, right);

        return {
            max(leftRes[0], rightRes[0]),
            min(leftRes[1], rightRes[1])
        };
    }
};
void solve() {
  for(int i = 1; i < 100; i++)
  {
    if (!fs::exists(datapath + "\\" + to_string(i) + ".in"))
        break;//文件不存在则结束
    cout << "Case " << i << ": "<< endl ;
    istringstream iss = load_in(i,datapath);
    istringstream ans_iss = load_out(i, datapath);

    //定义输入输出数据结构
    vector<int> arr;
    vector<int> ans;
    vector<int> res;

    //读取输入输出数据
    int a;
    while(iss >> a)
        arr.push_back(a);
    while(ans_iss >> a)
        ans.push_back(a);

    //执行算法
    {
    Timer timer = Timer();//计时器
    res = Solution::maxAndmin(arr);
    }
    cout<<"input size:"<<arr.size()<<endl;
    if(arr.size() <=20){
        cout << "Input: " ;
        for(auto i:arr)
            cout << i << " ";
        cout << endl;
    }
    cout<<"max:"<<res[0]<<" min:"<<res[1]<<endl;
    //比较结果
        if (res != ans)
        {
            // 红色文字：\033[31m 开启红色，\033[0m 重置颜色
            cout << "\033[31mWrong Answer\033[0m" << endl;
        }
        else
        {
            // 绿色文字：\033[32m 开启绿色，\033[0m 重置颜色
            cout << "\033[32mAccepted\033[0m" << endl;
        }
    cout<<"________________________________________________________"<<endl;
  }
}
int main()
{
    solve();
    return 0;
}
