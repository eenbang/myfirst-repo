#include<bits/stdc++.h>
using namespace std;
int main(){
    double x1, y1, x2, y2, de, dm;
    cin >> x1 >> y1 >> x2 >> y2;
    de = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    dm = fabs(x1 - x2) + fabs(y1 - y2);
    cout << fixed << setprecision(6) << fabs(de - dm) << endl;
    return 0;
}