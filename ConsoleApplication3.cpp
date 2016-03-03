// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int map[4][4];

void print_map() {
	system("cls");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << map[i][j] << "    ";
		}
		cout << endl;
	}
}

void add_random() {
	int temp[4] = {
		2,2,2,4
	};
	int i = rand() % 4;
	int j = rand() % 4;
	int k = rand() % 4;

	if (map[i][j] == 0) {
		map[i][j] = temp[k];
	}
	else
	{
		add_random();
	}
}

int init() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			map[i][j] = 0;
		}
	}

	for (int i = 0; i < 2;i++){
		add_random();
	}

	print_map();
	return 0;
}

int * remove_zero(int * ss)
{
	vector<int> resized;
	vector<int>::iterator it;
	for (int i = 0; i < 4; i++) {
		int temp = ss[i];
		if (temp != 0) {
			resized.push_back(temp);
		}
	}
	if (resized.size() == 0) {
		int * result = new int[4]{
			0,0,0,0
		};
		return result;
	}

	for (it = resized.begin(); it < resized.end()-1; it++) {
		if (*it == *(it + 1)) {
			*it = (*it) * 2;
			*(it + 1) = 0;
		}
	}

	//清除所有0
	resized.erase(std::remove(resized.begin(), resized.end(), 0), resized.end());

	//补充0
	while (resized.size()<4) {
		resized.push_back(0);
	}
	int * temp = new int[4]{
		0,0,0,0
	};
	int i = 0;
	for (it = resized.begin(); it < resized.end()-1; it++) {
		temp[i] = *it;
		i++;
	}
	return temp;
}

void move_left() {
	for (int i = 0; i < 4; i++) {
		int * temp = remove_zero(map[i]);
		memcpy(map[i], temp, 4*sizeof(int));
	}
	add_random();
}

void move_right() {
	for (int i = 0; i < 4; i++) {
		std::reverse(std::begin(map[i]), std::end(map[i]));
		int * temp = remove_zero(map[i]);
		memcpy(map[i], temp, 4*sizeof(int));
		std::reverse(std::begin(map[i]), std::end(map[i]));
	}
	add_random();
}

void transpose() {
	for (int i = 0; i < 3; i++) {
		for (int j = i+1; j < 4; j++) {
			int temp = map[i][j];
			map[i][j] = map[j][i];
			map[j][i] = temp;
		}
	}
}

void move_up() {
	transpose();
	move_left();
	transpose();
	print_map();
}

void move_down() {
	transpose();
	move_right();
	transpose();
	print_map();
}

int main() {
	init();
	while (true) {
		char c = _gettche();
		if (c == 'h') {
			move_left();
			print_map();
		}
		else {
			if (c == 'l') {
				move_right();
				print_map();
			}
			else
			{
				if (c == 'k') {
					move_up();
				}
				else
				{
					if (c =='j')
					{
						move_down();
					}
				}
			}
		}

	}
	return 0;
}
