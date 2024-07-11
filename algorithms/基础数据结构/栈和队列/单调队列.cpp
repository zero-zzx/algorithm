//�������� 
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1000010;
int a[N],n;
int q[N],k;

int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    
    int hh=0,tt=-1;
    for(int i=1;i<=n;i++){
        if(hh<=tt&&q[hh]<i-k+1) hh++;
        while(hh<=tt&&a[q[tt]]>=a[i]) tt--;
        q[++tt]=i;
        if(i>=k) cout<<a[q[hh]]<<' ';
    }
    cout<<endl;
    hh=0,tt=-1;
    for(int i=1;i<=n;i++){
        if(hh<=tt&&q[hh]<i-k+1) hh++;
        while(hh<=tt&&a[q[tt]]<=a[i]) tt--;
        q[++tt]=i;
        if(i>=k) cout<<a[q[hh]]<<' ';
    }
        
    return 0;
}
