#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; 
    cin >> n;
    int a[100000];
    for(int i=1; i<=n; i++){
        cin >> a[i];
    } 
    int max = a[1];
    int min = a[1];
    for(int j=1; j<=n; j++){
        if(a[j]>max){
            max = a[j];
        }
        if(a[j]<min){
            min = a[j];
        }
    }
    cout << max - min << endl;
    return 0;

}