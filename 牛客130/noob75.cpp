#include<iostream>
#include<iomanip>
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

point findMeetingPoint(line line_A,line line_B){
    point ret;
    
    if(line_A.point_A.x != line_A.point_B.x && line_B.point_A.x != line_B.point_B.x){
        double ka = (line_A.point_A.y-line_A.point_B.y)/(line_A.point_A.x-line_A.point_B.x);
        double ba = line_A.point_A.y - ka * line_A.point_A.x; 
        double kb = (line_B.point_A.y-line_B.point_B.y)/(line_B.point_A.x-line_B.point_B.x);
        double bb = line_B.point_A.y - kb * line_B.point_A.x;
        if(ka == kb) ret = point(-1,-1);
        else{
            ret.x = (bb-ba)/(ka-kb);
            ret.y = (bb*ka-ba*kb)/(ka-kb);
        }
    }
    else if(line_A.point_A.x == line_A.point_B.x && line_B.point_A.x != line_B.point_B.x){
        double kb = (line_B.point_A.y-line_B.point_B.y)/(line_B.point_A.x-line_B.point_B.x);
        ret.x = line_A.point_A.x;
        ret.y = ret.x *(line_B.point_A.y-line_B.point_B.y)/(line_B.point_A.x-line_B.point_B.x) + (line_B.point_A.y - kb * line_B.point_A.x);
    }
    else if(line_A.point_A.x != line_A.point_B.x && line_B.point_A.x == line_B.point_B.x){
        double ka = (line_A.point_A.y-line_A.point_B.y)/(line_A.point_A.x-line_A.point_B.x);
        ret.x = line_B.point_A.x;
        ret.y = ret.x *(line_A.point_A.y-line_A.point_B.y)/(line_A.point_A.x-line_A.point_B.x) + (line_A.point_A.y - ka * line_A.point_A.x);
    }
    else ret = point(-1,-1);
    return ret;
       
}


int main(){
    point A,B,C,D;
    cin>>A.x>>A.y>>B.x>>B.y>>C.x>>C.y>>D.x>>D.y;
    line AB=line(A,B);
    line CD=line(C,D);
    point ans = findMeetingPoint(AB,CD);
    cout << fixed << setprecision(6) <<ans.x<<" "<<ans.y;
    return 0;
}
//ÊºÉ½£¡£¡£¡£¡£¡