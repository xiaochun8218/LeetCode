#include <iostream>
#include <vector>
using namespace std;

//插入排序
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

//希尔排序
void shellSort(int arr[], int len)
{
	int gap = len / 2;
	while (gap)
	{
		for (int i = gap; i < len; i++)
		{
			int key = arr[i];
			int j = i - gap;
			while ( (j >= 0) && (arr[j] > key) )
			{
				arr[j + gap] = arr[j];
				j -= gap;
			}
			arr[j + gap] = key;
		}
		gap /= 2;
	}
}

//选择排序
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

//堆排序
void adjustHeap(int arr[], int len, int nodePos)
{
	int left = 2 * nodePos + 1;
	int right = 2 * nodePos + 2;

	int maxPos = nodePos;
	if ( (left < len) && (arr[left] > arr[maxPos]) )
	{
		maxPos = left;
	}
	if ( (right < len) && (arr[right] > arr[maxPos]) )
	{
		maxPos = right;
	}

	if (maxPos != nodePos)
	{
		int tmp = arr[nodePos];
		arr[nodePos] = arr[maxPos];
		arr[maxPos] = tmp;

		adjustHeap(arr, len, maxPos);
	}
}

void heapSort(int arr[], int len)
{
	for (int i = (len - 1) / 2; i >= 0; i--)
	{
		adjustHeap(arr, len, i);
	}

	for (int i = len - 1; i >= 0; i--)
	{
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;

		adjustHeap(arr, i, 0);
	}
}

//冒泡排序
void bubbleSort(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i; j++)
		{
			if (arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//快速排序
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


//二路-归并排序
void merge(int arr[], int low, int mid, int high)
{
	int i = low, j = mid + 1;
	int k = 0;
	int *tmp;
	tmp = (int *)malloc((high - low + 1)*sizeof(int));

	while (i <= mid && j <= high)
	{
		if (arr[i] <= arr[j])
		{
			tmp[k] = arr[i];
			i++;
			k++;
		}
		else
		{
			tmp[k] = arr[j];
			j++;
			k++;
		}
	}

	while (i <= mid)
	{
		tmp[k] = arr[i];
		i++;
		k++;
	}
	while (j <= high)
	{
		tmp[k] = arr[j];
		j++;
		k++;
	}

	for (k = 0, i = low; i <= high; k++, i++)
	{
		arr[i] = tmp[k];
	}

	free(tmp);
}

void mergePass(int arr[], int len, int length)
{
	int i;
	for (i = 0; i + 2 * length - 1 < len; i = i + 2 * length)
	{
		merge(arr, i, i + length - 1, i + 2*length -1);
	}

	if (i + length - 1 < len)
	{
		merge(arr, i, i + length - 1, len - 1);
	}
}

void mergeSort(int arr[], int len)
{
	for (int length = 1; length < len; length = 2 * length)
	{
		mergePass(arr, len, length);
	}
}

//计数排序
void countSort(int arr[], int len)
{
	int *countArr = (int *)malloc(100 * sizeof(int));
	int *sortArr = (int *)malloc(len * sizeof(int));

	for (int key = 0; key < 100; key++)
	{
		countArr[key] = 0;
	}
	for (int i = 0; i < len; i++)
	{
		countArr[arr[i]]++;
	}

	for (int key = 0; key < 100; key++)
	{
		countArr[key] += countArr[key - 1];
	}

	for (int i = len - 1; i >= 0; i--)
	{
		int key = arr[i];
		int pos = countArr[key] - 1;
		sortArr[pos] = key;
		countArr[key]--;
	}

	for (int i = 0; i < len; i++)
	{
		arr[i] = sortArr[i];
	}

	free(countArr);
	free(sortArr);
}

//桶排序
struct ListNode 
{
	int data;
	ListNode *next;
	ListNode(int val)
		: data(val)
		, next(nullptr)
	{

	}
};

void insertNode(ListNode *head, int val)
{
	ListNode *newNode = new ListNode(val);
	ListNode *pre = head;
	ListNode *cur = head->next;

	while (cur && (cur->data < val) )
	{
		pre = cur;
		cur = cur->next;
	}
	pre->next = newNode;
	newNode->next = cur;
}

ListNode* mergeList(ListNode *headOne, ListNode *headTwo)
{
	ListNode *tmp = new ListNode(0);

	if (!headOne->next)
	{
		tmp = headTwo;
		return tmp;
	}
	if (!headTwo->next)
	{
		tmp = headOne;
		return tmp;
	}

	ListNode *p = headOne->next;
	ListNode *q = headTwo->next;
	ListNode *r = tmp;
	while (p && q)
	{
		if (p->data <= q->data)
		{
			r->next = p;
			r = r->next;
			p = p->next;	
		}
		else
		{
			r->next = q;
			r = r->next;
			q = q->next;
		}
	}

	if (p)
		r->next = p;
	if (q)
		r->next = q;

	return tmp;
}

void bucketSort(int arr[], int len)
{
	int nBucketNum = 10;
	vector<ListNode*> vBucketNode;

	for (int i = 0; i < len; i++)
	{
		int pos = arr[i] % nBucketNum;
		ListNode *head = vBucketNode.at(pos);
		insertNode(head, arr[i]);
	}

	ListNode *head = vBucketNode.at(0);
	for (int i = 1; i < nBucketNum; i++)
	{
		ListNode *headIn = vBucketNode.at(i);
		head = mergeList(head, headIn);
	}

	for (int i = 0; i < len; i++)
	{
		arr[i] = head->next->data;
		head = head->next;
	}
}

//基数排序radixSort
int getMaxElem(int arr[], int len)
{
	int maxElem = arr[0];
	for (int i = 1; i < len; i++)
	{
		if (arr[i] > maxElem)
		{
			maxElem = arr[i];
		}
	}
	return maxElem;
}

void countSortByExp(int arr[], int len, int exp)
{
	int *countArr = (int *)malloc(10 * sizeof(int));
	int *sortArr = (int *)malloc(10 * sizeof(int));

	for (int key = 0; key < 10; key++)
	{
		countArr[key] = 0;
	}
	for (int i = 0; i < len; i++)
	{
		int key = arr[i] / exp % 10;
		countArr[key]++;
	}
	for (int key = 0; key < 10; key++)
	{
		countArr[key] += countArr[key - 1];
	}
	for (int i = len - 1; i >= 0; i--)
	{
		int key = arr[i] / exp % 10;
		int pos = countArr[key] - 1;
		sortArr[pos] = arr[i];
		countArr[key]--;
	}

	for (int i = 0; i < len; i++)
	{
		arr[i] = sortArr[i];
	}

	free(countArr);
	free(sortArr);
}

void radixSort(int arr[], int len)
{
	int maxElem = getMaxElem(arr, len);
	for (int exp = 1; maxElem / exp > 0; exp = exp * 10)
	{
		countSortByExp(arr, len, exp);
	}
}


int main()
{
    return 0;
}