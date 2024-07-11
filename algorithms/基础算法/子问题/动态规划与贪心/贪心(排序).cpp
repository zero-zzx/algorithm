//仓库选址
#include<iostream>
#include<algorithm>
using namespace std;
int a[100010],n,res;
int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    for(int i=0;i<n;i++) res+=a[i]-a[i>>1];
    cout<<res;
}

//排队打水
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
typedef long long ll;
int a[N],n;
ll b[N];
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    sort(a,a+n);
    ll res=0;
    for(int i=1;i<n;i++){
        b[i]=a[i-1]+b[i-1];
        res+=b[i];
    }
    cout<<res<<endl;
    return 0;
}



//合并果子
#include<queue>
using namespace std;
priority_queue<int,vector<int>,greater<int> >q;
long long res;
int main(){
    int n;
    cin>>n;
    int x;
    
    for(int i=0;i<n;i++){
        cin>>x;
        q.push(x);
    }
    for(int i=1;i<n;i++){
        int x=q.top();
        q.pop();
        int y=q.top();
        q.pop();
        int z=x+y;
        res+=z;
        q.push(z);
    }
    cout<<res<<endl;
    return 0;
} 
