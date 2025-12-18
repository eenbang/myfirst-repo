/*开发日志
* 游戏名：俄罗斯方块
* 开发时间：2025年12月
* 开发工具：EasyX图形库，Visual Studio 2022
* 01游戏框架设计 😊
  02游戏类实现 😊
  03方块类实现😊
  04游戏实现😊
*/


#include <iostream>
#include "Game.h"
#include "block.h"
#include <time.h>
/*
游戏管理对象：绘制，游戏的创建，游戏的释放
方块类：生成不同性质的方块，随机颜色

*/

int main() {
	//游戏窗口创建
	HWND hd = initgraph(350, 400);
	SetWindowText(hd, L"俄罗斯方块");
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	//生成游戏数据
	srand(time(NULL));
	Block::initShapes();
	// 绘制界面
	Game game;
	game.DrawView();
	game.DrawPrompt();

	Block block(game);
	Block next_block(game, 11, 2);

	clock_t start = 0;
	clock_t end = 0;

	next_block.draw();

	ExMessage em;

	//进入游戏循环
	BeginBatchDraw();
	while (true) {
		//游戏界面的更新
		block.clear();
		clearrectangle(20, 20, 220, 420);
		game.DrawView();

		//按键交互
		while (peekmessage(&em, EX_KEY) && em.message == WM_KEYDOWN)
		{
			switch (em.vkcode)
			{
			case VK_UP:
				block.rotate();
				break;
			case VK_DOWN:
				if (block.move())
				{
					block.addmap();
					block = next_block;
					block.setPosition();
					next_block.clear();
					next_block.setPosition(11,2);
					next_block.randomType();
					next_block.draw();

					if (block.checkCollision())
					{
						MessageBox(GetHWnd(), L"游戏结束", L"提示",MB_ICONWARNING);
						goto exit;
					}
				}
				break;
			case VK_LEFT:
				block.move(1);
				break;
			case VK_RIGHT:
				block.move(2);
				break;
			}
			

		}
		end = clock();
		if (end - start >= 500)
		{
			if (block.move())
			{
				block.addmap();
				block = next_block;
				block.setPosition();
				next_block.clear();
				next_block.setPosition(11, 2);
				next_block.randomType();
				next_block.draw();

				if (block.checkCollision())
				{
					MessageBox(GetHWnd(), L"游戏结束",L"提示", MB_ICONWARNING);
					goto exit;
				}

			}
			start = clock();
			game.UpdateGameTime();
		}
		//方块数据更新
		block.draw();
		game.ClearFullLine();

		FlushBatchDraw();
		Sleep(50);
		
	}
	//游戏结束，释放资源
	exit:
	EndBatchDraw();
	closegraph();

	return 0;
}