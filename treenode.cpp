#include "treenode.h"
float TreeNode::_weight[4] = { 0.5F,0.0F,0.5F,0.0F };

TreeNode::TreeNode(const Board & origin) :Board(origin)
{
	_eval();
}

TreeNode::TreeNode(const TreeNode & origin, int8 dir) : Board(origin)
{
	this->_depth = origin._depth + 1;
	_root = (TreeNode*)&origin;
	if (Move(dir)) { AddNum(); _eval(); /*printf("New node created: depth=%d, ses=%.3f\n",this->_depth,this->_eval_score);*/ }
	else _depth = -1;
}

void TreeNode::_qsort(COOR_DATA data[], int8 start, int8 end)
{
	if (start >= end)return;
	loop_control low = start, high = end;
	int8 pivot = data[start].value;
	COOR_DATA medium;

	while (high > low)
	{
		while (data[high].value >= pivot)
		{
			high--;
			if (high <= low)break;
		}
		while (data[low].value <= pivot)
		{
			low++;
			if (high <= low)break;
		}

		if (high <= low)break;
		medium = data[low];
		data[low] = data[high];
		data[high] = medium;
	}

	medium = data[high];
	data[high] = data[start];
	data[start] = medium;

	_qsort(data, start, high);
	_qsort(data, high < low ? low : low + 1, end);
}

inline int8 TreeNode::_abs(int8 x)
{
	return x >= 0 ? x : -x;
}
inline float TreeNode::_abs(float x)
{
	return x >= 0 ? x : -x;
}

int8 TreeNode::_adj(COOR * const coor1, COOR * const coor2)
{
	int8 i, j;
	if (coor1->X == coor2->X)
	{
		i = coor1->Y - coor2->Y;
		if (_abs(i) == 1)return 1;
		else
		{
			if (i > 0) {
				for (j = coor2->Y + 1; j < coor1->Y; j++)
					if (_board[coor1->X][j])return 0;
			}
			else {
				for (j = coor1->Y + 1; j < coor2->Y; j++)
					if (_board[coor1->X][j])return 0;
			}
			return 1;
		}
	}
	else if (coor1->Y == coor2->Y)
	{
		i = coor1->X - coor2->X;
		if (_abs(i) == 1)return 1;
		else
		{
			if (i > 0) {
				for (j = coor2->X + 1; j < coor1->X; j++)
					if (_board[j][coor1->Y])return 0;
			}
			else {
				for (j = coor1->X + 1; j < coor2->X; j++)
					if (_board[j][coor1->Y])return 0;
			}
			return 1;
		}
	}
	else return 0;
}

void TreeNode::_eval()
{

	_parameter[0] = _emptycoornum / 16.0F;

	loop_control i = 0, j = 0, k = 0;
	int8 nonemptycoornum = 16 - _emptycoornum;
	//int8
	//	nonemptycoornum = 16 - _emptycoornum,
	//	largenum = 0,
	//	smallnum = 0,
	//	largenum_pos = 0,//当前较大数在序列中的首个位置
	//	smallnum_pos = 1,//当前较小数在序列中的首个位置
	//	nextnum_pos = 0,//当前比较小数还小的数在序列中的首个位置
	//	largenum_rank = 0,//较大数的排名
	//	smallnum_rank = 1;//较小数的排名
	//int16
	//	total_value = 0,//加权值
	//	total_weight = 0;//总权值

	//COOR_DATA* _sorted_coor_data = new COOR_DATA[nonemptycoornum];
	//for (i = 0; i < 4; i++)
	//	for (j = 0; j < 4; j++)
	//		if (_board[i][j])
	//		{
	//			_sorted_coor_data[k].value = _board[i][j];
	//			_sorted_coor_data[k].coor.X = i;
	//			_sorted_coor_data[k].coor.Y = j;
	//			k++;
	//		}

	//_qsort(_sorted_coor_data, 0, nonemptycoornum - 1);

	//while (smallnum_pos < nonemptycoornum)
	//{
	//	while (smallnum_pos < nonemptycoornum && largenum == _sorted_coor_data[smallnum_pos].value)smallnum_pos++;

	//	largenum = _sorted_coor_data[largenum_pos].value;
	//	smallnum = smallnum_pos < nonemptycoornum ? _sorted_coor_data[smallnum_pos].value : 0;

	//	nextnum_pos = smallnum_pos + 1;
	//	while (nextnum_pos < nonemptycoornum && smallnum == _sorted_coor_data[nextnum_pos].value)nextnum_pos++;

	//	for (i = largenum_pos; i < smallnum_pos; i++)
	//	{
	//		for (j = largenum_pos + 1; j < smallnum_pos; j++)
	//		{
	//			total_value += _adj(&_sorted_coor_data[i].coor, &_sorted_coor_data[j].coor)*(largenum_rank << 1);
	//			total_weight += largenum_rank << 1;
	//		}
	//		if (smallnum)for (; j < nextnum_pos; j++)
	//		{
	//			total_value += _adj(&_sorted_coor_data[i].coor, &_sorted_coor_data[j].coor)*(largenum_rank + smallnum_rank);
	//			total_weight += largenum_rank + smallnum_rank;
	//		}
	//	}

	//	largenum_pos = smallnum_pos;
	//	smallnum_pos = nextnum_pos;
	//	largenum_rank++;
	//	smallnum_rank++;
	//}
	//_parameter[1] = total_value / (float)total_weight;
	//delete[] _sorted_coor_data;
	_parameter[1] = 0.0F;

	int16
		C1_total_value = 0,//left-right
		C1_equal_value = 0,
		C1_total_weight = 0,
		C2_total_value = 0,//up-down
		C2_equal_value = 0,
		C2_total_weight = 0;
	float C1 = 0, C2 = 0;
	loop_control
		next_j = 1;

	//left-right
	for (i = 0; i < 4; i++)
		for (j = 0, next_j = 1; j < 3; j = next_j, next_j = j + 1)
		{
			while (!_board[i][next_j] && next_j < 3)next_j++;

			if (_board[i][j] > _board[i][next_j])C1_total_value += _board[i][j] + _board[i][next_j];
			else if (_board[i][j] < _board[i][next_j]) C1_total_value -= _board[i][j] + _board[i][next_j];
			else C1_equal_value += _board[i][j] + _board[i][next_j];

			C1_total_weight += _board[i][j] + _board[i][next_j];
		}
	C1 = (_abs((float)C1_total_value) + C1_equal_value) / (float)C1_total_weight;

	//up-down
	for (i = 0; i < 4; i++)
		for (j = 0, next_j = 1; j < 3; j = next_j, next_j = j + 1)
		{
			while (!_board[next_j][i] && next_j < 3)next_j++;

			if (_board[j][i] > _board[next_j][i])C2_total_value += _board[j][i] + _board[next_j][i];
			else if (_board[j][i] < _board[next_j][i]) C2_total_value -= _board[j][i] + _board[next_j][i];
			else C2_equal_value += _board[j][i] + _board[next_j][i];

			C2_total_weight += _board[j][i] + _board[next_j][i];
		}
	C2 = (_abs((float)C2_total_value) + C2_equal_value) / (float)C2_total_weight;

	_parameter[2] = (C1 + C2) / 2.0F;
	_parameter[3] = 0.0F;
	//int16
	//	D_total_value = 0,//left-right
	//	D_equal_value = 0,
	//	D_total_weight = 0;

	//if (C1 >= C2)
	//{
	//	_parameter[2] = C1;
	//	//up-down
	//	for (i = 0; i < 4; i++)
	//		for (j = 0, next_j = 1; j < 3; j = next_j, next_j = j + 1)
	//		{
	//			while (!_board[next_j][i] && next_j < 3)next_j++;

	//			if ((i % 2) && _board[j][i] > _board[next_j][i] ||
	//				(!(i % 2)) && _board[j][i] < _board[next_j][i])
	//				D_total_value += _board[j][i] + _board[next_j][i];
	//			else if (_board[j][i] == _board[next_j][i])D_equal_value += _board[j][i] + _board[next_j][i];
	//			else D_total_value -= _board[j][i] + _board[next_j][i];

	//			D_total_weight += _board[j][i] + _board[next_j][i];
	//		}
	//}
	//else
	//{
	//	_parameter[2] = C2;
	//	//left-right
	//	for (i = 0; i < 4; i++)
	//		for (j = 0, next_j = 1; j < 3; j = next_j, next_j = j + 1)
	//		{
	//			while (!_board[i][next_j] && next_j < 3)next_j++;

	//			if ((i % 2) && _board[i][j] > _board[i][next_j] ||
	//				(!(i % 2)) && _board[i][j] < _board[i][next_j])
	//				D_total_value += _board[i][j] + _board[i][next_j];
	//			else if (_board[i][j] == _board[i][next_j])D_equal_value += _board[i][j] + _board[i][next_j];
	//			else D_total_value -= _board[i][j] + _board[i][next_j];

	//			D_total_weight += _board[i][j] + _board[i][next_j];
	//		}
	//}
	//_parameter[3] = (_abs((float)D_total_value) + D_equal_value) / (float)D_total_weight;
	_eval_score =
		_parameter[0] * _weight[0] +
		//	_parameter[1] * _weight[1] +
		_parameter[2] * _weight[2];// +
	//	_parameter[3] * _weight[3];
}
