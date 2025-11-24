#include <bits/stdc++.h>
using namespace std;
long long a[999][999];
int main(){
    int m,n;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i == 0 || j == 0) a[i][j] = 1;
            else a[i][j] = (a[i-1][j] + a[i][j-1]) % 1000000007;
        }
    }
    cout << a[n-1][m-1] << endl;
    return 0;
}