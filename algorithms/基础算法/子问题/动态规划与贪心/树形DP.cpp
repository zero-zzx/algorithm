//没有上司的舞会
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=6010;
int w[N],n,f[N][2];
int e[N],ne[N],h[N],idx;
bool st[N];
void add(int u,int v){
    e[idx]=v;ne[idx]=h[u];h[u]=idx++;
}
void dfs(int u){
    f[u][1]+=w[u];
    for(int i=h[u];i!=-1;i=ne[i]){
        int v=e[i];
        dfs(v);
        f[u][0]+=max(f[v][1],f[v][0]);
        f[u][1]+=f[v][0];
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",w+i);
    memset(h,-1,sizeof h);
    for(int i=0;i<n-1;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(v,u);
        st[u]=1;
    }
    int root=1;
    for(int i=1;i<=n;i++)
        if(st[i]==0){
           root=i;
           break;
        }
    dfs(root);    
    cout<<max(f[root][0],f[root][1]);
    return 0;
} 
