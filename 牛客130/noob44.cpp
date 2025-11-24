#include<bits/stdc++.h>
using namespace std;
int a[101];
int main(){
    int T = 0; int n,k;
    int S = 0,cnt = 0;
    cin >> T;
    for (int j = 1; j <= T ; j++ ){
        cin >> n >> k;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(a[i] >= k) S += a[i];
            if(a[i] == 0 && S >= 1) cnt++,S--;
        }
        cout << cnt << endl;
        S = 0;
        cnt = 0;
        
    }
}