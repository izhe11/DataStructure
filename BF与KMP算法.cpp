#include <iostream>
#include <memory>

using namespace std;
int BF(string s, string t);
int KMP(string s, string t);
int* getNext(string str);

int main()
{
	string s = "ABCDCABDEFG";
	string t = "ABD";

	int pos = KMP(s, t);
	cout << pos << endl;
}

//BF算法
int BF(string s, string t)
{
	int i = 0;
	int j = 0;
	while (i < s.size() && j < t.size())
	{
		if (s[i] == t[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;    //i复位，从开始匹配的下一个继续
			j = 0;            //j置0，从头开始
		}
	}

	if (j == t.size())  //匹配成功
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}

//KMP算法
int KMP(string s, string t)
{
	int i = 0;
	int j = 0;

	//获取子串的next数组
	int* next = getNext(t);
	unique_ptr<int> ptr(next);    //相当于delete

	int masterSize = s.size();
	int subSize = t.size();
	while (i < masterSize && j < subSize)
	{
		if (-1 == j || s[i] == t[j])    //若首字母匹配失败，j=-1
		{
			i++;
			j++;
		}
		else
		{
			//kmp核心时i不回退，只回退j，j值取决于next数组
			j = next[j];
		}
	}

	if (j == t.size())  //匹配成功
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}

//kmp算法获取子串next
int* getNext(string str)
{
	int* next = new int[str.size()];
	int j = 0;     //j用来遍历子串
	int k = -1;    //k记录子串长度
	next[j] = k;

	while (j < str.size() - 1)
	{
		if (-1 == k || str[k] == str[j])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];    //k值回退，继续找公共前后缀
		}
	}
	return next;
}