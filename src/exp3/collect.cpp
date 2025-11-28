#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 1. 补充最小限度的全局变量声明（必须补充，否则无法编译）
const int MAX_N = 10;
int n = 8; // 设定测试用例 n=8
// v 数组用于存储样本价值，但为了编译，先声明
int g[MAX_N + 1][MAX_N + 1];
// DP 数组：必须声明，否则 val 和 dyna 无法编译
int h[MAX_N + 1][MAX_N + 1][MAX_N + 1][MAX_N + 1];


// 2. val 函数：严格遵循图片上的内容
void val(int x1, int y1, int x2, int y2, int v_transfer) {
    if (x1 == x2 && y1 == y2) { 
        // 图片中的逻辑
        h[x1][y1][x2][y2] = max(h[x1][y1][x2][y2], v_transfer + g[x1][y1]);
    } else {
        // 图片中的逻辑 (逻辑有缺陷，但未修改)
        h[x1][y1][x2][y2] = max(h[x1][y1][x2][y2], v_transfer + g[x1][y1] + g[x2][y2]);
    }
}

// 3. dyna 函数：严格遵循图片上的循环结构和内部语句
void dyna() {
    int x1, y1, x2, y2, s, v; // 注意：图片中 v 变量名与样本价值数组 v 冲突

    // 初始化 h 数组（图片中的初始化部分）
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= n; k++)
                for (int l = 0; l <= n; l++)
                    h[i][j][k][l] = 0;

    h[1][1][1][1] = g[1][1]; // 图片中的逻辑

    for (s = 2; s <= n + n - 1; s++) {
        for (x1 = 1; x1 <= s - 1; x1++) {
            for (x2 = 1; x2 <= s - 1; x2++) {
                y1 = s - x1;
                y2 = s - x2;
                if(y1>n || y2>n) cout<<"error"<<endl;
                v = h[x1][y1][x2][y2]; // 图片中的逻辑

                // 图片中的 4 次 val 调用：参数和逻辑是错误的，但严格保留
                val(x1+1, y1  , x2+1, y2  , v); 
                val(x1+1, y1  , x2  , y2+1, v); 
                val(x1  , y1+1, x2+1, y2  , v);
                val(x1  , y1+1, x2  , y2+1, v);
            }
        }
        // 缺少滚动更新 g=h 的代码，会导致循环无限使用 g[1][1][1][1] 的值。
    }
}

// 4. 设置测试数据和主函数
void setup_test_case() {
    // 示例数据 v[r][c] = value
    g[2][3] = 13; g[2][6] = 6; 
    g[3][5] = 7;  g[4][4] = 14; 
    g[5][2] = 21; g[5][6] = 4; 
    g[6][3] = 15; g[7][2] = 14;
    // 初始化起点 g[1][1][1][1]
}

int main() {
    setup_test_case(); 
    dyna();
    
    // 最终结果
    int final_result = h[n][n][n][n];

    cout << "根据图片代码严格组合的测试结果：" << final_result << endl;

    if (final_result == 67) {
        cout << "测试样例通过：成功得到 67。" << endl;
    } else {
        cout << "测试样例失败。预期结果: 67, 实际结果: " << final_result << endl;
    }

    return 0;
}