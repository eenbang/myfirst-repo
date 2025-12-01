#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
int main(){
    int N;
    int wordsNum;
    int M;
    std::unordered_map <std::string,std::set<int> > mp;
    std::string word;
    std::cin >> N;
    for(int i = 1; i <= N; i++){
        std::cin >> wordsNum;
        while(wordsNum--){
            std::cin >> word;
            mp[word].insert(i);
        }
    }
    std::cin >> M;
    while(M--){
        std::cin >> word;
        for(auto it = mp[word].begin(); it != mp[word].end(); it++){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}