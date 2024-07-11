// 给定一个长度为 N 的整数数列，输出每个数左边第一个比它小的数，如果不存在则输出 -1
//1≤N≤105                   1≤数列中元素≤109
#include<iostream>
using namespace std;
const int N=100010;
int st[N],cnt,a[N];
int main(){
    int n,x;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x;
        while(cnt&&st[cnt-1]>=x) cnt--;
        if(cnt) a[i]=st[cnt-1];
        else a[i]=-1;
        st[cnt++]=x;
    }
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    return 0;
}
