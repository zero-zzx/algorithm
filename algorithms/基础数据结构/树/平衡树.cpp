//普通平衡树
#include<bits/stdc++.h>
using namespace std;
const int N = 100010, INF = 1e8;
int n;
struct Node
{
    int l, r;
    int k;
    int val;//堆中的编号
    int cnt, size;
}tr[N];
int root, idx;
void pushup(int u)
{
    tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].cnt;//上传节点信息，更新size
}
int new_node(int k)
{
    tr[ ++ idx].k = k;
    tr[idx].val = rand();//尽量随机，随手给个就行
    tr[idx].cnt = 1;
    tr[idx].size = 1;
    return idx;
}
void zig(int &u)//左右旋，没啥好说的，自己在纸上画一下就知道了
{
    int q = tr[u].l;
    tr[u].l = tr[q].r;
    tr[q].r = u;
    u = q;
    pushup(tr[u].r);
    pushup(u);//最后一定要记得上传，不然完了
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
void build()//建树操作，为了正确性增加两个哨兵，防止越界
{
    new_node(-INF), new_node(INF);
    root = 1, tr[1].r = 2;//初始化一下
    pushup(root);//上传信息
    if(tr[1].val< tr[2].val) zag(root);//不平衡了就旋转
}
void insert(int &u, int k)
{
    if(u == 0) u = new_node(k);//如果走到空了，就新建
    else
    {
        if(tr[u].k == k)//如果找到了相同的节点，就cnt++
        {
            tr[u].cnt ++;
        }
        else
        {
            if(tr[u].k > k)//否则看看是在左边还是在右边
            {
                insert(tr[u].l, k);
                if(tr[tr[u].l].val > tr[u].val) zig(u);//不平衡立马调整
            }
            else
            {
                insert(tr[u].r, k);
                if(tr[tr[u].r].val > tr[u].val) zag(u); 
            }
        }
    }
    pushup(u);//最后上传一下，是不是和线段树有点像啊？
}
void del(int &u, int k)//删除操作
{
    if(u == 0) return ;//如果没了说明节点不存在，就不管了。
    if(tr[u].k == k)//如果找到了这个点
    {
        if(tr[u].cnt > 1) tr[u].cnt --;//大于一好说，直接cnt --
        else//不大于一
        {
            if(tr[u].l || tr[u].r)//先看看是不是叶节点
            {
                if(!tr[u].r || tr[tr[u].l].val) 
                {
                    zig(u);
                    del(tr[u].r, k);//记得维护平衡哦
                }
                else
                {
                    zag(u);
                    del(tr[u].l, k);
                }
            }
            else u = 0;//是的话不用考虑平衡问题，直接删就是了
        }
    }
    else if(tr[u].k > k) del(tr[u].l, k);//如果没有找到就判断一下在左右两边的哪一边
    else del(tr[u].r, k);//找一下
    pushup(u);//上传更改
}
int get_rank(int u, int k)
{
    if(u == 0) return 0;//是0随便返回就行
    if(tr[u].k == k) return tr[tr[u].l].size + 1;//相等了那排名应该就是左边的数量加上自己
    if(tr[u].k > k) return get_rank(tr[u].l, k);//大了找左边
    return tr[tr[u].l].size + tr[u].cnt + get_rank(tr[u].r, k);//找右边
} 
int get_key(int u, int rank)
{
    if(u == 0) return INF;
    if(tr[tr[u].l].size >= rank) return get_key(tr[u].l, rank);//找左边
    if(tr[tr[u].l].size + tr[u].cnt >= rank) return tr[u].k;//如果满足条件就直接return
    return get_key(tr[u].r, rank - tr[tr[u].l].size - tr[u].cnt);//不然就找右边
}
int get_pr(int u, int k)//前驱
{
    if(u == 0) return -INF;
    if(tr[u].k >= k) return get_pr(tr[u].l, k);//找左边
    return max(get_pr(tr[u].r, k), tr[u].k);//可能是右边可能是这个数，所以用个max
}
int get_ne(int u, int k)//后继
{
    if(u == 0) return INF;//后继的写法和前驱相反，大家可以注意一下
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
        else cout << get_ne(root, x) << endl;//读入操作并进行处理
    }
    return 0;
}




//替罪羊树
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 100010;
const double alpha = 0.75;    // 啊啊啊   double ！！

struct Scape_goat
{
    int l, r;
    int val;
    int size;   //  子树的大小（包括它自己）， 包括被打了删除标记的结点
    int exist;
    int fact;
}tr[N];
int idx;
int root;
int rec[N], cnt;

// 每次新建节点只管他自己，不需要管儿子们
void build(int &u, int val)
{
    u = ++ idx;   // 开一个位置
    tr[u].val = val;
    tr[u].size = 1;
    tr[u].fact = 1;
    tr[u].exist = true;
}

/** 
 *  重构条件 ：      当前节点的左子树或右子树的size  > 当前结点的大小 乘 一个平衡因子alpha (一般取0.75)
 *               或者以当前结点为根的子树中被删掉的点 > 该子树大小的 30% 
 **/

bool isbalance(int u)
{
    if (tr[tr[u].l].size > tr[u].size * alpha || tr[tr[u].r].size > tr[u].size * alpha)  return false;
    if (tr[u].size - tr[u].fact > tr[u].size * 0.3) return false;
    return true;
}

/**
 * 重构： 将当前子树先中序遍历，  压扁，然后再拎起来
 **/

void inorder(int u)
{
    if (!u) return;
    inorder(tr[u].l);
    if (tr[u].exist) rec[++ cnt] = u;
    inorder(tr[u].r);
}

// pushup 的时候， 由于没有记录子节点到父节点的指针，  所以只能头递归
void pushup(int tmp, int op)
{
    if (!tmp) return;    //  整棵树都被删掉的情况
    if (tr[tmp].val > tr[op].val)
    {
        pushup(tr[tmp].l, op);
    }
    else pushup(tr[tmp].r, op);

    tr[tmp].size = tr[tr[tmp].l].size + tr[tr[tmp].r].size + 1;
    // fact 不需要修改
}

// l, r 指rec数组中存的子树中存在的结点
// u 是l ,r 这段区间所构成子树的根
void lift(int l, int r, int &u)
{
    if (l == r)   // 叶子结点
    {
        u = rec[l];    // 同样 传引用 将这个节点设置为他的父亲节点的儿子
        tr[u].l = tr[u].r = 0;
        tr[u].size = 1;
        tr[u].fact = 1;
        return ;
    }
    int mid = l + r >> 1;    // 找根
    // 因为 该树的定义为 左子树严格小于根， 所以 需要放置 连续mid左侧连续几个数相等的情况
    // 注意这儿的 l ,r mid 并不是结点，  rec[l, r, mid] 才是结点！！！
    while (mid > l and tr[rec[mid]].val == tr[rec[mid - 1]].val) mid --;
    u = rec[mid];
    if (mid == l)   tr[u].l = 0;
    else   lift(l, mid - 1, tr[u].l);   // 注意递归两边的时候传mid - 1 与 mid + 1, 千万不能有mid,  否则可能自己的根是自己，导致递归炸掉

    lift(mid + 1, r, tr[u].r);
    tr[u].size = tr[u].fact = r - l + 1;
}

void rebuild(int &u)
{
    cnt = 0;
    inorder(u);
    if (cnt == 0)   // 这颗子树整体都应该被删掉
    {
        u = 0;      // 即他作为他的父节点的子结点变成了0， 传引用的好书
        return;
    }
    // 否则， 分治 拎起来
    lift(1, cnt, u);
}

/**
 * 检查并判断一棵树是否需要重构
 * 从根节点向当前被操作的结点一路判断，   找到第一个需要被重构的结点，并重构它
 * 注意顺序不能反， 如果反过来找，就可能重构好几次。
 **/

// tmp 是当前的结点， 从root 开始,  op 代指刚被操作过的结点
void check(int &tmp, int op)
{
    if (tmp == op) return;
    if (!isbalance(tmp))
    {
        rebuild(tmp);
        pushup(root, tmp);  // 用子节点的size 更新父节点的size  
        return;
    }
    if (tr[op].val < tr[tmp].val) check(tr[tmp].l, op);
    else check(tr[tmp].r, op);
}

// 左边放小于根的， 右边放 >= 根的
void insert(int &u, int val)  // 上一层传来的参数是 tr[u].l 或 tr[u].r , 传引用相当于直接 修改 tr[u].l = xxx 
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

// 懒惰删除， 只打标记不真删， 只减fact 不减 size
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

// val 不一定存在
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

int get_pre(int val)  // 前驱
{
    int k = get_rank_by_num(val);
    return get_num_by_rank(k - 1);
}
int get_next(int val)
{
    // 注意不能  getnum(getrank(val) + 1)   防止 1224 这种情况，  排名x和x + 1可能是同一个数 
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
    int l,r; //分别表示左孩子和右孩子
    int key,val;  //key表示BST的节点键值，val表示堆中的优先级
    int cnt,size;  //cnt表示当前节点中key出现的次数，size表示当前节点的子树中树的个数
}tr[N];
int n,idx; //idx为树节点的标志值
int root; //根节点的标志值

void pushup(int p)//儿子信息更新父节点信息
{
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
    //左儿子树 数个数+ 右儿子树 数个数+ 当前节点数出现次数(重复次数)
}

int get_node(int key)
{
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;//默认创建时都是叶子节点
    return idx;
}


//右旋
void zig(int &p){  //因为根节点p会随之改变,所以要传入引用


    int q = tr[p].l;//先把p的左儿子q存下来 （这个就是要旋上来的节点）
    tr[p].l = tr[q].r;  //q的右孩子变成p的左孩子
    tr[q].r = p;   //p成为q的右孩子
    p = q;  //p指向新的根节点
    pushup(tr[p].r),pushup(p);//先更新 右子树,再更新根节点

}

//左旋
void zag(int &p){

    int q = tr[p].r;  //先把p的右孩子q存下来（这个就是要旋上来的节点）
    tr[p].r = tr[q].l;  //q的左孩子变成p的右孩子
    tr[q].l = p;   //p成为q的左孩子
    p = q;  //p指向新的根节点
    pushup(tr[p].l),pushup(p); //先更新  左子树，再更新根节点
}

void build()
{
    get_node(-INF),get_node(INF);
    root = 1,tr[1].r = 2;//根节点1号点,1号点的右儿子2号点
    //build的时候不要漏了维护树的结构
    pushup(root);
    if (tr[1].val < tr[2].val) zag(root);
}


void insert(int &p,int key)  //插入后，可能还不完全满足平衡树的性质，要通过一步步左旋或右旋维护成一颗平衡树
{
    if(!p) p = get_node(key);//找到了插入的位置,在该位置新建一个树节点
    else if(tr[p].key == key) tr[p].cnt++;//如果插入已有的值 cnt++
    else if(tr[p].key>key) //插入新的值 判断插入左子树还是右子树 直到叶子节点
    {//如果要插入的key比p的key小 递归tr[p]的左子树tr[p].l
        insert(tr[p].l,key);
        if(tr[tr[p].l].val > tr[p].val) zig(p);//如果左子树val大于root.val 就换上来
    }
    //维护val是根节点root.val > 子树 root.l.val or root.r.val 
    else
    {//如果要插入的key比p的key大 递归tr[p]的右子树tr[p].r
        insert(tr[p].r,key);
        if(tr[tr[p].r].val > tr[p].val) zag(p);//如果右子树val大于root.val 就换上来
    }
    pushup(p);
}


void remove(int &p,int key)
{
    if(!p) return;//如果删除的值不存在
    if(tr[p].key == key)//如果当前树节点的值恰好是等于要删除的key
    {
        if(tr[p].cnt>1) tr[p].cnt--;//如果cnt>1 cnt--
        else if(tr[p].l || tr[p].r)//否则判断是否有叶子节点 
        {   
            //需要满足堆的性质，所以将val大的哪一个节点翻上去
            //右旋把p翻下去放到右子树，同时把权值大的左子树翻上去成为根节点，一直递归到成为叶子节点删除
            if(!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val)
            {//如果没有右子树,那么肯定可以右旋 || 左子树的.val > 右子树的val
                zig(p);
                remove(tr[p].r,key);
            }
            else//否则左旋把p放到左子树 递归到叶子节点删除
            {
                zag(p);
                remove(tr[p].l,key);
            }
        }
        else p=0;//如果是叶子节点 直接删除
    }
    else if(tr[p].key > key) remove(tr[p].l,key);//如果 要删除的中序顺序key>当前节点p的tr[p].key 去p左子树删
    else remove(tr[p].r,key);
    pushup(p);
}



int get_rank_by_key(int p,int key)//通过数值找排名  传p而不是传&p
{
    if(!p) return 0;//如果p不存在 返回0
    if(tr[p].key==key) return tr[tr[p].l].size+1;//如果key和当前节点key相等 排名=左子树数的大小+1(当前节点)
    if(tr[p].key>key) return get_rank_by_key(tr[p].l,key);//漏了return
    //说明要找的key比当前节点小 去当前节点左子树找
    return tr[tr[p].l].size + tr[p].cnt + get_rank_by_key(tr[p].r,key);
    //去右边找返回的是右边子树的排名,所以还得加上根节点root数的个数以及根节点左子树总数root.l.size
}

int get_key_by_rank(int p,int rank)//通过排名找数值 传p而不是传&p
{
    if(!p) return INF;//p不存在 则返回不可能存在的排名
    if(tr[tr[p].l].size >=rank) return get_key_by_rank(tr[p].l,rank);//如果左子树数的个数>rank,则去左子树找
    if(tr[tr[p].l].size+tr[p].cnt>=rank) return tr[p].key;//左子树+当前节点个数>=rank,则就是当前节点
    //左子树+当前节点个数<rank,则递归右子树,同时往下传的rank-左子树-当前节点个数
    return get_key_by_rank(tr[p].r,rank-tr[tr[p].l].size-tr[p].cnt);//-tr[p].cnt
}

int get_prev(int p,int key)//找到严格小于key的数中的最大数 传p而不是传&p
{
    if(!p)return -INF;
    if(tr[p].key>=key) return get_prev(tr[p].l,key);//当前这个数>=key 则要找的数在当前节点的左子树里
    return max(tr[p].key, get_prev(tr[p].r, key));

}

int get_next(int p,int key)//找到严格大于key的数中的最小数 传p而不是传&p
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
        if(opt == 1) insert(root,x);  /**插入**/

        /**删除数值x(若有多个相同的数，应只删除一个) **/
        else if(opt == 2) remove(root,x);  
        /** 查询数值x的排名(若有多个相同的数，应输出最小的排名)。**/                                   
        else if (opt == 3) printf("%d\n", get_rank_by_key(root, x) - 1); 
        /** 查询排名为x的数值。**/
        else if (opt == 4) printf("%d\n", get_key_by_rank(root, x + 1)); 
        /** 求数值x的前驱(前驱定义为小于x的最大的数) **/
        else if (opt == 5) printf("%d\n", get_prev(root, x));  
        /** 求数值x的后继(后继定义为大于x的最小的数)**/
        else printf("%d\n", get_next(root, x));   
    }
}






//splay伸展树
#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

const int inf=0x3f3f3f3f;

int n;

struct Tree{
    int fa;//fa表示该点的父结点
    int son[2];//son[0]表示该点的左儿子,son[1]表示该点的右儿子
    int cnt;//cnt表示该点在树上出现的次数
    int siz;//siz表示以该点为根的子树的大小
    int val;//val表示该点的权值
}tree[MAXN];

int root,tot;//分别表示根结点和总结点数

void pushup(int x)//上传操作
{
    tree[x].siz=tree[tree[x].son[0]].siz+tree[tree[x].son[1]].siz+tree[x].cnt;
}


void rotate(int x)//旋转操作(涵盖左旋和右旋)
{
    int y=tree[x].fa;//y是x的父结点
    int z=tree[y].fa;//z是y的父结点,即z是x的祖父结点
    int k=tree[y].son[1]==x;//判断x是y的哪一个儿子,k=0表示左儿子,k=1表示右儿子
    tree[z].son[tree[z].son[1]==y]=x;//z的原来y的位置变为x
    tree[x].fa=z;//x的父结点修改为z
    tree[y].son[k]=tree[x].son[k^1];
    //若x是y的左儿子(k=0),则让y的左儿子(k=0)等于x原来的右儿子(k^1)
    //若x是y的右儿子(k=1),则上y的右儿子(k=1)等于x原来的左儿子(k^1)
    tree[tree[x].son[k^1]].fa=y;//更新x原来的(k^1)儿子的父结点为y
    tree[x].son[k^1]=y;//更新x的(k^1)儿子为y
    tree[y].fa=x;//更新y的父结点x
    pushup(y),pushup(x);//上传操作
}


void splay(int x,int goal)//将x旋转为goal的儿子,如果goal是0,则旋转至根
{
    while(tree[x].fa!=goal)//一直旋转到x成为goal的儿子
    {
        int y=tree[x].fa;//y是x的父结点
        int z=tree[y].fa;//z是y的父结点,即z是x的祖父结点
        if(z!=goal)//x的祖先结点z不是目标
        {
            if((tree[y].son[1]==x)^(tree[z].son[1]==y))
                rotate(x);//折线型先旋转x
            else rotate(y);//共线型先旋转y
        }
        rotate(x);//(无论前面是什么类型)都再旋转x
    }
    if(goal==0)//如果goal是0,则将根结点更新为x
        root=x;
}

void Find(int x)//查找x的位置,并将其旋转至根结点
{
    int p=root;//从根结点出发
    if(p==0)//树是空树
        return ;
    while(tree[p].son[x>tree[p].val]&&x!=tree[p].val)
        p=tree[p].son[x>tree[p].val];
    //直到检索到x=tree[p].val停止,
    //否则如果x>tree[p].val,在右子树查找,如果x<tree[p].val在左子树查找
    splay(p,0);
}

void Insert(int x)
{
    int p=root,fa=0;//从根结点p出发,p的父结点为fa
    while(p!=0&&x!=tree[p].val)//当p存在并且没有移动到当前的值
    {
        fa=p;//p向下走,fa变为p
        p=tree[p].son[x>tree[p].val];//若大于则在右子树查找,反之则在左子树查找
    }
    if(p!=0)//存在该值的位置
        tree[p].cnt++;//计数+1
    else//不存在该值的位置,新建一个结点保存
    {
        p=++tot;//新节点的位置
        if(fa!=0)//如果父结点非根
            tree[fa].son[x>tree[fa].val]=p;
        tree[p].son[0]=tree[p].son[1]=0;//新建的点不存在儿子
        tree[p].fa=fa;//更新父结点
        tree[p].val=x;//更新权值
        tree[p].cnt=1;//更新数量
        tree[p].siz=1;//更新以该点为根的子树的大小
    }
    splay(p,0);//把当前位置移到根,保证结构的平衡
}


int Pre_Next(int x,int state)//查询前驱和后继合并,state=0(找前驱),state=1(找后继)
{
    Find(x);//将x旋转至根结点
    int p=root;//从根结点出发
    //由于x可能不在树上,find函数找到是最接近x的点,故root可能是x的前驱或者后继
    if(tree[p].val>x&&state==1)//p(root)为后继
        return p;
    if(tree[p].val<x&&state==0)//p(root)为前驱
        return p;

    p=tree[root].son[state];//前驱到达它的左儿子,后继到达它的右儿子

    //前驱到达左儿子然后沿着该左儿子的右边一直走
    //后继到达右儿子然后沿着该右儿子的左边一直走
    while(tree[p].son[state^1]!=0)
        p=tree[p].son[state^1];
    return p;
}


void Remove(int x)//删除x
{
    int last=Pre_Next(x,0);//查找x的前驱
    int nex=Pre_Next(x,1);//查找x的后继
    splay(last,0),splay(nex,last);
    //将前驱旋转到根结点,后继旋转到根结点的下面
    //此时后继是前驱的右儿子,x是后继的左儿子,并且x是叶子结点
    int k=tree[nex].son[0];//后继的左儿子
    if(tree[k].cnt>1)//如果个数超过一个
    {
        tree[k].cnt--;//计数-1
        splay(k,0);//旋转
    }
    else tree[nex].son[0]=0;//这个结点直接丢掉(不存在)
}


int kth(int x)//查询排名为x的位置
{
    int p=root;
    if(tree[p].siz<x)//当前树上无这么多数
        return -1;//不存在
    while(1)
    {
        if(x<=tree[tree[p].son[0]].siz)//左儿子
            p=tree[p].son[0];
        else if(x>tree[tree[p].son[0]].siz+tree[p].cnt)//右儿子
        {
            x-=tree[tree[p].son[0]].siz+tree[p].cnt;
            p=tree[p].son[1];
        }
        else return p;//当前结点
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
        if(op==1)//插入数值num
            Insert(num);
        else if(op==2)//删除数值num
            Remove(num);
        else if(op==3)//查询数值num的排名
        {
            Find(num);
            printf("%d\n",tree[tree[root].son[0]].siz);
            //有哨兵,故结果不需要再+1
        }
        else if(op==4)//查询排名为num的数值
            printf("%d\n",tree[kth(num+1)].val);
        else if(op==5)//求数值num的前驱
            printf("%d\n",tree[Pre_Next(num,0)].val);
        else if(op==6)//求数值num的后继
            printf("%d\n",tree[Pre_Next(num,1)].val);        

    }



    return 0;
}

