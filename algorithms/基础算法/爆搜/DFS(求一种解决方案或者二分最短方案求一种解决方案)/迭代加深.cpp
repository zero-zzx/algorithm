//加成序列 
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 110;

int n;
int path[N];

bool dfs(int u, int k)  // u表示当前层数, k表示最大的层数
{
    if (u == k) {
        return path[u - 1] == n; 
    }

    bool st[N] = {0}; // 通过 bool数组排除等效冗余

    for (int i = u - 1; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            int s = path[i] + path[j];
            if (s > n || s <= path[u - 1] || st[s]) { // path一定是递增的
                continue;
            }

            st[s]   = true;
            path[u] = s;

            if (dfs(u + 1, k)) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    path[0] = 1;
    while (cin >> n, n) {
        int k = 1;
        while (!dfs(1, k)) {  // 不断扩大范围
            k++;
        }
        for (int i = 0; i < k; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

