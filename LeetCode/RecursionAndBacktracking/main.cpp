#include <iostream>
using namespace std;

//汉诺塔
void move(int n, char x, char z)
{
    cout << "num:" << n  <<  "x-->z" << endl;
}

void hannoi(int n, char x, char y, char z)
{
    if (n == 1)
    {
        return;
    }

    hannoi(n - 1, x, z, y);
    move(n, x, z);
    hannoi(n - 1, y, x, z);
}

//N皇后
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


//二分查找
int binarySearch(int arr[], const int key, int low, int high)
{
    if (low > high)
    {
        return -1;
    }

    //用 mid = (low + high) / 2 会有溢出风险
    /*
      low  = 0100 0000 0000 0000 0000 0000 0000 0000 
      high = 0100 0000 0000 0000 0000 0000 0000 0000 

      low + high = 1000 0000 0000 0000 0000 0000 0000 0000 
      int 有符号位，符号位为1表示负数，负数在机器中以补码形式保存
      数值位 取反加一得：1000 0000 0000 0000 0000 0000 0000 0000 = 2147483648
      low + high = -2147483648
    */
    int mid = low + (high - low) / 2;
    if (arr[mid] == key)
    {
        return mid;
    }
    else if (arr[mid] < key)
    {
        return binarySearch(arr, key, low, mid - 1);
    }
    else
    {
        return binarySearch(arr, key, mid + 1, high);
    }
}

int main()
{
	int n = 0;
	cin >> n;
	totalCount(n);
	return 0;
}