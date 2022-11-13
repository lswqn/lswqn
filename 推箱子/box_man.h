#pragma once

#ifndef BOX_MAN_H
#define BOX_MAN_H



#define RATIO 61			//墙,箱子,地板, 小人,小人在目的地上,目的地的图片大小

#define SCREEN_WIDTH 960	//舞台的长960
#define SCREEN_HEIGHT 768	//舞台的高768

#define SCREEN_WIDTH1  430	//胜利和失败的图片大小
#define SCREEN_HEIGHT1 240	//胜利和失败的图片大小

#define LINE 12				//地图最大的行
#define COLUMN 12			//地图最大的列

#define MAP_QUANTITY	7	//地图数量

#define STAR_X 100			//地图第一个图片的X坐标
#define STAR_Y 150			//地图第一个图片的Y坐标

#define COUNT 300			//游戏步数限制

//控制键 上、下、左、右 控制方向,'q' 退出
#define KEY_UP		'w'		//上
#define KEY_LEFT	'a'		//下
#define KEY_RIGHT	'd'		//左
#define KEY_DOWN	's'		//右
#define KEY_QUIT	'q'		//退出
#define KEY_RETREAT 'r'		//后退
#define KEY_RESTART	't'		//重新开始当前关卡
#define KEY_RESELECT 'o'	//重新选择关卡

#define isValid(pos) pos.x >= 0 && pos.x < LINE && pos.y >= 0 && pos.y < COLUMN  

typedef enum _PROPS		 PROPS;			//枚举类型别名
typedef enum _DIRECTION  DIRECTION;		//枚举类型别名
typedef struct _POS		 POS;			//结构体类型别名

//游戏背景图片
enum _BGIMAGE {
	BG,						//游戏背景
	VICTORY,				//游戏胜利背景
	OVER,					//游戏失败背景
	SOKOBAN,				//推箱子开始图片
	ALL1					//共有多少背景
};


//枚举
enum _PROPS {
	WALL,					//墙
	FLOOR,					//地板
	BOX_DES,				//箱子目的地
	MAN,					//小人
	BOX,					//箱子
	HIT,					//箱子命中目标
	MAN_DES,				//小人站在目的地上
	ALL						//共有多少元素
};

//游戏控制方向
enum _DIRECTION {
	UP,						//上
	DOWN,					//下
	LEFT,					//左
	RIGHT					//右
};

//结构体
struct _POS {
	int x;					//小人所在的二维数组的行
	int y;					//小人所在的二维数组的列
};

struct MAP {
	int line;			//地图的行
	int column;		//地图列
	int map[LINE][COLUMN];	//地图数组
};


#endif // !BOX_MAN.H