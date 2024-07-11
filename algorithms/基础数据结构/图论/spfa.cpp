//有边数限制的最短路
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int N=510,M=10010;
struct Node{
    int u,v,d;
}node[M];
int m;
int dis[N],n;
int bak[N];
void bellman_ford(int k){
    memset(dis,0x3f,sizeof dis);
    dis[1]=0;
    for(int i=0;i<k;i++){
        memcpy(bak,dis,sizeof dis);
        for(int j=0;j<m;j++){
            int u=node[j].u,v=node[j].v,d=node[j].d;
            dis[v]=min(dis[v],bak[u]+d);
        }

    }
    
}


int main(){
    int k;
    cin>>n>>m>>k;
    for(int i=0;i<m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        node[i]={u,v,d};
    }
    
    bellman_ford(k);
    
    if(dis[n]<0x3f3f3f3f/2){
        cout<<dis[n]<<endl;
    }else{
        cout<<"impossible"<<endl;
    }
    
    
    return 0;
}


//spfa
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
typedef pair<int,int> PII;
const int N=150010;
int e[N],w[N],ne[N],h[N],idx;
int dis[N],n;
bool vis[N];
void add(int u,int v,int d){
    w[idx]=d,e[idx]=v;ne[idx]=h[u];h[u]=idx++;
}
void spfa(){
    memset(dis,0x3f,sizeof dis);
    dis[1]=0;
    queue<int>q;
    q.push(1);
    vis[1]=1;
    while(q.size()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=h[u];~i;i=ne[i]){
            int v=e[i],d=w[i];
            if(dis[v]>dis[u]+d){
                dis[v]=dis[u]+d;
                if(vis[v]==0){
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}
int main(){
    int m;
    scanf("%d%d",&n,&m);
    memset(h,-1,sizeof h);
    int u,v,d;
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&u,&v,&d);
        add(u,v,d);
    }
    spfa();
    if(dis[n]==0x3f3f3f3f) puts("impossible");
    else cout<<dis[n];

    return 0;
} 
