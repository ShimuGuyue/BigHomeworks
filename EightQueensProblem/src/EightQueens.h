#pragma once
#include <vector>

class EightQueens
{
private:	// 成员变量
	int size;
	std::vector<std::vector<bool>> grid;

public:		// 构造函数
	EightQueens();

public:		// 菜单
	void Menu();

};
