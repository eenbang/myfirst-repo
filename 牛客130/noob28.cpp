#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    if(n%100/3 == 1) cout << "spring" << endl;
    else if(n%100/3 == 2) cout << "summer" << endl;
    else if(n%100/3 == 3) cout << "autumn" << endl;
    else cout << "winter" << endl;
}