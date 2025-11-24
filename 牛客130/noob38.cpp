#include<bits/stdc++.h>
using namespace std;    
int main(){
    int n;
    cin >> n;
    for(int i = 1; i<=n; i++){
        if(i % 4 == 0) continue;
        int j = i;
        while(j){
            if(j % 10 == 4) break;
            j = j / 10;
        }
        if(j) continue;
        cout << i << endl; 
    }
}