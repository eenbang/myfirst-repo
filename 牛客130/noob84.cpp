#include <iostream>
#include <stack>
#include <stdbool.h>
#include <string>


int main(){
    bool note = true;
    std::stack <char> s;
    std::string str;
    std::cin >> str;
    for(char c : str){
        if(c == '[' || c == '('){
            s.push(c);
        }
        else if (c == ']' || c == ')'){
            if(s.empty()) {note = false; break;}
            char top = s.top();
            s.pop();
            if((top == '[' && c == ']') || (top == '(' && c == ')')) note = true;
            else note = false;
        }
    }

    if(note) std::cout << "true";
    else std::cout << "false";
    
}