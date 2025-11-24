#include<iostream>
using namespace std;

char arr[1001][1001];
int num[1001][1001];

int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++ ){
        for(int j = 1; j <= m; j++ ){
            cin >> arr[i][j];
        }
    }
    for(int i = 1; i <= n; i++ ){
        for(int j = 1; j <= m; j++ ){
            if(arr[i-1][j-1]=='*') num[i][j]++;
            if(arr[i-1][j]=='*') num[i][j]++;
            if(arr[i-1][j+1]=='*') num[i][j]++;
            if(arr[i][j-1]=='*') num[i][j]++;
            if(arr[i][j+1]=='*') num[i][j]++;
            if(arr[i+1][j-1]=='*') num[i][j]++;
            if(arr[i+1][j]=='*') num[i][j]++;
            if(arr[i+1][j+1]=='*') num[i][j]++;
        }
    }
    for(int i = 1; i <= n; i++ ){
        for(int j = 1; j <= m; j++ ){
            if(arr[i][j]=='*') cout << '*';
            else cout << num[i][j];
        }
        cout << endl;
    }
}