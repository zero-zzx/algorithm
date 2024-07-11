//Ï£¶ûÅÅÐò
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100010;
int a[N],n;
int main(){
    cin>>n;
    for(int i=0;i<n;i++) scanf("%d",a+i);
    
    for(int gap=n>>1;gap;gap>>=1){
        for(int i=gap;i<n;i++){
            for(int j=i;j>=gap&&a[j]<a[j-gap];j-=gap){
                int t=a[j-gap];
                a[j-gap]=a[j];
                a[j]=t;
            }
        }
    }
    
    for(int i=0;i<n;i++) cout<<a[i]<<' ';
    return 0;
}



//¿ìÅÅ
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100010;

int a[N],n;
void q_sort(int l,int r){
    if(l==r){
        return;
    }
    int mid=a[l+r>>1],i=l-1,j=r+1;
    while(i<j){
        while(a[++i]<mid);
        while(a[--j]>mid);
        if(i<j){
            a[i]^=a[j]^=a[i]^=a[j];
        }
    }
    q_sort(l,j);
    q_sort(j+1,r);
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    
    q_sort(0,n-1);
    
    for(int i=0;i<n;i++){
        cout<<a[i]<<" \n"[i==n-1];
    }
}


//¹é²¢ÅÅÐò
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const int N=100010;

int a[N],b[N],n;
LL res;
void m_sort(int l,int r){
    if(l==r){
        return;
    }
    
    int mid=l+r>>1;
    m_sort(l,mid);
    m_sort(mid+1,r);
    
    int i=l,j=mid+1,k=0;
    while(i<=mid&&j<=r){
        if(a[i]<a[j]){
            b[k++]=a[i++];
        }else{
            res+=mid-i+1;
            b[k++]=a[j++];
        }
    }
    while(i<=mid) b[k++]=a[i++];
    while(j<=r) b[k++]=a[j++];
    
    
    for(int i=0;i<k;i++){
        a[l+i]=b[i];
    }
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    
    m_sort(0,n-1);
    
    for(int i=0;i<n;i++){
        cout<<a[i]<<" \n"[i==n-1];
    }
    // cout<<res<<endl;
    
    return 0;
} 
