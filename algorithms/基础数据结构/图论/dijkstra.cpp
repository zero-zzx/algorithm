//点数1e3 
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int N=510;

int g[N][N],n;
int dis[N];
bool st[N];
void dijkstra(int rt){
    memset(dis,0x3f,sizeof dis);
    dis[rt]=0;
    
    for(int k=0;k<n;k++){
        int p=-1;
        for(int i=1;i<=n;i++){
            if(st[i]==0&&(p==-1||dis[i]<dis[p])){
                p=i;
            }
        }
        
        st[p]=1;
        for(int i=1;i<=n;i++){
            dis[i]=min(dis[i],dis[p]+g[p][i]);
        }
        
    }
}


int main(){
    memset(g,0x3f,sizeof g);
    int m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        g[u][v]=min(g[u][v],d);
    }
    
    dijkstra(1);
    
    if(dis[n]!=0x3f3f3f3f){
        cout<<dis[n]<<endl;
    }else{
        cout<<-1<<endl;
    }
    
    
    
    return 0;
}



//点数、边数1e5
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=150010;
typedef pair<int,int> PII;

int h[N],e[N],ne[N],w[N],idx;
void add(int u,int v,int d){
    e[idx]=v;ne[idx]=h[u];w[idx]=d;h[u]=idx++;
}
int dis[N],n;
bool st[N];
void dijkstra(int rt){
    memset(dis,0x3f,sizeof dis);
    dis[rt]=0;
    
    priority_queue<PII,vector<PII>,greater<PII>> heap;
    heap.push({0,rt});
    while(heap.size()){
        auto p=heap.top();
        heap.pop();
        int u=p.second;
        if(st[u]) continue;
        
        st[u]=1;
        for(int i=h[u];~i;i=ne[i]){
            int v=e[i];
            if(dis[v]>dis[u]+w[i]){
                dis[v]=dis[u]+w[i];
                heap.push({dis[v],v});
            }
        }
        
        
    }
    
    
}

int main(){
    int m;
    cin>>n>>m;
    memset(h,-1,sizeof h);
    for(int i=0;i<m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        add(u,v,d);
    }
    
    dijkstra(1);
    
    if(dis[n]<0x3f3f3f3f){
        cout<<dis[n]<<endl;
    }else{
        cout<<-1<<endl;
    }
    
    
    
    return 0;
} 
