#include <iostream>

int main(){
    int N;
    std::cin >> N;
    std::string s;
    std::cin >> s;
    int ans = 0,count = 0;
    for (int i = 0; i < N ; i++){
        if(s[i] == 'a' || s[i] == 'h'){
            if(i == 0 || s[i - 1] != 'a' && s[i] == 'h' || s[i] == 'a' && s[i - 1] != 'h'){
                count = 1;
            }else{
                count++;
            }
        }
        ans = std::max(ans,count);
    }
    std::cout << ans;
}