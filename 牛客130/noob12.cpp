#include<bits/stdc++.h>
using namespace std;   
int main(){
    int num;
    int ge,shi,bai,qian;
    cin >> num;
    ge = num % 10;
    shi = (num / 10) % 10;
    bai = (num / 100) % 10;
    qian = num / 1000;
    cout << ge << shi << bai << qian;
    return 0;
}
   