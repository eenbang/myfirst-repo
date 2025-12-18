#include <iostream>

int main(){
    std::string s;
    std::cin >> s;
    int a = s[0] - '0';
    int b = s[1] - '0';
    int c = s.size() - 1;
    int d = s[2];
    if(d > '4') b++;
    if(b == 10){
        b = 0;
        a++;
    }  
    if(a == 10){
        a = 1;
        b = 0;
        c++;
    }
    std::cout << a << '.' << b << '*' << 10 << '^' << c;
    
}