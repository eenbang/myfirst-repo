#include<bits/stdc++.h>
using namespace std;    
int main(){
    double H = 0.0;
    int n;
    cin >> n;
    for(int i=1;i<=n;i++){
        H+=1.0/i;
    }
    cout << fixed << setprecision(6) << H << endl;
    return 0;
}