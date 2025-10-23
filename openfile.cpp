#include<bits/stdc++.h>
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;
int main()
{
    string filepath = R"(F:\Desktop\AlgorithmExperiment\data\maxAndmin\1.in)";

    if(fs::exists(filepath))
    {
        cout << "File exists." << endl;
    }
    else
    {
        cout << "File does not exist." << endl;
    }
    return 0;
}