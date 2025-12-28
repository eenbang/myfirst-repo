#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int n;
    cin >> n;
    int sum = 0;
    int average = 0;
    int arr[100000];
    int optimistic = 0;
    int negative = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        sum+=arr[i];
    }
    average = ceil((double)sum/n);
    for(int i = 0; i < n; i++){
        arr[i] = average - arr[i];
        if(arr[i] > 0) optimistic += arr[i];
        else negative -= arr[i];
    }
    cout << max(negative,optimistic) * 2 - min(negative,optimistic);
}