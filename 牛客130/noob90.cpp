#include <iostream>
#include <stack>
#include <string>

int main(){
    std::stack <int> s;
    std::string  str;
    int a = 0,n;
    std::cin >> n ;
    std::cin.ignore();
    std::getline(std::cin, str);
    for(int i = 0; i < str.size(); i++){
        if(str[i] == ' ') {
            s.push(a);
            if(a == n){
                std::cout << s.top() << " ";
                s.pop();
                n--;
            }
            a = 0;
        }
        else{
            a = a * 10 + str[i] - '0'; 
        }
    }
    s.push(a);
    while(!s.empty()){
        std::cout << s.top() << " ";
        s.pop();
    }
    
}