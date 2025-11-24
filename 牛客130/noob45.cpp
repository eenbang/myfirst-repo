#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,x;
    int count = 0;
    cin >> n >> x;
    for(int i = 1; i <= n; i++){
        int temp = i;
        while(1){
            if(temp % 10 == x) count++;
            temp = temp / 10;
            if(temp == 0) break; 
        }
    }
    cout << count << endl;
}