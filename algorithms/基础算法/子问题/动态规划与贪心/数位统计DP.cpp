//求a和b之间所有数字0-9出现的次数
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long LL;
int len(LL x){
    int cnt=0;
    while(x) x/=10,cnt++;
    return cnt;
}
LL count_(LL x,int q){//2
    int sz=len(x);
    LL res=0;
    for(int i=1;i<=sz;i++){//43256
        LL k=pow(10,i-1);//100
        LL lf=x/10/k;//43
        LL rt=x%k;//56
        LL d=(x-lf*k*10)/k;//2
        if(q){
            res+=lf*k;
        }else{
            if(lf) res+=(lf-1)*k;
        } 
        if(d>q&&lf|q) res+=k;
        if(d==q&&lf|q) res+=rt+1;
    }
    return res;
}


int main(){

    LL l,r;
    while(cin>>l>>r,l|r){
        if(l>r) swap(l,r);
        if(l<=0) l=1;
        for(int i=0;i<=9;i++){
            // cout<<count(r,i)<<" \n"[i==9];
            cout<<count(r,i)-count(l-1,i)<<" \n"[i==9];
        }
    }
} 
