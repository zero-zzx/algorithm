//最长上升子序列 
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100010;

int a[N],n;
int b[N],cnt;


int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    
    
    b[cnt++]=a[0];
    for(int i=1;i<n;i++){
        int x=a[i];
        if(x>b[cnt-1]){
            b[cnt++]=x;
        }else{
            int l=0,r=cnt-1;
            while(l<r){
                int mid=l+r>>1;
                if(b[mid]<x) l=mid+1;
                else r=mid;
            }
            b[l]=x;
        }
        
    }
    
    cout<<cnt<<endl;
    
    
    return 0;
}
