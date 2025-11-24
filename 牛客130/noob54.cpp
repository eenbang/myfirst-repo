#include<iostream>

int main(){
    std::string s1,s2;
    int i,j;
    std::string s[4] = {"mouse","cat","tiger","elephant"};
    std::cin >> s1 >> s2;
    for( i = 0; i < 4; i++){
        if(s1 == s[i]) break;
    }
    for( j = 0; j < 4; j++){
        if(s2 == s[j]) break;
    }
    if(i - j == 1 || i - j == -3) std::cout << "win";
    else if(j - i == 1 || j - i == -3) std::cout << "lose";
    else std::cout << "tie";
}