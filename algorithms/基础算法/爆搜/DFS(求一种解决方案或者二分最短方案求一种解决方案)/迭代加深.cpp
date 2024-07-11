//�ӳ����� 
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 110;

int n;
int path[N];

bool dfs(int u, int k)  // u��ʾ��ǰ����, k��ʾ���Ĳ���
{
    if (u == k) {
        return path[u - 1] == n; 
    }

    bool st[N] = {0}; // ͨ�� bool�����ų���Ч����

    for (int i = u - 1; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            int s = path[i] + path[j];
            if (s > n || s <= path[u - 1] || st[s]) { // pathһ���ǵ�����
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
        while (!dfs(1, k)) {  // ��������Χ
            k++;
        }
        for (int i = 0; i < k; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

