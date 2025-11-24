#include <iostream>
#include <stack>

int main(){
    std::stack <int> s;
    int n;
    std::cin >> n;
    while(n--){
        std::string oper;
        int x;
        std::cin >> oper;
        if(oper == "push"){
           std::cin >> x;
           s.push(x); 
        }
        if(oper == "pop"){
            if(!s.empty()) s.pop();
            else std::cout << "empty" << std::endl;
        }
        if(oper == "query"){
            if(!s.empty()) std::cout << s.top() << std::endl;
            else std::cout << "empty" << std::endl;
        } 
        if(oper == "size"){
            std::cout << s.size() << std::endl;
        }
    }
}