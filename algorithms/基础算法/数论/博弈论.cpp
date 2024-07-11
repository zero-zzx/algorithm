//尼姆游戏
//取石子 
#include<iostream>
using namespace std;
int main(){
    int n,x,res=0;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x;
        res^=x;
    }
    if(res==0) cout<<"No";
    else cout<<"Yes";
    return 0;
}

//取石子加强版
//有向图游戏，我能看到它了
#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_set>
using namespace std;

int f[110],n;
int sg(int x){
    if(f[x]!=-1) return f[x];
    
    unordered_set<int>S;
    for(int i=0;i<x;i++){
        for(int j=0;j<=i;j++){
            S.insert(sg(i)^sg(j));
        }
    }
    for(int i=0;;i++){
        if(S.count(i)==0){
            return f[x]=i;
        }
    }
    
}

int main(){
    cin>>n;
    
    memset(f,-1,sizeof f);
    
    int res=0;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        res^=sg(x);
    }
    
    if(res) puts("Yes");
    else puts("No");
    
    return 0;
} 
