#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c;
    cin >> a >> b >> c;
    int max = a,min = a;
    if (b>max) max = b;
    if (c>max) max = c;
    if (b<min) min = b;
    if (c<min) min = c;
    cout << "The maximum number is :  " << max << endl;
    cout << "The minimum number is :  " << min << endl;
}