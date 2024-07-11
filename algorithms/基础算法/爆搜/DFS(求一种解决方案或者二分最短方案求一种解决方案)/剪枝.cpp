//数独 
#include<iostream>
#include<algorithm>
#define lowbit(x) ((x) & (-x))
using namespace std;

const int N = 9, M = 1 << N;

//ones表示0-2^9里每个数有多少个1，map快速地找出这行哪一列可以填，比如map[(10)2] = 1就知道第二列可以填1
int ones[M], map[M];
//分别表示行，列，大方格子有哪些数字没有填
int rows[N], cols[N], cell[3][3];
char s[100];

//is_set = true则在x, y填上t, 否则则把x,y处的数字删掉, t 是0-8
void draw(int x, int y, int t, int is_set) {
    if(is_set)  s[x * N + y] = '1' + t; //t 是0-8
    else s[x * N + y] = '.';

    int v = 1 << t;
    if(!is_set) v = -v;

    //如果某位没被放，则它的二进制位应该是1， 所以应该减去v
    //如果放了，它的二进制应该是0，则经过上面的取反，负负得正，-v实际上就是把二进制0变为1
    rows[x] -= v;
    cols[y] -= v;
    cell[x / 3][y / 3] -= v;
}

//x行y列可以填哪个数字, 最后得到2^i + 2^j..+..，这些i, j就是可以填的数字，最后通过map[2^i]来得到这个数字
int get(int x, int y) {
    return rows[x] & cols[y] & cell[x / 3][y / 3];
}

int init() {
    //cnt表示还剩多少个数字没有填
    int cnt = 0;
    //初始状态state的9位二进制全是1
    int state = (1 << N) - 1;

    //如果row[0] = 111111111 代表第一行可以填9个数, 这里行号是0-8
    fill(rows, rows + N, state);   
    fill(cols, cols + N, state);
    fill(cell[0], cell[0] + N, state);

    for(int i = 0, k = 0; i < N; i++) {
        for(int j = 0; j < N; j++, k++) {
            if(s[k] != '.') {
                draw(i, j, s[k] - '1', true);
            }
            else cnt++;
        }
    }

    return cnt;
}

bool dfs(int cnt) {
    //填完所有数字，则返回
    if(!cnt) return true;  
    //最多可以填多少个数字
    int minv = 10; 
    int x, y;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(s[i * N + j] == '.') {
                //可以填的数字状态，如010001，是1则表示可以填
                int state = get(i, j);     
                 //选一个1的个数最少的，这样的分支数量最少
                if(ones[state] < minv) {
                    minv = ones[state];
                    x = i, y = j;
                } 
            }
        }
    }

    //依次做lowbit操作，选择每个分支
    for(int i = get(x, y); i ; i-= lowbit(i)) {

        //这个t就是要填充的数字
        int t = map[lowbit(i)];

        //填这个数字
        draw(x, y, t, true);    

        //这次填充成功，则返回
        if(dfs(cnt - 1)) return true;   

        //失败则回溯 
        draw(x, y, t, false);   
    }

    return false;
}

int main() {
    //打表，快速地知道可以哪一个数字
    for(int i = 0; i < N; i++) map[1 << i] = i;

    //ones记录每个状态有多少个1，用于选择分支少的开始搜索, 其中M = 1 << N
    for(int i = 0; i < M; i++) {
        for(int j = i; j; j -= lowbit(j)) {
            ones[i] += 1;
        }
    }

    while(cin >> s, s[0] != 'e') {
        int k = init();
        dfs(k);
        puts(s);
    }

    return 0;
}

