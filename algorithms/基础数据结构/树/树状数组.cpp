#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const int N=100010;
int a[N],n;
LL tr[N];
void add(int idx,int x){
    while(idx<n){
        tr[idx]+=x;
        idx+=idx&-idx;
    }
}
LL sum(int idx){
    LL res=0;
    while(idx){
        res+=tr[idx];
        idx-=idx&-idx;
    }
    return res;
}
int main(){
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        add(i,a[i]-a[i-1]);
    }
    while(m--){
        char ch;
        cin>>ch;
        if(ch=='C'){
            int l,r,d;
            cin>>l>>r>>d;
            add(l,d);
            add(r+1,-d);
        }else{
            int x;
            cin>>x;
            cout<<sum(x)<<endl;
        }
        
    }
}
