#include "src/EightQueens.h"

#include <iostream>
#include <windows.h>

int main()
{
	// 将控制台输出编码设置为 UTF-8，使得中文能正确输出
	SetConsoleOutputCP(CP_UTF8);
	// 将 C++ 与 C 的输入输出流解除同步
	std::ios::sync_with_stdio(false);

	// 创建八皇后问题的实例并调用菜单函数
	EightQueens eightQueens;
	eightQueens.Menu();

	return 0;
}
