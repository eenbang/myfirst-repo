#include<bits/stdc++.h>
using namespace std;
int a[101];
void del(int a[], int n, int k){
    if(k == n-1) a[k] = 0;
    else{
        for(int i = k ; i < n-1; i++){
            a[i] = a[i+1];
        }
    }    
}//删除长度为n的数组的下标为k的元素

int main(){
    int n,k,m;
    cin >> n >> k >> m;
    for(int i = 0; i < n; i++){
        a[i] = i;
    }
    for(int i = n; i > 1; i--){
        int delIndex = (k + m - 1) % i;//计算出要删除的下标
        del(a, i, delIndex);//删除该下标的元素
        k = delIndex % (i - 1);//更新下一个起始位置
    }
    cout << a[0] << endl;
    return 0;
}