int find(int x){return fa[x]==x?fa[x]:fa[x]=find(fa[x]);}

const int N=100010;
int h[N],e[N<<1],ne[N<<1],w[N<<1],idx;
void add(int u,int v,int d){
	e[idx]=v;w[idx]=d;ne[idx]=h[u];h[u]=idx++;
} 
memset(h,-1,sizeof h);
