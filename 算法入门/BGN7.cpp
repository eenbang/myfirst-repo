#include <iostream>

int main(){
    int T;
    unsigned long long x;
    std::cin >> T;
    while(T--){
        std::cin >> x;
        if(x == 2 || x == 3 || x == 5 || x == 6 || x == 8 || x == 11 || x == 14) std::cout << "No" << std::endl;
        else std::cout << "Yes" << std::endl;
    }
}