//版本一：拉链法 
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e5+10;
int h[N],e[N],ne[N],idx;
void add(int x){
    int k=(x%N+N)%N;
    e[idx]=x;ne[idx]=h[k];h[k]=idx++;
}
bool find(int x){
    int k=h[(x%N+N)%N];
    while(~k&&e[k]!=x) k=ne[k];
    return k!=-1;
}
int main(){
    int n;
    cin>>n;
    memset(h,-1,sizeof h);
    while(n--){
        char ch;
        int x;
        scanf(" %c%d",&ch,&x);
        if(ch=='I'){
            add(x);
        }
        else{
            if(find(x)) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
    }
    return 0;
}




//版本二：蹲坑法
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MOD=2e5+3,INF=0x3f3f3f3f;
int h[MOD];
int find(int x){
    int idx=(x%MOD+MOD)%MOD;
    while(h[idx]!=INF&&h[idx]!=x){
        if(++idx==MOD) idx=0;
    }
    return idx;
}
int main(){
    int n;
    cin>>n;
    memset(h,0x3f,sizeof h);
    while(n--){
        char ch;
        int x;
        scanf(" %c%d",&ch,&x);
        if(ch=='I'){
            h[find(x)]=x;
        }
        else{
            if(h[find(x)]==x) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
    }
    return 0;
} 
