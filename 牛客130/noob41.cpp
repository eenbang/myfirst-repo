#include<bits/stdc++.h>
using namespace std;
long long a[102];
int main(){
    int i = 1;
    while(1){
        cin >> a[i];
        if(a[i] == 0) break;
        i++;
    }
    for(int j = i - 1; j >= 1; j--){
        cout << a[j] << " ";
    }

}