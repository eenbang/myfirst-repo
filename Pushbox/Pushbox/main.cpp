#include <iostream>
#include <conio.h>
using namespace std;

void Draw_Map(int Map[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (Map[i][j]) {
            case 0:cout << " "; break;
            case 1:cout << "█";  break;
            case 2:cout << "□";  break;
            case 3:cout << "★";  break;
            case 4:cout << "♀";  break;
            case 5:cout << "□";  break;
            case 7:cout << "♀";  break;
            }
        }
        cout << endl;
    }
}
int main() {
    //绘制地图
    int Map[8][8] = {
        0,0,1,1,1,0,0,0,
        0,0,1,3,1,0,0,0,
        0,0,1,0,1,1,1,1,
        1,1,1,2,0,2,3,1,
        1,3,0,2,4,1,1,1,
        1,1,1,1,2,1,0,0,
        0,0,0,1,3,1,0,0,
        0,0,0,1,1,1,0,0
    };
    //确定人物位置

    while (1) {
        int i, j;
        //绘制并更新地图
        Draw_Map(Map);
        //显示坐标
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                
                if (Map[i][j] == 4 || Map[i][j] == 7) {
                    cout << "人物坐标位置:" << "("
                        << i + 1 << "," << j + 1 << ")" << endl;
                    break;
                }
            }
            if (Map[i][j] == 4 || Map[i][j] == 7) break;
        }
        //输入并且移动操作
        char input = _getch();
        switch (input) {
            //向上移动操作
            case 'w': {
                //前方为空白或者目的地
                if (Map[i - 1][j] == 0 || Map[i - 1][j] == 3) {
                    Map[i - 1][j] += 4;
                    Map[i][j] -= 4;
                }
                //前方为箱子（箱子前方为空白或者目的地）
                else if (Map[i - 1][j] == 2 || Map[i - 1][j] == 5) {
                    if (Map[i - 2][j] == 0 || Map[i - 2][j] == 3) {
                        Map[i][j] -= 4;
                        Map[i - 1][j] += 2;
                        Map[i - 2][j] += 2;
                    }
                }
                break;
            }
                    //向下移动操作
            case 's': {
                //前方为空白或者目的地
                if (Map[i + 1][j] == 0 || Map[i + 1][j] == 3) {
                    Map[i + 1][j] += 4;
                    Map[i][j] -= 4;
                }
                //前方为箱子（箱子前方为空白或者目的地）
                else if (Map[i + 1][j] == 2 || Map[i + 1][j] == 5) {
                    if (Map[i + 2][j] == 0 || Map[i + 2][j] == 3) {
                        Map[i][j] -= 4;
                        Map[i + 1][j] += 2;
                        Map[i + 2][j] += 2;
                    }
                }
                break;
            }
                    //向左移动操作
            case 'a': {
                //前方为空白或者目的地
                if (Map[i][j - 1] == 0 || Map[i][j - 1] == 3) {
                    Map[i][j - 1] += 4;
                    Map[i][j] -= 4;
                }
                //前方为箱子（箱子前方为空白或者目的地）
                else if (Map[i][j - 1] == 2 || Map[i][j - 1] == 5) {
                    if (Map[i][j - 2] == 0 || Map[i][j - 2] == 3) {
                        Map[i][j] -= 4;
                        Map[i][j - 1] += 2;
                        Map[i][j - 2] += 2;
                    }
                }
                break;
            }
                    //向右移动操作
            case 'd': {
                //前方为空白或者目的地
                if (Map[i][j + 1] == 0 || Map[i][j + 1] == 3) {
                    Map[i][j + 1] += 4;
                    Map[i][j] -= 4;
                }
                //前方为箱子（箱子前方为空白或者目的地）
                else if (Map[i][j + 1] == 2 || Map[i][j + 1] == 5) {
                    if (Map[i][j + 2] == 0 || Map[i][j + 2] == 3) {
                        Map[i][j] -= 4;
                        Map[i][j + 1] += 2;
                        Map[i][j + 2] += 2;
                    }
                }
                break;
            }
        } 
        Draw_Map(Map);
        //判定结束
        int count = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (Map[i][j] == 5) count++;
            }
        }
        if (count == 4) {
            system("cls");
            Draw_Map(Map);
            cout << "通关！！" << endl;
            exit(0);
        }
        //实现一个图层
        system("cls");
    }
    
}