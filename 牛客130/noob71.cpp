#include<iostream>
using namespace std;

// 定义学生结构体
struct Student{
    int id;
    int academic_score;
    int activity_score;
};

istream& operator>>(istream& in,Student& s){
    in >> s.id >> s.academic_score >> s.activity_score;
    return in;
}
// 评估函数：判断学生是否优秀
bool isExcellent(Student student){
    double S = student.academic_score * 0.7 +
               student.activity_score * 0.3;
    if(student.academic_score + student.activity_score > 140
        && S >= 80)           
        return true;
    else return false;

}

int main(){
    int N;
    Student student;
    bool result[1000];
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> student;
        if(isExcellent(student)) cout << "Excellent" << endl;
        else cout << "Not excellent" << endl;
    }
}

