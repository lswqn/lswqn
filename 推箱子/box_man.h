#pragma once

#ifndef BOX_MAN_H
#define BOX_MAN_H



#define RATIO 61			//ǽ,����,�ذ�, С��,С����Ŀ�ĵ���,Ŀ�ĵص�ͼƬ��С

#define SCREEN_WIDTH 960	//��̨�ĳ�960
#define SCREEN_HEIGHT 768	//��̨�ĸ�768

#define SCREEN_WIDTH1  430	//ʤ����ʧ�ܵ�ͼƬ��С
#define SCREEN_HEIGHT1 240	//ʤ����ʧ�ܵ�ͼƬ��С

#define LINE 12				//��ͼ������
#define COLUMN 12			//��ͼ������

#define MAP_QUANTITY	7	//��ͼ����

#define STAR_X 100			//��ͼ��һ��ͼƬ��X����
#define STAR_Y 150			//��ͼ��һ��ͼƬ��Y����

#define COUNT 300			//��Ϸ��������

//���Ƽ� �ϡ��¡����� ���Ʒ���,'q' �˳�
#define KEY_UP		'w'		//��
#define KEY_LEFT	'a'		//��
#define KEY_RIGHT	'd'		//��
#define KEY_DOWN	's'		//��
#define KEY_QUIT	'q'		//�˳�
#define KEY_RETREAT 'r'		//����
#define KEY_RESTART	't'		//���¿�ʼ��ǰ�ؿ�
#define KEY_RESELECT 'o'	//����ѡ��ؿ�

#define isValid(pos) pos.x >= 0 && pos.x < LINE && pos.y >= 0 && pos.y < COLUMN  

typedef enum _PROPS		 PROPS;			//ö�����ͱ���
typedef enum _DIRECTION  DIRECTION;		//ö�����ͱ���
typedef struct _POS		 POS;			//�ṹ�����ͱ���

//��Ϸ����ͼƬ
enum _BGIMAGE {
	BG,						//��Ϸ����
	VICTORY,				//��Ϸʤ������
	OVER,					//��Ϸʧ�ܱ���
	SOKOBAN,				//�����ӿ�ʼͼƬ
	ALL1					//���ж��ٱ���
};


//ö��
enum _PROPS {
	WALL,					//ǽ
	FLOOR,					//�ذ�
	BOX_DES,				//����Ŀ�ĵ�
	MAN,					//С��
	BOX,					//����
	HIT,					//��������Ŀ��
	MAN_DES,				//С��վ��Ŀ�ĵ���
	ALL						//���ж���Ԫ��
};

//��Ϸ���Ʒ���
enum _DIRECTION {
	UP,						//��
	DOWN,					//��
	LEFT,					//��
	RIGHT					//��
};

//�ṹ��
struct _POS {
	int x;					//С�����ڵĶ�ά�������
	int y;					//С�����ڵĶ�ά�������
};

struct MAP {
	int line;			//��ͼ����
	int column;		//��ͼ��
	int map[LINE][COLUMN];	//��ͼ����
};


#endif // !BOX_MAN.H