#include <iostream>
#include <stdlib.h>
#include <string>
#include <graphics.h>
#include <conio.h>
#include <mmsystem.h>
//pragma:编译指示;comment:注释;lib:系统会使用到的函数库
#pragma comment(lib,"winmm.lib")
#include "box_man.h"

using namespace std;

IMAGE images[ALL];			//保存墙,箱子,地板, 小人,目的地的图片

POS man;			//小人在二维数组中的位置

IMAGE bg_img[ALL1];					//保存背景图片




//游戏地图
/*
int map[LINE][COLUMN] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{ 0, 1, 4, 1, 0, 2, 1, 0, 1, 1, 0, 0},
{ 0, 1, 0, 1, 0, 1, 0, 0, 2, 1, 1, 0},
{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0},
{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0},
{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0},
{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/
/*
	WALL,					//0墙
	FLOOR,					//1地板
	BOX_DES,				//2箱子目的地
	MAN,					//3小人
	BOX,					//4箱子
	HIT,					//5箱子命中目标
	MAN_DES,				//6小人站在目的地上
*/

struct MAP map1[MAP_QUANTITY] = { 
{ 8, 8, {
{ 1, 1, 0, 0, 0, 1, 1, 1 },  //地图一
{ 1, 1, 0, 2, 0, 1, 1, 1 },
{ 1, 1, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 4, 1, 4, 2, 0 },
{ 0, 2, 1, 4, 3, 0, 0, 0 },
{ 0, 0, 0, 0, 4, 0, 1, 1 },
{ 1, 1, 1, 0, 2, 0, 1, 1 },
{ 1, 1, 1, 0, 0, 0, 1, 1 } } },
{ 9, 12,{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//地图二
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{ 0, 1, 4, 1, 0, 2, 1, 0, 1, 1, 0, 0},
{ 0, 1, 0, 1, 0, 1, 0, 0, 2, 1, 1, 0},
{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0},
{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0},
{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0},
{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} } },
{ 9, 9, {
{ 0, 0, 0, 0, 0, 1, 1, 1, 1},   //地图三
{ 0, 1, 3, 1, 0, 1, 1, 1, 1},
{ 0, 1, 4, 4, 0, 1, 0, 0, 0},
{ 0, 1, 4, 1, 0, 1, 0, 2, 0},
{ 0, 0, 0, 1, 0, 0, 0, 2, 0},
{ 1, 0, 0, 1, 1, 1, 1, 2, 0},
{ 1, 0, 1, 1, 1, 0, 1, 1, 0},
{ 1, 0, 1, 1, 1, 0, 0, 0, 0},
{ 1, 0, 0, 0, 0, 0, 1, 1, 1} } },
{ 7, 10, {
{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },  //地图四
{ 1, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 4, 0, 0, 0, 1, 1, 1, 0 },
{ 0, 1, 1, 1, 4, 1, 1, 4, 1, 0 },
{ 0, 1, 6, 2, 0, 1, 4, 1, 0, 0 },
{ 0, 0, 2, 2, 0, 1, 1, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 } } },
{ 8, 6, {
{ 1, 0, 0, 0, 0, 1 },    //地图五
{ 0, 0, 1, 1, 0, 1 },
{ 0, 3, 4, 1, 0, 1 },
{ 0, 0, 4, 1, 0, 0 },
{ 0, 0, 1, 4, 1, 0 },
{ 0, 2, 4, 1, 1, 0 },
{ 0, 2, 2, 5, 2, 0 },
{ 0, 0, 0, 0, 0, 0 } } },
{ 8, 8, {
{ 1, 0, 0, 0, 0, 0, 1, 1 },  //地图六
{ 1, 0, 1, 3, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 4, 1, 1, 0 },
{ 0, 1, 5, 2, 1, 2, 1, 0 },
{ 0, 1, 1, 4, 4, 1, 0, 0 },
{ 0, 0, 0, 1, 0, 2, 0, 1 },
{ 1, 1, 0, 1, 1, 1, 0, 1 },
{ 1, 1, 0, 0, 0, 0, 0, 1 } } }, 
{ 10, 11, {
{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},	//地图七
{ 1, 0, 0, 0, 0, 0, 2, 1, 1, 1, 0},
{ 1, 0, 1, 1, 0, 2, 2, 0, 0, 1, 0},
{ 1, 0, 1, 1, 4, 2, 2, 1, 1, 1, 0},
{ 1, 0, 1, 1, 0, 1, 2, 0, 1, 0, 0},
{ 0, 0, 0, 1, 0, 0, 4, 0, 1, 1, 0},
{ 0, 1, 4, 4, 1, 1, 1, 4, 4, 1, 0},
{ 0, 1, 0, 3, 0, 1, 1, 0, 1, 1, 0},
{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1} }}, };   //在这里增加地图，行数，列数，以及地图元素

/*****************************************
*判断游戏是否结束,如果不存在任何一个箱子目的地,就代表游戏结束
*输入:
*		map[LINE][COLUMN]	-	地图结构体中的数组
*		const int line		-	地图的行的常量
*		const int column	-	地图的列的常量
*返回值:
*		true	- 游戏结束
*		false	- 游戏继续
******************************************/
bool isGameOver(int map[LINE][COLUMN], const int line, const int column) {
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			if (map[i][j] == BOX_DES || map[i][j] == MAN_DES) {				
				return false;
			}
		}
	}
	Sleep(300);
	return true;
}
/*****************************************
*功能:实现游戏关卡提示
*输入:
*		bg			- 背景图片变量的指针
*		customsPass	-	当前关卡数
*输出:
*
******************************************/
void levelsPrompt(IMAGE *bg,int customsPass) {
	char str[16];

	putimage(0, 0, bg);									//打印传入背景图片
	settextcolor(WHITE);								//设置文字颜色为亮红
	setbkmode(TRANSPARENT);								//设置文字背景色为透明色
	RECT rec = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };		//绘制矩形
	settextstyle(100, 0, _T("宋体"));					//设置字体

	sprintf_s(str, "第 %d 关", customsPass);				//将int变量转换成char字符保存
	//textwidth 计算字符串的高度 textheight 计算字符串的宽度
	outtextxy(((SCREEN_WIDTH - textwidth(str))/ 2), ((SCREEN_HEIGHT - textheight(str))/ 2), str);
	Sleep(2000);
}

/*****************************************
*游戏结束场景,在玩家通关后显示
*输入:
*		bg		- 背景图片变量的指针
*		victory - 胜利图片指针
*返回值:无
******************************************/
void gemrOverScene(IMAGE *bg, IMAGE *victory,const int customsPass) {
	putimage(0, 0, bg);											//打印传入背景图片
	putimage((SCREEN_WIDTH - SCREEN_WIDTH1) / 2, 50, victory);	//打印传入的胜利图片
	settextcolor(BLUE);										//设置文字颜色为白色
	RECT rec = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };				//绘制矩形
	settextstyle(20, 0, _T("宋体"));							//设置字体
	//DT_CENTER:文字水平居中,DT_VCENTER:文字垂直居中,DT_SINGLELINE:显示一行,回车换行无效
	if (customsPass == MAP_QUANTITY) {
		drawtext(_T("恭喜你~\n您通关了全部关卡!您已经成为了推箱子老司机!按 'Q' 键结束游戏!重新开始请按 'T'"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	} 
	else {
		drawtext(_T("恭喜你~\n您通关了!按任意键进入下一关!"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		system("pause");
	}
	
	
}
/*****************************************
*游戏失败场景,在玩家失败后显示
*输入:
*		bg	 - 背景图片变量的指针
*		over - 失败图片指针
*返回值:无
******************************************/
void gameOverMan(IMAGE *bg, IMAGE *over) {
	putimage(0, 0, bg);									//打印传入背景图片
	putimage((SCREEN_WIDTH - SCREEN_WIDTH1) / 2, 50, over);	//打印传入的失败图片
	settextcolor(BLUE);								//设置文字颜色为白色
	RECT rec = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };		//绘制矩形
	settextstyle(20, 0, _T("宋体"));					//设置字体
	//DT_CENTER:文字水平居中,DT_VCENTER:文字垂直居中,DT_SINGLELINE:显示一行,回车换行无效
	drawtext(_T("GAME OVER!您的游戏步数超过300步,游戏结束!按 'Q' 键结束游戏!重新开始请按 'T'"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}


/*****************************************
*改变游戏地图视图中一格对应道具并重新显示
*输入:
*		pos					-	传入道具的位置
*		prop				-	传入道具类型
*		map[LINE][COLUMN]	-	地图结构体中的数组
*		const int line		-	地图的行的常量
*		const int column	-	地图的列的常量
*返回值:无
******************************************/
//第二版
void changoMap(POS *pos, PROPS prop, int map[LINE][COLUMN], const int line, const int column) {
	map[pos->x][pos->y] = prop;
	putimage(((SCREEN_WIDTH - (column * RATIO)) / 2) + pos->y * RATIO, 
		(((SCREEN_HEIGHT - (line * RATIO)) / 2) + (STAR_Y / 2)) + pos->x * RATIO, &images[prop]);
}
/*****************************************
*改变游戏地图视图中一格对应道具并重新显示
*输入:
*		line   - 道具在地图数组的行下标
*		column - 道具在地图数组的列下标
*		prop	- 道具类型
*返回值:无
******************************************/
/*第一版
void changoMap(int line, int column, enum _PROPS prop) {
	map[line][column] = prop;
	putimage(STAR_X + column * RATIO, STAR_Y + line * RATIO, &images[prop]);
}
*/

/*****************************************
*实现游戏四个方向(上、下、左、右)的控制
*输入:
*		direct				-	人前进的方向
*		count				-	步数统计初始值 0
*		retreat				-	小人上一次的操作
*		map[LINE][COLUMN]	-	地图结构体中的数组
*		const int line		-	地图的行的常量
*		const int column	-	地图的列的常量
*返回值:
*		如果有移动就返回步数初始值+1,否则小人撞墙没有移动返回当前步数 不增加1
******************************************/
void gameControl(DIRECTION direct, int &count, bool &ifMove, int map[LINE][COLUMN], const int line, const int column) {
	//int x = man.x;			//小人所在的二维数组的x坐标
	//int y = man.y;			//小人所在的二维数组的y坐标

	POS next_pos = man;			//为小人前面一格
	POS next_next_pos = man;	//小人前面两格



	switch (direct) {
	case UP:
		next_pos.x--;			//小人向上一格
		next_next_pos.x -= 2;	//箱子和小人同时向上一格
		break;
	case DOWN:
		next_pos.x++;			//小人向下一格
		next_next_pos.x += 2;	//箱子和小人同时向下一格
		break;
	case LEFT:
		next_pos.y--;			//小人向左一格
		next_next_pos.y -= 2;	//箱子和小人同时向左一格
		break;
	case RIGHT:
		next_pos.y++;			//小人向右一格
		next_next_pos.y += 2;	//箱子和小人同时向右一格
		break;
		//default:
			//break;
	}
	

	//第三版
	//宏展开 next_pos.x >= 0 && next_pos.x < LINE && next_pos.y >= 0 && next_pos.y < COLUMN
	if (isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR) {		//小人的前面是地板
		if (map[man.x][man.y] == MAN_DES) {				//如果是小人站在箱子目的地上
			changoMap(&next_pos, MAN, map, line, column);					//小人移动一格
			changoMap(&man, BOX_DES, map, line, column);					//恢复箱子目的地
			man = next_pos;								//将小人新的位置更新到当前位置
			count++;									//小人移动一次,步数统计加一
			ifMove = false;								//箱子未移动 ifMove 的值改为假
		}
		else if (map[man.x][man.y] == MAN) {			//如果小人在地板上
			changoMap(&next_pos, MAN, map, line, column);					//小人移动一格			
			changoMap(&man, FLOOR, map, line, column);						//原来小人的位置换成地板
			man = next_pos;								//将小人新的位置更新到当前位置
			count++;									//小人移动一次,步数统计加一
			ifMove = false;								//箱子未移动 ifMove 的值改为假
		}
	}
	else if (isValid(next_pos) && isValid(next_next_pos) && map[next_pos.x][next_pos.y] == BOX) {	//小人的前面是箱子
	 //两种情况,箱子前面是地板或者是箱子目的地
		if (map[next_next_pos.x][next_next_pos.y] == FLOOR) {				//箱子前面是地板
			//两种情况,小人在目的地上或者在地板上
			if (map[man.x][man.y] == MAN_DES) {				//如果是小人站在箱子目的地上的情况
				changoMap(&next_next_pos, BOX, map, line, column);				//箱子向前移动一格
				changoMap(&next_pos, MAN, map, line, column);					//小人移动一格
				changoMap(&man, BOX_DES, map, line, column);					//恢复箱子目的地
				man = next_pos;								//将小人新的位置更新到当前位
				count++;									//小人移动一次,步数统计加一
				ifMove = true;								//箱子移动 ifMove 的值改为真
			}
			else if (map[man.x][man.y] == MAN) {			//小人在地板上的情况
				changoMap(&next_next_pos, BOX, map, line, column);				//箱子向前移动一格
				changoMap(&next_pos, MAN, map, line, column);					//小人移动一格			
				changoMap(&man, FLOOR, map, line, column);						//原来小人的位置换成地板
				man = next_pos;								//将小人新的位置更新到当前位置
				count++;									//小人移动一次,步数统计加一
				ifMove = true;								//箱子移动 ifMove 的值改为真
			}
		}
		else if (map[next_next_pos.x][next_next_pos.y] == BOX_DES) {		//箱子前面是箱子目的地
			if (map[man.x][man.y] == MAN_DES) {				//小人在目的地上的情况
				changoMap(&next_next_pos, HIT, map, line, column);				//箱子目的地换成箱子命中目的地
				changoMap(&next_pos, MAN, map, line, column);					//小人从箱子目的地换到地板上			
				changoMap(&man, BOX_DES, map, line, column);					//原来小人的位置换成箱子目的地
				man = next_pos;								//将小人新的位置更新到当前位置
				count++;									//小人移动一次,步数统计加一
				ifMove = true;								//箱子移动 ifMove 的值改为真
			}
			else if (map[man.x][man.y] == MAN) {			//小人在地板上的情况
				changoMap(&next_next_pos, HIT, map, line, column);				//箱子目的地换成箱子命中目的地
				changoMap(&next_pos, MAN, map, line, column);					//小人向前移动一格			
				changoMap(&man, FLOOR, map, line, column);						//原来小人的位置换成地板
				man = next_pos;								//将小人新的位置更新到当前位置
				count++;									//小人移动一次,步数统计加一
				ifMove = true;								//箱子移动 ifMove 的值改为真
			}
		}
	}
	else if (isValid(next_pos) && isValid(next_next_pos) && map[next_pos.x][next_pos.y] == HIT) {	//箱子命中目标
		if (map[next_next_pos.x][next_next_pos.y] == FLOOR) {				//箱子目的地前面是地板
			if (map[man.x][man.y] == MAN) {						//小人在地板的情况
				changoMap(&next_next_pos, BOX, map, line, column);					//箱子命中目的地换成箱子
				changoMap(&next_pos, MAN_DES, map, line, column);					//小人站在箱子目的地上			
				changoMap(&man, FLOOR, map, line, column);							//原来小人的位置换成地板
				man = next_pos;									//将小人新的位置更新到当前位置
				count++;										//小人移动一次,步数统计加一
				ifMove = true;								//箱子移动 ifMove 的值改为真
			}
			else if (map[man.x][man.y] == MAN_DES) {			//小人在箱子目的地上的情况
				changoMap(&next_next_pos, BOX, map, line, column);					//箱子命中目的地换成箱子
				changoMap(&next_pos, MAN_DES, map, line, column);					//小人站在箱子目的地上			
				changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
				man = next_pos;									//将小人新的位置更新到当前位置
				count++;										//小人移动一次,步数统计加一
				ifMove = true;								//箱子移动 ifMove 的值改为真
			}

		}
		else if (map[next_next_pos.x][next_next_pos.y] == BOX_DES) {		//箱子命中目标前面是箱子目的地
			if (map[man.x][man.y] == MAN) {						//小人在地板的情况
				changoMap(&next_next_pos, HIT, map, line, column);					//箱子推出到下一个箱子目的地
				changoMap(&next_pos, MAN_DES, map, line, column);					//小人站在箱子目的地上			
				changoMap(&man, FLOOR, map, line, column);							//原来小人的位置换成地板
				man = next_pos;									//将小人新的位置更新到当前位置
				count++;										//小人移动一次,步数统计加一
				ifMove = true;									//箱子移动 ifMove 的值改为真
			}
			else if (map[man.x][man.y] == MAN_DES) {			//小人在箱子目的地上的情况
				changoMap(&next_next_pos, HIT, map, line, column);					//箱子命中目的地换成下一个箱子命中目标
				changoMap(&next_pos, MAN_DES, map, line, column);					//小人站在箱子目的地上的下一个目的地上		
				changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
				man = next_pos;									//将小人新的位置更新到当前位置
				count++;										//小人移动一次,步数统计加一
				ifMove = true;									//箱子移动 ifMove 的值改为真
			}
		}
	}
	else if (isValid(next_pos) && map[next_pos.x][next_pos.y] == BOX_DES) {	//小人前面是箱子目的地
		if (map[man.x][man.y] == MAN_DES) {						//小人在箱子目的地上的情况
			changoMap(&next_pos, MAN_DES, map, line, column);						//小人站在下一个箱子目的地上			
			changoMap(&man, BOX_DES, map, line, column);							//原来小人的位置换成地板
			man = next_pos;										//将小人新的位置更新到当前位置
			count++;											//小人移动一次,步数统计加一
			ifMove = false;								//箱子未移动 ifMove 的值改为假
		}
		else if (map[man.x][man.y] == MAN) {					//小人在地板上
			changoMap(&next_pos, MAN_DES, map, line, column);						//小人站在箱子目的地上			
			changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
			man = next_pos;										//将小人新的位置更新到当前位置
			count++;											//小人移动一次,步数统计加一
			ifMove = false;								//箱子未移动 ifMove 的值改为假
		}
	}	
}

/*****************************************
*功能: 加载资源
*输入:
*		bg_img - 背景图片数组
*输出:无
******************************************/
void loadResources(IMAGE *bg_img) {
	//搭建舞台
	//initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);	//设置舞台大小
	loadimage(&bg_img[BG], _T("35.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);	//加载背景图片并设置背景图片大小
	loadimage(&bg_img[VICTORY], _T("victory.png"), SCREEN_WIDTH1, SCREEN_HEIGHT1, true);		//胜利背景
	loadimage(&bg_img[OVER], _T("over.png"), SCREEN_WIDTH1, SCREEN_HEIGHT1, true);		//失败背景
	loadimage(&bg_img[SOKOBAN], _T("Sokoban.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);		//失败背景


	//putimage(0, 0, &bg_img[BG]);		//在控制台(0,0)坐标打印图片


	//加载道具图标
	loadimage(&images[WALL], _T("wall_right.bmp"), RATIO, RATIO, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX_DES], _T("des.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN], _T("man.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[HIT], _T("box_hit.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN_DES], _T("man_des.bmp"), RATIO, RATIO, true);
}
/*****************************************
*功能: 找到小人并打印步数和操作说明 关数
*输入:
*		bg_img - 背景图片数组
*		map[LINE][COLUMN]	-	地图结构体中的数组
*		const int line		-	地图的行的常量
*		const int column	-	地图的列的常量
*		customsPass			-	第几关
*输出:无
******************************************/
void initGameScene(int map[LINE][COLUMN], const int line, const int column, int customsPass) {

	char str[16];

	//循环打印道具图标到舞台指定位置
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			if (map[i][j] == MAN || map[i][j] == MAN_DES) {				//判断是不是小人,如果是小人,将小人的(x,y)坐标传入man中
				man.x = i;
				man.y = j;
			}			
			//STAR_X
			putimage(((SCREEN_WIDTH - (column * RATIO)) / 2) + j * RATIO,
				(((SCREEN_HEIGHT - (line * RATIO)) / 2) + (STAR_Y/2))+ i * RATIO, 
				&images[map[i][j]]);
		}
	}
	//STAR_Y + i * RATIO
	//(((SCREEN_HEIGHT - (line * RATIO))/2) + STAR_Y
	
	setcolor(BLUE);
	settextstyle(18, 0, _T("宋体"));
	setbkmode(TRANSPARENT);
	outtextxy(780, 10, "2022-13-14  9:05:20");

	//操作说明	
	settextstyle(20, 0, _T("宋体"));						//设置字体大小
	setcolor(LIGHTBLUE);									//设置字体颜色(蓝色)
	setbkmode(TRANSPARENT);									//设置文字背景色为透明色
	outtextxy(300, 25, _T(" 操作说明："));					//在指定位置输出文本
	outtextxy(300, 50, _T(" w / W 或者 ↑ ：向上"));		//在指定位置输出文本
	outtextxy(300, 75, _T(" s / S 或者 ↓ ：向下"));		//在指定位置输出文本
	outtextxy(300, 100, _T(" a / A 或者 ← ：向左"));		//在指定位置输出文本
	outtextxy(300, 125, _T(" d / D 或者 → ：向右"));		//在指定位置输出文本
	outtextxy(550, 50, _T(" t / T ：重新开始关卡"));		//在指定位置输出文本
	outtextxy(550, 75, _T(" r / R ：后退"));				//在指定位置输出文本
	outtextxy(550, 100, _T(" p / P ：重新选择关卡"));		//在指定位置输出文本
	outtextxy(550, 125, _T(" q / Q ：退出"));				//在指定位置输出文本
	

	//步数	
	setcolor(BLUE);								//设置字体颜色(红色)
	setbkmode(TRANSPARENT);						//设置文字背景色为透明色
	outtextxy(25, 25, _T("步数："));			//在指定位置输出文本
	outtextxy(75, 25, _T("0"));					//在指定位置输出初始分数	

	sprintf_s(str, "第 %d 关", customsPass);				//将int变量转换成char字符保存
	outtextxy((SCREEN_WIDTH - 100), 25, str);
}
/*****************************************
*功能:实现游戏后退一步
*输入:
*		retreat				-	玩家上一次操作的应用
*		count				-	玩家当前游戏步数
*		map[LINE][COLUMN]	-	地图结构体中的数组
*		const int line		-	地图的行的常量
*		const int column	-	地图的列的常量
*输出:
		返回游戏步数,后退一步后,游戏步数减一
******************************************/
void takeBack(char &retreat, int &count, bool &ifMove,int map[LINE][COLUMN], const int line, const int column) {
	//如果count = 0证明没有移动过,直接返回当前值
	if (count <= 0 || retreat == 0) return;
	POS last_pos = man;			//小人后面
	POS last_pos1 = man;		//小人前面
	POS last_last_pos = man;	//小人后两格

	switch (retreat) {
	case KEY_UP:
	case 72:
		last_pos1.x--;		//小人前面
		last_pos.x++;		//小人后面
		last_last_pos.x += 2;	//小人后面第二格
		break;
	case KEY_LEFT:
	case 80:
		last_pos1.x++;		//小人前面
		last_pos.x--;		//小人后面
		last_last_pos.x -= 2;	//小人后面第二格
		break;
	case KEY_RIGHT:
	case 75:
		last_pos1.y--;		//小人前面
		last_pos.y++;		//小人后面
		last_last_pos.y += 2;	//小人后面第二格
		break;
	case KEY_DOWN:
	case 77:
		last_pos1.y++;		//小人前面
		last_pos.y--;		//小人后面
		last_last_pos.y -= 2;	//小人后面第二格
		break;
	}

	//两种情况,一种小人在目的地上面,一种在地板上
	if (map[man.x][man.y] == MAN_DES) {
		if (map[last_pos1.x][last_pos1.y] == BOX) {					//小人前面是箱子
			if (ifMove == true) {									//ifMove 为真表示箱子移动过,后退箱子需要一起移动
				if (map[last_pos.x][last_pos.y] == BOX_DES) {		//小人后面是箱子目的地的情况
					changoMap(&last_pos1, FLOOR, map, line, column);					//将小人前面的箱子换成地板
					changoMap(&last_pos, MAN_DES, map, line, column);					//小人后退一格			
					changoMap(&man, HIT, map, line, column);							//原来小人的位置换成箱子命中目标
					man = last_pos;									//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {	//小人后面是地板的情况
					changoMap(&last_pos1, FLOOR, map, line, column);					//将小人前面的箱子换成地板
					changoMap(&last_pos, MAN, map, line, column);						//小人后退一格			
					changoMap(&man, HIT, map, line, column);							//原来小人的位置换成箱子命中目标
					man = last_pos;									//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
			}
			else {												//否则ifMove 为假表示箱子未移动过,后退箱子不需要一起移动
				if (map[last_pos.x][last_pos.y] == BOX_DES) {		//小人后面是箱子目的地的情况
					changoMap(&last_pos, MAN_DES, map, line, column);					//小人后退一格			
					changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
					man = last_pos;									//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {	//小人后面是地板的情况
					changoMap(&last_pos, MAN, map, line, column);						//小人后退一格			
					changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
					man = last_pos;									//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
			}

		}
		else if (map[last_pos1.x][last_pos1.y] == HIT) {		//小人前面是箱子命中目标
			if (ifMove == true) {									//ifMove 为真表示箱子移动过,后退箱子需要一起移动
				if (map[last_pos.x][last_pos.y] == BOX_DES) {		//小人当前位置在目的地上
					changoMap(&last_pos1, BOX_DES, map, line, column);					//将小人前面的箱子换成箱子目的地
					changoMap(&last_pos, MAN_DES, map, line, column);						//小人后退到地板上			
					changoMap(&man, HIT, map, line, column);							//原来小人的位置换成箱子命中目标
					man = last_pos;									//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {	//小人在后面是地板的情况
					changoMap(&last_pos1, BOX_DES, map, line, column);					//将小人前面的箱子换成箱子目的地
					changoMap(&last_pos, MAN, map, line, column);						//小人后退到下一个地板上			
					changoMap(&man, HIT, map, line, column);							//原来小人的位置换成箱子命中目的地
					man = last_pos;									//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
			}
			else {												//否则ifMove 为假表示箱子未移动过,后退箱子不需要一起移动
				if (map[last_pos.x][last_pos.y] == BOX_DES) {		//小人当前位置在目的地上
					changoMap(&last_pos, MAN_DES, map, line, column);					//小人后退到地板上			
					changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
					man = last_pos;									//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {	//小人在后面是地板的情况
					changoMap(&last_pos, MAN, map, line, column);						//小人后退到下一个地板上			
					changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
					man = last_pos;									//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == FLOOR) {	//小人前面是地板的情况
			if (map[last_pos.x][last_pos.y] == BOX_DES) {
				changoMap(&last_pos, MAN_DES, map, line, column);					//小人后退一格			
				changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
				man = last_pos;									//将小人新的位置更新到当前位置
				count--;										//步数减一
			}
			else if (map[last_pos.x][last_pos.y] == FLOOR) {	//小人在后面是地板的情况
				changoMap(&last_pos, MAN, map, line, column);						//小人后退到下一个地板上			
				changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子命中目的地
				man = last_pos;									//将小人新的位置更新到当前位置
				count--;										//步数减一
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == BOX_DES) {	//小人前面是箱子目的地的情况
			if (map[last_pos.x][last_pos.y] == BOX_DES) {		//小人后面是箱子目的地的情况
				changoMap(&last_pos1, BOX_DES, map, line, column);					//将小人前面的箱子换成箱子目的地
				changoMap(&last_pos, MAN_DES, map, line, column);					//小人后面的箱子目的地换成小人在箱子目的地			
				changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
				man = last_pos;									//将小人新的位置更新到当前位置
				count--;										//步数减一
			}
			else if (map[last_pos.x][last_pos.y] == FLOOR) {	//小人后面是地板的情况
				changoMap(&last_pos1, BOX_DES, map, line, column);					//将小人前面的箱子换成箱子目的地
				changoMap(&last_pos, MAN, map, line, column);						//小人后面换成小人在地板上		
				changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
				man = last_pos;									//将小人新的位置更新到当前位置
				count--;										//步数减一
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == WALL) {		//小人前面是墙的情况
			if (map[last_pos.x][last_pos.y] == FLOOR) {			//小人后面是地板的情况
				changoMap(&last_pos, MAN, map, line, column);						//小人后面换成小人在地板上
				changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
				man = last_pos;									//将小人新的位置更新到当前位置
				count--;										//步数减一
			}
			else if (map[last_pos.x][last_pos.y] == BOX_DES) {//小人后面是箱子目的地的情况
				changoMap(&last_pos, MAN_DES, map, line, column);					//小人后面换成小人在箱子目的地上
				changoMap(&man, BOX_DES, map, line, column);						//原来小人的位置换成箱子目的地
				man = last_pos;									//将小人新的位置更新到当前位置
				count--;										//步数减一
			}
		}
	}
	else if (map[man.x][man.y] == MAN) {							//小人在地板上的情况
	 //小人前面是箱子、箱子命中目标、地板、箱子目的地
		if (map[last_pos1.x][last_pos1.y] == BOX) {						//小人前面是箱子的情况
			if (ifMove == true) {										//ifMove 为真表示箱子移动过,后退箱子需要一起移动
				if (map[last_pos.x][last_pos.y] == BOX_DES) {			//小人后面是箱子目的地的情况
					changoMap(&last_pos1, FLOOR, map, line, column);						//箱子原来的位置换成地板
					changoMap(&last_pos, MAN_DES, map, line, column);						//小人后面换成小人在箱子目的地上	
					changoMap(&man, BOX, map, line, column);								//原来小人的位置换成箱子
					man = last_pos;										//将小人新的位置更新到当前位置
					count--;											//步数减一
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {		//小人前面是地板的情况
					changoMap(&last_pos1, FLOOR, map, line, column);						//箱子原来的位置换成地板
					changoMap(&last_pos, MAN, map, line, column);							//小人后退一格			
					changoMap(&man, BOX, map, line, column);								//原来小人的位置换成箱子
					man = last_pos;										//将小人新的位置更新到当前位置
					count--;											//步数减一
				}
			}
			else {													//否则ifMove 为假表示箱子未移动过,后退箱子不需要一起移动
				if (map[last_pos.x][last_pos.y] == BOX_DES) {			//小人后面是箱子目的地的情况
					changoMap(&last_pos, MAN_DES, map, line, column);						//小人后面换成小人在箱子目的地上	
					changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
					man = last_pos;										//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {		//小人前面是地板的情况
					changoMap(&last_pos, MAN, map, line, column);							//小人后退一格			
					changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
					man = last_pos;										//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
			}

		}
		else if (map[last_pos1.x][last_pos1.y] == HIT) {			//小人前面是箱子命中箱子目的地的情况
			if (ifMove == true) {										//ifMove 为真表示箱子移动过,后退箱子需要一起移动
				if (map[last_pos.x][last_pos.y] == FLOOR) {				//小人后面是箱子目的地的情况
					changoMap(&last_pos1, BOX_DES, map, line, column);						//箱子命中目标换成箱子目的地
					changoMap(&last_pos, MAN, map, line, column);							//小人后退一格			
					changoMap(&man, BOX, map, line, column);								//原来小人的位置换成箱子
					man = last_pos;										//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
				else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//小人后面是箱子目的地的情况
					changoMap(&last_pos1, BOX_DES, map, line, column);						//箱子命中目标换成箱子目的地
					changoMap(&last_pos, MAN_DES, map, line, column);						//小人面换成小人在箱子目的地上
					changoMap(&man, BOX, map, line, column);								//原来小人的位置换成箱子
					man = last_pos;										//将小人新的位置更新到当前位置
					count--;										//步数减一
				}
			}
			else {													//否则ifMove 为假表示箱子未移动过,后退箱子不需要一起移动
				if (map[last_pos.x][last_pos.y] == FLOOR) {				//小人后面是箱子目的地的情况
					changoMap(&last_pos, MAN, map, line, column);							//小人后退一格			
					changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
					man = last_pos;										//将小人新的位置更新到当前位置
					count--;											//步数减一
				}
				else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//小人后面是箱子目的地的情况
					changoMap(&last_pos, MAN_DES, map, line, column);						//小人面换成小人在箱子目的地上
					changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
					man = last_pos;										//将小人新的位置更新到当前位置
					count--;											//步数减一
				}
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == FLOOR) {		//小人前面是地板的情况
			if (map[last_pos.x][last_pos.y] == FLOOR) {				//小人后面是地板的情况
				changoMap(&last_pos, MAN, map, line, column);							//小人后退一格			
				changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
				man = last_pos;										//将小人新的位置更新到当前位置
				count--;											//步数减一
			}
			else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//小人后面是箱子目的地的情况
				changoMap(&last_pos, MAN_DES, map, line, column);						//小人后退一格			
				changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
				man = last_pos;										//将小人新的位置更新到当前位置
				count--;											//步数减一
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == BOX_DES) {		//小人前面是箱子目的地
			if (map[last_pos.x][last_pos.y] == FLOOR) {				//小人后面是地板的情况
				changoMap(&last_pos, MAN, map, line, column);							//小人后退一格站在目的地上			
				changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
				man = last_pos;										//将小人新的位置更新到当前位置
				count--;											//步数减一
			}
			else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//小人后面是箱子目的地上的情况
				changoMap(&last_pos, MAN_DES, map, line, column);						//小人后退一格站在目的地上			
				changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成箱子目的地
				man = last_pos;										//将小人新的位置更新到当前位置
				count--;											//步数减一
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == WALL) {			//小人前面是墙的情况
			if (map[last_pos.x][last_pos.y] == FLOOR) {				//小人后面是地板的情况
				changoMap(&last_pos, MAN, map, line, column);							//小人后退一格站在目的地上			
				changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成地板
				man = last_pos;										//将小人新的位置更新到当前位置
				count--;										//步数减一
			}
			else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//小人后面是箱子目的地上的情况
				changoMap(&last_pos, MAN_DES, map, line, column);						//小人后退一格站在目的地上			
				changoMap(&man, FLOOR, map, line, column);								//原来小人的位置换成箱子目的地
				man = last_pos;										//将小人新的位置更新到当前位置
				count--;										//步数减一
			}

		}
	}
	//return count;
	ifMove = false;												//小人推完箱子之后没有回退就将 ifMove 置为假
}
/*****************************************
*功能:开始游戏
*输入:
*		bg - 背景图片指针
*输出:
*		无
******************************************/
void startInterface(IMAGE* bg) {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);				//设置舞台大小
	putimage(0, 0, &bg[SOKOBAN]);									//打印传入背景图片

	MOUSEMSG mouse;//定义鼠标消息的变量
	while (1) {
		//循环获取鼠标状态
		mouse = GetMouseMsg();

		switch (mouse.uMsg) {
		case WM_LBUTTONDOWN:
			if (mouse.x > 755 && mouse.x < 920 && mouse.y > 644 && mouse.y < 720) {
				//清除屏幕内容
				cleardevice();
				return;
			}
		}
		//Sleep(10);
	}
}
/*****************************************
*功能:关卡选择
*输入:
*		bg - 背景图片指针
*输出:
*		无
******************************************/
int checkpointChoice(IMAGE* bg, int customsPass) {
	MOUSEMSG mouse;//定义鼠标消息的变量
	putimage(0, 0, &bg[BG]);									//打印传入背景图片
	customsPass = 0;
	const char* str[MAP_QUANTITY] = {
		"第一关",
		"第二关",
		"第三关",
		"第四关",
		"第五关",
		"第六关",
		"第七关"
	};
	setcolor(WHITE);										//设置字体颜色(红色)
	settextstyle(18, 0, _T("宋体"));							//设置字体
	setbkmode(TRANSPARENT);								//设置文字背景色为透明色
	for (int i = 0; i < MAP_QUANTITY; i++) {
		rectangle(100 + (i * 110), 100, 200 + (i * 110), 150);	//绘制矩形
		outtextxy(125 + (i * 110), 120, str[i]);			//在矩形中打印文字
	}
	
	setcolor(BLUE);
	setbkmode(TRANSPARENT);
	outtextxy(780, 10, "2022-13-14  9:05:20");

	setcolor(WHITE);										//设置字体颜色(红色)
	setbkmode(TRANSPARENT);								//设置文字背景色为透明色
	outtextxy(100, 50, _T(" 请选择你要从第几关开始玩："));				//在指定位置输出文本

	outtextxy(100, 170, "人生路上过客很多,每个人都有各自的终点,他们向东向西向南向北,而我向你.");
	outtextxy(100, 190, "春有百花秋有月，夏有凉风冬有雪，而我只想早晚都有你。");
	outtextxy(100, 210, "我喜欢你，从黑夜到黎明，从冷冬到暖春，从一秒到一生，生生不息，轮回不止。");

	setcolor(LIGHTBLUE);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "微软雅黑");

	outtextxy(350, 240, "《涉江采芙蓉》");
	outtextxy(300, 300, "涉江采芙蓉，兰泽多芳草。");
	outtextxy(300, 360, "采之欲遗谁？所思在远道。");
	outtextxy(300, 420, "还顾望旧乡，长路漫浩浩。");
	outtextxy(300, 480, "同心而离居，忧伤以终老。");

	setcolor(YELLOW);
	settextstyle(30, 0, "黑体");
	outtextxy(340,530,"—执着于属于自己的人与事物");
	while (1) {
		//循环获取鼠标状态
		mouse = GetMouseMsg();

		switch (mouse.uMsg) {
		case WM_LBUTTONDOWN:
			if (mouse.x > 100 && mouse.x < 200 && mouse.y > 100 && mouse.y < 150) {
				//清除屏幕内容
				//cleardevice();
				return customsPass;
			}
			else if (mouse.x > 100 + (1 * 110) && mouse.x < 200 + (1 * 110) && mouse.y > 100 && mouse.y < 150) {
				//cleardevice();
				return customsPass + 1;
			}
			else if (mouse.x > 100 + (2 * 110) && mouse.x < 200 + (2 * 110) && mouse.y > 100 && mouse.y < 150) {
				//cleardevice();
				return customsPass + 2;
			}
			else if (mouse.x > 100 + (3 * 110) && mouse.x < 200 + (3 * 110) && mouse.y > 100 && mouse.y < 150) {
				//cleardevice();
				return customsPass + 3;
			}
			else if (mouse.x > 100 + (4 * 110) && mouse.x < 200 + (4 * 110) && mouse.y > 100 && mouse.y < 150) {
				//cleardevice();
				return customsPass + 4;
			}
			else if (mouse.x > 100 + (5 * 110) && mouse.x < 200 + (5 * 110) && mouse.y > 100 && mouse.y < 150) {
				//cleardevice();
				return customsPass + 5;
			}
			else if (mouse.x > 100 + (6 * 110) && mouse.x < 200 + (6 * 110) && mouse.y > 100 && mouse.y < 150) {
				//cleardevice();
				return customsPass + 6;
			}
		}
		//Sleep(10);
	}

	//system("pause");
}
/*****************************************
*功能:开始游戏
*输入:
*		无
*输出:
*		无
******************************************/
void startGame(int customsPass) {
	//游戏环节
	bool quit = false;				//用于判断是否退出
	int count = 0;					//玩家游戏步数统计接收
	char str[16];					//保存统计步数
	char ch = '\0';					//保存玩家当前操作
	char retreat = '\0';			//保存玩家当前操作用于回退
	bool ifMove = false;			//用于判断小人前面的箱子有没有移动
	//int customsPass = 0;			//关卡控制		
	struct MAP *pmap = NULL;		//定义地图结构体指针
	struct MAP map2[MAP_QUANTITY] = { 0,0,{0} };	//拷贝当前地图
	pmap = &map1[customsPass];		//指向第一个地图
	while (quit == false) {
		//拷贝所有地图
		for (int i = 0; i < MAP_QUANTITY; i++) {
			map2[i] = map1[i];
		}
		//map2[customsPass] = map1[customsPass];		//拷贝当前地图,用于重新开始当前关卡
		//memcpy(map2.map, map1, sizeof(map1->map));

		//打印第一关页面
		levelsPrompt(&bg_img[BG], customsPass + 1);


		//找到小人并打印步数和操作说明 关数

		initGameScene(pmap->map, pmap->line, pmap->column, customsPass + 1);

		//设置步数的动态数字的实心矩形填充色
		int bgColor = getpixel(0, 0);	//获取背景色
		setfillcolor(bgColor);

		do {
			if (_kbhit()) {				//玩家有无按键操作
				if ((ch == KEY_UP || ch == 72) ||
					(ch == KEY_DOWN || ch == 80) ||
					(ch == KEY_LEFT || ch == 75) ||
					(ch == KEY_RIGHT || ch == 77)) {
					retreat = ch;			//保存玩家当前操作用于回退
				}
				ch = _getch();			//获取玩家按键保存到 ch中			
				//判断玩家的按键
				if (ch == KEY_UP || ch == 72 || ch == (KEY_UP - 32)) {				//上
					gameControl(UP, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_DOWN || ch == 80 || ch == (KEY_DOWN - 32)) {	//下
					gameControl(DOWN, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_LEFT || ch == 75 || ch == (KEY_LEFT - 32)) {	//左
					gameControl(LEFT, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_RIGHT || ch == 77 || ch == (KEY_RIGHT - 32)) {	//右
					gameControl(RIGHT, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_RETREAT || ch == (KEY_RETREAT - 32)) {				//后退
					takeBack(retreat, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_RESTART || ch == (KEY_RESTART - 32)) {				//重新开始当前关卡
					if (count <= 0) {						//如果步数为零,表示小人未移动过,无需重置地图
						continue;	//执行下一次循环
					}
					map1[customsPass] = map2[customsPass];				//恢复地图
					initGameScene(pmap->map, pmap->line, pmap->column, customsPass + 1);	//打印恢复的地图
					count = 0;								//步数置零
				}
				else if (ch == KEY_RESELECT || ch == (KEY_RESELECT - 32)) {
					customsPass = checkpointChoice(bg_img, customsPass);
				}
				else if (ch == KEY_QUIT || ch == (KEY_QUIT - 32)) {				//退出
					quit = true;
				}

				//动态打印分数
				sprintf_s(str, "%d", count);				//将int变量转换成char字符保存
				solidrectangle(75, 25, 125, 50);				//绘制步数的动态数字的实心矩形
				outtextxy(75, 25, str);						//在指定位置输出转换的变量值			

				if (isGameOver(pmap->map, pmap->line, pmap->column)) {
					if ((customsPass + 1) < MAP_QUANTITY) {
						gemrOverScene(&bg_img[BG], &bg_img[VICTORY], customsPass + 1);
						levelsPrompt(&bg_img[BG], customsPass + 2);						//下一关提示页面
						pmap++;															//进入下一关						
						initGameScene(pmap->map, pmap->line, pmap->column, customsPass + 2);	//加载下一关地图
						customsPass++;
						map2[customsPass] = map1[customsPass];										//将新地图拷贝一份到map2中,用于恢复当前关卡
						count = 0;													//下一关步数置零
						setfillcolor(bgColor);			//设置下一关步数的动态数字的实心矩形填充色
					}
					else {
						gemrOverScene(&bg_img[BG], &bg_img[VICTORY], customsPass + 1);
						//system("pause");
						quit = true;
					}
				}
				if (count > COUNT) {
					gameOverMan(&bg_img[BG], &bg_img[OVER]);					
					quit = true;
				}
			}
			Sleep(100);					//休眠0.1秒
		} while (quit == false); //!quit

		if (ch == KEY_QUIT || ch == (KEY_QUIT - 32)) {
			settextcolor(WHITE);										//设置文字颜色为白色
			RECT rec = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };				//绘制矩形
			settextstyle(30, 0, _T("宋体"));							//设置字体
			drawtext(_T("推箱子老司机您确定要退出吗? 确定请按 'Q',重新开始请按 'T'"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		while (quit == true) {
			if (_kbhit()) {				//玩家有无按键操作			
				ch = _getch();			//获取玩家按键保存到 ch中	
				if (ch == KEY_RESTART || ch == (KEY_RESTART - 32)) {
					quit = false;
					for (int i = 0; i < MAP_QUANTITY; i++) {	//恢复全部初始地图
						map1[i] = map2[i];
					}
					customsPass = 0;							//关卡置零
					pmap = &map1[0];							//pmap重新指向第一个地图
					break;
				}
				else if (ch == KEY_QUIT || ch == (KEY_QUIT - 32)) {	//确认退出
					break;
				}

			}
			Sleep(100);
		}
	}
}



int main(void) {
	int customsPass = 0;			//关卡控制		

	//加载资源
	loadResources(bg_img);

	//开始界面
	startInterface(bg_img);
	//加载时间
	setcolor(BLUE);
	settextstyle(18, 0, _T("宋体"));
	setbkmode(TRANSPARENT);
	outtextxy(780, 10, "2022-13-14  9:05:20");
	//加载音乐；send:发射
	mciSendString("play 等不来花开.mp3 repeat",0,0,0);
	//关卡选择
	customsPass = checkpointChoice(bg_img, customsPass);

	//开始游戏
	startGame(customsPass);


	//游戏结束释放资源
	closegraph();
	return 0;
}