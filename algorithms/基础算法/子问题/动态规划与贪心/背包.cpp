//01背包 
#include<iostream>
#include<cstdio>
using namespace std;
int a[1010],n,m;
int main(){
    scanf("%d%d",&m,&n);
    for(int i=0;i<m;i++){
        int w,v;
        scanf("%d%d",&w,&v);
        for(int j=n;j>=w;j--) a[j]=max(a[j],a[j-w]+v);
    }
    cout<<a[n]<<endl;
    return 0;
}

//完全背包
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[1010],n;

int main(){
    
    int v;
    cin>>n>>v;
    for(int i=0;i<n;i++){
        int u,w;
        cin>>u>>w;
        for(int j=u;j<=v;j++){
            a[j]=max(a[j],a[j-u]+w);
        }
    }
    cout<<a[v]<<endl;
    
    
}


//多重背包
#include<iostream>
using namespace std;
const int N=2010;
int a[N],n;
int sv[20],sw[20],cnt;
int main(){
    int m;
    cin>>m>>n;
    while(m--){
        int v,w,s;
        cin>>v>>w>>s;
        cnt=0;
        int p=1;
        while(p<=s){
            sv[cnt]=p*v;
            sw[cnt++]=p*w;
            s-=p;
            p<<=1;
        }
        if(s){
            sv[cnt]=s*v;
            sw[cnt++]=s*w;
        }
        for(int i=0;i<cnt;i++)
            for(int j=n;j>=sv[i];j--) a[j]=max(a[j],a[j-sv[i]]+sw[i]); 
    }
    cout<<a[n]<<endl;
}


//分组背包
#include<iostream>
#include<cstring>
using namespace std;
const int N=110;
int a[N],n,b[N];
int main(){
    int m;
    cin>>m>>n;
    while(m--){
        int v,w,s;
        cin>>s;
        memcpy(b,a,sizeof a);
        while(s--){
            cin>>v>>w;
            for(int i=n;i>=v;i--) a[i]=max(a[i],b[i-v]+w);
        }
    }
    cout<<a[n];
} 
