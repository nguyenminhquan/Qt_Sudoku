#include "solver.h"

int identical_row(char arr[9][9], int rowIndex, int collumnIndex)
{
    for (int j = 0; j < 9; ++j)
        if (arr[rowIndex][collumnIndex] == arr[rowIndex][j] && collumnIndex != j && arr[rowIndex][collumnIndex]!='0')
            return 1;
    return 0;
}
int identical_collumn(char arr[9][9], int rowIndex, int collumnIndex)
{
    for (int i = 0; i < 9; ++i)
        if (arr[rowIndex][collumnIndex] == arr[i][collumnIndex] && rowIndex != i && arr[rowIndex][collumnIndex]!='0')
            return 1;
    return 0;
}
int identical_block(char arr[9][9], int rowIndex, int collumnIndex)
{
    for (int i = 0; i < 9; i += 3)
        for (int j = 0; j < 9; j += 3)
        {
            for (int ii = i; ii < i + 3; ++ii)
                for (int jj = j; jj < j + 3; ++jj)
                {
                    if (ii == rowIndex && jj == collumnIndex)
                    {
                        for (ii = i; ii < i + 3; ++ii)
                            for (jj = j; jj < j + 3; ++jj)
                                if (arr[ii][jj] == arr[rowIndex][collumnIndex] && ii != rowIndex && jj != collumnIndex && arr[rowIndex][collumnIndex]!='0')
                                    return 1;
                        return 0;
                    }
                }
        }
    return 0;
}

void stepback(char arr[9][9], int &rowIndex, int &collumnIndex)
{
    for (int i = rowIndex; i>-1; --i)
        for (int j = 8; j>-1; --j)
            if (arr[i][j] == '0' && (i != rowIndex || (i == rowIndex && j < collumnIndex)))
            {
                rowIndex = i;
                collumnIndex = j;
                return;
            }
}

void solve(char arr[9][9])
{
    char outter[9][9];
    memcpy(outter, arr, sizeof(char) * 9 * 9);
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
        {
            if (outter[i][j] == '0')
            {
                do
                {
                    while (1)
                    {
                        ++outter[i][j];
                        if (outter[i][j] > '9')
                        {
                            outter[i][j] = '0';
                            stepback(arr, i, j);
                        }
                        else break;
                    }
                } while (identical_row(outter, i, j) + identical_collumn(outter, i, j) + identical_block(outter, i, j) != 0);
            }
        }
    memcpy(arr, outter, sizeof(char) * 9 * 9);
}
