#include<bits/stdc++.h>
using namespace std;
string BaseData = R"(F:\Desktop\AlgorithmExperiment\data)";
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
    }
};
istringstream load_in(int i, string datapath)
{
    string file_path = datapath + "\\" + to_string(i) + ".in";
    ifstream file(file_path);
    string file_content(
        (std::istreambuf_iterator<char>(file)), // 起始迭代器（文件开头）
        std::istreambuf_iterator<char>()        // 结束迭代器（文件末尾）
    );
    file.close();
    istringstream iss(file_content);
    return iss;
}
istringstream load_out(int i,string datapath)
{
    string file_path = datapath + "\\" + to_string(i) + ".out";
    ifstream file(file_path);
    string file_content(
        (std::istreambuf_iterator<char>(file)), // 起始迭代器（文件开头）
        std::istreambuf_iterator<char>()        // 结束迭代器（文件末尾）
    );
    file.close();
    istringstream iss(file_content);
    return iss;
}