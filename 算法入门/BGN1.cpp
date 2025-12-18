#include <iostream>

int main(){
    int arr[5];
    std::cin >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4];
    for(int i = 0; i < 5; i++){
        if(arr[i] == 1) std::cout << i+1;
    }
}