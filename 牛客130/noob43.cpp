#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main(){
    int T = 0;
    int n,max = 0,min = 1e9;
    double average = 0.0,sum = 0.0,fangcha = 0.0;
    cin >> T;
    for (int i = 1; i <= T ; i++ ){
        cin >> n;
        for(int j = 1; j <= n; j++){
            cin >> a[j];
            sum += a[j];
            if (max < a[j]) max = a[j];
            if (min > a[j]) min = a[j];    
        }
        cout << max - min << " ";
        average = sum / n;
        for(int j = 1; j <= n; j++){
            fangcha += pow((a[j] - average),2) / n;
        }
        cout << fixed << setprecision(3) << fangcha << endl;
        fangcha = 0.0;
        sum = 0.0;
        max = 0;
        min = 1e9;   
    }
}