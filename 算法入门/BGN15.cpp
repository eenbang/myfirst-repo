#include <iostream>

int main(){
    int t,a1,a2,b1,b2;
    std::cin >> t;
    while(t--){
        std::cin >> a1 >> a2 >> b1 >> b2;
        int wina = 0;
        if(a1 > b1 && a2 >= b2) wina++;
    
        if(a1 > b2 && a2 >= b1) wina++;
      
        if(a2 > b1 && a1 >= b2) wina++;
      
        if(a2 > b2 && a1 >= b1) wina++;
      
        std::cout << wina << std::endl;
    }
}