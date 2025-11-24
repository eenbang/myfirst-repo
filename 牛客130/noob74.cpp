#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct point{
    double x,y;
    point(double A,double B){
        x=A,y=B;
    }
    point() = default;
};

struct line{
    point point_A,point_B;
    line(point A,point B){
        point_A = A,point_B = B;
    }
    line() = default;
};

struct Circle{
    point O;
    int r;
    Circle(point A,int B){
        O=A,r=B;
    }
    Circle() = default;
};

double getDistance(const Circle& circle, const line& l) {
    double a = l.point_B.y - l.point_A.y;
    double b = l.point_A.x - l.point_B.x;
    double c = l.point_A.y*l.point_B.x - l.point_B.y*l.point_A.x;
    double d = fabs(a*circle.O.x + b*circle.O.y + c)/sqrt(a*a+b*b);
    double ret = sqrt(pow(circle.r,2)-d*d) *2;
    return ret;
}
int main() {
    double ox, oy, r;
    double x1, y1, x2, y2;
    
    cin >> ox >> oy >> r;
    cin >> x1 >> y1 >> x2 >> y2;
    
    point center(ox, oy);
    Circle circle(center, (int)r);
    
    point p1(x1, y1);
    point p2(x2, y2);
    line l(p1, p2);
    
    double result = getDistance(circle, l);
    cout << fixed << setprecision(6) << result << endl;
    
    return 0;
} 