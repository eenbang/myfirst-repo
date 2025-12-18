#include <iostream>

int main(){
    int t;
    std::cin >> t;
    char map[5][5] = {' '};
    while(t--){
        bool flagyukari = false;
        bool flagkou = false;
        for(int i = 1; i < 4; i++){
            for(int j = 1; j < 4; j++){
                std::cin >> map[i][j];
            }
        }
        for(int i = 1; i < 4; i++){
            for(int j = 1; j < 4; j++){
                if(map[i][j] == '*' && (map[i-1][j] == 'o' && map[i+1][j] == 'o'||map[i][j-1] == 'o' && map[i][j+1] == 'o'))
                flagyukari = true;
                if(map[i][j] == 'o' && (map[i-1][j] == '*' && map[i+1][j] == '*'||map[i][j-1] == '*' && map[i][j+1] == '*'))
                flagkou = true;
            }
        }
        if(flagyukari && !flagkou) std::cout << "yukari" << std::endl;
        else if(flagkou && !flagyukari) std::cout << "kou" << std::endl;
        else std::cout << "draw" << std::endl;

    }

}