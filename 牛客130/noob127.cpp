#include <iostream>
#include <map>
#include <vector>
#include <string>
int main(){
    int N;
    std::string city,state; long long count2 = 0;
    std::cin >> N;
    long long num = 0;
    std::map <std::string,std::map <std::string,int> > counts;
    for(int i = 0; i < N; i++){
        std::cin >> city >> state;
        counts[city.substr(0,2)][state] += 1;
    }
    for(auto const& [p1,inner_map] : counts){
        for(auto const& [s1,count1] : inner_map){
            if(p1 == s1) continue;
            if(counts.count(s1) && counts[s1].count(p1)){
                count2 = counts[s1][p1];
                num += (long long)count1 * count2; 
            }
        }
        
    }
    std::cout << num/2 << std::endl;

}