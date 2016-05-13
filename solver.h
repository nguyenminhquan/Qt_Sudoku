#ifndef SOLVER
#define SOLVER

#include <cstring>

int identical_row(char arr[9][9], int rowIndex, int collumnIndex);
int identical_collumn(char arr[9][9], int rowIndex, int collumnIndex);
int identical_block(char arr[9][9], int rowIndex, int collumnIndex);
void stepback(char arr[9][9], int &rowIndex, int &collumnIndex);
void solve(char arr[9][9]);

#endif // SOLVER
