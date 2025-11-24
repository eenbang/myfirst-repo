#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct point {
    double x, y;
    point(double A, double B) :x(A), y(B) {}
    point() = default;
};

struct line {
    point point_A, point_B;
    line(point A, point B) :point_A(A), point_B(B) {}
    line() = default;
};
//A = y2 - y1
//B = x1 - x2
//C = x2 * y1 - x1 * y2
double getDistance(point P, line L) {
    double a = L.point_B.y - L.point_A.y;
    double b = L.point_A.x - L.point_B.x;
    double c = L.point_B.x * L.point_A.y - L.point_B.y * L.point_A.x;
    double d = (P.x * a + b * P.y + c) / (sqrt(a * a + b * b));
    return fabs(d);
}

int main() {
    point p;
    cin >> p.x >> p.y;
    line l;
    cin >> l.point_A.x >> l.point_A.y >> l.point_B.x >> l.point_B.y;
    cout << fixed << setprecision(2) << getDistance(p, l);

}
