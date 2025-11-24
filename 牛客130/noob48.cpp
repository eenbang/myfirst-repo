#include<bits/stdc++.h>
using namespace std;
int arr[1001][1001];
int main(){
    int n,m; long long sum = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> arr[i][j];
            sum += arr[i][j];
        }
    }
    cout << sum << endl;
    return 0;
}