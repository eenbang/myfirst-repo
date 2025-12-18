#include "Game.h"

void Game::DrawView()
{
	//绘制游戏区域边框
	roundrect(10, 10, 340, 430, 10, 10);
	rectangle(20, 20, 220, 420);  
	
	//绘制游戏区域
	setfillcolor(LIGHTCYAN);//设置填充颜色
	for(int i = 0;i < MAP_WIDTH; ++i)
	{
		for(int j = 0; j < MAP_HEIGHT; ++j)
		{
			if(map[i][j]) //如果该位置有方块
			{
				//一个方块的坐标表示
				int left = 20 + i * 20;
				int top = 20 + j * 20;//左上角坐标
				int right = left + 20;
				int bottom = top + 20;//右下角坐标
				fillrectangle(left, top, right, bottom);//绘制方块
			}
		}
	}
}

void Game::DrawPrompt()
{
	//设置字体
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30; //字体高度
	wcscpy_s(f.lfFaceName, L"微软雅黑"); //字体名称
	f.lfQuality = DEFAULT_QUALITY; //字体质量
	settextstyle(&f); //应用字体设置
	settextcolor(BLACK); //设置字体颜色

	//绘制提示信息
	outtextxy(235, 20, L"下一个方块");
	rectangle(240, 60, 320, 140);

	f.lfHeight = 25;//字体高度
	settextstyle(&f); //应用字体设置

	//绘制得分信息
	wchar_t str[10];
	wsprintf(str, L"得分:%d", this->score);
	outtextxy(230, 150, str);

	//绘制时间信息
	wsprintf(str, L"时间:%d秒", this->game_time/1000);
	outtextxy(230, 175, str);

	//绘制游戏标题
	f.lfHeight = 40; //字体高度
	settextstyle(&f); //应用字体设置
	settextcolor(RED); //设置字体颜色
	
	outtextxy(234, 250, L"俄罗斯");
	outtextxy(250, 290, L"方块");
	outtextxy(240, 330, L"Tetris");
	
}

bool Game::CheckFullLine(int line) const
{
	for (int i = 0; i < MAP_WIDTH; ++i)
	{
		if (map[i][line] == 0)
		{
			return false;
		}
	}
	return true;
}

void Game::ClearFullLine()
{
	int line = -1;
	for(int i = 0; i < MAP_HEIGHT; ++i)
	{
		if(CheckFullLine(i))
		{
			line = i;
			break; 
		}
	}
	if(line != -1)
	{ 
		for (int i = line; i > 0; --i)
		{
			for(int j = 0; j < MAP_WIDTH; ++j)
			{
				map[j][i] = map[j][i - 1];
			}	
		}
		this->score += 10; //每清除一行得10分
	}
	this->DrawPrompt();
}

void Game::UpdateGameTime()
{
	game_time += 500;
}

void Game::SetMapData(int x, int y, bool v)
{
	map[x][y] = v;
}

bool Game::GetMapData(int x, int y)
{
	return map[x][y];	
}
