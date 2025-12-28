#include <iostream>

using namespace std;

int SumDays(int,int,int);
int MonthDays(int,int);

int main(){
    int year,month,day;    
    while(cin >> year >> month >> day){ 
        cout << SumDays(year,month,day) << endl;
    }
}

int SumDays(int year,int month,int day){
    int ret = 0;
    for(int i = 1; i <= month - 1; i++){
        ret += MonthDays(year,i);
    }
    ret+=day;
    return ret;
}

int MonthDays(int year,int month){
    int ret = -1;
    switch(month){
        case 1: 
            ret = 31;
            break;
        case 2:
            if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ret = 29;
            else ret = 28;
            break;
        case 3:
            ret = 31;
            break;
        case 4:
            ret = 30;
            break;
        case 5:
            ret = 31;
            break;
        case 6:
            ret = 30;
            break;
        case 7:
            ret = 31;
            break;
        case 8:
            ret = 31;
            break;
        case 9:
            ret = 30;
            break;
        case 10:
            ret = 31;
            break;
        case 11:
            ret = 30;
            break;
        case 12:
            ret = 31;
            break;
    }
    return ret;
}