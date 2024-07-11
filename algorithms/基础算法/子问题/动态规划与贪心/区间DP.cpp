//石子合并 
#include<iostream>
#include<cstdio>
using namespace std;
const int N=310;
int a[N],n;
int f[N][N];

int main(){
    cin>>n;
    int x;
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        a[i]=a[i-1]+x;
    }
    for(int len=2;len<=n;len++)
        for(int i=1;i+len-1<=n;i++){
            int l=i,r=i+len-1;
            f[l][r]=1e8;
            for(int k=l;k<r;k++) f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]+a[r]-a[l-1]);
        }
    cout<<f[1][n]<<endl;
    return 0;
}
