#include <iostream>
using namespace std;

//N»Êºó
int nCount = 0;
bool check(int row, int col, int solution[])
{
	for (int r = 0; r < row; r++)
	{
		if ( (col == solution[r]) || (row - r == abs(col - solution[r])) )
		{
			return false;
		}
	}
	return true;
}

void backtracking(int n, int row, int solution[])
{
	if (row == n)
	{
		nCount++;
		return;
	}

	for (int col = 0; col < n; col++)
	{
		solution[row] = col;

		if (check(row, col, solution))
		{
			backtracking(n, row + 1, solution);
		}

		solution[row] = -1;
	}
}

int totalCount(int n)
{
	nCount = 0;
	backtracking(n, 0, new int[n]);
	return nCount;
}

int main()
{
	int n = 0;
	cin >> n;
	totalCount(n);
	return 0;
}