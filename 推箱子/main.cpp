#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

using namespace std;

#define RATIO 61

#define SCREEN_WIDTH   960
#define SCREEN_HEIGHT  768

//���� �ϡ��¡����� ���Ʒ��� ����q���˳�
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
	WALL,			//ǽ
	FLOOR,			//�ذ�
	BOX_DES,		//����Ŀ�ĵ�
	MAN,			//С��
	BOX,			//����
	HIT,			//��������Ŀ��
	ALL
};

//��Ϸ���Ʒ���
enum _DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};



struct _POS {
	int x;			//С�����ڶ�ά�������
	int y;			//С�����ڶ�ά�������
};

IMAGE images[ALL];

struct _POS man;			//С�����ڶ�ά�����е�λ��

/*��Ϸ��ͼ*/
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
*�ı���Ϸ��ͼ��һ���Ӧ���߲�������ʾ
*����:
*		line    - �����ڵ�ͼ��������±�
*		column- - �����ڵ�ͼ��������±�
*		prop    - ���ߵ�����
*	����ֵ:��	
***************************************************/
void changeMap(int line, int column, enum _PROPS prop){
	map[line][column] = prop;
	putimage(START_X+column*RATIO, START_Y+line*RATIO, &images[prop]);
}

/**************************************************
*ʵ����Ϸ�ĸ�����(�ϡ��¡�����)�Ŀ���
*���룺
* direct - ��ǰ������
* ���:��
***************************************************/
void gameControl(enum _DIRECTION direct){
	int  x = man.x;
	int  y = man.y;

	if(direct=UP){//�ȴ���ǰ�������ǵذ�����
		if((x-1)>=0 && map[x-1][y] == FLOOR){
			changeMap(x-1,y,MAN);//С�˵�ǰ��һ��
			man.x = x -1;
			changeMap(x, y, FLOOR);
	    }
	}else if(direct == DOWN){
		if((x+1)<LINE && map[x+1][y] == FLOOR){
			changeMap(x+1,y,MAN);//С�˵�ǰ��һ��
			man.x = x + 1;
			changeMap(x, y, FLOOR);
	    }
   }else if(direct == LEFT){
		if((y - 1)>=0 && map[x][y-1] == FLOOR){
			changeMap(x,y-1,MAN);//С�˵�ǰ��һ��
			man.y = y - 1;
			changeMap(x, y, FLOOR);
	    }
  }else if(direct == RIGHT){
		if((y + 1)<COLUMN && map[x][y+1] == FLOOR){
			changeMap(x,y+1,MAN);//С�˵�ǰ��һ��
			man.y = y + 1;
			changeMap(x, y, FLOOR);
	    }
  }

}

int main(void){
	IMAGE bg_img;

	//��̨��Ϸ
	initgraph(SCREEN_WIDTH,SCREEN_HEIGHT);
	loadimage(&bg_img, _T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_img);

	//���ص���ͼ��
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

	//��Ϸ����
	bool quit = false;


	do{
		if(_kbhit()){//��Ұ���
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









