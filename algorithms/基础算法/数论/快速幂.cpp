//快速幂 
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
ll qpow(ll a,ll b,ll p){
    ll res=1;
    while(b){
        if(b&1) res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
int main(){
    int n;
    cin>>n;
    while(n--){
        int a,b,p;
        scanf("%d%d%d",&a,&b,&p);
        cout<<qpow(a,b,p)<<endl;
    }
    return 0;
}


//快速幂求逆元
#include<iostream>
using namespace std;
typedef unsigned long long ull;
ull a,mod;
ull qpow(ull x,ull y){
    ull res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>a>>mod;
        if(a%mod==0) cout<<"impossible"<<endl;
        else cout<<qpow(a,mod-2)<<endl;
    }
}


//线性求逆元
inv[1] = 1;
for(int i = 2;i<=n;i++)
{
    inv[i] = (ll)(p - p/i)*(inv[p%i]) % p;
} 
