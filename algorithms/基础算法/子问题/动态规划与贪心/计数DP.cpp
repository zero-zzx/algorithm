//һ�������� n���Ա�ʾ�����ɸ�������֮�ͣ����磺n=n1+n2+��+nk������ n1��n2�ݡ���nk,k��1��
//���ǽ�������һ�ֱ�ʾ��Ϊ������ n��һ�ֻ��֡�
//���ڸ���һ�������� n��������� n���ж����ֲ�ͬ�Ļ��ַ�����
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
