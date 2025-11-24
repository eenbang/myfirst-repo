#include <bits/stdc++.h>
using namespace std;
int main(){
    int A[20];
    A[0] = 0;
    A[1] = 1;
    A[2] = 1;
    for(int i = 3; i < 20; i++){
        A[i] = A[i-1] + A[i-2] * 2 + A[i-3];
    }
    int n;
    cin >> n;
    cout << A[n-1] << endl;
    return 0;
}