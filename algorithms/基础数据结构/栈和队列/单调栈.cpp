// ����һ������Ϊ N ���������У����ÿ������ߵ�һ������С�������������������� -1
//1��N��105                   1��������Ԫ�ء�109
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
