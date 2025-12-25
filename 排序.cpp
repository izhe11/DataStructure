#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;
void BubbleSort(int arr[], int size);
void SelectSort(int arr[], int size);
void InsertSort(int arr[], int size);
int Partation(int arr[], int left, int right);
void QuickSort(int arr[], int begin, int end);
void QuickSort(int arr[], int size);

int main()
{
	int arr[10];
	srand(time(0));

	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	QuickSort(arr,10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}

//冒泡排序
void BubbleSort(int arr[], int size)
{
	//处理次数，最后一次只剩一个元素需排序，故无需处理即size-1
	for (int i = 0; i < size - 1; i++)    
	{
		bool flag = false;		
		for (int j = 0; j < size - 1 - i; j++)  //每次处理的过程,每次处理后最后一个元素为最大值无需下一次处理
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = true;
			}
		}
		//如果没有进行数据交换(flag未置true)，则表面数据已有序
		if (!flag)
		{
			return;
		}
	}
}

//选择排序
void SelectSort(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int min = arr[i];   //初始最小值
		int k = i;          //最小值下标
		for (int j = i + 1; j < size; j++)
		{
			//找到最小值
			if (arr[j] < min)
			{
				min = arr[j];
				k = j;
			}
		}
		//把最小值交换
		if (k != i)
		{
			int temp = arr[i];
			arr[i] = arr[k];
			arr[k] = temp;
		}
	}
	
}

//插入排序
void InsertSort(int arr[], int size)
{
	for (int i = 1; i < size; i++)    //第一个元素无需排序
	{
		int val = arr[i];
		int j = i - 1;
		for (j; j >= 0; j--)
		{
			if (arr[j] <= val)
			{
				break;
			}
			arr[j + 1] = arr[j];     //大于val将较大者放后面
		}
		arr[j + 1] = val;
	}
}

//快速排序递归函数
void QuickSort(int arr[], int begin, int end)  //begin为左端，end为右端
{
	if (begin >= end)      //递归结束条件
	{
		return;
	}
	//if (end - begin <= 50)      //快速排序优化，当序列趋近有序时使用插入排序
	//{
	//	InsertSort(arr, begin, end);
	//	return;
	//}
	
	//根据基准数对[begin,ebd]进行排序分割处理
	int pos = Partation(arr, begin, end);
	//对基准数左边序列和右边序列分别再次进行快速排序
	QuickSort(arr, begin, pos - 1);     //左边序列
	QuickSort(arr, pos + 1, end);       //右边序列
}
//快速排序分割处理函数
int Partation(int arr[], int left, int right)
{
	//int val = arr[left];    //基准数
	//优化：基准数的选取，选择arr[left],arr[right],arr[(left+right)/2]中大小位于中间的值作为基准数
	int mid = (left + right) / 2;
	int baseNum = left;
	if ((arr[left] <= arr[mid] && arr[mid] <= arr[right]) || 
		                       (arr[left] >= arr[mid] && arr[mid] >= arr[right]))
	{
		baseNum = mid;
	}
	else if ((arr[left] <= arr[right] && arr[right] <= arr[mid]) ||
		                        (arr[left] >= arr[right] && arr[right] >= arr[mid]))
	{
		baseNum = right;
	}
	swap(arr[left], arr[mid]);       //将3数中位数交换到left处
	int val = arr[left];

	//快速排序处理
	while (left < right)
	{
		while (left < right && arr[right] > val)
		{
			right--;
		}
		if (left < right)
		{
			arr[left] = arr[right];
			left++;
		}

		while (left < right && arr[left] < val)
		{
			left++;
		}
		if (left < right)
		{
			arr[right] = arr[left];
			right--;
		}
	}
	//left=right的位置为存放基准数的位置,返回基准数位置（下标）
	arr[left] = val;
	return left; 
}
//快速排序接口
void QuickSort(int arr[], int size)
{
	//调用快速排序递归函数处理
	return QuickSort(arr, 0, size - 1);
}