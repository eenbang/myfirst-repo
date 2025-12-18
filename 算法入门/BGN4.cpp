#include <iostream>

int main(){
    int n;
    std::cin >> n;
    int t = n/8;
    int ret = -1;
    for(int i = 0; i <= t+1; i++){
        if(n-i*8 < 0) continue;
        if((n-i*8)%6 == 0) ret = i + (n-i*8)/6;
    }
    std::cout << ret;
}