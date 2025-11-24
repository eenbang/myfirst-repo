#include<bits/stdc++.h>
using namespace std;
int main(){
    int n; int sum = 0;
    cin >> n;
    for(int i = 1; i<=n; i++){
        sum +=((i+1)*i)/2;
    }
    cout << sum << endl;    
    return 0;
}