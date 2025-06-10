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

private:	// 内部运行指令
	// 每次执行算法后恢复棋盘
	void Restore();

private:	// 内部算法
	// 递归回溯
	void Recursive_backtracking();
	// 非递归回溯
	void NonRecursive_backtracking();
	// 排列树的递归回溯
	void RecursiveTree_backtracking();
};
