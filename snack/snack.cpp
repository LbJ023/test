// snack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

//�����ͼ�Ĵ�С
#define MAP_HEIGHT 20
#define MAP_WIDTH 60

typedef struct Position{
	int x;//x����
	int y;//y����
}Position;

typedef struct Snake{
	int size;//̰���ߵĳ���
	Position pos[MAP_WIDTH * MAP_WIDTH];
}Snake;

void DrawChar(int x,int y,char ch)
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	//���ù���λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	putchar(ch);
}

void Init_Map()
{
	for(int i=0;i<=MAP_HEIGHT;i++)
	{
		//��
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
//ʳ������λ��
void Init_Food()
{
	srand((unsigned)time(NULL));
	g_food.x=rand()%MAP_WIDTH;
	g_food.y=rand()%MAP_HEIGHT;
	DrawChar(g_food.x,g_food.y,'#');
}
//��Ϸ��ʼ ̰���ߵĴ�С
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

//����̰����
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
		//����Ƿ��а�������
		if(_kbhit())
		{
			key=_getch();	
		}
		//��q�˳���Ϸ
		if(key=='q'|| key=='Q')
		{
			return;
		}
		// ��ʱ
		Sleep(100);
	}
}

void Score()
{

}

int main(int argc, char* argv[])
{
	// ��ʼ��������ͼ
	Init();

	// ��Ϸ����ѭ��������������Ϸ����ˢ�£�����ײǽ���¼�
	GameLoop();

	// ��ӡ�÷�
	//Score();
	return 0;
}

