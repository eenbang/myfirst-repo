#include <iostream>
int main(){
    int i,l,r,x;
    bool flag = false;
    std::cin >> l >> r >> x;
    for(i = l; i <= r; i++){
        if(i % x == 0) {
            flag = true;
            break;
        }
    }
    if(flag) std::cout << i;
    else std::cout << -1;
}