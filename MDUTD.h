#pragma once
#define LEFT 1
#define RIGHT 4
#define UP 2
#define DOWN 3
#define VOID 0
#define REV(x) (5-x)

#define START (-2)
#define OVER (-1)
#define ERROR (-1)

#define random(x) ((int)(x*rand()/(0x7fff+1.0F)))

typedef signed char int8;
typedef short int16;
typedef signed char loop_control;
typedef struct
{
	int8 X;//行标
	int8 Y;//列标
}COOR;
typedef struct
{
	int8 value;
	COOR coor;
}COOR_DATA;