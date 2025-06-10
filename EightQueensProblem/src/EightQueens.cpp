#include "EightQueens.h"

#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;

EightQueens::EightQueens() : size(8), grid(size, vector<bool>(size, false))
{}

void EightQueens::Menu()
{
	cout << "开始进行八皇后问题的求解算法演示..." << endl;
	cout << "[键入 Enter 键继续]" << endl;
	{string rubbish; getline(cin, rubbish);}

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
		{
			cout << "开始演示递归回溯算法..." << endl;
			Recursive_backtracking();
		}
		else if (choice == "2")
		{
			cout << "开始演示非递归回溯算法..." << endl;
			NonRecursive_backtracking();
		}
		else if (choice == "3")
		{
			cout << "开始演示排列树的递归回溯算法..." << endl;
			RecursiveTree_backtracking();
		}
		else if (choice == "q")
		{
			cout << "正在退出演示..." << endl;
			cout << "程序已退出。" << endl;
			break;
		}
		else
		{
			cout << "无效的选择，请重新输入。" << endl;
		}

		cout << "[键入 Enter 键继续]" << endl;
		{string rubbish; getline(cin, rubbish);}
	}
}

void EightQueens::Restore()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			grid[i][j] = false;
		}
	}
}

void EightQueens::Recursive_backtracking()
{


	this->Restore();
}

void EightQueens::NonRecursive_backtracking()
{


	this->Restore();
}

void EightQueens::RecursiveTree_backtracking()
{


	this->Restore();
}