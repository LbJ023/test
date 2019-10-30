// snack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

//定义地图的大小
#define MAP_HEIGHT 20
#define MAP_WIDTH 60

typedef struct Position{
	int x;//x坐标
	int y;//y坐标
}Position;

typedef struct Snake{
	int size;//贪吃蛇的长度
	Position pos[MAP_WIDTH * MAP_WIDTH];
}Snake;

void DrawChar(int x,int y,char ch)
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	//设置光标的位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	putchar(ch);
}

void Init_Map()
{
	for(int i=0;i<=MAP_HEIGHT;i++)
	{
		//行
		for(int j=0;j<=MAP_WIDTH;j++)
		{
			if(j==MAP_WIDTH)
			{
				printf("|\n");
			}
			else if(i==MAP_HEIGHT)
			{
				printf("-");
			}
			else
			{
				printf(" ");
			}
		}
	}
}


Snake g_snake;
Position g_food;
//食物的随机位置
void Init_Food()
{
	srand((unsigned)time(NULL));
	g_food.x=rand()%MAP_WIDTH;
	g_food.y=rand()%MAP_HEIGHT;
	DrawChar(g_food.x,g_food.y,'#');
}
//游戏开始 贪吃蛇的大小
void Init_Snake()
{
	g_snake.size=3;
	g_snake.pos[0].x=MAP_WIDTH /2;
	g_snake.pos[0].y=MAP_HEIGHT /2;

	g_snake.pos[1].x=MAP_WIDTH /2 -1;
	g_snake.pos[1].y=MAP_HEIGHT /2;

	g_snake.pos[2].x=MAP_WIDTH /2 -2;
	g_snake.pos[2].y=MAP_HEIGHT /2;
}

//绘制贪吃蛇
void DrawSnake()
{
	for(int i=0;i<g_snake.size;i++)
	{
		if(i==0)
		{
			DrawChar(g_snake.pos[i].x,g_snake.pos[i].y,'*');
		}
		else
		{
			DrawChar(g_snake.pos[i].x,g_snake.pos[i].y,'#');
		}
	}
}

void Init()
{
	Init_Map();
	Init_Snake();
	DrawSnake();
	Init_Food();
}

void UpdateScreen()
{
	DrawSnake();
}

void GameLoop()
{
	int key=0;
	while (1)
	{
		//检测是否有按键输入
		if(_kbhit())
		{
			key=_getch();	
		}
		//按q退出游戏
		if(key=='q'|| key=='Q')
		{
			return;
		}
		// 延时
		Sleep(100);
	}
}

void Score()
{

}

int main(int argc, char* argv[])
{
	// 初始化，画地图
	Init();

	// 游戏的主循环，按键处理，游戏画面刷新，处理撞墙等事件
	GameLoop();

	// 打印得分
	//Score();
	return 0;
}

