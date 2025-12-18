#include "block.h"

bool Block::shapes[7][4][4] = { 0 };

Block::Block(Game& game, int x, int y)
	: x(x), y(y), game(game)
{
	type = rand() % 7; //随机生成方块类型

	switch (type)
	{
	case 0:
		color = LIGHTBLUE;
		break;
	case 1:
		color = GREEN;
		break;
	case 2:
		color = LIGHTGREEN;
		break;
	case 3:
		color = RED;
		break;
	case 4:
		color = BLACK;
		break;
	case 5:
		color = YELLOW;
		break;
	case 6:
		color = BROWN;
		break;
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			currentShape[i][j] = shapes[type][i][j];
		}
	}
	direction = true;
}

bool Block::move(int direction)
{
	switch (direction)
	{
	case 0: //向下
		++y;
		if (checkCollision())
		{
			--y;
			return true;
		}
		break;
	case 1: //向左
		--x;
		if (checkCollision())
		{
			++x;
		}
		break;
	case 2: //向右
		++x;
		if (checkCollision())
		{
			--x;
		}
		break;
	}
	return false;
}

void Block::draw()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (currentShape[i][j])
			{
				if (j + y > 0) //只绘制在可见区域的方块
				{
					setfillcolor(this->color);
					int left = 20 + 20 * (x + i);
					int top = 20 + 20 * (y + j);

					fillrectangle(left, top, left + 20, top + 20);
				}
			}
		}
	}
}
void Block::clear()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (currentShape[i][j])
			{
				int left = 20 + 20 * (x + i);
				int top = 20 + 20 * (y + j);
				clearrectangle(left, top, left + 20, top + 20);
			}
		}
	}

}

void Block::addmap()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (currentShape[i][j])
			{
				game.SetMapData(x + i, y + j, currentShape[i][j]);
			}
		}
	}
}

void Block::rotate()
{
	if (type == 4) return; //方块类型4不旋转
	bool temp;
	if (!direction)
	{
		//角旋转
		temp = currentShape[0][0];
		currentShape[0][0] = currentShape[0][2];
		currentShape[0][2] = currentShape[2][2];
		currentShape[2][2] = currentShape[2][0];
		currentShape[2][0] = temp;

		//十字中心旋转
		temp = currentShape[1][0];
		currentShape[1][0] = currentShape[0][1];
		currentShape[0][1] = currentShape[1][2];
		currentShape[1][2] = currentShape[2][1];
		currentShape[2][1] = temp;
	}
	else
	{
		temp = currentShape[0][0];
		currentShape[0][0] = currentShape[2][0];
		currentShape[2][0] = currentShape[2][2];
		currentShape[2][2] = currentShape[0][2];
		currentShape[0][2] = temp;

		//十字中心旋转
		temp = currentShape[1][0];
		currentShape[1][0] = currentShape[2][1];
		currentShape[2][1] = currentShape[1][2];
		currentShape[1][2] = currentShape[0][1];
		currentShape[0][1] = temp;
	}

	// 修复 case 标签错误，将 case 语句放入 switch(type) 内部
	switch (type)
	{
	case 0:
		if (currentShape[1][3])
		{
			currentShape[1][3] = false;
			currentShape[3][1] = true;
		}
		else
		{
			currentShape[1][3] = true;
			currentShape[3][1] = false;
		}
		break;
	case 5:
		//正z型方块
		if (!checkCollision())
			direction = !direction;
		break;
	case 6:
		//反z型方块
		if (!checkCollision())
			direction = !direction;
		break;
	}

	if (checkCollision())
	{
		if (direction)
		{
			temp = currentShape[0][0];
			currentShape[0][0] = currentShape[2][0];
			currentShape[2][0] = currentShape[2][2];
			currentShape[2][2] = currentShape[0][2];
			currentShape[0][2] = temp;

			//十字中心旋转
			temp = currentShape[1][0];
			currentShape[1][0] = currentShape[2][1];
			currentShape[2][1] = currentShape[1][2];
			currentShape[1][2] = currentShape[0][1];
			currentShape[0][1] = temp;
		}
		else
		{
			temp = currentShape[0][0];
			currentShape[0][0] = currentShape[2][0];
			currentShape[2][0] = currentShape[2][2];
			currentShape[2][2] = currentShape[0][2];
			currentShape[0][2] = temp;

			//十字中心旋转
			temp = currentShape[1][0];
			currentShape[1][0] = currentShape[2][1];
			currentShape[2][1] = currentShape[1][2];
			currentShape[1][2] = currentShape[0][1];
			currentShape[0][1] = temp;
		}

		if (type == 0)
		{
			if (currentShape[1][3])
			{
				currentShape[1][3] = false;
				currentShape[3][1] = true;
			}
			else
			{
				currentShape[1][3] = true;
				currentShape[3][1] = false;
			}
		}
	}
}

bool Block::checkCollision() const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (!currentShape[i][j])
				continue;

			int nx = x + i;  // 网格坐标
			int ny = y + j;  // 网格坐标

			// 1. 左右越界
			if (nx < 0 || nx >= 10)
				return true;

			// 2. 下越界
			if (ny >= 20)
				return true;

			// 3. 与已有方块重叠
			if (game.GetMapData(nx, ny))
				return true;
		}
	}
	return false;
}

void Block::initShapes()
{
	shapes[0][1][0] = shapes[0][1][1] = shapes[0][1][2] = shapes[0][1][3] = true; //I型方块
	shapes[1][0][0] = shapes[1][1][0] = shapes[1][1][1] = shapes[1][1][2] = true;
	shapes[2][2][0] = shapes[2][1][0] = shapes[2][1][1] = shapes[2][1][2] = true;
	shapes[3][1][0] = shapes[3][0][1] = shapes[3][1][1] = shapes[3][2][1] = true;
	shapes[4][0][0] = shapes[4][0][1] = shapes[4][1][1] = shapes[4][1][0] = true;
	shapes[5][0][0] = shapes[5][1][0] = shapes[5][1][1] = shapes[5][2][1] = true;
	shapes[6][2][0] = shapes[6][0][1] = shapes[6][1][1] = shapes[6][1][0] = true;
}		   

void Block::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;	
}

void Block::randomType()
{
	type = rand() % 7; //随机生成方块类型

	switch (type)
	{
	case 0:
		color = LIGHTBLUE;
		break;
	case 1:
		color = GREEN;
		break;
	case 2:
		color = LIGHTGREEN;
		break;
	case 3:
		color = RED;
		break;
	case 4:
		color = BLACK;
		break;
	case 5:
		color = YELLOW;
		break;
	case 6:
		color = BROWN;
		break;
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			currentShape[i][j] = shapes[type][i][j];
		}
	}
	direction = true;
}

void Block::operator=(const Block& other)
{
	x = other.x;
	y = other.y;
	type = other.type;
	direction = other.direction;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->currentShape[i][j] = other.currentShape[i][j];
		}
	}
	color = other.color;
}

