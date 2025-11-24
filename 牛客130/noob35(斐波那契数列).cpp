#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n; int first = 1, second = 1, third = 1;
    for(int i=3; i<=n; i++){
        third = first + second;
        first = second;
        second = third;
    }
    cout << third << endl;    
    return 0;   
    
}