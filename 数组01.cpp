#include <cstring>
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

class Array
{
public:
	Array(int size = 10) : mCur(0), mCap(size)  //初始化参数mCur=0，mCap_=size
	{
		mpArr = new int[mCap]();           //初始化数组为0
	}
	~Array()
	{
		delete[] mpArr;
		mpArr = nullptr;    //使mpArr为空指针，避免野指针
	}

public:
	void push_back(int val)   //末尾增加元素
	{
		if (mCur == mCap)     //若数组已满，则扩容
		{
			expand(2 * mCap);
		}
		mpArr[mCur] = val;    //mCur即为末尾元素的下一个元素下标
		mCur++;
	}
	void pop_back()           //末尾删除元素
	{
		if (mCur == 0)
			return;
		mCur--;
	}
	void insert(int pos, int val)     //按位置插入元素
	{
		if (pos < 0 || pos > mCur)  //错误插入位置
			return;
		if (mCur == mCap)          //数组空间不足时需扩容
		{
			expand(2 * mCap);
		}

		//移动元素,插入位置之后的元素往后移一位
		for (int i = mCur - 1; i >= pos; i--)
		{
			mpArr[i + 1] = mpArr[i];
		}
		mpArr[pos] = val;
		mCur++;         //插入元素后有效元素+1
	}
	void erase(int pos)               //删除指定位置(下标)元素
	{
		if (pos < 0 || pos > mCur)
		{
			return;
		}
		//移动元素
		for (int i = pos + 1; i < mCur; i++)
		{
			mpArr[i - 1] = mpArr[i];
		}
		mCur--;
	}
	int find(int val)                //查询元素位置
	{
		for (int i = 0; i < mCur; i++)
		{
			if (mpArr[i] == val)
				return i;
		}
		return -1;
	}
	void show()const               //打印数组
	{
		for (int i = 0; i < mCur; i++)
		{
			cout << mpArr[i] << " ";
		}
		cout << endl;
	}

private:
	void expand(int size)      //数组扩容
	{
		//1.开辟新内存空间
		int* p = new int[size]; 
		//2.将数组元素复制到新内存中
		memcpy(p, mpArr, sizeof(int) * mCap);
		//3.释放旧内存
		delete[] mpArr;

		mpArr = p;
		mCap = size;
	}

private:
	int* mpArr;    //指向可扩容数组内存
	int mCap;      //数组容量
	int mCur;      //数组有效元素个数
};

int main()
{
	Array arr;
	srand(time(0));

	for (int i = 0; i < 10; i++)
	{
		arr.push_back(rand() % 100);
	}

	arr.show();
	arr.pop_back();
	arr.show();
	arr.erase(4);
	arr.show();
}