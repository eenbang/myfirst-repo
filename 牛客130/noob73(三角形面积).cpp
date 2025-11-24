#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
struct point{
    double x,y;
    point(double A, double B):x(A),y(B){}
    point() = default;
};

struct triangle{
    point a,b,c;
    triangle(point a, point b, point c): a(a),b(b),c(c){}
    triangle() = default;
};
//area=21?
//?x1?(y2??y3?)+x2?(y3??y1?)+x3?(y1??y2?)
double getArea(triangle T){
    double area = T.a.x*(T.b.y-T.c.y)+T.b.x*(T.c.y-T.a.y)
                  +T.c.x*(T.a.y-T.b.y);
    return fabs(area) / 2.0;
}
int main(){
    triangle T;
    cin >> T.a.x >> T.a.y 
    >> T.b.x >> T.b.y
    >> T.c.x >> T.c.y;
    cout << fixed << setprecision(2) << getArea(T);
}