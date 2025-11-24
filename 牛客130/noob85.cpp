#include <iostream>
#include <stack>
#include <string>

int main(){
    std::string str;
    std::cin >> str;
    std::stack <char> s;
    bool note = true;
    for(char c : str){
        if(c == 'a') s.push('a');
        else if (c == 'b'){
            if(s.empty()){note = false; break;}
            s.pop();
        }
    }
    if(note && s.empty()) std::cout << "Good";
    else std::cout << "Bad";
}