#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

using namespace std;

#define RATIO 61

#define SCREEN_WIDTH   960
#define SCREEN_HEIGHT  768

//按键 上、下、左、右 控制方向 ，‘q’退出
#define KEY_UP			    'w'	  //char'a'
#define KEY_LEFT			'a'
#define KEY_RIGHT			'd'
#define KEY_DOWN			's'
#define KEY_QUIT			'q' 

#define LINE   9
#define COLUMN 12

#define START_X   100
#define START_Y	  150

enum _PROPS{
	WALL,			//墙
	FLOOR,			//地板
	BOX_DES,		//箱子目的地
	MAN,			//小人
	BOX,			//箱子
	HIT,			//箱子命中目标
	ALL
};

//游戏控制方向
enum _DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};



struct _POS {
	int x;			//小人所在二维数组的行
	int y;			//小人所在二维数组的列
};

IMAGE images[ALL];

struct _POS man;			//小人所在二维数组中的位置

/*游戏地图*/
int map[LINE][COLUMN] = 
{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 1, 0 },
{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0 },
{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0 },
{ 0, 1, 1, 1, 1, 3, 1, 1, 1, 4, 1, 0 },
{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

/***************************************************
*改变游戏视图中一格对应道具并重新显示
*输入:
*		line    - 道具在地图数组的行下标
*		column- - 道具在地图数组的列下标
*		prop    - 道具的类型
*	返回值:无	
***************************************************/
void changeMap(int line, int column, enum _PROPS prop){
	map[line][column] = prop;
	putimage(START_X+column*RATIO, START_Y+line*RATIO, &images[prop]);
}

/**************************************************
*实现游戏四个方向(上、下、左、右)的控制
*输入：
* direct - 人前进方向
* 输出:无
***************************************************/
void gameControl(enum _DIRECTION direct){
	int  x = man.x;
	int  y = man.y;

	if(direct=UP){//先处理前进方向是地板的情况
		if((x-1)>=0 && map[x-1][y] == FLOOR){
			changeMap(x-1,y,MAN);//小人的前进一格
			man.x = x -1;
			changeMap(x, y, FLOOR);
	    }
	}else if(direct == DOWN){
		if((x+1)<LINE && map[x+1][y] == FLOOR){
			changeMap(x+1,y,MAN);//小人的前进一格
			man.x = x + 1;
			changeMap(x, y, FLOOR);
	    }
   }else if(direct == LEFT){
		if((y - 1)>=0 && map[x][y-1] == FLOOR){
			changeMap(x,y-1,MAN);//小人的前进一格
			man.y = y - 1;
			changeMap(x, y, FLOOR);
	    }
  }else if(direct == RIGHT){
		if((y + 1)<COLUMN && map[x][y+1] == FLOOR){
			changeMap(x,y+1,MAN);//小人的前进一格
			man.y = y + 1;
			changeMap(x, y, FLOOR);
	    }
  }

}

int main(void){
	IMAGE bg_img;

	//搭台唱戏
	initgraph(SCREEN_WIDTH,SCREEN_HEIGHT);
	loadimage(&bg_img, _T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_img);

	//加载道具图标
	loadimage(&images[WALL], _T("wall.bmp"), RATIO, RATIO, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX_DES], _T("des.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN], _T("man.bmp") ,RATIO, RATIO, true);
	loadimage(&images[BOX], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[HIT], _T("box.bmp"), RATIO, RATIO, true);

	for(int i = 0; i < LINE; i++){
		for(int j = 0;j < COLUMN; j++){
			if(map[i][j]==MAN){
				man.x = i;
				man.y = j;
			}

			putimage(START_X+j*RATIO,START_Y+i*RATIO,&images[map[i][j]]);
		}
	}

	//游戏环节
	bool quit = false;


	do{
		if(_kbhit()){//玩家按键
			char ch= _getch();

			if(ch == KEY_UP){
				gameControl(UP);
			}else if(ch == KEY_DOWN){
				gameControl(DOWN);
			}else if(ch == KEY_LEFT){
				gameControl(LEFT);
			}else if(ch == KEY_RIGHT){
				gameControl(RIGHT);
			}else if(ch == KEY_QUIT){
					quit  = true;
			}
		}
		Sleep(100);
	}while(quit=false); //!quit
	
	system("pause");
	return 0;
}









