#include "MDUTD.h"
#include "board.h"
#include <cstdio>
using std::printf;
class Board;
/*
	�����������������������һ����Ĳ�ͬ�����Ǵ�����������ڵķ������ƣ�
	ֻҪͬ��һ����Ϳ��Բ�������ͬһ����Ĳ�ͬ������Ϊ�������캯������ĳ�Ա������
	��ֵ�������ڸ����У�������Ȩ�޷���˽�����ݳ�Ա��
*/

/*������������Ϊ����/������������һ��Ϊ���ɿ����̣��ڶ���Ϊ�������캯����������Ϊ����������*/
Board::Board()
{
	COOR* ptr = nullptr;
	loop_control i, j;
	ptr = this->_emptycoorlist = new COOR[this->_emptycoornum];
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			ptr->X = i;
			ptr->Y = j;
			ptr++;
		}
}
Board::Board(const Board& origin)
{
	loop_control i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			this->_board[i][j] = origin._board[i][j];
	this->_emptycoornum = origin._emptycoornum;
	this->_max = origin._max;
	this->_steps = origin._steps;
	this->_emptycoorlist = new COOR[this->_emptycoornum];
	for (i = 0; i < _emptycoornum; i++)
		this->_emptycoorlist[i] = origin._emptycoorlist[i];//���
}
Board::Board(int8(*source)[4])
{
	loop_control i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			_board[i][j] = source[i][j];
			if (_board[i][j])_emptycoornum--;
			if (_board[i][j] > _max)_max = _board[i][j];
		}
	_emptycoorlist = new COOR[_emptycoornum];
	COOR* ptr = _emptycoorlist;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (!_board[i][j]) { ptr->X = i; ptr->Y = j; ptr++; }
}
Board::~Board()
{
	delete[] _emptycoorlist;
}

void Board::Clear()
{
	delete[] _emptycoorlist;
	COOR* ptr = nullptr;
	loop_control i, j;
	_max = _steps = _score = 0;
	_emptycoornum = 16;
	ptr = this->_emptycoorlist = new COOR[16];
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			_board[i][j] = 0;
			ptr->X = i; ptr->Y = j;
			ptr++;
		}
}
void Board::Initialize()
{
	AddNum();
	AddNum();
}
void Board::Print()
{
	loop_control i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
			if (_board[i][j])printf("|%6d|", GetRealValue(_board[i][j]));
			else printf("|      |");
		putchar('\n');
	}
	printf("steps=%6d     score=%8d\n", _steps, _score);
}
void Board::ShortPrint(int playtime)
{
	if(playtime)printf("%d,\t%d\t%d\t%d\n", playtime, _max, _steps, _score);
	else printf("%d\t%d\t%d\n", _max, _steps, _score);
}
void Board::SaveToFile()
{
	const char path[] = "D:\\program files\\2048\\SR4\\rundata\\rundata4.2.0.2.xls";
	//const char path[50] = "D:\\program files\\2048\\SR4\\rundata\\rundata0.6.xls";
	FILE *fp;
	if ((fp = fopen(path, "a")) == NULL)
	{
		printf(">>�浵ʧ�ܣ�"); exit(1);
	}
	fprintf(fp, "%d\t%d\t%d\n",_max, _steps, _score);
	fclose(fp);
}
void Board::AddNum()
{
	int8 rand_num = random(_emptycoornum), i = 0;
	COOR* coor = _emptycoorlist + rand_num;
	_setValue(coor, random(10) ? 1 : 2);
	_emptycoornum--;
	//���·������ꡣ
	for (i = rand_num + 1; i <= _emptycoornum; i++)//λ��
		_emptycoorlist[i - 1] = _emptycoorlist[i];
	//ע�⣬����λ������δ�ͷ�β���ռ䣬Ҳ����Ҫ����delete[]�����Զ�ȫ��ɾ����
}
bool Board::GameOver()
{
	if (_emptycoornum)return false;
	else
	{
		loop_control i = 0, j = 0;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				if (_board[i][j] == _board[i][j + 1] ||
					_board[i][j] == _board[i + 1][j])return false;
		for (i = 0, j = 3; i < 3; i++)
			if (_board[i][j] == _board[i + 1][j])return false;
		for (i = 3, j = 0; j < 3; j++)
			if (_board[i][j] == _board[i][j + 1])return false;
	}
	return true;
}

bool Board::Move(int8 dir)
{
	bool valid_move = false;
	switch (dir)
	{
	case LEFT:	valid_move = _left();	break;
	case RIGHT:	valid_move = _right();	break;
	case UP:	valid_move = _up();		break;
	case DOWN:	valid_move = _down();	break;
	default:							break;
	}
	if (valid_move)
	{
		_steps++;
		loop_control i, j;
		delete[] _emptycoorlist;
		//��ʱ_emptycoornum�Ѿ����£���ֻ�����������ڴ�ռ䣬��ɨ���������̼��ɡ�
		_emptycoorlist = new COOR[_emptycoornum];
		COOR* ptr = _emptycoorlist;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (!_board[i][j]) { ptr->X = i; ptr->Y = j; ptr++; }
	}
	return valid_move;
}
bool Board::_left()
{
	int8 i, j, k, p;
	bool move_flag = false, merge_flag = false;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			if (!_board[i][j])
			{
				for (k = p = 1; k + j < 4; k++)
					if (!_board[i][k + j])p++;
					else { move_flag = true; break; }
				if (p + j == 4)break;
				for (k = j + p; k <= 3; k++)_board[i][k - p] = _board[i][k];
				for (k = p; k > 0; k--)_board[i][4 - k] = 0;
			}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			if (_board[i][j] && _board[i][j] == _board[i][j + 1])
			{
				merge_flag = true;
				_emptycoornum++;
				_board[i][j] ++;
				if (_board[i][j] > _max)_max = _board[i][j];
				_score += GetRealValue(_board[i][j]);
				for (k = j + 2; k <= 3; k++)_board[i][k - 1] = _board[i][k];
				_board[i][3] = 0;
			}
	return move_flag || merge_flag;
}
bool Board::_right()
{
	int8 i, j, k, p;
	bool move_flag = false, merge_flag = false;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			if (!_board[i][3 - j])
			{
				for (k = p = 1; k + j < 4; k++)
					if (!_board[i][3 - k - j])p++;
					else { move_flag = true; break; }
				if (p + j == 4)break;
				for (k = j + p; k <= 3; k++)_board[i][3 - k + p] = _board[i][3 - k];
				for (k = p; k > 0; k--)_board[i][k - 1] = 0;
			}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			if (_board[i][3 - j] && _board[i][3 - j] == _board[i][2 - j])
			{
				merge_flag = true;
				_emptycoornum++;
				_board[i][3 - j] ++;
				if (_board[i][3 - j] > _max)_max = _board[i][3 - j];
				_score += GetRealValue(_board[i][3 - j]);
				for (k = j + 2; k <= 3; k++)_board[i][4 - k] = _board[i][3 - k];
				_board[i][0] = 0;
			}
	return move_flag || merge_flag;
}
bool Board::_up()
{
	int8 i, j, k, p;
	bool move_flag = false, merge_flag = false;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			if (!_board[j][i])
			{
				for (k = p = 1; k + j < 4; k++)
					if (!_board[k + j][i])p++;
					else { move_flag = true; break; }
				if (p + j == 4)break;
				for (k = j + p; k <= 3; k++)_board[k - p][i] = _board[k][i];
				for (k = p; k > 0; k--)_board[4 - k][i] = 0;
			}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			if (_board[j][i] && _board[j][i] == _board[j + 1][i])
			{
				merge_flag = true;
				_emptycoornum++;
				_board[j][i] ++;
				if (_board[j][i] > _max)_max = _board[j][i];
				_score += GetRealValue(_board[j][i]);
				for (k = j + 2; k <= 3; k++)_board[k - 1][i] = _board[k][i];
				_board[3][i] = 0;
			}
	return move_flag || merge_flag;
}
bool Board::_down()
{
	int8 i, j, k, p;
	bool move_flag = false, merge_flag = false;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			if (!_board[3 - j][i])
			{
				for (k = p = 1; k + j < 4; k++)
					if (!_board[3 - k - j][i])p++;
					else { move_flag = true; break; }
				if (p + j == 4)break;
				for (k = j + p; k <= 3; k++)_board[3 - k + p][i] = _board[3 - k][i];
				for (k = p; k > 0; k--)_board[k - 1][i] = 0;
			}

	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			if (_board[3 - j][i] && _board[3 - j][i] == _board[2 - j][i])
			{
				merge_flag = true;
				_emptycoornum++;
				_board[3 - j][i] ++;
				if (_board[3 - j][i] > _max)_max = _board[3 - j][i];
				_score += GetRealValue(_board[3 - j][i]);
				for (k = j + 2; k <= 3; k++)_board[4 - k][i] = _board[3 - k][i];
				_board[0][i] = 0;
			}
	return move_flag || merge_flag;
}