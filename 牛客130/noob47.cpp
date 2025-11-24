#include<bits/stdc++.h>
using namespace std;
int arr[10000];
int main(){
    int L,M,a,b;
    cin >> L >> M;
    for(int i = 1; i <= M; i++){
        cin >> a >> b;
        for (int j = a; j <= b; j++){
            arr[j] = -1;
        }
    }
    int sum = 0;
    for(int i = 0; i <= L; i++){
        if(arr[i] != -1) sum++;
    }
    cout << sum << endl;
    return 0;
}