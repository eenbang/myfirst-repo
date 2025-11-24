#include<bits/stdc++.h>
using namespace std;
int main(){
    int T,n; bool note ;
    cin >> T;
    for(int i = 0;i < T;i++){
        note = true;
        cin >> n;
        for (int j = 2;j < n;j++){
            if(n%j == 0) {
                cout << "No" << endl;
                note = false;
                break; 
            }
        }
        if (n == 1) cout << "No" << endl;   
        else if(note == true) cout << "Yes" << endl;
    }
}