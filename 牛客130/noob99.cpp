#include <iostream>
#include <set>

int main(){
    std::set <int> M;
    int x,n,oper;
    std::cin >> n;
    while(n--){
        std::cin >> oper;
        if(oper == 1){
            std::cin >> x;
            if(!M.count(x)) M.insert(x);
    
        }
        if(oper == 2){
            std::cin >> x;
            if(M.count(x)) M.erase(x);
        }
        if(oper == 3){
            std::cin >> x;
            if(M.count(x)) std::cout << "YES" << std::endl;
            else std::cout << "NO" << std::endl;
        }
        if(oper == 4){
            std::cout << M.size() << std::endl;
        }
        if(oper == 5){
            std::cin >> x;
            auto it = M.lower_bound(x);
            if (it == M.begin()) std::cout << -1 << std::endl;
            else std::cout << *(--it) << std::endl;
        }
        if(oper == 6){
            std::cin >> x;
            auto it = M.upper_bound(x);
            if(it == M.end()) std::cout << -1 << std::endl;
            else std::cout << *it << std::endl;
        }

    }
    
}