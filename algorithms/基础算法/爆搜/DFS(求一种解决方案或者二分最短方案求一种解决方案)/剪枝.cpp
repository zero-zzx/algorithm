//���� 
#include<iostream>
#include<algorithm>
#define lowbit(x) ((x) & (-x))
using namespace std;

const int N = 9, M = 1 << N;

//ones��ʾ0-2^9��ÿ�����ж��ٸ�1��map���ٵ��ҳ�������һ�п��������map[(10)2] = 1��֪���ڶ��п�����1
int ones[M], map[M];
//�ֱ��ʾ�У��У��󷽸�������Щ����û����
int rows[N], cols[N], cell[3][3];
char s[100];

//is_set = true����x, y����t, �������x,y��������ɾ��, t ��0-8
void draw(int x, int y, int t, int is_set) {
    if(is_set)  s[x * N + y] = '1' + t; //t ��0-8
    else s[x * N + y] = '.';

    int v = 1 << t;
    if(!is_set) v = -v;

    //���ĳλû���ţ������Ķ�����λӦ����1�� ����Ӧ�ü�ȥv
    //������ˣ����Ķ�����Ӧ����0���򾭹������ȡ��������������-vʵ���Ͼ��ǰѶ�����0��Ϊ1
    rows[x] -= v;
    cols[y] -= v;
    cell[x / 3][y / 3] -= v;
}

//x��y�п������ĸ�����, ���õ�2^i + 2^j..+..����Щi, j���ǿ���������֣����ͨ��map[2^i]���õ��������
int get(int x, int y) {
    return rows[x] & cols[y] & cell[x / 3][y / 3];
}

int init() {
    //cnt��ʾ��ʣ���ٸ�����û����
    int cnt = 0;
    //��ʼ״̬state��9λ������ȫ��1
    int state = (1 << N) - 1;

    //���row[0] = 111111111 �����һ�п�����9����, �����к���0-8
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
    //�����������֣��򷵻�
    if(!cnt) return true;  
    //����������ٸ�����
    int minv = 10; 
    int x, y;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(s[i * N + j] == '.') {
                //�����������״̬����010001����1���ʾ������
                int state = get(i, j);     
                 //ѡһ��1�ĸ������ٵģ������ķ�֧��������
                if(ones[state] < minv) {
                    minv = ones[state];
                    x = i, y = j;
                } 
            }
        }
    }

    //������lowbit������ѡ��ÿ����֧
    for(int i = get(x, y); i ; i-= lowbit(i)) {

        //���t����Ҫ��������
        int t = map[lowbit(i)];

        //���������
        draw(x, y, t, true);    

        //������ɹ����򷵻�
        if(dfs(cnt - 1)) return true;   

        //ʧ������� 
        draw(x, y, t, false);   
    }

    return false;
}

int main() {
    //������ٵ�֪��������һ������
    for(int i = 0; i < N; i++) map[1 << i] = i;

    //ones��¼ÿ��״̬�ж��ٸ�1������ѡ���֧�ٵĿ�ʼ����, ����M = 1 << N
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

