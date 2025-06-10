#include "EightQueens.h"

#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;

EightQueens::EightQueens() : size(8), grid(size, vector<bool>(size, false))
{}

