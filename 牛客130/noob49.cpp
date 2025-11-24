#include<bits/stdc++.h>
using namespace std;
int arr[11][11];
int main(){
    int n;
    bool flag = true;
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> arr[i][j];    
        }
    }
    for(int i = n; i >= 2; i--){
        for(int j = i - 1; j >= 1; j--){
            if(arr[i][j] != 0){
                cout << "NO" << endl;
                flag = false;
                break;
            }
        }
        if(!flag) break;
    }
    if(flag) cout << "YES" << endl;
}