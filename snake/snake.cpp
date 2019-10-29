// snake.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>
//游戏功能列表

void Init()
{	
	
}

void Gameloop()
{
	while(1)
	{
		Sleep(100);//延时
	}
}

void Score()
{

}
int main(int argc, char* argv[])
{
	Init();//初始化，画地图

	Gameloop();//游戏主循环，按键处理，游戏画面刷新，处理撞墙事件

	Score();//打印得分

	return 0;
}

