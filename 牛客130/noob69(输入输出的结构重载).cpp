#include<iostream>
#include <string>
using namespace std;
struct Students{
    public: //struct Students
    string name;
    int cha,mat,eng;
    int score ;
};
istream& operator >> (istream& in,  Students& p){
        in >> p.name >> p.cha >> p.mat >> p.eng;
        p.score = p.cha + p.mat + p.eng;
        return in;
}
ostream& operator << (ostream& out,const Students& p){
        out << p.name <<' '<< p.cha << ' ' << p.mat 
        <<' '<< p.eng;
        return out;
}

int main(){
    int N;
    cin >> N;
    Students person[1000];
    int i, maxIndex = 0;
    for(i = 0; i < N;i++){
        cin >> person[i];
        if (person[i].score > person[maxIndex].score) 
            maxIndex = i;
    }
    cout << person[maxIndex];
}