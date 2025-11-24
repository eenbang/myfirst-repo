#include <iostream>
#include <stack>
#include <string>
int main(){
    int T;
    std::cin >> T;
    while(T--){
        std::stack <char> s,S;
        std::string str;
        std::cin >> str;
        for(int i = 0; i < str.size(); i++){
            if(str[i] == 'o'){
                if(!s.empty() && s.top() == 'o'){
                    s.pop();
                    if(!s.empty() && s.top() == 'O'){
                    s.pop();
                    }else s.push('O');   
                }else s.push('o');
            }
            else if(str[i] == 'O'){
                if(!s.empty() && s.top() == 'O'){
                    s.pop();
                }else s.push('O');  
            }
        }
    
        while(!s.empty()){
            S.push(s.top());
            s.pop();
        }
        while(!S.empty()){
            std::cout << S.top();
            S.pop();
        }
        std::cout << std::endl;
        
    }
}