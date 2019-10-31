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

//用键盘的w/a/s/d输入来控制贪吃蛇的上下左右移动
void SnakeMove(int key)
{
	int delta_x=0;
	int delta_y=0;

	if(key=='w'|| key=='W')
	{
		delta_x=0;
		delta_y=-1;
	}
	else if(key=='s'|| key=='S')
	{
		delta_x=0;
		delta_y=1;
	}
	else if(key=='a'|| key=='A')
	{
		delta_x=-1;
		delta_y=0;
	}
	else if(key=='d'|| key=='D')
	{
		delta_x=1;
		delta_y=0;
	}
	else
	{
		return;	//无效按键
	}

	DrawChar(g_snake.pos[g_snake.size-1].x,g_snake.pos[g_snake.size-1].y,' ');//删除尾节点
	
	//1、后一个节点=前一个节点的坐标
	//2、g_snake.size-1:最后一个节点的坐标
	//3、i>0:不包括头节点
	for(int i=g_snake.size-1;i>0;i--)
	{
		g_snake.pos[i].x=g_snake.pos[i-1].x;
		g_snake.pos[i].y=g_snake.pos[i-1].y;
	}

		g_snake.pos[0].x +=delta_x;
		g_snake.pos[0].y +=delta_y;
}

void Eat_food()
{
	if(g_snake.pos[0].x ==g_food.x &&g_snake.pos[0].y==g_food.y)
	{
		g_snake.size++;
		//新的尾节点跟食物的坐标一致
		g_snake.pos[g_snake.size-1].x=g_food.x;
		g_snake.pos[g_snake.size-1].y=g_food.y;
		Init_Food();
	}	
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
		//键盘移动贪吃蛇
		SnakeMove(key);

		//处理撞墙等事件
		Eat_food();

		//更新画面
		UpdateScreen();

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
	Score();
	return 0;
}

