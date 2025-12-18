#pragma once
#include "Game.h"

class Block
{
public:
	Block(Game& game, int x = (MAP_WIDTH - 4) / 2, int y = 0);
public:
	//移动:0向下，1向左，2向右
	bool move(int direction = 0); 
	//绘制
	void draw();
	//清楚
	void clear();
	//添加到地图
	void addmap();
	//旋转，false为左，true为右
	void rotate();
	//碰撞检测
	bool checkCollision() const;
	//生成方块
	static void initShapes();
	//设置坐标
	void setPosition(int x = (MAP_WIDTH - 4) / 2, int y = 0);
	//随机方块类型
	void randomType();
	void operator = (const Block& other);
private:
	int x;
	int y;
	int type;
	COLORREF color;
	Game& game;
	static bool shapes[7][4][4];
	bool currentShape[4][4];
	bool direction;
};