//一个正整数 n可以表示成若干个正整数之和，形如：n=n1+n2+…+nk，其中 n1≥n2≥…≥nk,k≥1。
//我们将这样的一种表示称为正整数 n的一种划分。
//现在给定一个正整数 n，请你求出 n共有多少种不同的划分方法。
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1010,MOD=1e9+7;
int a[N];

int main(){
    
    int x;
    cin>>x;
    a[0]=1;
    for(int i=x;i>=1;i--){
        for(int j=i;j<=x;j++){
            a[j]=(a[j]+a[j-i])%MOD;
        }
    }
    cout<<a[x]<<endl;
    return 0;
} 
