#include<bits/stdc++.h>
using namespace std;
int main(){
    int today,tomorrow;
    cin >> today;
    tomorrow = today + 1;
    if (tomorrow == 8){
        tomorrow = 1;
    }
    cout << tomorrow << endl;
    return 0;
}