#include "EightQueens.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
#include <sstream>
using std::stringstream;
#include <filesystem>
using std::filesystem::create_directories;
using std::filesystem::path;
#include <iomanip>
using std::setw;
using std::setfill;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::to_string;
using std::getline;
#define LINE_IGNORE {string rubbish; getline(cin, rubbish);}
#include <stack>
using std::stack;

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
			PermutationTree_backtracking();
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
	cout << "开始进行递归回溯算法..." << endl;

	// 递归回溯算法的核心逻辑
	// 使用四个数组来记录每一行、每一列和两条对角线上当前放置的皇后数量
	vector<int> rows(size);
	vector<int> cols(size);
	vector<int> diag_left (2 * size - 1);
	vector<int> diag_right(2 * size - 1);
	int ans = 0; // 解的数量
	auto Dfs = [this, &rows, &cols, &diag_left, &diag_right, &ans](auto &&Dfs, int i, int j, int count_queen) -> void
	{

		// 如果所有格子都被判断过，结束递归搜索，返回答案
		if (i == size)
		{
			// 如果正好放置了八个皇后，解的数量加一
			if (count_queen == size)
			{
				++ans;
				// 打印当前棋盘到文件

				stringstream file_path; 
				file_path << "../output/solutions/RecursiveBacktracking/" << setw(3) << setfill('0') << ans << ".txt";
				Print(file_path.str());
			}
			return;
		}

		/*
		对于每个位置，分成放置皇后和不放置皇后两种情况进行递归求解
		*/

		// 如果当前位置不放置皇后，直接进入下一个位置
		j + 1 < size ? Dfs(Dfs, i, j + 1, count_queen) : Dfs(Dfs, i + 1, 0, count_queen);

		// 如果当前位置放置皇后，检查是否满足条件，满足条件则进入下一个位置
		if (rows[i] || cols[j] || diag_left[i + j] || diag_right[size - (i - j)])
			return;
		// 在棋盘上放置皇后，更新相关状态
		grid[i][j] = true;
		++rows[i];
		++cols[j];
		++diag_left[i + j];
		++diag_right[size - (i - j)];
		// 进入下一个位置
		j + 1 < size ? Dfs(Dfs, i, j + 1, count_queen + 1) : Dfs(Dfs, i + 1, 0, count_queen + 1);
		// 回溯，撤销放置皇后操作，恢复相关状态
		grid[i][j] = false;
		--rows[i];
		--cols[j];
		--diag_left[i + j];
		--diag_right[size - (i - j)];
	};
	// 执行递归回溯算法
	Dfs(Dfs, 0, 0, 0);

	// 输出结果
	cout << "递归回溯算法找到的解的数量为：" << ans << endl;

	// 算法演示完成后恢复棋盘
	this->Restore();
	cout << "递归回溯算法完成，所有可行解已被输出到文件。" << endl;
}

void EightQueens::NonRecursive_backtracking()
{
	// 正常人不会用这种垃圾算法……
	cout << "开始演示非递归回溯算法..." << endl;

	// 使用四个数组来记录每一行、每一列和两条对角线上当前放置的皇后数量
	vector<int> rows(size);
	vector<int> cols(size);
	vector<int> diag_left (2 * size - 1);
	vector<int> diag_right(2 * size - 1);

	struct Data 
	{
	    int i, j;        // 当前位置 (i,j)
	    int count;       // 到目前为止已放置的皇后数
	    int branch;      // 下一个要尝试的分支：0=跳过，1=放置，2=完成回退
	    bool placed;     // 本层是否放置过皇后，用于回退时恢复状态
	};

	int ans = 0;
	stack<Data> stk;
	stk.push({0, 0, 0, 0, false});
	while (!stk.empty())
	{
		auto &[i, j, count, branch, placed] = stk.top();
		if (i == size)
		{
			if (count == size)
			{
				++ans;
				stringstream file_path;
				file_path << "../output/solutions/NonRecursiveBacktracking/" << setw(3) << setfill('0') << ans << ".txt";
				Print(file_path.str());
			}
			stk.pop();
			continue;
		}
		// 计算下一个位置
		int next_i, next_j;
		j + 1 == size ?
			(next_i = i + 1, next_j = 0) :
			(next_i = i, next_j = j + 1);
		if (branch == 0)
		{
			// 分支 0：不在 (i,j) 放皇后，直接“递归”到下一个位置
			branch = 1;
			stk.push({next_i, next_j, count, 0, false});
		}
		else if (branch == 1)
		{
			// 分支 1：尝试在 (i,j) 放皇后
			branch = 2;
			if (rows[i] || cols[j] || diag_left[i + j]  ||diag_right[size - (i - j)])
				continue;
			// 放置皇后，更新状态
			grid[i][j] = true;
			++rows[i];
			++cols[j];
			++diag_left[i + j];
			++diag_right[size - (i - j)];
			placed = true;
			// 进入下一位置
			stk.push({next_i, next_j, count + 1, 0, false});
		}
		else
		{
			// 分支 2：两种尝试都结束，执行回退
			if (placed)
			{
				// 如果本层放过皇后，则撤销放置
				grid[i][j] = false;
				--rows[i];
				--cols[j];
				--diag_left[i + j];
				--diag_right[size - (i - j)];
			}
			stk.pop();
		}
	}

	cout << "非递归回溯算法找到的解的数量为：" << ans << endl;
	this->Restore();
	cout << "非递归回溯算法演示完成。" << endl;
}

void EightQueens::PermutationTree_backtracking()
{
    cout << "开始演示排列树的递归回溯算法..." << endl;

    // 列索引初始为 0,1,2,...,size-1，后续通过 swap 就地生成排列
    std::vector<int> cols(size);
    for (int i = 1; i < size; ++i)
	{
		cols[i] = i;
	}

    // 斜线冲突标记
    vector<int> diag_left (2 * size - 1);    // i + j
    vector<int> diag_right(2 * size - 1, 0);   // j - i + (size - 1)

    int ans = 0;
	// 递归搜索：row 表示当前要在第 row 行放置皇后
	auto dfs = [this, &cols, &diag_left, &diag_right, &ans](auto &&dfs, int row)
	{
		if (row == size)
		{
			++ans;
			std::stringstream file_path;
			file_path << "../output/solutions/PermutationTree_backtracking/" << std::setw(3) << std::setfill('0') << ans << ".txt";
			Print(file_path.str());
			return;
		}

		for (int i = row; i < size; ++i)
		{
			// 将第 i 个候选列交换到 row 位置，构造第 row 行的列号
			std::swap(cols[row], cols[i]);
			int col = cols[row];
			// 冲突检测：同列通过 permutation 本身就能避免，故只检测两条对角线即可
			if (diag_left[row + col] == 0 && diag_right[col - row + (size - 1)] == 0)
			{
				// 放置皇后
				grid[row][col] = true;
				++diag_left[row + col];
				++diag_right[col - row + (size - 1)];

				// 继续放下一行
				dfs(dfs, row + 1);

				// 回溯：撤销放置
				grid[row][col] = false;
				--diag_left[row + col];
				--diag_right[col - row + (size - 1)];
			}

			// 恢复交换，为下一个候选做准备
			std::swap(cols[row], cols[i]);
		}
	};

    dfs(dfs, 0);

    cout << "递归回溯算法找到的解的数量为：" << ans << endl;
    this->Restore();
    cout << "排列树的递归回溯算法演示完成。" << endl;
}

void EightQueens::Print(std::string file_path)
{
	// 创建文件目录
	create_directories(path(file_path).parent_path());
	// 打印当前棋盘到指定文件
	ofstream fout(file_path);
	
	fout << "   1  2  3  4  5  6  7  8" << endl;
	for (int i = 0; i < size; ++i)
	{
		auto &v = grid[i];
		fout << i + 1 << " {";
		for (int j = 0; j < size; ++j)
		{
			bool b = v[j];
			if (j != 0)
				fout << ", ";
			fout << (b ? "Q" : "_");
		}
		fout << "}" << endl;
	}
	fout << endl;
	fout.close();
}