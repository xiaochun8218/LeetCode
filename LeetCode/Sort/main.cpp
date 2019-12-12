#include <iostream>
using namespace std;

//≤Â»Î≈≈–Ú
void insertSort(int arr[], int len)
{
    for (int i = 1; i < len; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while ( (j >= 0) && (arr[j] > key) )
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

//—°‘Ò≈≈–Ú
void selectSort(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		int temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
	}
}

//√∞≈›≈≈–Ú
void bubbleSort(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i; j++)
		{
			int temp = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = temp;
		}
	}
}

//øÏÀŸ≈≈–Ú
int partition(int arr[], int left, int right)
{
	int key = arr[left];

	int i = left;
	int j = right;
	while (i != j)
	{
		while ((i < j) && (arr[j] >= key))
			j--;
		arr[i] = arr[j];
		while ((i < j) && (arr[i] <= key))
			i++;
		arr[j] = arr[i];
	}
	arr[i] = key;

	return i;
}

void quickSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int i = partition(arr, left, right);
		quickSort(arr, left, i - 1);
		quickSort(arr, i + 1, right);
	}
}

int main()
{
    return 0;
}