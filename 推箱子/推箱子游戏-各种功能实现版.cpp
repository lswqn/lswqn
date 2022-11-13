#include <iostream>
#include <stdlib.h>
#include <string>
#include <graphics.h>
#include <conio.h>
#include <mmsystem.h>
//pragma:����ָʾ;comment:ע��;lib:ϵͳ��ʹ�õ��ĺ�����
#pragma comment(lib,"winmm.lib")
#include "box_man.h"

using namespace std;

IMAGE images[ALL];			//����ǽ,����,�ذ�, С��,Ŀ�ĵص�ͼƬ

POS man;			//С���ڶ�ά�����е�λ��

IMAGE bg_img[ALL1];					//���汳��ͼƬ




//��Ϸ��ͼ
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
	WALL,					//0ǽ
	FLOOR,					//1�ذ�
	BOX_DES,				//2����Ŀ�ĵ�
	MAN,					//3С��
	BOX,					//4����
	HIT,					//5��������Ŀ��
	MAN_DES,				//6С��վ��Ŀ�ĵ���
*/

struct MAP map1[MAP_QUANTITY] = { 
{ 8, 8, {
{ 1, 1, 0, 0, 0, 1, 1, 1 },  //��ͼһ
{ 1, 1, 0, 2, 0, 1, 1, 1 },
{ 1, 1, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 4, 1, 4, 2, 0 },
{ 0, 2, 1, 4, 3, 0, 0, 0 },
{ 0, 0, 0, 0, 4, 0, 1, 1 },
{ 1, 1, 1, 0, 2, 0, 1, 1 },
{ 1, 1, 1, 0, 0, 0, 1, 1 } } },
{ 9, 12,{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//��ͼ��
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{ 0, 1, 4, 1, 0, 2, 1, 0, 1, 1, 0, 0},
{ 0, 1, 0, 1, 0, 1, 0, 0, 2, 1, 1, 0},
{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0},
{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0},
{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0},
{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} } },
{ 9, 9, {
{ 0, 0, 0, 0, 0, 1, 1, 1, 1},   //��ͼ��
{ 0, 1, 3, 1, 0, 1, 1, 1, 1},
{ 0, 1, 4, 4, 0, 1, 0, 0, 0},
{ 0, 1, 4, 1, 0, 1, 0, 2, 0},
{ 0, 0, 0, 1, 0, 0, 0, 2, 0},
{ 1, 0, 0, 1, 1, 1, 1, 2, 0},
{ 1, 0, 1, 1, 1, 0, 1, 1, 0},
{ 1, 0, 1, 1, 1, 0, 0, 0, 0},
{ 1, 0, 0, 0, 0, 0, 1, 1, 1} } },
{ 7, 10, {
{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },  //��ͼ��
{ 1, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 4, 0, 0, 0, 1, 1, 1, 0 },
{ 0, 1, 1, 1, 4, 1, 1, 4, 1, 0 },
{ 0, 1, 6, 2, 0, 1, 4, 1, 0, 0 },
{ 0, 0, 2, 2, 0, 1, 1, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 } } },
{ 8, 6, {
{ 1, 0, 0, 0, 0, 1 },    //��ͼ��
{ 0, 0, 1, 1, 0, 1 },
{ 0, 3, 4, 1, 0, 1 },
{ 0, 0, 4, 1, 0, 0 },
{ 0, 0, 1, 4, 1, 0 },
{ 0, 2, 4, 1, 1, 0 },
{ 0, 2, 2, 5, 2, 0 },
{ 0, 0, 0, 0, 0, 0 } } },
{ 8, 8, {
{ 1, 0, 0, 0, 0, 0, 1, 1 },  //��ͼ��
{ 1, 0, 1, 3, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 4, 1, 1, 0 },
{ 0, 1, 5, 2, 1, 2, 1, 0 },
{ 0, 1, 1, 4, 4, 1, 0, 0 },
{ 0, 0, 0, 1, 0, 2, 0, 1 },
{ 1, 1, 0, 1, 1, 1, 0, 1 },
{ 1, 1, 0, 0, 0, 0, 0, 1 } } }, 
{ 10, 11, {
{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},	//��ͼ��
{ 1, 0, 0, 0, 0, 0, 2, 1, 1, 1, 0},
{ 1, 0, 1, 1, 0, 2, 2, 0, 0, 1, 0},
{ 1, 0, 1, 1, 4, 2, 2, 1, 1, 1, 0},
{ 1, 0, 1, 1, 0, 1, 2, 0, 1, 0, 0},
{ 0, 0, 0, 1, 0, 0, 4, 0, 1, 1, 0},
{ 0, 1, 4, 4, 1, 1, 1, 4, 4, 1, 0},
{ 0, 1, 0, 3, 0, 1, 1, 0, 1, 1, 0},
{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1} }}, };   //���������ӵ�ͼ���������������Լ���ͼԪ��

/*****************************************
*�ж���Ϸ�Ƿ����,����������κ�һ������Ŀ�ĵ�,�ʹ�����Ϸ����
*����:
*		map[LINE][COLUMN]	-	��ͼ�ṹ���е�����
*		const int line		-	��ͼ���еĳ���
*		const int column	-	��ͼ���еĳ���
*����ֵ:
*		true	- ��Ϸ����
*		false	- ��Ϸ����
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
*����:ʵ����Ϸ�ؿ���ʾ
*����:
*		bg			- ����ͼƬ������ָ��
*		customsPass	-	��ǰ�ؿ���
*���:
*
******************************************/
void levelsPrompt(IMAGE *bg,int customsPass) {
	char str[16];

	putimage(0, 0, bg);									//��ӡ���뱳��ͼƬ
	settextcolor(WHITE);								//����������ɫΪ����
	setbkmode(TRANSPARENT);								//�������ֱ���ɫΪ͸��ɫ
	RECT rec = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };		//���ƾ���
	settextstyle(100, 0, _T("����"));					//��������

	sprintf_s(str, "�� %d ��", customsPass);				//��int����ת����char�ַ�����
	//textwidth �����ַ����ĸ߶� textheight �����ַ����Ŀ��
	outtextxy(((SCREEN_WIDTH - textwidth(str))/ 2), ((SCREEN_HEIGHT - textheight(str))/ 2), str);
	Sleep(2000);
}

/*****************************************
*��Ϸ��������,�����ͨ�غ���ʾ
*����:
*		bg		- ����ͼƬ������ָ��
*		victory - ʤ��ͼƬָ��
*����ֵ:��
******************************************/
void gemrOverScene(IMAGE *bg, IMAGE *victory,const int customsPass) {
	putimage(0, 0, bg);											//��ӡ���뱳��ͼƬ
	putimage((SCREEN_WIDTH - SCREEN_WIDTH1) / 2, 50, victory);	//��ӡ�����ʤ��ͼƬ
	settextcolor(BLUE);										//����������ɫΪ��ɫ
	RECT rec = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };				//���ƾ���
	settextstyle(20, 0, _T("����"));							//��������
	//DT_CENTER:����ˮƽ����,DT_VCENTER:���ִ�ֱ����,DT_SINGLELINE:��ʾһ��,�س�������Ч
	if (customsPass == MAP_QUANTITY) {
		drawtext(_T("��ϲ��~\n��ͨ����ȫ���ؿ�!���Ѿ���Ϊ����������˾��!�� 'Q' ��������Ϸ!���¿�ʼ�밴 'T'"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	} 
	else {
		drawtext(_T("��ϲ��~\n��ͨ����!�������������һ��!"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		system("pause");
	}
	
	
}
/*****************************************
*��Ϸʧ�ܳ���,�����ʧ�ܺ���ʾ
*����:
*		bg	 - ����ͼƬ������ָ��
*		over - ʧ��ͼƬָ��
*����ֵ:��
******************************************/
void gameOverMan(IMAGE *bg, IMAGE *over) {
	putimage(0, 0, bg);									//��ӡ���뱳��ͼƬ
	putimage((SCREEN_WIDTH - SCREEN_WIDTH1) / 2, 50, over);	//��ӡ�����ʧ��ͼƬ
	settextcolor(BLUE);								//����������ɫΪ��ɫ
	RECT rec = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };		//���ƾ���
	settextstyle(20, 0, _T("����"));					//��������
	//DT_CENTER:����ˮƽ����,DT_VCENTER:���ִ�ֱ����,DT_SINGLELINE:��ʾһ��,�س�������Ч
	drawtext(_T("GAME OVER!������Ϸ��������300��,��Ϸ����!�� 'Q' ��������Ϸ!���¿�ʼ�밴 'T'"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}


/*****************************************
*�ı���Ϸ��ͼ��ͼ��һ���Ӧ���߲�������ʾ
*����:
*		pos					-	������ߵ�λ��
*		prop				-	�����������
*		map[LINE][COLUMN]	-	��ͼ�ṹ���е�����
*		const int line		-	��ͼ���еĳ���
*		const int column	-	��ͼ���еĳ���
*����ֵ:��
******************************************/
//�ڶ���
void changoMap(POS *pos, PROPS prop, int map[LINE][COLUMN], const int line, const int column) {
	map[pos->x][pos->y] = prop;
	putimage(((SCREEN_WIDTH - (column * RATIO)) / 2) + pos->y * RATIO, 
		(((SCREEN_HEIGHT - (line * RATIO)) / 2) + (STAR_Y / 2)) + pos->x * RATIO, &images[prop]);
}
/*****************************************
*�ı���Ϸ��ͼ��ͼ��һ���Ӧ���߲�������ʾ
*����:
*		line   - �����ڵ�ͼ��������±�
*		column - �����ڵ�ͼ��������±�
*		prop	- ��������
*����ֵ:��
******************************************/
/*��һ��
void changoMap(int line, int column, enum _PROPS prop) {
	map[line][column] = prop;
	putimage(STAR_X + column * RATIO, STAR_Y + line * RATIO, &images[prop]);
}
*/

/*****************************************
*ʵ����Ϸ�ĸ�����(�ϡ��¡�����)�Ŀ���
*����:
*		direct				-	��ǰ���ķ���
*		count				-	����ͳ�Ƴ�ʼֵ 0
*		retreat				-	С����һ�εĲ���
*		map[LINE][COLUMN]	-	��ͼ�ṹ���е�����
*		const int line		-	��ͼ���еĳ���
*		const int column	-	��ͼ���еĳ���
*����ֵ:
*		������ƶ��ͷ��ز�����ʼֵ+1,����С��ײǽû���ƶ����ص�ǰ���� ������1
******************************************/
void gameControl(DIRECTION direct, int &count, bool &ifMove, int map[LINE][COLUMN], const int line, const int column) {
	//int x = man.x;			//С�����ڵĶ�ά�����x����
	//int y = man.y;			//С�����ڵĶ�ά�����y����

	POS next_pos = man;			//ΪС��ǰ��һ��
	POS next_next_pos = man;	//С��ǰ������



	switch (direct) {
	case UP:
		next_pos.x--;			//С������һ��
		next_next_pos.x -= 2;	//���Ӻ�С��ͬʱ����һ��
		break;
	case DOWN:
		next_pos.x++;			//С������һ��
		next_next_pos.x += 2;	//���Ӻ�С��ͬʱ����һ��
		break;
	case LEFT:
		next_pos.y--;			//С������һ��
		next_next_pos.y -= 2;	//���Ӻ�С��ͬʱ����һ��
		break;
	case RIGHT:
		next_pos.y++;			//С������һ��
		next_next_pos.y += 2;	//���Ӻ�С��ͬʱ����һ��
		break;
		//default:
			//break;
	}
	

	//������
	//��չ�� next_pos.x >= 0 && next_pos.x < LINE && next_pos.y >= 0 && next_pos.y < COLUMN
	if (isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR) {		//С�˵�ǰ���ǵذ�
		if (map[man.x][man.y] == MAN_DES) {				//�����С��վ������Ŀ�ĵ���
			changoMap(&next_pos, MAN, map, line, column);					//С���ƶ�һ��
			changoMap(&man, BOX_DES, map, line, column);					//�ָ�����Ŀ�ĵ�
			man = next_pos;								//��С���µ�λ�ø��µ���ǰλ��
			count++;									//С���ƶ�һ��,����ͳ�Ƽ�һ
			ifMove = false;								//����δ�ƶ� ifMove ��ֵ��Ϊ��
		}
		else if (map[man.x][man.y] == MAN) {			//���С���ڵذ���
			changoMap(&next_pos, MAN, map, line, column);					//С���ƶ�һ��			
			changoMap(&man, FLOOR, map, line, column);						//ԭ��С�˵�λ�û��ɵذ�
			man = next_pos;								//��С���µ�λ�ø��µ���ǰλ��
			count++;									//С���ƶ�һ��,����ͳ�Ƽ�һ
			ifMove = false;								//����δ�ƶ� ifMove ��ֵ��Ϊ��
		}
	}
	else if (isValid(next_pos) && isValid(next_next_pos) && map[next_pos.x][next_pos.y] == BOX) {	//С�˵�ǰ��������
	 //�������,����ǰ���ǵذ����������Ŀ�ĵ�
		if (map[next_next_pos.x][next_next_pos.y] == FLOOR) {				//����ǰ���ǵذ�
			//�������,С����Ŀ�ĵ��ϻ����ڵذ���
			if (map[man.x][man.y] == MAN_DES) {				//�����С��վ������Ŀ�ĵ��ϵ����
				changoMap(&next_next_pos, BOX, map, line, column);				//������ǰ�ƶ�һ��
				changoMap(&next_pos, MAN, map, line, column);					//С���ƶ�һ��
				changoMap(&man, BOX_DES, map, line, column);					//�ָ�����Ŀ�ĵ�
				man = next_pos;								//��С���µ�λ�ø��µ���ǰλ
				count++;									//С���ƶ�һ��,����ͳ�Ƽ�һ
				ifMove = true;								//�����ƶ� ifMove ��ֵ��Ϊ��
			}
			else if (map[man.x][man.y] == MAN) {			//С���ڵذ��ϵ����
				changoMap(&next_next_pos, BOX, map, line, column);				//������ǰ�ƶ�һ��
				changoMap(&next_pos, MAN, map, line, column);					//С���ƶ�һ��			
				changoMap(&man, FLOOR, map, line, column);						//ԭ��С�˵�λ�û��ɵذ�
				man = next_pos;								//��С���µ�λ�ø��µ���ǰλ��
				count++;									//С���ƶ�һ��,����ͳ�Ƽ�һ
				ifMove = true;								//�����ƶ� ifMove ��ֵ��Ϊ��
			}
		}
		else if (map[next_next_pos.x][next_next_pos.y] == BOX_DES) {		//����ǰ��������Ŀ�ĵ�
			if (map[man.x][man.y] == MAN_DES) {				//С����Ŀ�ĵ��ϵ����
				changoMap(&next_next_pos, HIT, map, line, column);				//����Ŀ�ĵػ�����������Ŀ�ĵ�
				changoMap(&next_pos, MAN, map, line, column);					//С�˴�����Ŀ�ĵػ����ذ���			
				changoMap(&man, BOX_DES, map, line, column);					//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = next_pos;								//��С���µ�λ�ø��µ���ǰλ��
				count++;									//С���ƶ�һ��,����ͳ�Ƽ�һ
				ifMove = true;								//�����ƶ� ifMove ��ֵ��Ϊ��
			}
			else if (map[man.x][man.y] == MAN) {			//С���ڵذ��ϵ����
				changoMap(&next_next_pos, HIT, map, line, column);				//����Ŀ�ĵػ�����������Ŀ�ĵ�
				changoMap(&next_pos, MAN, map, line, column);					//С����ǰ�ƶ�һ��			
				changoMap(&man, FLOOR, map, line, column);						//ԭ��С�˵�λ�û��ɵذ�
				man = next_pos;								//��С���µ�λ�ø��µ���ǰλ��
				count++;									//С���ƶ�һ��,����ͳ�Ƽ�һ
				ifMove = true;								//�����ƶ� ifMove ��ֵ��Ϊ��
			}
		}
	}
	else if (isValid(next_pos) && isValid(next_next_pos) && map[next_pos.x][next_pos.y] == HIT) {	//��������Ŀ��
		if (map[next_next_pos.x][next_next_pos.y] == FLOOR) {				//����Ŀ�ĵ�ǰ���ǵذ�
			if (map[man.x][man.y] == MAN) {						//С���ڵذ�����
				changoMap(&next_next_pos, BOX, map, line, column);					//��������Ŀ�ĵػ�������
				changoMap(&next_pos, MAN_DES, map, line, column);					//С��վ������Ŀ�ĵ���			
				changoMap(&man, FLOOR, map, line, column);							//ԭ��С�˵�λ�û��ɵذ�
				man = next_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count++;										//С���ƶ�һ��,����ͳ�Ƽ�һ
				ifMove = true;								//�����ƶ� ifMove ��ֵ��Ϊ��
			}
			else if (map[man.x][man.y] == MAN_DES) {			//С��������Ŀ�ĵ��ϵ����
				changoMap(&next_next_pos, BOX, map, line, column);					//��������Ŀ�ĵػ�������
				changoMap(&next_pos, MAN_DES, map, line, column);					//С��վ������Ŀ�ĵ���			
				changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = next_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count++;										//С���ƶ�һ��,����ͳ�Ƽ�һ
				ifMove = true;								//�����ƶ� ifMove ��ֵ��Ϊ��
			}

		}
		else if (map[next_next_pos.x][next_next_pos.y] == BOX_DES) {		//��������Ŀ��ǰ��������Ŀ�ĵ�
			if (map[man.x][man.y] == MAN) {						//С���ڵذ�����
				changoMap(&next_next_pos, HIT, map, line, column);					//�����Ƴ�����һ������Ŀ�ĵ�
				changoMap(&next_pos, MAN_DES, map, line, column);					//С��վ������Ŀ�ĵ���			
				changoMap(&man, FLOOR, map, line, column);							//ԭ��С�˵�λ�û��ɵذ�
				man = next_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count++;										//С���ƶ�һ��,����ͳ�Ƽ�һ
				ifMove = true;									//�����ƶ� ifMove ��ֵ��Ϊ��
			}
			else if (map[man.x][man.y] == MAN_DES) {			//С��������Ŀ�ĵ��ϵ����
				changoMap(&next_next_pos, HIT, map, line, column);					//��������Ŀ�ĵػ�����һ����������Ŀ��
				changoMap(&next_pos, MAN_DES, map, line, column);					//С��վ������Ŀ�ĵ��ϵ���һ��Ŀ�ĵ���		
				changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = next_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count++;										//С���ƶ�һ��,����ͳ�Ƽ�һ
				ifMove = true;									//�����ƶ� ifMove ��ֵ��Ϊ��
			}
		}
	}
	else if (isValid(next_pos) && map[next_pos.x][next_pos.y] == BOX_DES) {	//С��ǰ��������Ŀ�ĵ�
		if (map[man.x][man.y] == MAN_DES) {						//С��������Ŀ�ĵ��ϵ����
			changoMap(&next_pos, MAN_DES, map, line, column);						//С��վ����һ������Ŀ�ĵ���			
			changoMap(&man, BOX_DES, map, line, column);							//ԭ��С�˵�λ�û��ɵذ�
			man = next_pos;										//��С���µ�λ�ø��µ���ǰλ��
			count++;											//С���ƶ�һ��,����ͳ�Ƽ�һ
			ifMove = false;								//����δ�ƶ� ifMove ��ֵ��Ϊ��
		}
		else if (map[man.x][man.y] == MAN) {					//С���ڵذ���
			changoMap(&next_pos, MAN_DES, map, line, column);						//С��վ������Ŀ�ĵ���			
			changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
			man = next_pos;										//��С���µ�λ�ø��µ���ǰλ��
			count++;											//С���ƶ�һ��,����ͳ�Ƽ�һ
			ifMove = false;								//����δ�ƶ� ifMove ��ֵ��Ϊ��
		}
	}	
}

/*****************************************
*����: ������Դ
*����:
*		bg_img - ����ͼƬ����
*���:��
******************************************/
void loadResources(IMAGE *bg_img) {
	//���̨
	//initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);	//������̨��С
	loadimage(&bg_img[BG], _T("35.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);	//���ر���ͼƬ�����ñ���ͼƬ��С
	loadimage(&bg_img[VICTORY], _T("victory.png"), SCREEN_WIDTH1, SCREEN_HEIGHT1, true);		//ʤ������
	loadimage(&bg_img[OVER], _T("over.png"), SCREEN_WIDTH1, SCREEN_HEIGHT1, true);		//ʧ�ܱ���
	loadimage(&bg_img[SOKOBAN], _T("Sokoban.jpg"), SCREEN_WIDTH, SCREEN_HEIGHT, true);		//ʧ�ܱ���


	//putimage(0, 0, &bg_img[BG]);		//�ڿ���̨(0,0)�����ӡͼƬ


	//���ص���ͼ��
	loadimage(&images[WALL], _T("wall_right.bmp"), RATIO, RATIO, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX_DES], _T("des.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN], _T("man.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[HIT], _T("box_hit.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN_DES], _T("man_des.bmp"), RATIO, RATIO, true);
}
/*****************************************
*����: �ҵ�С�˲���ӡ�����Ͳ���˵�� ����
*����:
*		bg_img - ����ͼƬ����
*		map[LINE][COLUMN]	-	��ͼ�ṹ���е�����
*		const int line		-	��ͼ���еĳ���
*		const int column	-	��ͼ���еĳ���
*		customsPass			-	�ڼ���
*���:��
******************************************/
void initGameScene(int map[LINE][COLUMN], const int line, const int column, int customsPass) {

	char str[16];

	//ѭ����ӡ����ͼ�굽��ָ̨��λ��
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			if (map[i][j] == MAN || map[i][j] == MAN_DES) {				//�ж��ǲ���С��,�����С��,��С�˵�(x,y)���괫��man��
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
	settextstyle(18, 0, _T("����"));
	setbkmode(TRANSPARENT);
	outtextxy(780, 10, "2022-13-14  9:05:20");

	//����˵��	
	settextstyle(20, 0, _T("����"));						//���������С
	setcolor(LIGHTBLUE);									//����������ɫ(��ɫ)
	setbkmode(TRANSPARENT);									//�������ֱ���ɫΪ͸��ɫ
	outtextxy(300, 25, _T(" ����˵����"));					//��ָ��λ������ı�
	outtextxy(300, 50, _T(" w / W ���� �� ������"));		//��ָ��λ������ı�
	outtextxy(300, 75, _T(" s / S ���� �� ������"));		//��ָ��λ������ı�
	outtextxy(300, 100, _T(" a / A ���� �� ������"));		//��ָ��λ������ı�
	outtextxy(300, 125, _T(" d / D ���� �� ������"));		//��ָ��λ������ı�
	outtextxy(550, 50, _T(" t / T �����¿�ʼ�ؿ�"));		//��ָ��λ������ı�
	outtextxy(550, 75, _T(" r / R ������"));				//��ָ��λ������ı�
	outtextxy(550, 100, _T(" p / P ������ѡ��ؿ�"));		//��ָ��λ������ı�
	outtextxy(550, 125, _T(" q / Q ���˳�"));				//��ָ��λ������ı�
	

	//����	
	setcolor(BLUE);								//����������ɫ(��ɫ)
	setbkmode(TRANSPARENT);						//�������ֱ���ɫΪ͸��ɫ
	outtextxy(25, 25, _T("������"));			//��ָ��λ������ı�
	outtextxy(75, 25, _T("0"));					//��ָ��λ�������ʼ����	

	sprintf_s(str, "�� %d ��", customsPass);				//��int����ת����char�ַ�����
	outtextxy((SCREEN_WIDTH - 100), 25, str);
}
/*****************************************
*����:ʵ����Ϸ����һ��
*����:
*		retreat				-	�����һ�β�����Ӧ��
*		count				-	��ҵ�ǰ��Ϸ����
*		map[LINE][COLUMN]	-	��ͼ�ṹ���е�����
*		const int line		-	��ͼ���еĳ���
*		const int column	-	��ͼ���еĳ���
*���:
		������Ϸ����,����һ����,��Ϸ������һ
******************************************/
void takeBack(char &retreat, int &count, bool &ifMove,int map[LINE][COLUMN], const int line, const int column) {
	//���count = 0֤��û���ƶ���,ֱ�ӷ��ص�ǰֵ
	if (count <= 0 || retreat == 0) return;
	POS last_pos = man;			//С�˺���
	POS last_pos1 = man;		//С��ǰ��
	POS last_last_pos = man;	//С�˺�����

	switch (retreat) {
	case KEY_UP:
	case 72:
		last_pos1.x--;		//С��ǰ��
		last_pos.x++;		//С�˺���
		last_last_pos.x += 2;	//С�˺���ڶ���
		break;
	case KEY_LEFT:
	case 80:
		last_pos1.x++;		//С��ǰ��
		last_pos.x--;		//С�˺���
		last_last_pos.x -= 2;	//С�˺���ڶ���
		break;
	case KEY_RIGHT:
	case 75:
		last_pos1.y--;		//С��ǰ��
		last_pos.y++;		//С�˺���
		last_last_pos.y += 2;	//С�˺���ڶ���
		break;
	case KEY_DOWN:
	case 77:
		last_pos1.y++;		//С��ǰ��
		last_pos.y--;		//С�˺���
		last_last_pos.y -= 2;	//С�˺���ڶ���
		break;
	}

	//�������,һ��С����Ŀ�ĵ�����,һ���ڵذ���
	if (map[man.x][man.y] == MAN_DES) {
		if (map[last_pos1.x][last_pos1.y] == BOX) {					//С��ǰ��������
			if (ifMove == true) {									//ifMove Ϊ���ʾ�����ƶ���,����������Ҫһ���ƶ�
				if (map[last_pos.x][last_pos.y] == BOX_DES) {		//С�˺���������Ŀ�ĵص����
					changoMap(&last_pos1, FLOOR, map, line, column);					//��С��ǰ������ӻ��ɵذ�
					changoMap(&last_pos, MAN_DES, map, line, column);					//С�˺���һ��			
					changoMap(&man, HIT, map, line, column);							//ԭ��С�˵�λ�û�����������Ŀ��
					man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {	//С�˺����ǵذ�����
					changoMap(&last_pos1, FLOOR, map, line, column);					//��С��ǰ������ӻ��ɵذ�
					changoMap(&last_pos, MAN, map, line, column);						//С�˺���һ��			
					changoMap(&man, HIT, map, line, column);							//ԭ��С�˵�λ�û�����������Ŀ��
					man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
			}
			else {												//����ifMove Ϊ�ٱ�ʾ����δ�ƶ���,�������Ӳ���Ҫһ���ƶ�
				if (map[last_pos.x][last_pos.y] == BOX_DES) {		//С�˺���������Ŀ�ĵص����
					changoMap(&last_pos, MAN_DES, map, line, column);					//С�˺���һ��			
					changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
					man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {	//С�˺����ǵذ�����
					changoMap(&last_pos, MAN, map, line, column);						//С�˺���һ��			
					changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
					man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
			}

		}
		else if (map[last_pos1.x][last_pos1.y] == HIT) {		//С��ǰ������������Ŀ��
			if (ifMove == true) {									//ifMove Ϊ���ʾ�����ƶ���,����������Ҫһ���ƶ�
				if (map[last_pos.x][last_pos.y] == BOX_DES) {		//С�˵�ǰλ����Ŀ�ĵ���
					changoMap(&last_pos1, BOX_DES, map, line, column);					//��С��ǰ������ӻ�������Ŀ�ĵ�
					changoMap(&last_pos, MAN_DES, map, line, column);						//С�˺��˵��ذ���			
					changoMap(&man, HIT, map, line, column);							//ԭ��С�˵�λ�û�����������Ŀ��
					man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {	//С���ں����ǵذ�����
					changoMap(&last_pos1, BOX_DES, map, line, column);					//��С��ǰ������ӻ�������Ŀ�ĵ�
					changoMap(&last_pos, MAN, map, line, column);						//С�˺��˵���һ���ذ���			
					changoMap(&man, HIT, map, line, column);							//ԭ��С�˵�λ�û�����������Ŀ�ĵ�
					man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
			}
			else {												//����ifMove Ϊ�ٱ�ʾ����δ�ƶ���,�������Ӳ���Ҫһ���ƶ�
				if (map[last_pos.x][last_pos.y] == BOX_DES) {		//С�˵�ǰλ����Ŀ�ĵ���
					changoMap(&last_pos, MAN_DES, map, line, column);					//С�˺��˵��ذ���			
					changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
					man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {	//С���ں����ǵذ�����
					changoMap(&last_pos, MAN, map, line, column);						//С�˺��˵���һ���ذ���			
					changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
					man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == FLOOR) {	//С��ǰ���ǵذ�����
			if (map[last_pos.x][last_pos.y] == BOX_DES) {
				changoMap(&last_pos, MAN_DES, map, line, column);					//С�˺���һ��			
				changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count--;										//������һ
			}
			else if (map[last_pos.x][last_pos.y] == FLOOR) {	//С���ں����ǵذ�����
				changoMap(&last_pos, MAN, map, line, column);						//С�˺��˵���һ���ذ���			
				changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�����������Ŀ�ĵ�
				man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count--;										//������һ
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == BOX_DES) {	//С��ǰ��������Ŀ�ĵص����
			if (map[last_pos.x][last_pos.y] == BOX_DES) {		//С�˺���������Ŀ�ĵص����
				changoMap(&last_pos1, BOX_DES, map, line, column);					//��С��ǰ������ӻ�������Ŀ�ĵ�
				changoMap(&last_pos, MAN_DES, map, line, column);					//С�˺��������Ŀ�ĵػ���С��������Ŀ�ĵ�			
				changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count--;										//������һ
			}
			else if (map[last_pos.x][last_pos.y] == FLOOR) {	//С�˺����ǵذ�����
				changoMap(&last_pos1, BOX_DES, map, line, column);					//��С��ǰ������ӻ�������Ŀ�ĵ�
				changoMap(&last_pos, MAN, map, line, column);						//С�˺��滻��С���ڵذ���		
				changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count--;										//������һ
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == WALL) {		//С��ǰ����ǽ�����
			if (map[last_pos.x][last_pos.y] == FLOOR) {			//С�˺����ǵذ�����
				changoMap(&last_pos, MAN, map, line, column);						//С�˺��滻��С���ڵذ���
				changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count--;										//������һ
			}
			else if (map[last_pos.x][last_pos.y] == BOX_DES) {//С�˺���������Ŀ�ĵص����
				changoMap(&last_pos, MAN_DES, map, line, column);					//С�˺��滻��С��������Ŀ�ĵ���
				changoMap(&man, BOX_DES, map, line, column);						//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = last_pos;									//��С���µ�λ�ø��µ���ǰλ��
				count--;										//������һ
			}
		}
	}
	else if (map[man.x][man.y] == MAN) {							//С���ڵذ��ϵ����
	 //С��ǰ�������ӡ���������Ŀ�ꡢ�ذ塢����Ŀ�ĵ�
		if (map[last_pos1.x][last_pos1.y] == BOX) {						//С��ǰ�������ӵ����
			if (ifMove == true) {										//ifMove Ϊ���ʾ�����ƶ���,����������Ҫһ���ƶ�
				if (map[last_pos.x][last_pos.y] == BOX_DES) {			//С�˺���������Ŀ�ĵص����
					changoMap(&last_pos1, FLOOR, map, line, column);						//����ԭ����λ�û��ɵذ�
					changoMap(&last_pos, MAN_DES, map, line, column);						//С�˺��滻��С��������Ŀ�ĵ���	
					changoMap(&man, BOX, map, line, column);								//ԭ��С�˵�λ�û�������
					man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
					count--;											//������һ
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {		//С��ǰ���ǵذ�����
					changoMap(&last_pos1, FLOOR, map, line, column);						//����ԭ����λ�û��ɵذ�
					changoMap(&last_pos, MAN, map, line, column);							//С�˺���һ��			
					changoMap(&man, BOX, map, line, column);								//ԭ��С�˵�λ�û�������
					man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
					count--;											//������һ
				}
			}
			else {													//����ifMove Ϊ�ٱ�ʾ����δ�ƶ���,�������Ӳ���Ҫһ���ƶ�
				if (map[last_pos.x][last_pos.y] == BOX_DES) {			//С�˺���������Ŀ�ĵص����
					changoMap(&last_pos, MAN_DES, map, line, column);						//С�˺��滻��С��������Ŀ�ĵ���	
					changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
					man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
				else if (map[last_pos.x][last_pos.y] == FLOOR) {		//С��ǰ���ǵذ�����
					changoMap(&last_pos, MAN, map, line, column);							//С�˺���һ��			
					changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
					man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
			}

		}
		else if (map[last_pos1.x][last_pos1.y] == HIT) {			//С��ǰ����������������Ŀ�ĵص����
			if (ifMove == true) {										//ifMove Ϊ���ʾ�����ƶ���,����������Ҫһ���ƶ�
				if (map[last_pos.x][last_pos.y] == FLOOR) {				//С�˺���������Ŀ�ĵص����
					changoMap(&last_pos1, BOX_DES, map, line, column);						//��������Ŀ�껻������Ŀ�ĵ�
					changoMap(&last_pos, MAN, map, line, column);							//С�˺���һ��			
					changoMap(&man, BOX, map, line, column);								//ԭ��С�˵�λ�û�������
					man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
				else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//С�˺���������Ŀ�ĵص����
					changoMap(&last_pos1, BOX_DES, map, line, column);						//��������Ŀ�껻������Ŀ�ĵ�
					changoMap(&last_pos, MAN_DES, map, line, column);						//С���滻��С��������Ŀ�ĵ���
					changoMap(&man, BOX, map, line, column);								//ԭ��С�˵�λ�û�������
					man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
					count--;										//������һ
				}
			}
			else {													//����ifMove Ϊ�ٱ�ʾ����δ�ƶ���,�������Ӳ���Ҫһ���ƶ�
				if (map[last_pos.x][last_pos.y] == FLOOR) {				//С�˺���������Ŀ�ĵص����
					changoMap(&last_pos, MAN, map, line, column);							//С�˺���һ��			
					changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
					man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
					count--;											//������һ
				}
				else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//С�˺���������Ŀ�ĵص����
					changoMap(&last_pos, MAN_DES, map, line, column);						//С���滻��С��������Ŀ�ĵ���
					changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
					man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
					count--;											//������һ
				}
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == FLOOR) {		//С��ǰ���ǵذ�����
			if (map[last_pos.x][last_pos.y] == FLOOR) {				//С�˺����ǵذ�����
				changoMap(&last_pos, MAN, map, line, column);							//С�˺���һ��			
				changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
				man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
				count--;											//������һ
			}
			else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//С�˺���������Ŀ�ĵص����
				changoMap(&last_pos, MAN_DES, map, line, column);						//С�˺���һ��			
				changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
				man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
				count--;											//������һ
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == BOX_DES) {		//С��ǰ��������Ŀ�ĵ�
			if (map[last_pos.x][last_pos.y] == FLOOR) {				//С�˺����ǵذ�����
				changoMap(&last_pos, MAN, map, line, column);							//С�˺���һ��վ��Ŀ�ĵ���			
				changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
				man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
				count--;											//������һ
			}
			else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//С�˺���������Ŀ�ĵ��ϵ����
				changoMap(&last_pos, MAN_DES, map, line, column);						//С�˺���һ��վ��Ŀ�ĵ���			
				changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
				count--;											//������һ
			}
		}
		else if (map[last_pos1.x][last_pos1.y] == WALL) {			//С��ǰ����ǽ�����
			if (map[last_pos.x][last_pos.y] == FLOOR) {				//С�˺����ǵذ�����
				changoMap(&last_pos, MAN, map, line, column);							//С�˺���һ��վ��Ŀ�ĵ���			
				changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û��ɵذ�
				man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
				count--;										//������һ
			}
			else if (map[last_pos.x][last_pos.y] == BOX_DES) {	//С�˺���������Ŀ�ĵ��ϵ����
				changoMap(&last_pos, MAN_DES, map, line, column);						//С�˺���һ��վ��Ŀ�ĵ���			
				changoMap(&man, FLOOR, map, line, column);								//ԭ��С�˵�λ�û�������Ŀ�ĵ�
				man = last_pos;										//��С���µ�λ�ø��µ���ǰλ��
				count--;										//������һ
			}

		}
	}
	//return count;
	ifMove = false;												//С����������֮��û�л��˾ͽ� ifMove ��Ϊ��
}
/*****************************************
*����:��ʼ��Ϸ
*����:
*		bg - ����ͼƬָ��
*���:
*		��
******************************************/
void startInterface(IMAGE* bg) {
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);				//������̨��С
	putimage(0, 0, &bg[SOKOBAN]);									//��ӡ���뱳��ͼƬ

	MOUSEMSG mouse;//���������Ϣ�ı���
	while (1) {
		//ѭ����ȡ���״̬
		mouse = GetMouseMsg();

		switch (mouse.uMsg) {
		case WM_LBUTTONDOWN:
			if (mouse.x > 755 && mouse.x < 920 && mouse.y > 644 && mouse.y < 720) {
				//�����Ļ����
				cleardevice();
				return;
			}
		}
		//Sleep(10);
	}
}
/*****************************************
*����:�ؿ�ѡ��
*����:
*		bg - ����ͼƬָ��
*���:
*		��
******************************************/
int checkpointChoice(IMAGE* bg, int customsPass) {
	MOUSEMSG mouse;//���������Ϣ�ı���
	putimage(0, 0, &bg[BG]);									//��ӡ���뱳��ͼƬ
	customsPass = 0;
	const char* str[MAP_QUANTITY] = {
		"��һ��",
		"�ڶ���",
		"������",
		"���Ĺ�",
		"�����",
		"������",
		"���߹�"
	};
	setcolor(WHITE);										//����������ɫ(��ɫ)
	settextstyle(18, 0, _T("����"));							//��������
	setbkmode(TRANSPARENT);								//�������ֱ���ɫΪ͸��ɫ
	for (int i = 0; i < MAP_QUANTITY; i++) {
		rectangle(100 + (i * 110), 100, 200 + (i * 110), 150);	//���ƾ���
		outtextxy(125 + (i * 110), 120, str[i]);			//�ھ����д�ӡ����
	}
	
	setcolor(BLUE);
	setbkmode(TRANSPARENT);
	outtextxy(780, 10, "2022-13-14  9:05:20");

	setcolor(WHITE);										//����������ɫ(��ɫ)
	setbkmode(TRANSPARENT);								//�������ֱ���ɫΪ͸��ɫ
	outtextxy(100, 50, _T(" ��ѡ����Ҫ�ӵڼ��ؿ�ʼ�棺"));				//��ָ��λ������ı�

	outtextxy(100, 170, "����·�Ϲ��ͺܶ�,ÿ���˶��и��Ե��յ�,����������������,��������.");
	outtextxy(100, 190, "���аٻ������£��������綬��ѩ������ֻ���������㡣");
	outtextxy(100, 210, "��ϲ���㣬�Ӻ�ҹ�����������䶬��ů������һ�뵽һ����������Ϣ���ֻز�ֹ��");

	setcolor(LIGHTBLUE);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "΢���ź�");

	outtextxy(350, 240, "���潭��ܽ�ء�");
	outtextxy(300, 300, "�潭��ܽ�أ�����෼�ݡ�");
	outtextxy(300, 360, "��֮����˭����˼��Զ����");
	outtextxy(300, 420, "���������磬��·���ƺơ�");
	outtextxy(300, 480, "ͬ�Ķ���ӣ����������ϡ�");

	setcolor(YELLOW);
	settextstyle(30, 0, "����");
	outtextxy(340,530,"��ִ���������Լ�����������");
	while (1) {
		//ѭ����ȡ���״̬
		mouse = GetMouseMsg();

		switch (mouse.uMsg) {
		case WM_LBUTTONDOWN:
			if (mouse.x > 100 && mouse.x < 200 && mouse.y > 100 && mouse.y < 150) {
				//�����Ļ����
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
*����:��ʼ��Ϸ
*����:
*		��
*���:
*		��
******************************************/
void startGame(int customsPass) {
	//��Ϸ����
	bool quit = false;				//�����ж��Ƿ��˳�
	int count = 0;					//�����Ϸ����ͳ�ƽ���
	char str[16];					//����ͳ�Ʋ���
	char ch = '\0';					//������ҵ�ǰ����
	char retreat = '\0';			//������ҵ�ǰ�������ڻ���
	bool ifMove = false;			//�����ж�С��ǰ���������û���ƶ�
	//int customsPass = 0;			//�ؿ�����		
	struct MAP *pmap = NULL;		//�����ͼ�ṹ��ָ��
	struct MAP map2[MAP_QUANTITY] = { 0,0,{0} };	//������ǰ��ͼ
	pmap = &map1[customsPass];		//ָ���һ����ͼ
	while (quit == false) {
		//�������е�ͼ
		for (int i = 0; i < MAP_QUANTITY; i++) {
			map2[i] = map1[i];
		}
		//map2[customsPass] = map1[customsPass];		//������ǰ��ͼ,�������¿�ʼ��ǰ�ؿ�
		//memcpy(map2.map, map1, sizeof(map1->map));

		//��ӡ��һ��ҳ��
		levelsPrompt(&bg_img[BG], customsPass + 1);


		//�ҵ�С�˲���ӡ�����Ͳ���˵�� ����

		initGameScene(pmap->map, pmap->line, pmap->column, customsPass + 1);

		//���ò����Ķ�̬���ֵ�ʵ�ľ������ɫ
		int bgColor = getpixel(0, 0);	//��ȡ����ɫ
		setfillcolor(bgColor);

		do {
			if (_kbhit()) {				//������ް�������
				if ((ch == KEY_UP || ch == 72) ||
					(ch == KEY_DOWN || ch == 80) ||
					(ch == KEY_LEFT || ch == 75) ||
					(ch == KEY_RIGHT || ch == 77)) {
					retreat = ch;			//������ҵ�ǰ�������ڻ���
				}
				ch = _getch();			//��ȡ��Ұ������浽 ch��			
				//�ж���ҵİ���
				if (ch == KEY_UP || ch == 72 || ch == (KEY_UP - 32)) {				//��
					gameControl(UP, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_DOWN || ch == 80 || ch == (KEY_DOWN - 32)) {	//��
					gameControl(DOWN, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_LEFT || ch == 75 || ch == (KEY_LEFT - 32)) {	//��
					gameControl(LEFT, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_RIGHT || ch == 77 || ch == (KEY_RIGHT - 32)) {	//��
					gameControl(RIGHT, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_RETREAT || ch == (KEY_RETREAT - 32)) {				//����
					takeBack(retreat, count, ifMove, pmap->map, pmap->line, pmap->column);
				}
				else if (ch == KEY_RESTART || ch == (KEY_RESTART - 32)) {				//���¿�ʼ��ǰ�ؿ�
					if (count <= 0) {						//�������Ϊ��,��ʾС��δ�ƶ���,�������õ�ͼ
						continue;	//ִ����һ��ѭ��
					}
					map1[customsPass] = map2[customsPass];				//�ָ���ͼ
					initGameScene(pmap->map, pmap->line, pmap->column, customsPass + 1);	//��ӡ�ָ��ĵ�ͼ
					count = 0;								//��������
				}
				else if (ch == KEY_RESELECT || ch == (KEY_RESELECT - 32)) {
					customsPass = checkpointChoice(bg_img, customsPass);
				}
				else if (ch == KEY_QUIT || ch == (KEY_QUIT - 32)) {				//�˳�
					quit = true;
				}

				//��̬��ӡ����
				sprintf_s(str, "%d", count);				//��int����ת����char�ַ�����
				solidrectangle(75, 25, 125, 50);				//���Ʋ����Ķ�̬���ֵ�ʵ�ľ���
				outtextxy(75, 25, str);						//��ָ��λ�����ת���ı���ֵ			

				if (isGameOver(pmap->map, pmap->line, pmap->column)) {
					if ((customsPass + 1) < MAP_QUANTITY) {
						gemrOverScene(&bg_img[BG], &bg_img[VICTORY], customsPass + 1);
						levelsPrompt(&bg_img[BG], customsPass + 2);						//��һ����ʾҳ��
						pmap++;															//������һ��						
						initGameScene(pmap->map, pmap->line, pmap->column, customsPass + 2);	//������һ�ص�ͼ
						customsPass++;
						map2[customsPass] = map1[customsPass];										//���µ�ͼ����һ�ݵ�map2��,���ڻָ���ǰ�ؿ�
						count = 0;													//��һ�ز�������
						setfillcolor(bgColor);			//������һ�ز����Ķ�̬���ֵ�ʵ�ľ������ɫ
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
			Sleep(100);					//����0.1��
		} while (quit == false); //!quit

		if (ch == KEY_QUIT || ch == (KEY_QUIT - 32)) {
			settextcolor(WHITE);										//����������ɫΪ��ɫ
			RECT rec = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };				//���ƾ���
			settextstyle(30, 0, _T("����"));							//��������
			drawtext(_T("��������˾����ȷ��Ҫ�˳���? ȷ���밴 'Q',���¿�ʼ�밴 'T'"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		while (quit == true) {
			if (_kbhit()) {				//������ް�������			
				ch = _getch();			//��ȡ��Ұ������浽 ch��	
				if (ch == KEY_RESTART || ch == (KEY_RESTART - 32)) {
					quit = false;
					for (int i = 0; i < MAP_QUANTITY; i++) {	//�ָ�ȫ����ʼ��ͼ
						map1[i] = map2[i];
					}
					customsPass = 0;							//�ؿ�����
					pmap = &map1[0];							//pmap����ָ���һ����ͼ
					break;
				}
				else if (ch == KEY_QUIT || ch == (KEY_QUIT - 32)) {	//ȷ���˳�
					break;
				}

			}
			Sleep(100);
		}
	}
}



int main(void) {
	int customsPass = 0;			//�ؿ�����		

	//������Դ
	loadResources(bg_img);

	//��ʼ����
	startInterface(bg_img);
	//����ʱ��
	setcolor(BLUE);
	settextstyle(18, 0, _T("����"));
	setbkmode(TRANSPARENT);
	outtextxy(780, 10, "2022-13-14  9:05:20");
	//�������֣�send:����
	mciSendString("play �Ȳ�������.mp3 repeat",0,0,0);
	//�ؿ�ѡ��
	customsPass = checkpointChoice(bg_img, customsPass);

	//��ʼ��Ϸ
	startGame(customsPass);


	//��Ϸ�����ͷ���Դ
	closegraph();
	return 0;
}