#include <iostream>
int main(){
    int X, Y;
    std::cin >> X >> Y;
    if(X != Y && X != 0 - Y){
        if(X == 0 ) std::cout << 2;
        else if(Y == 0) std::cout << 1;
        else std::cout << -1;
    }
    else{
        if(X == Y) std::cout << 0;
        else{
            std::cout << 3;
        }     
    }
}