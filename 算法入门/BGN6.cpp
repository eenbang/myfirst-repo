#include <iostream>
#include <string>

int ShortestDistance(char c1,char c2){
    int ret = abs(c1 - c2);
    if(ret < 26 - ret) return ret;
    else return 26-ret;
}
int main(){
    std::string subs;
    std::string s,s1;
    std::cin >> subs >> s;
    int temp = 0;
    int n1 = subs.size();
    int n = s.size();
    int min = 1e9;
    for(int i = 0; i <= n - n1; i++){
        temp = 0;
        s1 = s.substr(i,n1);
        for(int j = 0; j < n1; j++){
            temp += ShortestDistance(subs[j],s1[j]);
        }
        if (min > temp) min = temp;
    }
    std::cout << min;
    
}