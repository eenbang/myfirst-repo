#include <iostream>
#include <string>
void Switch(std::string& s,int len){
    char temp1,temp2;
    for(int i = 0; i < len; i++){
        if(s[i] == 'm'){
            s[i] = 'n';
            s.insert(s.begin() + i+1,'n');
            len++;
        }
        if(s[i] == 'w'){
            s[i] = 'v';
            s.insert(s.begin()+i+1,'v');
            len++;
        }
        if(s[i] == 'd' || s[i] == 'p' || s[i] == 'q'){
            s[i] = 'b';
        }
        if(s[i] == 'u') s[i] = 'n';
    }
}

int main(){
    int T;
    std::cin >> T;
    while(T--){
        std::string s;
        std::cin >> s;
        bool flag = true;
        int len = s.size();
        Switch(s,len);
        for(int i = 0; i < s.size(); i++){
            if(s[i] != s[s.size() - i - 1]){
                flag = false;
                break;
            }
        }
        if(flag) std::cout << "YES" << std::endl;
        else std::cout << "NO" << std::endl;
    }    
}