#pragma once

#include <easyx.h>

const int MAP_WIDTH = 10;  //游戏区域宽度
const int MAP_HEIGHT = 20; //游戏区域高度

class Game
{
public:
//绘制游戏界面
	void DrawView();
	//绘制游戏提示界面
	void DrawPrompt();
	//判断是否满行
	bool CheckFullLine(int line)const;
	//清楚满行
	void ClearFullLine();

	//更新游戏时间
	void UpdateGameTime();
	//设置map数据
	void SetMapData(int x, int y, bool v);
	//获取map数据
	bool GetMapData(int x, int y);
private:
	bool map[MAP_WIDTH][MAP_HEIGHT]{ 0 };//游戏区域数据
	int score = 0; //游戏得分
	int game_time = 0; //游戏时间
};