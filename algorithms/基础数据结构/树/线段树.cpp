#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const int N=100010;
struct Node{
    LL x,tag;
    int l,r;
}tr[N<<2];
int a[N],n;
LL build(int l,int r,int p){
    tr[p].l=l;
    tr[p].r=r;
    if(l==r){
        tr[p].x=a[l];
    }else{
        int mid=l+r>>1;
        build(l,mid,p<<1);
        build(mid+1,r,p<<1|1);
        tr[p].x=tr[p<<1].x+tr[p<<1|1].x;
    }
}

void down(int p){
    LL x=tr[p].tag;
    tr[p<<1].tag+=x;
    tr[p<<1|1].tag+=x;
    tr[p<<1].x+=(tr[p<<1].r-tr[p<<1].l+1)*x;
    tr[p<<1|1].x+=(tr[p<<1|1].r-tr[p<<1|1].l+1)*x;
    tr[p].tag=0;
}
void add(int p,int l,int r,LL k){
    if(tr[p].l>r||tr[p].r<l) return;
    if(tr[p].l>=l&&tr[p].r<=r){
        tr[p].x+=(tr[p].r-tr[p].l+1)*k;
        tr[p].tag+=k;
        return;
    }
    down(p);
    add(p<<1,l,r,k);
    add(p<<1|1,l,r,k);
    tr[p].x=tr[p<<1].x+tr[p<<1|1].x;
}

LL query(int p,int l,int r){
    if(tr[p].l>r||tr[p].r<l) return 0;
    if(tr[p].l>=l&&tr[p].r<=r){
        return tr[p].x;
    }
    down(p);
    return query(p<<1,l,r)+query(p<<1|1,l,r);
}

int main(){
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,n,1);
    while(m--){
        char ch;
        cin>>ch;
        if(ch=='Q'){
            int l,r;
            cin>>l>>r;
            cout<<query(1,l,r)<<endl;
        }else{
            int l,r,k;
            cin>>l>>r>>k;
            add(1,l,r,k);
        }
    }
    return 0;
}
