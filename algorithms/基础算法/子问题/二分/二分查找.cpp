//1.给定一段递增区间，求某个数出现的位置
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100010;
int a[N],n;
int lf(int x){
    int l=0,r=n-1;
    while(l<r){
        int mid=l+r>>1;
        if(a[mid]<x) l=mid+1;
        else r=mid;
    }
    return a[l]==x?l:-1;
}
int rt(int x){
    int l=0,r=n-1;
    while(l<r){
        int mid=l+r+1>>1;
        if(a[mid]>x) r=mid-1;
        else  l=mid;
    }
    return a[l]==x?l:-1;
}

int main(){
    int q;
    cin>>n>>q;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    
    while(q--){
        int x;
        cin>>x;
        cout<<lf(x)<<' '<<rt(x)<<endl;
    }
    
    return 0;
}
