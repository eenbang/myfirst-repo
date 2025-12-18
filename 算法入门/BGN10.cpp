#include <iostream>

int main(){
    int t;
    std::cin >> t;
    while(t--){
        std::string s;
        std::cin >> s;
        int sum = 0;
        int count2 = 0, count3 = 0;
        for(int i = 0; i < s.size(); i++){
            sum += s[i] - '0';
            if(s[i] == '2') count2 ++;//+2
            if(s[i] == '3') count3 ++;//+6
        }
        sum = sum % 9;
        int temp;
        bool flag = false;
        if(sum == 0){
            flag = true;
        }
        else{
            for(int i = 0; i <= count3; i++){
                for(int j = 0; j <= count2; j++){
                    temp = sum;
                    temp = temp + i*6 + j*2;   
                    if (temp % 9 == 0) flag = true;                 
                } 
            }
        }
        if(flag) std::cout << "YES" << std::endl;
        else std::cout << "NO" << std::endl;
    }
}