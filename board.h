#pragma once
#include "MDUTD.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>
#ifdef MULTI_THREAD
#include <pthread.h>
#pragma comment(lib,"pthreadVC2.lib")
#endif
using namespace std;
#define CORE_VERSION 3
class Board
{
public:
	Board();//���ɿ�����
	Board(const Board& origin);//������캯��
	Board(int8(*source)[4]);//����������������
	~Board();//��������

	void Clear();//������̣���ʼ��ȫ������
	void Initialize();//�������������
	bool GameOver();//�ж���Ϸ�Ƿ����
	bool Move(int8 dir = 0);//�ƶ�����
	void AddNum();//�������
	void Print();//��ӡ����
	void ShortPrint(int playtime = 0);//��ӡ���н��
	void SaveToFile();//�������ļ�

	int8 GetValue(const COOR* const coor);//��ö���ֵ
	int  GetRealValue(int8 value);//���ʵ����ֵ
	int  GetScore();//��ȡ����
	short GetSteps();//��ȡ����
	int8(*GetBoard())[4];//��ȡ������ָ��

protected://���г�Ա�͵س�ʼ����C++11��
	int8 _board[4][4] = { 0 };//����
	int8 _emptycoornum = 16;//�ո��Ӹ���
	COOR* _emptycoorlist = nullptr;//�ո���������ͷָ��
	int  _score = 0;//����
	int8 _max = 0;//����������ƶ��������кϳ�������ж��޸ġ�
	short _steps = 0;//������Move����Ч����������޸ġ�

	//�����ƶ�����װ��
	bool _left();
	bool _right();
	bool _up();
	bool _down();
	void _setValue(COOR* const coor, int8 value);//��������ã������������
};
/*
	��C++���ʵ�ֹ����У������Ҫ����Ա�������ó�inline���������Ļ���
	��Ҫ�����ͷ�ļ�.h�ж��������������������Ӧ��.cpp�ļ��ж��塣
	C++������ֻ�ܽ�Դ����Ƕ�룬��û�취���ⲿ���н���������Ƕ�롣
*/
inline void Board::_setValue(COOR* const coor, int8 value)
{
	_board[coor->X][coor->Y] = value;
}
inline int8 Board::GetValue(const COOR* const coor)
{
	return _board[coor->X][coor->Y];
}
inline int  Board::GetRealValue(int8 value)
{
	return value ? 1 << value : 0;
}
inline int  Board::GetScore()
{
	return _score;
}
inline short Board::GetSteps()
{
	return _steps;
}
inline int8(*Board::GetBoard())[4]
{
	return _board;
}