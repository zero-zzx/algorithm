//��ͨƽ����
#include<bits/stdc++.h>
using namespace std;
const int N = 100010, INF = 1e8;
int n;
struct Node
{
    int l, r;
    int k;
    int val;//���еı��
    int cnt, size;
}tr[N];
int root, idx;
void pushup(int u)
{
    tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].cnt;//�ϴ��ڵ���Ϣ������size
}
int new_node(int k)
{
    tr[ ++ idx].k = k;
    tr[idx].val = rand();//������������ָ�������
    tr[idx].cnt = 1;
    tr[idx].size = 1;
    return idx;
}
void zig(int &u)//��������ûɶ��˵�ģ��Լ���ֽ�ϻ�һ�¾�֪����
{
    int q = tr[u].l;
    tr[u].l = tr[q].r;
    tr[q].r = u;
    u = q;
    pushup(tr[u].r);
    pushup(u);//���һ��Ҫ�ǵ��ϴ�����Ȼ����
}
void zag(int &u)
{
    int q = tr[u].r;
    tr[u].r = tr[q].l;
    tr[q].l = u;
    u = q;
    pushup(tr[u].l);
    pushup(u);
}
void build()//����������Ϊ����ȷ�����������ڱ�����ֹԽ��
{
    new_node(-INF), new_node(INF);
    root = 1, tr[1].r = 2;//��ʼ��һ��
    pushup(root);//�ϴ���Ϣ
    if(tr[1].val< tr[2].val) zag(root);//��ƽ���˾���ת
}
void insert(int &u, int k)
{
    if(u == 0) u = new_node(k);//����ߵ����ˣ����½�
    else
    {
        if(tr[u].k == k)//����ҵ�����ͬ�Ľڵ㣬��cnt++
        {
            tr[u].cnt ++;
        }
        else
        {
            if(tr[u].k > k)//���򿴿�������߻������ұ�
            {
                insert(tr[u].l, k);
                if(tr[tr[u].l].val > tr[u].val) zig(u);//��ƽ���������
            }
            else
            {
                insert(tr[u].r, k);
                if(tr[tr[u].r].val > tr[u].val) zag(u); 
            }
        }
    }
    pushup(u);//����ϴ�һ�£��ǲ��Ǻ��߶����е��񰡣�
}
void del(int &u, int k)//ɾ������
{
    if(u == 0) return ;//���û��˵���ڵ㲻���ڣ��Ͳ����ˡ�
    if(tr[u].k == k)//����ҵ��������
    {
        if(tr[u].cnt > 1) tr[u].cnt --;//����һ��˵��ֱ��cnt --
        else//������һ
        {
            if(tr[u].l || tr[u].r)//�ȿ����ǲ���Ҷ�ڵ�
            {
                if(!tr[u].r || tr[tr[u].l].val) 
                {
                    zig(u);
                    del(tr[u].r, k);//�ǵ�ά��ƽ��Ŷ
                }
                else
                {
                    zag(u);
                    del(tr[u].l, k);
                }
            }
            else u = 0;//�ǵĻ����ÿ���ƽ�����⣬ֱ��ɾ������
        }
    }
    else if(tr[u].k > k) del(tr[u].l, k);//���û���ҵ����ж�һ�����������ߵ���һ��
    else del(tr[u].r, k);//��һ��
    pushup(u);//�ϴ�����
}
int get_rank(int u, int k)
{
    if(u == 0) return 0;//��0��㷵�ؾ���
    if(tr[u].k == k) return tr[tr[u].l].size + 1;//�����������Ӧ�þ�����ߵ����������Լ�
    if(tr[u].k > k) return get_rank(tr[u].l, k);//���������
    return tr[tr[u].l].size + tr[u].cnt + get_rank(tr[u].r, k);//���ұ�
} 
int get_key(int u, int rank)
{
    if(u == 0) return INF;
    if(tr[tr[u].l].size >= rank) return get_key(tr[u].l, rank);//�����
    if(tr[tr[u].l].size + tr[u].cnt >= rank) return tr[u].k;//�������������ֱ��return
    return get_key(tr[u].r, rank - tr[tr[u].l].size - tr[u].cnt);//��Ȼ�����ұ�
}
int get_pr(int u, int k)//ǰ��
{
    if(u == 0) return -INF;
    if(tr[u].k >= k) return get_pr(tr[u].l, k);//�����
    return max(get_pr(tr[u].r, k), tr[u].k);//�������ұ߿�����������������ø�max
}
int get_ne(int u, int k)//���
{
    if(u == 0) return INF;//��̵�д����ǰ���෴����ҿ���ע��һ��
    if(tr[u].k <= k) return get_ne(tr[u].r, k);
    return min(get_ne(tr[u].l, k), tr[u].k);
}
int main()
{
    build();
    cin >> n;
    while(n --)
    {
        int op, x;
        cin >> op >> x;
        if(op == 1) insert(root, x);
        else if(op == 2) del(root, x);
        else if(op == 3) cout << get_rank(root, x) - 1 << endl;
        else if(op == 4) cout << get_key(root, x + 1) << endl;
        else if(op == 5) cout << get_pr(root, x) << endl;
        else cout << get_ne(root, x) << endl;//������������д���
    }
    return 0;
}




//��������
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 100010;
const double alpha = 0.75;    // ������   double ����

struct Scape_goat
{
    int l, r;
    int val;
    int size;   //  �����Ĵ�С���������Լ����� ����������ɾ����ǵĽ��
    int exist;
    int fact;
}tr[N];
int idx;
int root;
int rec[N], cnt;

// ÿ���½��ڵ�ֻ�����Լ�������Ҫ�ܶ�����
void build(int &u, int val)
{
    u = ++ idx;   // ��һ��λ��
    tr[u].val = val;
    tr[u].size = 1;
    tr[u].fact = 1;
    tr[u].exist = true;
}

/** 
 *  �ع����� ��      ��ǰ�ڵ������������������size  > ��ǰ���Ĵ�С �� һ��ƽ������alpha (һ��ȡ0.75)
 *               �����Ե�ǰ���Ϊ���������б�ɾ���ĵ� > ��������С�� 30% 
 **/

bool isbalance(int u)
{
    if (tr[tr[u].l].size > tr[u].size * alpha || tr[tr[u].r].size > tr[u].size * alpha)  return false;
    if (tr[u].size - tr[u].fact > tr[u].size * 0.3) return false;
    return true;
}

/**
 * �ع��� ����ǰ���������������  ѹ�⣬Ȼ����������
 **/

void inorder(int u)
{
    if (!u) return;
    inorder(tr[u].l);
    if (tr[u].exist) rec[++ cnt] = u;
    inorder(tr[u].r);
}

// pushup ��ʱ�� ����û�м�¼�ӽڵ㵽���ڵ��ָ�룬  ����ֻ��ͷ�ݹ�
void pushup(int tmp, int op)
{
    if (!tmp) return;    //  ����������ɾ�������
    if (tr[tmp].val > tr[op].val)
    {
        pushup(tr[tmp].l, op);
    }
    else pushup(tr[tmp].r, op);

    tr[tmp].size = tr[tr[tmp].l].size + tr[tr[tmp].r].size + 1;
    // fact ����Ҫ�޸�
}

// l, r ָrec�����д�������д��ڵĽ��
// u ��l ,r ������������������ĸ�
void lift(int l, int r, int &u)
{
    if (l == r)   // Ҷ�ӽ��
    {
        u = rec[l];    // ͬ�� ������ ������ڵ�����Ϊ���ĸ��׽ڵ�Ķ���
        tr[u].l = tr[u].r = 0;
        tr[u].size = 1;
        tr[u].fact = 1;
        return ;
    }
    int mid = l + r >> 1;    // �Ҹ�
    // ��Ϊ �����Ķ���Ϊ �������ϸ�С�ڸ��� ���� ��Ҫ���� ����mid���������������ȵ����
    // ע������� l ,r mid �����ǽ�㣬  rec[l, r, mid] ���ǽ�㣡����
    while (mid > l and tr[rec[mid]].val == tr[rec[mid - 1]].val) mid --;
    u = rec[mid];
    if (mid == l)   tr[u].l = 0;
    else   lift(l, mid - 1, tr[u].l);   // ע��ݹ����ߵ�ʱ��mid - 1 �� mid + 1, ǧ������mid,  ��������Լ��ĸ����Լ������µݹ�ը��

    lift(mid + 1, r, tr[u].r);
    tr[u].size = tr[u].fact = r - l + 1;
}

void rebuild(int &u)
{
    cnt = 0;
    inorder(u);
    if (cnt == 0)   // ����������嶼Ӧ�ñ�ɾ��
    {
        u = 0;      // ������Ϊ���ĸ��ڵ���ӽ������0�� �����õĺ���
        return;
    }
    // ���� ���� ������
    lift(1, cnt, u);
}

/**
 * ��鲢�ж�һ�����Ƿ���Ҫ�ع�
 * �Ӹ��ڵ���ǰ�������Ľ��һ·�жϣ�   �ҵ���һ����Ҫ���ع��Ľ�㣬���ع���
 * ע��˳���ܷ��� ����������ң��Ϳ����ع��ü��Ρ�
 **/

// tmp �ǵ�ǰ�Ľ�㣬 ��root ��ʼ,  op ��ָ�ձ��������Ľ��
void check(int &tmp, int op)
{
    if (tmp == op) return;
    if (!isbalance(tmp))
    {
        rebuild(tmp);
        pushup(root, tmp);  // ���ӽڵ��size ���¸��ڵ��size  
        return;
    }
    if (tr[op].val < tr[tmp].val) check(tr[tmp].l, op);
    else check(tr[tmp].r, op);
}

// ��߷�С�ڸ��ģ� �ұ߷� >= ����
void insert(int &u, int val)  // ��һ�㴫���Ĳ����� tr[u].l �� tr[u].r , �������൱��ֱ�� �޸� tr[u].l = xxx 
{
    if (!u)
    {
        build(u, val);
        check(root, u);
        return;
    }
    tr[u].size ++;
    tr[u].fact ++;
    if (val < tr[u].val) insert(tr[u].l, val);
    else insert(tr[u].r, val);
}

// ����ɾ���� ֻ���ǲ���ɾ�� ֻ��fact ���� size
void del(int u, int val)
{
    tr[u].fact --;
    if (tr[u].exist and tr[u].val == val)
    {
        tr[u].exist = false;
        check(root, u);
        return;
    }
    if (val < tr[u].val) del(tr[u].l, val);
    else del(tr[u].r, val);
}

// val ��һ������
int get_rank_by_num(int val)
{
    int tp = root;
    int rank = 1;
    while (tp)
    {
        if (val <= tr[tp].val) tp = tr[tp].l;
        else
        {
            rank += tr[tr[tp].l].fact + tr[tp].exist;
            tp = tr[tp].r;
        }
    }
    return rank;
}

int get_num_by_rank(int k)
{
    int tp = root;
    while (tp)
    {
        if (tr[tr[tp].l].fact + tr[tp].exist == k and tr[tp].exist) break;   
        if (tr[tr[tp].l].fact >= k) 
        {
            tp = tr[tp].l;
        }
        else 
        {
            k -= tr[tr[tp].l].fact + tr[tp].exist;
            tp = tr[tp].r;
        }
    }
    return tr[tp].val;
}

int get_pre(int val)  // ǰ��
{
    int k = get_rank_by_num(val);
    return get_num_by_rank(k - 1);
}
int get_next(int val)
{
    // ע�ⲻ��  getnum(getrank(val) + 1)   ��ֹ 1224 ���������  ����x��x + 1������ͬһ���� 
    int k = get_rank_by_num(val + 1);
    return get_num_by_rank(k);
}

int main()
{
    int n;
    scanf("%d", &n);
    int opt, x;
    while (n --)    
    {
        scanf("%d%d", &opt, &x);
        if (opt == 1)
        {
            insert(root, x);
        }
        else if (opt == 2)
        {
            del(root, x);
        }
        else if (opt == 3)
        {
            printf("%d\n", get_rank_by_num(x));
        }
        else if (opt == 4)
        {
            printf("%d\n", get_num_by_rank(x));
        }
        else if (opt == 5)
        {   
            printf("%d\n", get_pre(x));
        }
        else if (opt == 6)
        {
            printf("%d\n", get_next(x));
        }
    }

    return 0;
}












//treap
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 100010,INF = 1e8;
struct Node{
    int l,r; //�ֱ��ʾ���Ӻ��Һ���
    int key,val;  //key��ʾBST�Ľڵ��ֵ��val��ʾ���е����ȼ�
    int cnt,size;  //cnt��ʾ��ǰ�ڵ���key���ֵĴ�����size��ʾ��ǰ�ڵ�����������ĸ���
}tr[N];
int n,idx; //idxΪ���ڵ�ı�־ֵ
int root; //���ڵ�ı�־ֵ

void pushup(int p)//������Ϣ���¸��ڵ���Ϣ
{
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
    //������� ������+ �Ҷ����� ������+ ��ǰ�ڵ������ִ���(�ظ�����)
}

int get_node(int key)
{
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;//Ĭ�ϴ���ʱ����Ҷ�ӽڵ�
    return idx;
}


//����
void zig(int &p){  //��Ϊ���ڵ�p����֮�ı�,����Ҫ��������


    int q = tr[p].l;//�Ȱ�p�������q������ ���������Ҫ�������Ľڵ㣩
    tr[p].l = tr[q].r;  //q���Һ��ӱ��p������
    tr[q].r = p;   //p��Ϊq���Һ���
    p = q;  //pָ���µĸ��ڵ�
    pushup(tr[p].r),pushup(p);//�ȸ��� ������,�ٸ��¸��ڵ�

}

//����
void zag(int &p){

    int q = tr[p].r;  //�Ȱ�p���Һ���q���������������Ҫ�������Ľڵ㣩
    tr[p].r = tr[q].l;  //q�����ӱ��p���Һ���
    tr[q].l = p;   //p��Ϊq������
    p = q;  //pָ���µĸ��ڵ�
    pushup(tr[p].l),pushup(p); //�ȸ���  ���������ٸ��¸��ڵ�
}

void build()
{
    get_node(-INF),get_node(INF);
    root = 1,tr[1].r = 2;//���ڵ�1�ŵ�,1�ŵ���Ҷ���2�ŵ�
    //build��ʱ��Ҫ©��ά�����Ľṹ
    pushup(root);
    if (tr[1].val < tr[2].val) zag(root);
}


void insert(int &p,int key)  //����󣬿��ܻ�����ȫ����ƽ���������ʣ�Ҫͨ��һ��������������ά����һ��ƽ����
{
    if(!p) p = get_node(key);//�ҵ��˲����λ��,�ڸ�λ���½�һ�����ڵ�
    else if(tr[p].key == key) tr[p].cnt++;//����������е�ֵ cnt++
    else if(tr[p].key>key) //�����µ�ֵ �жϲ������������������� ֱ��Ҷ�ӽڵ�
    {//���Ҫ�����key��p��keyС �ݹ�tr[p]��������tr[p].l
        insert(tr[p].l,key);
        if(tr[tr[p].l].val > tr[p].val) zig(p);//���������val����root.val �ͻ�����
    }
    //ά��val�Ǹ��ڵ�root.val > ���� root.l.val or root.r.val 
    else
    {//���Ҫ�����key��p��key�� �ݹ�tr[p]��������tr[p].r
        insert(tr[p].r,key);
        if(tr[tr[p].r].val > tr[p].val) zag(p);//���������val����root.val �ͻ�����
    }
    pushup(p);
}


void remove(int &p,int key)
{
    if(!p) return;//���ɾ����ֵ������
    if(tr[p].key == key)//�����ǰ���ڵ��ֵǡ���ǵ���Ҫɾ����key
    {
        if(tr[p].cnt>1) tr[p].cnt--;//���cnt>1 cnt--
        else if(tr[p].l || tr[p].r)//�����ж��Ƿ���Ҷ�ӽڵ� 
        {   
            //��Ҫ����ѵ����ʣ����Խ�val�����һ���ڵ㷭��ȥ
            //������p����ȥ�ŵ���������ͬʱ��Ȩֵ�������������ȥ��Ϊ���ڵ㣬һֱ�ݹ鵽��ΪҶ�ӽڵ�ɾ��
            if(!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val)
            {//���û��������,��ô�϶��������� || ��������.val > ��������val
                zig(p);
                remove(tr[p].r,key);
            }
            else//����������p�ŵ������� �ݹ鵽Ҷ�ӽڵ�ɾ��
            {
                zag(p);
                remove(tr[p].l,key);
            }
        }
        else p=0;//�����Ҷ�ӽڵ� ֱ��ɾ��
    }
    else if(tr[p].key > key) remove(tr[p].l,key);//��� Ҫɾ��������˳��key>��ǰ�ڵ�p��tr[p].key ȥp������ɾ
    else remove(tr[p].r,key);
    pushup(p);
}



int get_rank_by_key(int p,int key)//ͨ����ֵ������  ��p�����Ǵ�&p
{
    if(!p) return 0;//���p������ ����0
    if(tr[p].key==key) return tr[tr[p].l].size+1;//���key�͵�ǰ�ڵ�key��� ����=���������Ĵ�С+1(��ǰ�ڵ�)
    if(tr[p].key>key) return get_rank_by_key(tr[p].l,key);//©��return
    //˵��Ҫ�ҵ�key�ȵ�ǰ�ڵ�С ȥ��ǰ�ڵ���������
    return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r,key);
    //ȥ�ұ��ҷ��ص����ұ�����������,���Ի��ü��ϸ��ڵ�root���ĸ����Լ����ڵ�����������root.l.size
}

int get_key_by_rank(int p,int rank)//ͨ����������ֵ ��p�����Ǵ�&p
{
    if(!p) return INF;//p������ �򷵻ز����ܴ��ڵ�����
    if(tr[tr[p].l].size >=rank) return get_key_by_rank(tr[p].l,rank);//������������ĸ���>rank,��ȥ��������
    if(tr[tr[p].l].size+tr[p].cnt>=rank) return tr[p].key;//������+��ǰ�ڵ����>=rank,����ǵ�ǰ�ڵ�
    //������+��ǰ�ڵ����<rank,��ݹ�������,ͬʱ���´���rank-������-��ǰ�ڵ����
    return get_key_by_rank(tr[p].r,rank-tr[tr[p].l].size-tr[p].cnt);//-tr[p].cnt
}

int get_prev(int p,int key)//�ҵ��ϸ�С��key�����е������ ��p�����Ǵ�&p
{
    if(!p)return -INF;
    if(tr[p].key>=key) return get_prev(tr[p].l,key);//��ǰ�����>=key ��Ҫ�ҵ����ڵ�ǰ�ڵ����������
    return max(tr[p].key, get_prev(tr[p].r, key));

}

int get_next(int p,int key)//�ҵ��ϸ����key�����е���С�� ��p�����Ǵ�&p
{
    if (!p) return INF;
    if (tr[p].key <= key) return get_next(tr[p].r, key);
    return min(tr[p].key, get_next(tr[p].l, key));
}





int main(){

    build();
    cin >> n;
    for(int i = 0;i < n;++i){
        int opt,x;
        scanf("%d%d",&opt,&x);
        if(opt == 1) insert(root,x);  /**����**/

        /**ɾ����ֵx(���ж����ͬ������Ӧֻɾ��һ��) **/
        else if(opt == 2) remove(root,x);  
        /** ��ѯ��ֵx������(���ж����ͬ������Ӧ�����С������)��**/                                   
        else if (opt == 3) printf("%d\n", get_rank_by_key(root, x) - 1); 
        /** ��ѯ����Ϊx����ֵ��**/
        else if (opt == 4) printf("%d\n", get_key_by_rank(root, x + 1)); 
        /** ����ֵx��ǰ��(ǰ������ΪС��x��������) **/
        else if (opt == 5) printf("%d\n", get_prev(root, x));  
        /** ����ֵx�ĺ��(��̶���Ϊ����x����С����)**/
        else printf("%d\n", get_next(root, x));   
    }
}






//splay��չ��
#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

const int inf=0x3f3f3f3f;

int n;

struct Tree{
    int fa;//fa��ʾ�õ�ĸ����
    int son[2];//son[0]��ʾ�õ�������,son[1]��ʾ�õ���Ҷ���
    int cnt;//cnt��ʾ�õ������ϳ��ֵĴ���
    int siz;//siz��ʾ�Ըõ�Ϊ���������Ĵ�С
    int val;//val��ʾ�õ��Ȩֵ
}tree[MAXN];

int root,tot;//�ֱ��ʾ�������ܽ����

void pushup(int x)//�ϴ�����
{
    tree[x].siz=tree[tree[x].son[0]].siz+tree[tree[x].son[1]].siz+tree[x].cnt;
}


void rotate(int x)//��ת����(��������������)
{
    int y=tree[x].fa;//y��x�ĸ����
    int z=tree[y].fa;//z��y�ĸ����,��z��x���游���
    int k=tree[y].son[1]==x;//�ж�x��y����һ������,k=0��ʾ�����,k=1��ʾ�Ҷ���
    tree[z].son[tree[z].son[1]==y]=x;//z��ԭ��y��λ�ñ�Ϊx
    tree[x].fa=z;//x�ĸ�����޸�Ϊz
    tree[y].son[k]=tree[x].son[k^1];
    //��x��y�������(k=0),����y�������(k=0)����xԭ�����Ҷ���(k^1)
    //��x��y���Ҷ���(k=1),����y���Ҷ���(k=1)����xԭ���������(k^1)
    tree[tree[x].son[k^1]].fa=y;//����xԭ����(k^1)���ӵĸ����Ϊy
    tree[x].son[k^1]=y;//����x��(k^1)����Ϊy
    tree[y].fa=x;//����y�ĸ����x
    pushup(y),pushup(x);//�ϴ�����
}


void splay(int x,int goal)//��x��תΪgoal�Ķ���,���goal��0,����ת����
{
    while(tree[x].fa!=goal)//һֱ��ת��x��Ϊgoal�Ķ���
    {
        int y=tree[x].fa;//y��x�ĸ����
        int z=tree[y].fa;//z��y�ĸ����,��z��x���游���
        if(z!=goal)//x�����Ƚ��z����Ŀ��
        {
            if((tree[y].son[1]==x)^(tree[z].son[1]==y))
                rotate(x);//����������תx
            else rotate(y);//����������תy
        }
        rotate(x);//(����ǰ����ʲô����)������תx
    }
    if(goal==0)//���goal��0,�򽫸�������Ϊx
        root=x;
}

void Find(int x)//����x��λ��,��������ת�������
{
    int p=root;//�Ӹ�������
    if(p==0)//���ǿ���
        return ;
    while(tree[p].son[x>tree[p].val]&&x!=tree[p].val)
        p=tree[p].son[x>tree[p].val];
    //ֱ��������x=tree[p].valֹͣ,
    //�������x>tree[p].val,������������,���x<tree[p].val������������
    splay(p,0);
}

void Insert(int x)
{
    int p=root,fa=0;//�Ӹ����p����,p�ĸ����Ϊfa
    while(p!=0&&x!=tree[p].val)//��p���ڲ���û���ƶ�����ǰ��ֵ
    {
        fa=p;//p������,fa��Ϊp
        p=tree[p].son[x>tree[p].val];//��������������������,��֮��������������
    }
    if(p!=0)//���ڸ�ֵ��λ��
        tree[p].cnt++;//����+1
    else//�����ڸ�ֵ��λ��,�½�һ����㱣��
    {
        p=++tot;//�½ڵ��λ��
        if(fa!=0)//��������Ǹ�
            tree[fa].son[x>tree[fa].val]=p;
        tree[p].son[0]=tree[p].son[1]=0;//�½��ĵ㲻���ڶ���
        tree[p].fa=fa;//���¸����
        tree[p].val=x;//����Ȩֵ
        tree[p].cnt=1;//��������
        tree[p].siz=1;//�����Ըõ�Ϊ���������Ĵ�С
    }
    splay(p,0);//�ѵ�ǰλ���Ƶ���,��֤�ṹ��ƽ��
}


int Pre_Next(int x,int state)//��ѯǰ���ͺ�̺ϲ�,state=0(��ǰ��),state=1(�Һ��)
{
    Find(x);//��x��ת�������
    int p=root;//�Ӹ�������
    //����x���ܲ�������,find�����ҵ�����ӽ�x�ĵ�,��root������x��ǰ�����ߺ��
    if(tree[p].val>x&&state==1)//p(root)Ϊ���
        return p;
    if(tree[p].val<x&&state==0)//p(root)Ϊǰ��
        return p;

    p=tree[root].son[state];//ǰ���������������,��̵��������Ҷ���

    //ǰ�����������Ȼ�����Ÿ�����ӵ��ұ�һֱ��
    //��̵����Ҷ���Ȼ�����Ÿ��Ҷ��ӵ����һֱ��
    while(tree[p].son[state^1]!=0)
        p=tree[p].son[state^1];
    return p;
}


void Remove(int x)//ɾ��x
{
    int last=Pre_Next(x,0);//����x��ǰ��
    int nex=Pre_Next(x,1);//����x�ĺ��
    splay(last,0),splay(nex,last);
    //��ǰ����ת�������,�����ת������������
    //��ʱ�����ǰ�����Ҷ���,x�Ǻ�̵������,����x��Ҷ�ӽ��
    int k=tree[nex].son[0];//��̵������
    if(tree[k].cnt>1)//�����������һ��
    {
        tree[k].cnt--;//����-1
        splay(k,0);//��ת
    }
    else tree[nex].son[0]=0;//������ֱ�Ӷ���(������)
}


int kth(int x)//��ѯ����Ϊx��λ��
{
    int p=root;
    if(tree[p].siz<x)//��ǰ��������ô����
        return -1;//������
    while(1)
    {
        if(x<=tree[tree[p].son[0]].siz)//�����
            p=tree[p].son[0];
        else if(x>tree[tree[p].son[0]].siz+tree[p].cnt)//�Ҷ���
        {
            x-=tree[tree[p].son[0]].siz+tree[p].cnt;
            p=tree[p].son[1];
        }
        else return p;//��ǰ���
    }
}


int main()
{
    scanf("%d",&n);
    Insert(inf);
    Insert(-inf);
    for(int i=1;i<=n;i++)
    {
        int op,num;
        scanf("%d %d",&op,&num);
        if(op==1)//������ֵnum
            Insert(num);
        else if(op==2)//ɾ����ֵnum
            Remove(num);
        else if(op==3)//��ѯ��ֵnum������
        {
            Find(num);
            printf("%d\n",tree[tree[root].son[0]].siz);
            //���ڱ�,�ʽ������Ҫ��+1
        }
        else if(op==4)//��ѯ����Ϊnum����ֵ
            printf("%d\n",tree[kth(num+1)].val);
        else if(op==5)//����ֵnum��ǰ��
            printf("%d\n",tree[Pre_Next(num,0)].val);
        else if(op==6)//����ֵnum�ĺ��
            printf("%d\n",tree[Pre_Next(num,1)].val);        

    }



    return 0;
}

