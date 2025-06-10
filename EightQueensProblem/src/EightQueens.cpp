#include "EightQueens.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::getline;
#define LINE_IGNORE {string rubbish; getline(cin, rubbish);}

EightQueens::EightQueens() : size(8), grid(size, vector<bool>(size, false))
{}

void EightQueens::Menu()
{
	cout << "开始进行八皇后问题的求解算法演示..." << endl;
	cout << "[键入 Enter 键继续]" << endl;
	LINE_IGNORE

	// 不断读取用户输入，进行算法演示
	while (1)
	{
		cout << "请选择要演示的算法：" << endl;
		cout << "1. 递归回溯" << endl;
		cout << "2. 非递归回溯" << endl;
		cout << "3. 排列树的递归回溯" << endl;
		cout << "q. 退出" << endl;

		string choice;
		getline(cin, choice);
		if (choice == "1")
			Recursive_backtracking();
		else if (choice == "2")
			NonRecursive_backtracking();
		else if (choice == "3")
			RecursiveTree_backtracking();
		else if (choice == "q")
			break;
		else
			cout << "无效的选择，请重新输入。" << endl;

		cout << "[键入 Enter 键继续]" << endl;
		LINE_IGNORE
	}
	cout << "程序已退出。" << endl;
}

void EightQueens::Restore()
{
	grid.assign(size, vector<bool>(size, false));
}

void EightQueens::Recursive_backtracking()
{
	cout << "开始演示递归回溯算法..." << endl;



	// 算法演示完成后恢复棋盘
	this->Restore();
	cout << "递归回溯算法演示完成。" << endl;
}

void EightQueens::NonRecursive_backtracking()
{
	cout << "开始演示非递归回溯算法..." << endl;



	// 算法演示完成后恢复棋盘
	this->Restore();
	cout << "非递归回溯算法演示完成。" << endl;
}

void EightQueens::RecursiveTree_backtracking()
{
	cout << "开始演示排列树的递归回溯算法..." << endl;



	// 算法演示完成后恢复棋盘
	this->Restore();
	cout << "排列树的递归回溯算法演示完成。" << endl;
}