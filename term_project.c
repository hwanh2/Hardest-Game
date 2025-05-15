#include <stdio.h>
#include <conio.h>
#include <Windows.h>

// 색상 정의
#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15

#define STAR '*'
#define BLANK ' '

#define ESC 0x1b

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define ENTER '\r'
#define SPACE ' '
#define WIDTH 40
#define HEIGHT 24

int Delay = 100; // 100 msec delay, 이 값을 줄이면 속도가 빨라진다.
int start_map[24][40] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,3,0,0,1,3,0,0,1,3,0,0,1,1,1,1,1,3,1,1,1,3,0,0,1,1,1,3,0,1,1,1,3,1,1,1,1,1,3},
	{0,2,3,0,0,2,3,0,2,2,2,3,0,2,3,0,0,2,3,2,3,0,2,3,0,2,3,0,0,2,3,0,0,0,0,0,2,3,0,0},
	{0,1,3,0,0,1,3,0,1,3,1,3,0,1,3,0,0,1,3,1,3,0,0,1,3,1,3,0,0,1,3,0,0,0,0,0,1,3,0,0},
	{0,2,2,2,2,2,3,0,2,3,2,3,0,2,2,2,2,2,3,2,3,0,0,2,3,2,2,2,3,0,2,2,3,0,0,0,2,3,0,0},
	{0,1,3,0,0,1,3,1,1,1,1,1,3,1,3,1,3,0,0,1,3,0,0,1,3,1,3,0,0,0,0,0,1,3,0,0,1,3,0,0},
	{0,2,3,0,0,2,3,2,3,0,0,2,3,2,3,0,2,3,0,2,3,0,2,3,0,2,3,0,0,0,0,0,2,3,0,0,2,3,0,0},
	{0,1,3,0,0,1,3,1,3,0,0,1,3,1,3,0,0,1,3,1,1,1,3,0,0,1,1,1,3,1,1,1,3,0,0,0,1,3,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,3,0,0,1,3,0,0,0,1,3,0,0,0,0,1,3,0,1,1,1,1,3,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,3,0,0,0,0,0,2,3,2,3,0,0,2,2,3,0,0,2,2,3,0,2,3,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,3,0,0,0,0,0,1,3,1,3,0,0,1,3,1,3,1,3,1,3,0,1,3,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,3,2,2,2,3,0,2,3,2,3,0,0,2,3,2,2,2,3,2,3,0,2,2,2,2,3,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,3,0,1,3,0,1,1,1,1,1,3,0,1,3,0,1,3,0,1,3,0,1,3,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,2,2,2,2,3,2,3,0,0,2,3,0,2,3,0,2,3,0,2,3,0,2,3,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,3,0,1,3,0,0,1,3,0,1,3,0,0,0,0,1,3,0,1,1,1,1,3,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,99,0,10,11,12,13,14,15,16,17,18,19,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,23,24,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};

int map1[24][40] = {
	{7,7,7,7,7,20,21,22,7,7,7,7,7,7,7,7,7,7,7,23,24,25,7,7,7,7,7,7,7,7,26,27,28,29,30,31,32,33,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,3,1,1,1,1,1,1,4,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,18,8,8,2,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,0,3,4,8,8,8,2,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,8,8,8,2,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,8,8,8,2,7,7,7,7,7},
	{7,7,7,7,3,1,1,1,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,8,8,8,2,7,7,7,7,7},
	{7,7,7,7,2,8,8,8,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,8,8,8,2,7,7,7,7,7},
	{7,7,7,7,2,8,8,8,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,8,8,8,2,7,7,7,7,7},
	{7,7,7,7,2,8,8,8,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,6,1,1,1,5,7,7,7,7,7},
	{7,7,7,7,2,8,99,8,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,2,8,8,8,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,2,8,8,8,6,5,0,3,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,5,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,2,8,8,8,88,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,6,11,11,11,11,11,11,5,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
};

int map2[24][40] = {
	{7,7,7,7,7,20,21,22,7,7,7,7,7,7,7,7,7,7,7,23,24,25,7,7,7,7,7,7,7,7,26,27,28,29,30,31,32,33,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,3,1,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,1,1,4,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,8,8,8,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,8,99,8,88,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,8,8,8,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,8,8,8,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,6,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,1,5,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,6,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,5,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
};

int map3[24][40] = {
	{7,7,7,7,7,20,21,22,7,7,7,7,7,7,7,7,7,7,7,23,24,25,7,7,7,7,7,7,7,7,26,27,28,29,30,31,32,33,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,3,1,1,1,1,4,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,8,8,8,8,2,7,7,7,7,7,7,7,7,3,1,1,1,1,4,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,8,8,99,8,2,7,7,7,7,7,7,7,7,2,8,8,8,8,2,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,8,8,8,8,2,7,7,7,7,7,7,7,7,2,18,8,8,8,2,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,88,3,1,1,5,7,7,7,7,7,7,7,7,2,0,3,1,1,5,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,6,1,4,7,7,7,7,7,7,7,3,1,5,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,3,1,1,1,5,0,0,0,2,7,7,7,7,7,7,7,2,0,0,0,6,1,1,1,4,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,0,0,0,3,1,1,1,5,7,7,7,7,7,7,7,6,1,1,1,4,0,0,0,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,0,0,0,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,0,0,0,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,0,0,0,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,88,80,8,8,88,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,2,0,0,0,0,0,0,0,0,0,88,80,8,8,88,0,0,0,0,0,0,0,0,0,2,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,6,1,1,4,9,0,0,0,0,0,88,80,8,8,88,0,0,0,0,0,9,3,1,1,5,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
};

int map4[24][40] = {
	{7,7,7,7,7,20,21,22,7,7,7,7,7,7,7,7,7,7,7,23,24,25,7,7,7,7,7,7,7,7,26,27,28,29,30,31,32,33,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,7,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,50,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,50,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,50,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,90,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,88,88,88,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,7,7},
	{7,7,2,8,8,8,3,1,1,1,1,1,1,1,1,1,1,1,1,5,6,1,1,1,1,1,1,1,1,1,1,1,1,4,18,18,18,2,7,7},
	{7,7,2,8,99,8,2,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,8,8,8,2,7,7},
	{7,7,2,8,8,8,2,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,8,8,8,2,7,7},
	{7,7,6,1,1,1,5,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,1,1,1,5,7,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
};

void removeCursor(void) { // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

// 화면 지우기고 원하는 배경색으로 설정한다.
void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);
}

int deaths = 0;
void show_startmap() { //게임의 초기화면을 출력
	int x, y;
	for (y = 0; y < 23; y++) {
		for (x = 0; x < 40; x++) {
			if (start_map[y][x] != 0) {
				gotoxy(x * 2, y);
			}
			switch (start_map[y][x]) {
			case 0: textcolor(WHITE, BLACK); printf("  "); textcolor(BLACK, WHITE);
				break;
			case 1: textcolor(CYAN1, BLACK); printf("■"); textcolor(BLACK, WHITE);
				break;
			case 2: textcolor(CYAN2, BLACK); printf("■"); textcolor(BLACK, WHITE);
				break;
			case 3: textcolor(GRAY2, GRAY2); printf(" "); textcolor(BLACK, BLACK); printf(" "); textcolor(BLACK, WHITE);
				break;
			case 10: textcolor(BLACK, CYAN1); printf("  "); textcolor(BLACK, WHITE);
				break;
			case 11: textcolor(BLACK, CYAN1); printf("S "); textcolor(BLACK, WHITE);
				break;
			case 12: textcolor(BLACK, CYAN1); printf("T "); textcolor(BLACK, WHITE);
				break;
			case 13: textcolor(BLACK, CYAN1); printf("A "); textcolor(BLACK, WHITE);
				break;
			case 14: textcolor(BLACK, CYAN1); printf("R "); textcolor(BLACK, WHITE);
				break;
			case 15: textcolor(BLACK, CYAN1); printf("T "); textcolor(BLACK, WHITE);
				break;
			case 16: textcolor(BLACK, CYAN1); printf("( "); textcolor(BLACK, WHITE);
				break;
			case 17: textcolor(BLACK, CYAN1); printf("EN"); textcolor(BLACK, WHITE);
				break;
			case 18: textcolor(BLACK, CYAN1); printf("TE"); textcolor(BLACK, WHITE);
				break;
			case 19: textcolor(BLACK, CYAN1); printf("R "); textcolor(BLACK, WHITE);
				break;
			case 20: textcolor(BLACK, CYAN1); printf(") "); textcolor(BLACK, WHITE);
				break;
			case 22: textcolor(CYAN1, BLACK); printf("Q "); textcolor(BLACK, WHITE);
				break;
			case 23: textcolor(CYAN1, BLACK); printf("U "); textcolor(BLACK, WHITE);
				break;
			case 24: textcolor(CYAN1, BLACK); printf("I "); textcolor(BLACK, WHITE);
				break;
			case 25: textcolor(CYAN1, BLACK); printf("T "); textcolor(BLACK, WHITE);
				break;
			case 88: textcolor(WHITE, BLACK); printf("  "); textcolor(BLACK, WHITE);
				break;
			case 99: textcolor(WHITE, BLACK); printf("▶"); textcolor(BLACK, WHITE);
				break;
			default:
				break;
			}
		}
	}
}

void move_startmap() { //게임의 초기화면의 색을 바꿔줌
	int x, y;
	for (y = 0; y < 24; y++) {
		for (x = 0; x < 40; x++) {
			if (start_map[y][x] == 1) {
				start_map[y][x] = 2;
			}
			else if (start_map[y][x] == 2) {
				start_map[y][x] = 1;
			}
		}
	}
}
int ROUND;
int print_background1 = 0;
int print_background2 = 0;
int print_background3 = 0;
int print_background4 = 0;

void show_map(int map[][40]) //게임의 맵을 출력
{
	int x, y;
	for (y = 0; y < 24; y++) {
		for (x = 0; x < 40; x++) {
			if (map[y][x] != 0) {
				gotoxy(x * 2, y);
			}
			switch (map[y][x]) {
			case 0: printf("  "); break;
			case 1: printf("━"); break;
			case 2: printf("┃"); break;
			case 3: printf("┏"); break;
			case 4: printf("┓"); break;
			case 5: printf("┛"); break;
			case 6: printf("┗"); break;
			case 7:
				if (ROUND == 1) {
					if (print_background1 == 0) {
						textcolor(CYAN2, CYAN2);
						printf("  ");
						textcolor(BLACK, WHITE);
					}
				}
				else if (ROUND == 2) {
					if (print_background2 == 0) {
						textcolor(CYAN1, CYAN1);
						printf("  ");
						textcolor(BLACK, WHITE);
					}
				}
				else if (ROUND == 3) {
					if (print_background3 == 0) {
						textcolor(YELLOW1, YELLOW1);
						printf("  ");
						textcolor(BLACK, WHITE);
					}
				}
				else if (ROUND == 4) {
					if (print_background4 == 0) {
						textcolor(RED2, RED2);
						printf("  ");
						textcolor(BLACK, WHITE);
					}
				}
				break;
			case 8: textcolor(GREEN2, GREEN2); printf("  "); textcolor(BLACK, WHITE);
				break;
			case 9: textcolor(YELLOW1, WHITE); printf("●"); textcolor(BLACK, WHITE);
				break;
			case 10:
				if (ROUND == 4) {
					textcolor(RED1, WHITE);
					printf("●");
					textcolor(BLACK, WHITE);
				}
				else {
					textcolor(BLUE1, WHITE);
					printf("●");
					textcolor(BLACK, WHITE);
				}
				break;
			case 11: printf("━"); break;
			case 99:
				if (ROUND == 4) {
					textcolor(BLUE1, WHITE);
					printf("■");
					textcolor(BLACK, WHITE);
				}
				else {
					textcolor(RED2, WHITE);
					printf("■");
					textcolor(BLACK, WHITE);
				}
				break;
			case 18: textcolor(GREEN2, GREEN2); printf("  "); textcolor(BLACK, WHITE); break;
			case 77: printf("  "); break;
			case 80: textcolor(GREEN2, GREEN2); printf("  "); textcolor(BLACK, WHITE); break;
			case 88: printf("  "); break;
			case 50:
				if (ROUND == 4) {
					textcolor(RED1, WHITE);
					printf("●");
					textcolor(BLACK, WHITE);
				}
				else {
					textcolor(BLUE1, WHITE);
					printf("●");
					textcolor(BLACK, WHITE);
				}
				break;
			case 51: printf("  ");
				break;
			case 90: textcolor(GRAY2, WHITE); printf("●"); textcolor(BLACK, WHITE);
				break;
			case 20: textcolor(YELLOW2, GRAY2); printf("Ｅ"); textcolor(BLACK, WHITE);
				break;
			case 21: textcolor(YELLOW2, GRAY2); printf("Ｓ"); textcolor(BLACK, WHITE);
				break;
			case 22: textcolor(YELLOW2, GRAY2); printf("Ｃ"); textcolor(BLACK, WHITE);
				break;
			case 23:
				textcolor(YELLOW2, GRAY2);
				if (ROUND == 1) {
					printf("１");
				}
				else if (ROUND == 2) {
					printf("２");
				}
				else if (ROUND == 3) {
					printf("３");
				}
				else if (ROUND == 4) {
					printf("４");
				}
				textcolor(BLACK, WHITE);
				break;
			case 24: textcolor(YELLOW2, GRAY2); printf("／"); textcolor(BLACK, WHITE);
				break;
			case 25: textcolor(YELLOW2, GRAY2); printf("４"); textcolor(BLACK, WHITE);
				break;
			case 26: textcolor(YELLOW2, GRAY2); printf("Ｄ"); textcolor(BLACK, WHITE);
				break;
			case 27: textcolor(YELLOW2, GRAY2); printf("Ｅ"); textcolor(BLACK, WHITE);
				break;
			case 28: textcolor(YELLOW2, GRAY2); printf("Ａ"); textcolor(BLACK, WHITE);
				break;
			case 29: textcolor(YELLOW2, GRAY2); printf("Ｔ");
				break;
			case 30: textcolor(YELLOW2, GRAY2); printf("Ｈ"); textcolor(BLACK, WHITE);
				break;
			case 31: textcolor(YELLOW2, GRAY2); printf("Ｓ"); textcolor(BLACK, WHITE);
				break;
			case 32: textcolor(YELLOW2, GRAY2); printf("："); textcolor(BLACK, WHITE);
				break;
			case 33: textcolor(YELLOW2, GRAY2); printf("%d ", deaths); textcolor(BLACK, WHITE);
				break;
			default:
				break;
			}
		}
	}
	if (ROUND == 1)
		print_background1 = 1;
	if (ROUND == 2)
		print_background2 = 1;
	if (ROUND == 3)
		print_background3 = 1;
	if (ROUND == 4)
		print_background3 = 1;
}

int block1_x1 = 10;
int block1_y1 = 8;
int block1_x2 = 28;
int block1_y2 = 9;

void init_block1()  // 장애물의 초기 위치 //굳이 안 만들어도 되었었던 것 같음
{
	for (int i = 0; i < 8; i += 2) {
		map1[block1_y1 + i][block1_x1] = 10;
	}
	for (int i = 0; i < 8; i += 2) {
		map1[block1_y2 + i][block1_x2] = 10;
	}
}

int block2_x1 = 12;
int block2_y1 = 6;
int block2_x2 = 13;
int block2_y2 = 16;
int check_item = 0;

void init_block2() {
	for (int i = 0; i < 16; i += 2) {
		map2[block2_y1][block2_x1 + i] = 10;
	}
	for (int i = 0; i < 14; i += 2) {
		map2[block2_y2][block2_x2 + i] = 10;
	}
}

int block3_x1 = 14;
int block3_y1 = 8;
int block3_x2 = 12;
int block3_y2 = 9;
int block3_x3 = 8;
int block3_y3 = 17;
int block3_x4 = 10;
int block3_y4 = 16;
int block3_x5 = 11;
int block3_y5 = 19;
int block3_x6 = 12;
int block3_y6 = 21;
int block3_x7 = 23;
int block3_y7 = 19;
int block3_x8 = 22;
int block3_y8 = 21;
int block3_x9 = 30;
int block3_y9 = 17;
int block3_x10 = 28;
int block3_y10 = 16;
int block3_x11 = 24;
int block3_y11 = 8;
int block3_x12 = 26;
int block3_y12 = 9;

void init_block3() {
	for (int i = 0; i < 8; i += 2) {
		map3[block3_y1 + i][block3_x1] = 10;
	}
	for (int i = 0; i < 8; i += 2) {
		map3[block3_y2 + i][block3_x2] = 10;
	}
	for (int i = -2; i < 4; i += 2) {
		map3[block3_y3 + i][block3_x3] = 10;
	}
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y4 + i][block3_x4] = 10;
	}
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y5][block3_x5 + i] = 10;
	}
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y6][block3_x6 + i] = 10;
	}
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y7][block3_x7 + i] = 10;
	}
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y8][block3_x8 + i] = 10;
	}
	for (int i = -2; i < 4; i += 2) {
		map3[block3_y9 + i][block3_x9] = 10;
	}
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y10 + i][block3_x10] = 10;
	}
	for (int i = 0; i < 8; i += 2) {
		map3[block3_y11 + i][block3_x11] = 10;
	}
	for (int i = 0; i < 8; i += 2) {
		map3[block3_y12 + i][block3_x12] = 10;
	}
}

int block4_x1 = 3;
int block4_y1 = 3;
int block4_x2 = 3;
int block4_y2 = 18;
int block4_x3 = 18;
int block4_y3 = 3;
int block4_x4 = 18;
int block4_y4 = 18;
int block4_x5 = 21;
int block4_y5 = 3;
int block4_x6 = 22;
int block4_y6 = 18;
int block4_x7 = 36;
int block4_y7 = 18;
int block4_x8 = 21;
int block4_y8 = 17;
int block4_x9 = 4;
int block4_y9 = 4;
int block4_x10 = 17;
int block4_y10 = 17;

void init_block4() {

	map4[block4_y1][block4_x1] = 10;
	map4[block4_y2][block4_x2] = 10;
	map4[block4_y3][block4_x3] = 10;
	map4[block4_y4][block4_x4] = 10;

	for (int i = 0; i < 16; i += 2) {
		map4[block4_y5][block4_x5 + i] = 10;
	}
	for (int i = 0; i < 16; i += 2) {
		map4[block4_y6][block4_x6 + i] = 10;
	}
	for (int i = 0; i < 16; i += 2) {
		map4[block4_y7 - i][block4_x7] = 10;
	}
	for (int i = 0; i < 16; i += 2) {
		map4[block4_y8 - i][block4_x8] = 10;
	}
	map4[block4_y9][block4_x9] = 10;
	map4[block4_y9 - 1][block4_x9 - 1] = 10;
	map4[block4_y9 - 1][block4_x9 + 1] = 10;
	map4[block4_y9 + 1][block4_x9 - 1] = 10;
	map4[block4_y9 + 1][block4_x9 + 1] = 10;

	map4[block4_y10][block4_x10] = 10;
	map4[block4_y10 - 1][block4_x10 - 1] = 10;
	map4[block4_y10 - 1][block4_x10 + 1] = 10;
	map4[block4_y10 + 1][block4_x10 - 1] = 10;
	map4[block4_y10 + 1][block4_x10 + 1] = 10;

}

int move1_1 = 1; //장애물이 움직이는 방향을 바꿔줌
int move1_2 = 1;
int oldx, oldy, newx, newy;
void move_block1() {
	int x, y;
	//장애물을 지움
	for (y = 0; y < 24; y++) {
		for (x = 0; x < 40; x++) {
			if (map1[y][x] == 10) {
				map1[y][x] = 0;
			}
		}
	}
	//첫번째 장애물
	if (map1[block1_y1][block1_x1 + move1_1] == 2) {
		move1_1 = -move1_1; // 움직일 곳이 궤선을 만나면 부호 바꿔줌
	}
	block1_x1 += move1_1;

	for (int i = 0; i < 8; i += 2) {
		map1[block1_y1 + i][block1_x1] = 10;
	}
	//두번째 장애물
	if (map1[block1_y2][block1_x2 + move1_2] == 2) {
		move1_2 = -move1_2; // 움직일 곳이 궤선을 만나면 부호 바꿔줌
	}
	block1_x2 += move1_2;

	for (int i = 0; i < 8; i += 2) {
		map1[block1_y2 + i][block1_x2] = 10;
	}
	if (map1[newy][newx / 2] == 10) { // 캐릭터가 멈춰있을 때 장애물에 닿으면
		oldx = newx = 12;
		oldy = newy = 14;
		map1[newy][newx / 2] = 99;
		deaths++;
	}
}


int move2_1 = 1;
int move2_2 = -1;
void move_block2() {
	//맵에 있는 장애물을 지움
	int x, y;
	for (y = 0; y < 24; y++) {
		for (x = 0; x < 40; x++) {
			if (map2[y][x] == 10) {
				map2[y][x] = 0;
			}
		}
	}
	//첫번째 장애물
	if (map2[block2_y1 + move2_1][block2_x1] == 1 || map2[block2_y1 + move2_1][block2_x1] == 11) {
		move2_1 = -move2_1; // 움직일 곳이 궤선을 만나면 부호 바꿔줌
	}

	block2_y1 += move2_1;
	//장애물의 위치 이동
	for (int i = 0; i < 16; i += 2) {
		if (map2[block2_y1][block2_x1 + i] != 9) { // 장애물이 아이템을 만나도 아이템이 안없어짐
			map2[block2_y1][block2_x1 + i] = 10;
		}
	}

	// 두번 장애물
	if (map2[block2_y2 + move2_2][block2_x2] == 1 || map2[block2_y2 + move2_2][block2_x2] == 11) {
		move2_2 = -move2_2;
	}
	block2_y2 += move2_2;
	for (int i = 0; i < 14; i += 2) {
		if (map2[block2_y2][block2_x2 + i] != 9) { // 장애물이 아이템을 만나도 아이템이 안없어짐
			map2[block2_y2][block2_x2 + i] = 10;
		}
	}

	if (map2[newy][newx / 2] == 10) { // 캐릭터가 멈춰있을 때 장애물에 닿으면
		oldx = newx = 18;
		oldy = newy = 11;
		map2[newy][newx / 2] = 99;
		map2[11][19] = 9;
		check_item = 0;
		deaths++;
	}
}
int move3_1 = -1;
int move3_2 = 1;
int move3_3 = 1;
int move3_4 = -1;
int move3_5 = 1;
int move3_6 = -1;
int move3_7 = -1;
int move3_8 = 1;
int move3_9 = -1;
int move3_10 = 1;
int move3_11 = 1;
int move3_12 = -1;
int save = 0;
int check_item3 = 0;
void move_block3() {
	int x, y;
	// 첫번째 장애물
	for (y = 0; y < 24; y++) {
		for (x = 0; x < 40; x++) {
			if (map3[y][x] == 10) {
				map3[y][x] = 0;
			}
		}
	}
	if (map3[block3_y1][block3_x1 + move3_1] == 2) {
		move3_1 = -move3_1;
	}
	block3_x1 += move3_1;
	for (int i = 0; i < 8; i += 2) {
		map3[block3_y1 + i][block3_x1] = 10;
	}

	// 두번째 장애물
	if (map3[block3_y2][block3_x2 + move3_2] == 2) {
		move3_2 = -move3_2;
	}
	block3_x2 += move3_2;
	for (int i = 0; i < 8; i += 2) {
		map3[block3_y2 + i][block3_x2] = 10;
	}

	//세번째 장애물
	if (map3[block3_y3][block3_x3 + move3_3] == 2) {
		move3_3 = -move3_3;
	}
	block3_x3 += move3_3;
	for (int i = -2; i < 4; i += 2) {
		map3[block3_y3 + i][block3_x3] = 10;
	}

	//네번째 장애물
	if (map3[block3_y4][block3_x4 + move3_4] == 2 || map3[block3_y4][block3_x4 + move3_4] == 3) {
		move3_4 = -move3_4;
	}
	block3_x4 += move3_4;
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y4 + i][block3_x4] = 10;
	}

	// 다섯번째 장애물
	if (map3[block3_y5 + move3_5][block3_x5] == 1 || map3[block3_y5 + move3_5][block3_x5] == 6) {
		move3_5 = -move3_5;
	}
	block3_y5 += move3_5;
	for (int i = 0; i < 6; i += 2) {
		if (map3[block3_y5][block3_x5] == 0) { // 장애물이 아이템을 지우고 나면
			if (check_item3 == 0) { // 캐릭터가 아이템을 먹지 않았을 때 아이템이 다시 생김
				map3[21][11] = 9;
			}
		}
		map3[block3_y5][block3_x5 + i] = 10;

	}

	// 여섯번째 장애물
	if (map3[block3_y6 + move3_6][block3_x6] == 1) {
		move3_6 = -move3_6;
	}
	block3_y6 += move3_6;
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y6][block3_x6 + i] = 10;
	}

	// 일곱번째 장애물
	if (map3[block3_y7 + move3_7][block3_x7] == 1) {
		move3_7 = -move3_7;
	}
	block3_y7 += move3_7;
	for (int i = 0; i < 6; i += 2) {
		if (map3[block3_y7][block3_x7] == 0) {
			if (check_item3 != 2) {
				map3[21][27] = 9;
			}
		}
		map3[block3_y7][block3_x7 + i] = 10;
	}

	// 여덟번째 장애물
	if (map3[block3_y8 + move3_8][block3_x8] == 1) {
		move3_8 = -move3_8;
	}
	block3_y8 += move3_8;
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y8][block3_x8 + i] = 10;
	}

	// 아홉번째 장애물
	if (map3[block3_y9][block3_x9 + move3_9] == 2) {
		move3_9 = -move3_9;
	}
	block3_x9 += move3_9;
	for (int i = -2; i < 4; i += 2) {
		map3[block3_y9 + i][block3_x9] = 10;
	}

	// 열번째 장애물
	if (map3[block3_y10][block3_x10 + move3_10] == 2 || map3[block3_y10][block3_x10 + move3_10] == 4) {
		move3_10 = -move3_10;
	}
	block3_x10 += move3_10;
	for (int i = 0; i < 6; i += 2) {
		map3[block3_y10 + i][block3_x10] = 10;
	}

	// 열한번째 장애물
	if (map3[block3_y11][block3_x11 + move3_11] == 2) {
		move3_11 = -move3_11;
	}
	block3_x11 += move3_11;
	for (int i = 0; i < 8; i += 2) {
		map3[block3_y11 + i][block3_x11] = 10;
	}

	// 열두번째 장애물
	if (map3[block3_y12][block3_x12 + move3_12] == 2) {
		move3_12 = -move3_12;
	}
	block3_x12 += move3_12;
	for (int i = 0; i < 8; i += 2) {
		map3[block3_y12 + i][block3_x12] = 10;
	}
	if (map3[newy][newx / 2] == 10) { // 캐릭터가 멈춰있을 때 장애물에 닿으면
		if (save == 0) {
			oldx = newx = 28;
			oldy = newy = 4;
			map3[newy][newx / 2] = 99;
			check_item3 = 0;
			deaths++;
		}
		else {
			oldx = newx = 38;
			oldy = newy = 20;
			map3[newy][newx / 2] = 99;
			map3[19][21] = 88;
			map3[20][21] = 88;
			map3[21][21] = 88;
			check_item3 = 0;
			deaths++;
		}
	}
}

int move4_1y = 1;
int move4_1x = 1;
int move4_2y = -1;
int move4_2x = 1;
int move4_3y = 1;
int move4_3x = -1;
int move4_4y = -1;
int move4_4x = -1;
int move4_5 = 1;
int move4_6 = -1;
int move4_7 = -1;
int move4_8 = 1;
int move4_9x = 1;
int move4_9y = 1;
int move4_10x = -1;
int move4_10y = -1;
int check_x1 = 1;
int check_y1 = 0;
int check_x2 = -1;
int check_y2 = 0;

int check_key = 0;
void move_block4() {
	int x, y;
	for (y = 0; y < 24; y++) {
		for (x = 0; x < 40; x++) {
			if (map4[y][x] == 10) {
				map4[y][x] = 0;
			}
		}
	}

	//첫번째 장애물
	if (map4[block4_y1 + move4_1y][block4_x1 + move4_1x] == 3 || map4[block4_y1 + move4_1y][block4_x1 + move4_1x] == 5) {
		move4_1x = -move4_1x;
		move4_1y = -move4_1y;
	}
	block4_x1 += move4_1x;
	block4_y1 += move4_1y;
	if (map4[block4_y1][block4_x1] == 0) {
		if (check_key == 0) {
			map4[11][11] = 90;
		}
	}
	map4[block4_y1][block4_x1] = 10;

	//두번째 장애물
	if (map4[block4_y2 + move4_2y][block4_x2 + move4_2x] == 1 || map4[block4_y2 + move4_2y][block4_x2 + move4_2x] == 2) {
		move4_2x = -move4_2x;
		move4_2y = -move4_2y;
	}
	block4_x2 += move4_2x;
	block4_y2 += move4_2y;
	if (map4[block4_y2][block4_x2] == 0) {
		if (check_key == 0) {
			map4[11][11] = 90;
		}
	}
	map4[block4_y2][block4_x2] = 10;

	//세번째 장애물
	if (map4[block4_y3 + move4_3y][block4_x3 + move4_3x] == 1 || map4[block4_y3 + move4_3y][block4_x3 + move4_3x] == 2) {
		move4_3x = -move4_3x;
		move4_3y = -move4_3y;
	}
	block4_x3 += move4_3x;
	block4_y3 += move4_3y;
	if (map4[block4_y3][block4_x3] == 0) {
		if (check_key == 0) {
			map4[11][11] = 90;
		}
	}
	map4[block4_y3][block4_x3] = 10;

	//네번째 장애물
	if (map4[block4_y4 + move4_4y][block4_x4 + move4_4x] == 3 || map4[block4_y4 + move4_4y][block4_x4 + move4_4x] == 5) {
		move4_4x = -move4_4x;
		move4_4y = -move4_4y;
	}
	block4_x4 += move4_4x;
	block4_y4 += move4_4y;
	if (map4[block4_y4][block4_x4] == 0) {
		if (check_key == 0) {
			map4[11][11] = 90;
		}
	}
	map4[block4_y4][block4_x4] = 10;
	//다섯번째 장애물
	if (map4[block4_y5 + move4_5][block4_x5] == 1) {
		move4_5 = -move4_5; // 움직일 곳이 궤선을 만나면 부호 바꿔줌
	}
	block4_y5 += move4_5;

	for (int i = 0; i < 16; i += 2) {
		map4[block4_y5][block4_x5 + i] = 10;
	}
	//여섯번째 장애물
	if (map4[block4_y6 + move4_6][block4_x6] == 1) {
		move4_6 = -move4_6; // 움직일 곳이 궤선을 만나면 부호 바꿔줌
	}
	block4_y6 += move4_6;

	for (int i = 0; i < 16; i += 2) {
		map4[block4_y6][block4_x6 + i] = 10;
	}
	//일곱번째 장애물
	if (map4[block4_y7][block4_x7 + move4_7] == 2) {
		move4_7 = -move4_7; // 움직일 곳이 궤선을 만나면 부호 바꿔줌
	}
	block4_x7 += move4_7;

	for (int i = 0; i < 16; i += 2) {
		map4[block4_y7 - i][block4_x7] = 10;
	}
	//여덟번째 장애물
	if (map4[block4_y8][block4_x8 + move4_8] == 2) {
		move4_8 = -move4_8; // 움직일 곳이 궤선을 만나면 부호 바꿔줌
	}
	block4_x8 += move4_8;

	for (int i = 0; i < 16; i += 2) {
		map4[block4_y8 - i][block4_x8] = 10;
	}
	//아홉번째 장애물
	//오른쪽으로 이동
	if (check_x1 == 1 && check_y1 == 0) {
		if (map4[block4_y9][block4_x9 + 2] == 2 || map4[block4_y9][block4_x9 + 2] == 50 ||
			map4[block4_y9][block4_x9 + 2] == 51) {
			//깜빡이는거 방지
			map4[block4_y9][block4_x9] = 10;
			map4[block4_y9 - 1][block4_x9 - 1] = 10;
			map4[block4_y9 - 1][block4_x9 + 1] = 10;
			map4[block4_y9 + 1][block4_x9 - 1] = 10;
			map4[block4_y9 + 1][block4_x9 + 1] = 10;
			move4_9x = -move4_9x;
			check_x1 = 0;
			check_y1 = 1;
		}
		if (check_x1 == 1 && check_y1 == 0) {
			block4_x9 += move4_9x;
			map4[block4_y9][block4_x9] = 10;
			map4[block4_y9 - 1][block4_x9 - 1] = 10;
			map4[block4_y9 - 1][block4_x9 + 1] = 10;
			map4[block4_y9 + 1][block4_x9 - 1] = 10;
			map4[block4_y9 + 1][block4_x9 + 1] = 10;
		}
	}
	//아래로 이동
	else if (check_x1 == 0 && check_y1 == 1) {
		if (map4[block4_y9 + 2][block4_x9] == 1) {
			//깜빡이는거 방지
			map4[block4_y9][block4_x9] = 10;
			map4[block4_y9 - 1][block4_x9 - 1] = 10;
			map4[block4_y9 - 1][block4_x9 + 1] = 10;
			map4[block4_y9 + 1][block4_x9 - 1] = 10;
			map4[block4_y9 + 1][block4_x9 + 1] = 10;
			move4_9y = -move4_9y;
			check_x1 = -1;
			check_y1 = 0;
		}
		if (check_x1 == 0 && check_y1 == 1) {
			block4_y9 += move4_9y;
			map4[block4_y9][block4_x9] = 10;
			map4[block4_y9 - 1][block4_x9 - 1] = 10;
			map4[block4_y9 - 1][block4_x9 + 1] = 10;
			map4[block4_y9 + 1][block4_x9 - 1] = 10;
			map4[block4_y9 + 1][block4_x9 + 1] = 10;
		}

	}
	//왼쪽으로 이동
	else if (check_x1 == -1 && check_y1 == 0) {
		if (map4[block4_y9][block4_x9 - 2] == 2) {
			//깜빡이는거 방지
			map4[block4_y9][block4_x9] = 10;
			map4[block4_y9 - 1][block4_x9 - 1] = 10;
			map4[block4_y9 - 1][block4_x9 + 1] = 10;
			map4[block4_y9 + 1][block4_x9 - 1] = 10;
			map4[block4_y9 + 1][block4_x9 + 1] = 10;
			move4_9x = -move4_9x;
			check_x1 = 0;
			check_y1 = -1;
			//// 장애물이 지나갔을때 값이 없어지는것을 방지
			//map4[18][3] = 88;
			//map4[18][4] = 88;
			//map4[18][5] = 88;
		}
		if (check_x1 == -1 && check_y1 == 0) {
			block4_x9 += move4_9x;
			map4[block4_y9][block4_x9] = 10;
			map4[block4_y9 - 1][block4_x9 - 1] = 10;
			map4[block4_y9 - 1][block4_x9 + 1] = 10;
			map4[block4_y9 + 1][block4_x9 - 1] = 10;
			map4[block4_y9 + 1][block4_x9 + 1] = 10;
		}
	}
	//위로 이동
	else if (check_x1 == 0 && check_y1 == -1) {
		if (map4[block4_y9 - 2][block4_x9] == 1) {
			//깜빡이는거 방지
			map4[block4_y9][block4_x9] = 10;
			map4[block4_y9 - 1][block4_x9 - 1] = 10;
			map4[block4_y9 - 1][block4_x9 + 1] = 10;
			map4[block4_y9 + 1][block4_x9 - 1] = 10;
			map4[block4_y9 + 1][block4_x9 + 1] = 10;
			move4_9y = -move4_9y;
			check_x1 = 1;
			check_y1 = 0;
		}
		if (check_x1 == 0 && check_y1 == -1) {
			block4_y9 += move4_9y;
			map4[block4_y9][block4_x9] = 10;
			map4[block4_y9 - 1][block4_x9 - 1] = 10;
			map4[block4_y9 - 1][block4_x9 + 1] = 10;
			map4[block4_y9 + 1][block4_x9 - 1] = 10;
			map4[block4_y9 + 1][block4_x9 + 1] = 10;
		}
	}
	//열번째 장애물
	//오른쪽으로 이동
	if (check_x2 == 1 && check_y2 == 0) {
		if (map4[block4_y10][block4_x10 + 2] == 2 || map4[block4_y10][block4_x10 + 2] == 50 ||
			map4[block4_y10][block4_x10 + 2] == 51) {
			//깜빡이는거 방지
			map4[block4_y10][block4_x10] = 10;
			map4[block4_y10 - 1][block4_x10 - 1] = 10;
			map4[block4_y10 - 1][block4_x10 + 1] = 10;
			map4[block4_y10 + 1][block4_x10 - 1] = 10;
			map4[block4_y10 + 1][block4_x10 + 1] = 10;
			move4_10x = -move4_10x;
			check_x2 = 0;
			check_y2 = 1;
		}
		if (check_x2 == 1 && check_y2 == 0) {
			block4_x10 += move4_10x;
			map4[block4_y10][block4_x10] = 10;
			map4[block4_y10 - 1][block4_x10 - 1] = 10;
			map4[block4_y10 - 1][block4_x10 + 1] = 10;
			map4[block4_y10 + 1][block4_x10 - 1] = 10;
			map4[block4_y10 + 1][block4_x10 + 1] = 10;
		}
	}
	//아래로 이동
	else if (check_x2 == 0 && check_y2 == 1) {
		if (map4[block4_y10 + 2][block4_x10] == 1) {
			map4[block4_y10][block4_x10] = 10;
			map4[block4_y10 - 1][block4_x10 - 1] = 10;
			map4[block4_y10 - 1][block4_x10 + 1] = 10;
			map4[block4_y10 + 1][block4_x10 - 1] = 10;
			map4[block4_y10 + 1][block4_x10 + 1] = 10;
			move4_10y = -move4_10y;
			check_x2 = -1;
			check_y2 = 0;
		}
		if (check_x2 == 0 && check_y2 == 1) {
			block4_y10 += move4_10y;
			map4[block4_y10][block4_x10] = 10;
			map4[block4_y10 - 1][block4_x10 - 1] = 10;
			map4[block4_y10 - 1][block4_x10 + 1] = 10;
			map4[block4_y10 + 1][block4_x10 - 1] = 10;
			map4[block4_y10 + 1][block4_x10 + 1] = 10;
		}

	}
	//왼쪽으로 이동
	else if (check_x2 == -1 && check_y2 == 0) {
		if (map4[block4_y10][block4_x10 - 2] == 2) {
			//깜빡이는 것 방지
			map4[block4_y10][block4_x10] = 10;
			map4[block4_y10 - 1][block4_x10 - 1] = 10;
			map4[block4_y10 - 1][block4_x10 + 1] = 10;
			map4[block4_y10 + 1][block4_x10 - 1] = 10;
			map4[block4_y10 + 1][block4_x10 + 1] = 10;
			move4_10x = -move4_10x;
			check_x2 = 0;
			check_y2 = -1;
			//// 장애물이 지나갔을때 값이 없어지는것을 방지
			//map4[18][3] = 88;
			//map4[18][4] = 88;
			//map4[18][5] = 88;
		}
		if (check_x2 == -1 && check_y2 == 0) {
			block4_x10 += move4_10x;
			map4[block4_y10][block4_x10] = 10;
			map4[block4_y10 - 1][block4_x10 - 1] = 10;
			map4[block4_y10 - 1][block4_x10 + 1] = 10;
			map4[block4_y10 + 1][block4_x10 - 1] = 10;
			map4[block4_y10 + 1][block4_x10 + 1] = 10;

		}
	}
	//위로 이동
	else if (check_x2 == 0 && check_y2 == -1) {
		if (map4[block4_y10 - 2][block4_x10] == 1) {
			map4[block4_y10][block4_x10] = 10;
			map4[block4_y10 - 1][block4_x10 - 1] = 10;
			map4[block4_y10 - 1][block4_x10 + 1] = 10;
			map4[block4_y10 + 1][block4_x10 - 1] = 10;
			map4[block4_y10 + 1][block4_x10 + 1] = 10;
			move4_10y = -move4_10y;
			check_x2 = 1;
			check_y2 = 0;
		}
		if (check_x2 == 0 && check_y2 == -1) {
			block4_y10 += move4_10y;
			map4[block4_y10][block4_x10] = 10;
			map4[block4_y10 - 1][block4_x10 - 1] = 10;
			map4[block4_y10 - 1][block4_x10 + 1] = 10;
			map4[block4_y10 + 1][block4_x10 - 1] = 10;
			map4[block4_y10 + 1][block4_x10 + 1] = 10;
		}
	}
	if (map4[newy][newx / 2] == 10) { // 캐릭터가 멈춰있을 때 장애물에 닿으면
		oldx = newx = 8;
		oldy = newy = 20;
		map4[newy][newx / 2] = 99;
		// 아이템과 벽 다시 생성
		map4[3][19] = 50;
		map4[4][19] = 50;
		map4[5][19] = 50;
		map4[3][20] = 50;
		map4[4][20] = 50;
		map4[5][20] = 50;
		map4[11][11] = 90;
		check_key = 0;
		deaths++;
	}
}

int start_x, start_y;
void main()
{
	unsigned char ch; // 특수키 0xe0 을 입력받으려면 unsigned char 로 선언해야 함

	int keep_moving;
	unsigned char answer;
	unsigned char esc;

	start_x = 24;
	start_y = 18;
	init_block4();
	system("title 장애물 피하기 게임");
	removeCursor();
	cls(CYAN2, CYAN2);
	//게임의 초기화면 출력
	while (1) {
		if (kbhit() == 1) {
			answer = getch();
			if (answer == '\r') {
				if (start_y == 18) {
					goto ROUND1;
				}
				else if (start_y == 20) {
					return;
				}
			}
			if (answer == SPECIAL1 || answer == SPECIAL2) {
				answer = getch();
				switch (answer) {
				case UP:
					if (start_map[start_y - 1][start_x / 2] != 88) {
						start_map[start_y - 2][start_x / 2] = 99;
						start_map[start_y][start_x / 2] = 0;
						start_y -= 2;
					}
					break;

				case DOWN:
					if (start_map[start_y + 1][start_x / 2] != 88) {
						start_map[start_y + 2][start_x / 2] = 99;
						start_map[start_y][start_x / 2] = 0;
						start_y += 2;
					}
					break;
				default:
					break;
				}
			}
		}
		move_startmap();
		show_startmap();
		Sleep(200);
	}

ROUND1:
	ROUND = 1;
	newx = oldx = 12;
	newy = oldy = 14;
	removeCursor();
	init_block1();
	textcolor(BLACK, WHITE);
	cls(WHITE, WHITE);
	ch = 0; // 초기값 정지상태
	keep_moving = 0;
	while (1) {
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			if (ch == ESC) {
				gotoxy(28, 8); printf("┏━━━━━━━━━━━┓");
				gotoxy(28, 9); printf("┃       일시정지       ┃");
				gotoxy(28, 10); printf("┃━━━━━━━━━━━┃");
				gotoxy(28, 11); printf("┃   계속하기 : Enter   ┃");
				gotoxy(28, 12); printf("┃   끝내기   : ESC     ┃");
				gotoxy(28, 13); printf("┗━━━━━━━━━━━┛");
				while (1) {
					if (kbhit() == 1) {
						esc = getch();
						if (esc == ESC) {
							return 0;
						}
						else if (esc == '\r') {
							break;
						}
					}
				}
			}
			if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
				// 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
				ch = getch();
				switch (ch) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:
					keep_moving = 1;
					break;
				default: // 방향키가 아니면 멈춘다
					keep_moving = 0;
				}
			}
		}
		if (keep_moving) { // 움직이고 있으면	

			switch (ch) {
			case UP:
				if (map1[oldy - 1][oldx / 2] == 10) { // 장애물에 충돌하면
					map1[oldy][oldx / 2] = 88;
					newx = 12;
					newy = 14;
					map1[newy][newx / 2] = 99;
					deaths++;
				}
				else if (map1[oldy - 1][oldx / 2] != 1 && map1[oldy - 1][oldx / 2] != 5 && // 궤선을 만나지 않을때만 이동 가능
					map1[oldy - 1][oldx / 2] != 6) {
					if (map1[oldy - 1][oldx / 2] == 8) {
						newy = oldy - 1;
						map1[oldy][oldx / 2] = 8;
						map1[newy][oldx / 2] = 99;
					}
					else {
						newy = oldy - 1;
						map1[oldy][oldx / 2] = 0; // 원래의 위치 지우고
						map1[newy][oldx / 2] = 99; // 새로운 위치에 저장
					}
				}
				break;
			case DOWN:
				if (map1[oldy + 1][oldx / 2] == 10) { // 장애물에 충돌하면
					map1[oldy][oldx / 2] = 88;
					newx = 12;
					newy = 14;
					map1[newy][newx / 2] = 99;
					deaths++;
				}
				else if (map1[oldy + 1][oldx / 2] != 4 &&
					map1[oldy + 1][oldx / 2] != 3 && map1[oldy + 1][oldx / 2] != 11) {
					if (map1[oldy + 1][oldx / 2] == 8) {
						newy = oldy + 1;
						map1[oldy][oldx / 2] = 8;
						map1[newy][oldx / 2] = 99;
					}
					else {
						newy = oldy + 1;
						map1[oldy][oldx / 2] = 0;
						map1[newy][oldx / 2] = 99;
					}
				}
				break;
			case LEFT:
				if (map1[oldy][oldx / 2 - 1] == 10) { // 장애물에 충돌하면
					map1[oldy][oldx / 2] = 88;
					newx = 12;
					newy = 14;
					map1[newy][newx / 2] = 99;
					deaths++;
				}
				else if (map1[oldy][(oldx / 2) - 1] != 2 && map1[oldy][(oldx / 2) - 1] != 5) {
					if (map1[oldy][oldx / 2 - 1] == 8) { // 세이브존이면
						newx = oldx - 2;
						map1[oldy][oldx / 2] = 8;
						map1[oldy][oldx / 2 - 1] = 99;
					}
					else {
						newx = oldx - 2;
						map1[oldy][oldx / 2] = 0;
						map1[oldy][(oldx / 2) - 1] = 99;
					}
				}
				break;
			case RIGHT:
				if (map1[oldy][oldx / 2 + 1] == 10) { // 장애물에 충돌하면
					map1[oldy][oldx / 2] = 88;
					newx = 12;
					newy = 14;
					map1[newy][newx / 2] = 99; // 시작 위치
					deaths++;
				}
				else if (map1[oldy][(oldx / 2) + 1] != 2 && map1[oldy][(oldx / 2) + 1] != 6 &&
					map1[oldy][(oldx / 2) + 1] != 3) {
					if (map1[oldy][(oldx / 2) + 1] == 18) { //포인트에 가면 다음 라운드로 이동
						goto ROUND2;
					}
					if (map1[oldy][oldx / 2 + 1] == 8 || map1[oldy][oldx / 2 + 1] == 88) {
						newx = oldx + 2;
						map1[oldy][oldx / 2] = 8;
						map1[oldy][oldx / 2 + 1] = 99;
					}
					else if (map1[oldy][oldx / 2 + 1] == map1[17][9]) {
						newx = oldx + 2;
						map1[oldy][oldx / 2] = 88;
						map1[oldy][oldx / 2 + 1] = 99;
					}
					else {
						newx = oldx + 2;
						map1[oldy][oldx / 2] = 0;
						map1[oldy][(oldx / 2) + 1] = 99;
					}
				}
				break;
			}

			oldx = newx; // 마지막 위치를 기억한다.
			oldy = newy;
			keep_moving = 0;
		}
		move_block1();
		show_map(map1);
		Sleep(15); // Delay를 줄이면 속도가 빨라진다.
	}


ROUND2:
	ROUND = 2;
	newx = oldx = 18;
	newy = oldy = 11;
	removeCursor();
	init_block2();
	ch = 0; // 초기값 정지상태
	keep_moving = 0;
	while (1) {
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			if (ch == ESC) {
				gotoxy(28, 8); printf("┏━━━━━━━━━━━┓");
				gotoxy(28, 9); printf("┃       일시정지       ┃");
				gotoxy(28, 10); printf("┃━━━━━━━━━━━┃");
				gotoxy(28, 11); printf("┃   계속하기 : Enter   ┃");
				gotoxy(28, 12); printf("┃   끝내기   : ESC     ┃");
				gotoxy(28, 13); printf("┗━━━━━━━━━━━┛");
				while (1) {
					if (kbhit() == 1) {
						esc = getch();
						if (esc == ESC) {
							return 0;
						}
						else if (esc == '\r') {
							break;
						}
					}
				}
			}
			if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
				// 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
				ch = getch();
				switch (ch) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:
					keep_moving = 1;
					break;
				default: // 방향키가 아니면 멈춘다
					keep_moving = 0;
				}
			}
		}
		if (keep_moving) { // 움직이고 있으면	

			switch (ch) {
			case UP:
				if (map2[oldy - 1][oldx / 2] == 9) { // 아이템을 먹으면 사라짐
					map2[oldy - 1][oldx / 2] = 0;
					check_item = 1;
				}
				if (map2[oldy - 1][oldx / 2] == 10) { // 장애물에 충돌하면
					map2[oldy][oldx / 2] = 88;
					newx = 18;
					newy = 11;
					map2[newy][newx / 2] = 99;
					map2[11][19] = 9;
					check_item = 0;
					deaths++;
				}
				else if (map2[oldy - 1][oldx / 2] != 1 && map2[oldy - 1][oldx / 2] != 5 && // 궤선을 만나지 않을때만 이동 가능
					map2[oldy - 1][oldx / 2] != 6 && map2[oldy - 1][oldx / 2] != 11) { // 11지워도 되나 확인
					if (map2[oldy - 1][oldx / 2] == 8) {
						newy = oldy - 1;
						map2[oldy][oldx / 2] = 8;
						map2[newy][oldx / 2] = 99;
					}
					else {
						newy = oldy - 1;
						map2[oldy][oldx / 2] = 0; // 원래의 위치 지우고
						map2[newy][oldx / 2] = 99; // 새로운 위치에 저장
					}
				}
				break;
			case DOWN:
				if (map2[oldy + 1][oldx / 2] == 9) {// 아이템을 먹으면 사라짐
					map2[oldy + 1][oldx / 2] = 0;
					check_item = 1;
				}
				if (map2[oldy + 1][oldx / 2] == 10) { // 장애물에 충돌하면
					map2[oldy][oldx / 2] = 88;
					newx = 18;
					newy = 11;
					map2[newy][newx / 2] = 99;
					map2[11][19] = 9;
					check_item = 0;
					deaths++;
				}
				else if (map2[oldy + 1][oldx / 2] != 1 && map2[oldy + 1][oldx / 2] != 4 &&
					map2[oldy + 1][oldx / 2] != 3 && map2[oldy + 1][oldx / 2] != 11) {
					if (map2[oldy + 1][oldx / 2] == 8) {
						newy = oldy + 1;
						map2[oldy][oldx / 2] = 8;
						map2[newy][oldx / 2] = 99;
					}
					else {
						newy = oldy + 1;
						map2[oldy][oldx / 2] = 0;
						map2[newy][oldx / 2] = 99;
					}
				}
				break;
			case LEFT:
				if (map2[oldy][(oldx / 2) - 1] == 9) {// 아이템을 먹으면 사라짐
					map2[oldy][(oldx / 2) - 1] = 0;
					check_item = 1;
				}
				if (map2[oldy][oldx / 2 - 1] == 10) { // 장애물에 충돌하면
					map2[oldy][oldx / 2] = 88;
					newx = 18;
					newy = 11;
					map2[newy][newx / 2] = 99;
					map2[11][19] = 9;
					check_item = 0;
					deaths++;
				}
				else if (map2[oldy][(oldx / 2) - 1] != 2 && map2[oldy][(oldx / 2) - 1] != 5 &&
					map2[oldy][(oldx / 2) - 1] != 4 && map2[oldy][(oldx / 2) - 1] != 11) {
					if (map2[oldy][oldx / 2 - 1] == 8) {
						newx = oldx - 2;
						map2[oldy][oldx / 2] = 8;
						map2[oldy][oldx / 2 - 1] = 99;
					}
					else {
						newx = oldx - 2;
						map2[oldy][oldx / 2] = 0;
						map2[oldy][(oldx / 2) - 1] = 99;
					}
				}
				break;
			case RIGHT:
				if (map2[oldy][(oldx / 2) + 1] == 9) {// 아이템을 먹으면 사라짐
					map2[oldy][(oldx / 2) + 1] = 0;
					check_item = 1;
				}
				if (map2[oldy][oldx / 2 + 1] == 10) { // 장애물에 충돌하면
					map2[oldy][oldx / 2] = 88;
					newx = 18;
					newy = 11;
					map2[newy][newx / 2] = 99; // 시작 위치
					map2[11][19] = 9;
					check_item = 0;
					deaths++;
				}
				else if (map2[oldy][(oldx / 2) + 1] != 2 && map2[oldy][(oldx / 2) + 1] != 6 &&
					map2[oldy][(oldx / 2) + 1] != 3 && map2[oldy][(oldx / 2) + 1] != 11) {
					if (map2[oldy][(oldx / 2) + 1] == 8 && check_item == 1) { // 아이템을 먹고 포인트에 가면 ROUND3으로 이동
						goto ROUND3;
					}
					if (map2[oldy][oldx / 2 + 1] == 8 || map2[oldy][oldx / 2 + 1] == 88) {
						newx = oldx + 2;
						map2[oldy][oldx / 2] = 8;
						map2[oldy][oldx / 2 + 1] = 99;
					}
					else if (map2[oldy][oldx / 2 + 1] == map2[10][12] || map2[oldy][oldx / 2 + 1] == map2[11][12] ||
						map2[oldy][oldx / 2 + 1] == map2[12][12]) {
						newx = oldx + 2;
						map2[oldy][oldx / 2] = 88;
						map2[oldy][oldx / 2 + 1] = 99;
					}
					else {
						newx = oldx + 2;
						map2[oldy][oldx / 2] = 0;
						map2[oldy][(oldx / 2) + 1] = 99;
					}
				}
				break;
			}

			oldx = newx; // 마지막 위치를 기억한다.
			oldy = newy;
			keep_moving = 0;
		}
		move_block2();
		show_map(map2);
		Sleep(70); // Delay를 줄이면 속도가 빨라진다.
	}
ROUND3:
	ROUND = 3;
	newx = oldx = 28;
	newy = oldy = 4;
	removeCursor();
	cls(CYAN2, CYAN2);
	init_block3();
	//textcolor(BLACK, WHITE);
	ch = 0; // 초기값 정지상태
	keep_moving = 0;
	while (1) {
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			if (ch == ESC) {
				/*gotoxy(28, 8); printf("┏━━━━━━━━━━━┓");
				gotoxy(28, 9); printf("┃       일시정지       ┃");
				gotoxy(28, 10); printf("┃━━━━━━━━━━━┃");
				gotoxy(28, 11); printf("┃   계속하기 : Enter   ┃");
				gotoxy(28, 12); printf("┃   끝내기   : ESC     ┃");
				gotoxy(28, 13); printf("┗━━━━━━━━━━━┛");
				while (1) {
					if (kbhit() == 1) {
						esc = getch();
						if (esc == ESC) {
							return 0;
						}
						else if (esc == '\r') {
							break;
						}
					}
				}*/
				break;
			}
			if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
				// 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
				ch = getch();
				switch (ch) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:
					keep_moving = 1;
					break;
				default: // 방향키가 아니면 멈춘다
					keep_moving = 0;
				}
			}
		}
		if (keep_moving) { // 움직이고 있으면	

			switch (ch) {
			case UP:
				if (map3[oldy - 1][oldx / 2] == 10) { // 장애물에 충돌하면
					if (save == 0) { // 세이브가 0일때
						map3[oldy][oldx / 2] = 0; // 이전 위치 지우고 시작 위치로 초기화
						newx = 28;
						newy = 4;
						map3[newy][newx / 2] = 99;
						deaths++; // 데스 수 증가
					}
					else { // 세이브가 1일때
						map3[oldy][oldx / 2] = 0; // 이전 위치 지우고 세이브 위치로 초기화
						newx = 38;
						newy = 20;
						map3[newy][newx / 2] = 99;
						deaths++;
						check_item3 = 0; // 아이템도 다시 생성
					}
				}
				else if (map3[oldy - 1][oldx / 2] != 1 && map3[oldy - 1][oldx / 2] != 5 && // 궤선을 만나지 않을때만 이동 가능
					map3[oldy - 1][oldx / 2] != 6) {
					if (map3[oldy - 1][oldx / 2] == 18 && check_item3 == 2) { // 아이템을 먹고 포인트에 가면 4라운드로 이동
						goto ROUND4;
					}
					if (map3[oldy - 1][oldx / 2] == 8 || map3[oldy - 1][oldx / 2] == 80) { // 세이브존일때
						newy = oldy - 1;
						map3[oldy][oldx / 2] = 8; //이동하면서 초록색 배경 그려줌
						map3[newy][oldx / 2] = 99;
					}
					else {
						newy = oldy - 1;
						map3[oldy][oldx / 2] = 0; // 원래의 위치 지우고
						map3[newy][oldx / 2] = 99; // 새로운 위치에 저장
					}
				}
				break;
			case DOWN:
				if (map3[oldy + 1][oldx / 2] == 10) { // 장애물에 충돌하면
					if (save == 0) {
						map3[oldy][oldx / 2] = 0; // 이전 위치 지우고 시작 위치로 초기화
						newx = 28;
						newy = 4;
						map3[newy][newx / 2] = 99;
						deaths++;
					}
					else {
						map3[oldy][oldx / 2] = 0; // 이전 위치 지우고 세이브 위치로 초기화
						newx = 38;
						newy = 20;
						map3[newy][newx / 2] = 99;
						deaths++;
						check_item3 = 0;
					}
				}
				else if (map3[oldy + 1][oldx / 2] != 4 && map3[oldy + 1][oldx / 2] != 3 && // 궤선을 만나지 않을때만 이동 가능
					map3[oldy + 1][oldx / 2] != 1) {
					if (map3[oldy + 1][oldx / 2] == 8 || map3[oldy + 1][oldx / 2] == 88 || // 세이브존일때 
						map3[oldy + 1][oldx / 2] == 80) {
						newy = oldy + 1;
						map3[oldy][oldx / 2] = 8; // 이동하면서 초록색 배경 그려줌
						map3[newy][oldx / 2] = 99;
					}
					else if (map3[oldy + 1][oldx / 2] == map3[7][12]) { // 캐릭터가 map3 초기 세이브존에서 내려올 때
						newy = oldy + 1;
						map3[oldy][oldx / 2] = 88;
						map3[newy][oldx / 2] = 99;
					}
					else {
						newy = oldy + 1;
						map3[oldy][oldx / 2] = 0;
						map3[newy][oldx / 2] = 99;
					}
				}
				break;
			case LEFT:
				if (map3[oldy][(oldx / 2) - 1] == 9) { // 왼쪽 아이템을 먹으면 사라지고 체크 변수 1로 변경
					map3[oldy][(oldx / 2) - 1] = 0;
					check_item3 = 1;
				}
				if (map3[oldy][oldx / 2 - 1] == 10) { // 장애물에 충돌하면
					if (save == 0) {
						map3[oldy][oldx / 2] = 0;
						newx = 28;
						newy = 4;
						map3[newy][newx / 2] = 99;
						deaths++;
					}
					else {
						map3[oldy][oldx / 2] = 0;
						newx = 38;
						newy = 20;
						map3[newy][newx / 2] = 99;
						deaths++;
						check_item3 = 0;
					}
				}
				else if (map3[oldy][(oldx / 2) - 1] != 2 && map3[oldy][(oldx / 2) - 1] != 5 && // 궤선
					map3[oldy][(oldx / 2) - 1] != 4) {
					if (map3[oldy][oldx / 2 - 1] == 8 || map3[oldy][oldx / 2 - 1] == 88 ||
						map3[oldy][oldx / 2 - 1] == 80) { // 세이브존이면
						newx = oldx - 2;
						map3[oldy][oldx / 2] = 8;
						map3[19][17] = 88;
						map3[20][17] = 88;
						map3[21][17] = 88;
						map3[19][21] = 88;
						map3[20][21] = 88;
						map3[21][21] = 88;
						map3[oldy][oldx / 2 - 1] = 99;
					}
					else {
						newx = oldx - 2;
						map3[oldy][oldx / 2] = 0;
						map3[oldy][(oldx / 2) - 1] = 99;
					}
				}
				break;
			case RIGHT:
				if (map3[oldy][(oldx / 2) + 1] == 9) { // 오른쪽 아이템을 먹으면 사라지고 체크 변수 2로 변경
					map3[oldy][(oldx / 2) + 1] = 0;
					check_item3 = 2;
				}
				if (map3[oldy][oldx / 2 + 1] == 10) { // 장애물에 충돌하면
					if (save == 0) {
						map3[oldy][oldx / 2] = 0;
						newx = 28;
						newy = 4;
						map3[newy][newx / 2] = 99; // 시작 위치
						deaths++;
					}
					else {
						map3[oldy][oldx / 2] = 0;
						newx = 38;
						newy = 20;
						map3[newy][newx / 2] = 99; // 시작 위치
						deaths++;
						check_item3 = 0;
					}
				}
				else if (map3[oldy][(oldx / 2) + 1] != 2 && map3[oldy][(oldx / 2) + 1] != 6 &&
					map3[oldy][(oldx / 2) + 1] != 3) {
					if (map3[oldy][oldx / 2 + 1] == 8 || map3[oldy][oldx / 2 + 1] == 88 ||
						map3[oldy][oldx / 2 + 1] == 80) {
						if (map3[oldy][oldx / 2 + 1] == 80) { // 세이브존일때
							save = 1;
						}
						newx = oldx + 2;
						map3[oldy][oldx / 2] = 8; // 전의 위치를 초록색으로
						map3[19][17] = 88;
						map3[20][17] = 88;
						map3[21][17] = 88;
						map3[19][21] = 88;
						map3[20][21] = 88;
						map3[21][21] = 88;
						map3[oldy][oldx / 2 + 1] = 99;
					}

					else {
						newx = oldx + 2;
						map3[oldy][oldx / 2] = 0;
						map3[oldy][(oldx / 2) + 1] = 99;
					}
				}
				break;
			}
			map3[5][26] = 18; // 아이템을 안먹고 포인트에 간 경우 포인트의 값이 없어지는 것을 방지
			oldx = newx; // 마지막 위치를 기억한다.
			oldy = newy;
			keep_moving = 0;
		}
		move_block3();
		show_map(map3);
		Sleep(300); // Delay를 줄이면 속도가 빨라진다.
	}
ROUND4:
	ROUND = 4;
	newx = oldx = 8;
	newy = oldy = 20;
	removeCursor();
	cls(WHITE, BLACK);
	init_block4();
	textcolor(BLACK, WHITE);
	ch = 0; // 초기값 정지상태
	keep_moving = 0;
	while (1) {
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch(); // key 값을 읽는다
			if (ch == ESC) {
				gotoxy(28, 8); printf("┏━━━━━━━━━━━┓");
				gotoxy(28, 9); printf("┃       일시정지       ┃");
				gotoxy(28, 10); printf("┃━━━━━━━━━━━┃");
				gotoxy(28, 11); printf("┃   계속하기 : Enter   ┃");
				gotoxy(28, 12); printf("┃   끝내기   : ESC     ┃");
				gotoxy(28, 13); printf("┗━━━━━━━━━━━┛");
				while (1) {
					if (kbhit() == 1) {
						esc = getch();
						if (esc == ESC) {
							return 0;
						}
						else if (esc == '\r') {
							break;
						}
					}
				}
			}
			if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
				// 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
				ch = getch();
				switch (ch) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:
					keep_moving = 1;
					break;
				default: // 방향키가 아니면 멈춘다
					keep_moving = 0;
				}
			}
		}
		if (keep_moving) { // 움직이고 있으면	

			switch (ch) {
			case UP:
				if (map4[oldy - 1][oldx / 2] == 9) { // 아이템을 먹으면 사라짐
					map4[oldy - 1][oldx / 2] = 0;
					check_item = 1;
				}
				if (map4[oldy - 1][oldx / 2] == 90) { // 키를 먹으면
					map4[oldy - 1][oldx / 2] = 0;
					map4[3][19] = 51;
					map4[4][19] = 51;
					map4[5][19] = 51;
					map4[3][20] = 51;
					map4[4][20] = 51;
					map4[5][20] = 51;
					check_key = 1;
				}
				if (map4[oldy - 1][oldx / 2] == 10) { // 장애물에 충돌하면
					map4[oldy][oldx / 2] = 0;
					newx = 8;
					newy = 20;
					map4[newy][newx / 2] = 99;
					map4[3][19] = 50;
					map4[4][19] = 50;
					map4[5][19] = 50;
					map4[3][20] = 50;
					map4[4][20] = 50;
					map4[5][20] = 50;
					map4[11][11] = 90;
					check_item = 0;
					check_key = 0;
					deaths++;
				}
				else if (map4[oldy - 1][oldx / 2] != 1) { // 궤선을 만나지 않을때만 이동 가능
					if (map4[oldy - 1][oldx / 2] == 8 || map4[oldy - 1][oldx / 2] == 88) {
						newy = oldy - 1;
						map4[oldy][oldx / 2] = 8;
						map4[18][3] = 88;
						map4[18][4] = 88;
						map4[18][5] = 88;
						map4[newy][oldx / 2] = 99;
					}
					else {
						if (check_key == 1) {
							map4[3][19] = 51;
							map4[4][19] = 51;
							map4[5][19] = 51;
							map4[3][20] = 51;
							map4[4][20] = 51;
							map4[5][20] = 51;
						}
						newy = oldy - 1;
						map4[oldy][oldx / 2] = 0; // 원래의 위치 지우고
						map4[newy][oldx / 2] = 99; // 새로운 위치에 저장
					}
				}
				break;
			case DOWN:
				if (map4[oldy + 1][oldx / 2] == 9) {// 아이템을 먹으면 사라짐
					map4[oldy + 1][oldx / 2] = 0;
					check_item = 1;
				}
				if (map4[oldy + 1][oldx / 2] == 90) {
					map4[oldy + 1][oldx / 2] = 0;
					map4[3][19] = 51;
					map4[4][19] = 51;
					map4[5][19] = 51;
					map4[3][20] = 51;
					map4[4][20] = 51;
					map4[5][20] = 51;
					check_key = 1;
				}
				if (map4[oldy + 1][oldx / 2] == 10) { // 장애물에 충돌하면
					map4[oldy][oldx / 2] = 0;
					newx = 8;
					newy = 20;
					map4[newy][newx / 2] = 99;
					map4[3][19] = 50;
					map4[4][19] = 50;
					map4[5][19] = 50;
					map4[3][20] = 50;
					map4[4][20] = 50;
					map4[5][20] = 50;
					map4[11][11] = 90;
					check_item = 0;
					check_key = 0;
					deaths++;
				}
				else if (map4[oldy + 1][oldx / 2] != 1 && map4[oldy + 1][oldx / 2] != 4 &&
					map4[oldy + 1][oldx / 2] != 3) {
					if (map4[oldy + 1][oldx / 2] == 18) { // 포인트존에 가면 게임 종료
						goto CLEAR;
					}
					if (map4[oldy + 1][oldx / 2] == 8) {
						newy = oldy + 1;
						map4[oldy][oldx / 2] = 8;
						map4[18][3] = 88;
						map4[18][4] = 88;
						map4[18][5] = 88;
						map4[newy][oldx / 2] = 99;
					}
					else {
						if (check_key == 1) {
							map4[3][19] = 51;
							map4[4][19] = 51;
							map4[5][19] = 51;
							map4[3][20] = 51;
							map4[4][20] = 51;
							map4[5][20] = 51;
						}
						newy = oldy + 1;
						map4[oldy][oldx / 2] = 0;
						map4[newy][oldx / 2] = 99;
					}
				}
				break;
			case LEFT:
				if (map4[oldy][(oldx / 2) - 1] == 9) {// 아이템을 먹으면 사라짐
					map4[oldy][(oldx / 2) - 1] = 0;
					check_item = 1;
				}
				if (map4[oldy][oldx / 2 - 1] == 90) {
					map4[oldy][oldx / 2 - 1] = 0;
					map4[3][19] = 51;
					map4[4][19] = 51;
					map4[5][19] = 51;
					map4[3][20] = 51;
					map4[4][20] = 51;
					map4[5][20] = 51;
					check_key = 1;
				}
				if (map4[oldy][oldx / 2 - 1] == 10) { // 장애물에 충돌하면
					map4[oldy][oldx / 2] = 0;
					newx = 8;
					newy = 20;
					map4[newy][newx / 2] = 99;
					map4[3][19] = 50;
					map4[4][19] = 50;
					map4[5][19] = 50;
					map4[3][20] = 50;
					map4[4][20] = 50;
					map4[5][20] = 50;
					map4[11][11] = 90;
					check_item = 0;
					check_key = 0;
					deaths++;
				}
				else if (map4[oldy][(oldx / 2) - 1] != 2 && map4[oldy][(oldx / 2) - 1] != 5 &&
					map4[oldy][(oldx / 2) - 1] != 4) {
					if (map4[oldy][oldx / 2 - 1] == 8) {
						newx = oldx - 2;
						map4[oldy][oldx / 2] = 8;
						map4[18][3] = 88;
						map4[18][4] = 88;
						map4[18][5] = 88;
						map4[oldy][oldx / 2 - 1] = 99;
					}
					else {
						if (check_key == 1) {
							map4[3][19] = 51;
							map4[4][19] = 51;
							map4[5][19] = 51;
							map4[3][20] = 51;
							map4[4][20] = 51;
							map4[5][20] = 51;
						}
						newx = oldx - 2;
						map4[oldy][oldx / 2] = 0;
						map4[oldy][(oldx / 2) - 1] = 99;
					}
				}
				break;
			case RIGHT:
				if (map4[oldy][(oldx / 2) + 1] == 9) {// 아이템을 먹으면 사라짐
					map4[oldy][(oldx / 2) + 1] = 0;
					check_item = 1;
				}
				if (map4[oldy][oldx / 2 + 1] == 90) {
					map4[oldy][oldx / 2 + 1] = 0;
					map4[3][19] = 51;
					map4[4][19] = 51;
					map4[5][19] = 51;
					map4[3][20] = 51;
					map4[4][20] = 51;
					map4[5][20] = 51;
					check_key = 1;
				}
				if (map4[oldy][oldx / 2 + 1] == 10 || map4[oldy][oldx / 2 + 1] == 50) { // 장애물에 충돌하면
					map4[oldy][oldx / 2] = 0;
					newx = 8;
					newy = 20;
					map4[newy][newx / 2] = 99; // 시작 위치
					map4[3][19] = 50;
					map4[4][19] = 50;
					map4[5][19] = 50;
					map4[3][20] = 50;
					map4[4][20] = 50;
					map4[5][20] = 50;
					map4[11][11] = 90;
					check_item = 0;
					check_key = 0;
					deaths++;
				}
				else if (map4[oldy][(oldx / 2) + 1] != 2 && map4[oldy][(oldx / 2) + 1] != 6 &&
					map4[oldy][(oldx / 2) + 1] != 3 && map4[oldy][(oldx / 2) + 1] != 11) {
					if (map4[oldy][oldx / 2 + 1] == 8) {
						newx = oldx + 2;
						map4[oldy][oldx / 2] = 8;
						map4[18][3] = 88;
						map4[18][4] = 88;
						map4[18][5] = 88;
						map4[oldy][oldx / 2 + 1] = 99;
					}
					else {
						if (check_key == 1) {
							map4[3][19] = 51;
							map4[4][19] = 51;
							map4[5][19] = 51;
							map4[3][20] = 51;
							map4[4][20] = 51;
							map4[5][20] = 51;
						}
						newx = oldx + 2;
						map4[oldy][oldx / 2] = 0;
						map4[oldy][(oldx / 2) + 1] = 99;
					}
				}
				break;
			}


			oldx = newx; // 마지막 위치를 기억한다.
			oldy = newy;
			keep_moving = 0;
		}
		move_block4();
		show_map(map4);
		Sleep(70); // Delay를 줄이면 속도가 빨라진다.
	}
CLEAR:
	while (1) {
		int c1, c2;
		do { // 색을 변경하면서 Game Over 출력
			c1 = rand() % 16;
			c2 = rand() % 16;
		} while (c1 == c2);
		textcolor(BLACK, WHITE);
		gotoxy(26, 8); printf("┏━━━━━━━━━━━━━┓");
		gotoxy(26, 9); printf("┃                          ┃");
		gotoxy(26, 10);
		printf("┃   "); textcolor(c1, c2); printf("    Game Clear    "); textcolor(BLACK, WHITE); printf("     ┃");
		gotoxy(26, 11); printf("┃                          ┃");
		gotoxy(26, 12); printf("┃                          ┃");
		gotoxy(26, 13); printf("┃      "); textcolor(WHITE, BLACK); printf(" DEATHS: % d ", deaths); textcolor(BLACK, WHITE);
		printf("        ┃");
		gotoxy(26, 14); printf("┃                          ┃");
		gotoxy(26, 15); printf("┃                          ┃");
		gotoxy(26, 16); printf("┗━━━━━━━━━━━━━┛");
		Sleep(300);
		if (kbhit()) {
			ch = getch();

			break;
		}
	}
}