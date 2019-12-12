#include <iostream>
using namespace std;

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

int main()
{
    return 0;
}