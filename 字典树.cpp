#include <iostream>
#include <map>
#include <string>	
#include <vector>
using namespace std;

//trie字典树
class TrieTree
{
public:
	TrieTree() 
	{
		root_ = new TrieNode('\0', 0);   //根节点初始化
	}
	//字典树添加字符串
	void add(const string& word)
	{
		TrieNode* cur = root_;
		for (int i = 0; i < word.size(); i++)
		{
			auto childIt = cur->mapNode_.find(word[i]);
			if (childIt == cur->mapNode_.end())
			{
				//若没有相应字符则创建一个节点
				TrieNode* child = new TrieNode(word[i], 0);
				cur->mapNode_.emplace(word[i], child);      //新节点增加到map中
				cur = child;                                //cur后移
			}
			else
			{
				//若相应字符已存在则cur后移
				cur = childIt->second;
			}
		}

		//遍历完后cur指向word最后一个字符
		cur->freqs_++;
	}

	//字典树查找
	int query(const string& word)
	{
		TrieNode* cur = root_;
		for (int i = 0; i < word.size(); i++)
		{
			auto childIt = cur->mapNode_.find(word[i]);
			if (childIt == cur->mapNode_.end())
			{
				return 0;           //没有该单词
			}

			cur = childIt->second;  //存在，cur指向下一节点
		}
		return cur->freqs_;
	}

	//字典树前序遍历，递归
	void preOrder()
	{
		string word;
		vector<string> wordList;
		preOrder(root_, word, wordList);
		for (auto word : wordList)
			cout << word << endl;

	}

private:
	//节点定义
	struct TrieNode
	{
		TrieNode(char ch, int freqs) 
			: ch_(ch), freqs_(freqs) {}   //初始化构造
		char ch_;                         //节点储存的字符
		int freqs_;                       //以该节点结尾的单词出现的频率
		map<char, TrieNode*> mapNode_;    //子节点映射
	};

	TrieNode* root_;                     //根节点

	//前序遍历递归函数
	void preOrder(TrieNode* cur, string word, vector<string>& wordList)
	{
		if (cur != root_)
		{
			word.push_back(cur->ch_);        //遍历一个单词用word储存
			if (cur->freqs_ > 0)
			{
				//到达最后一个字符，即完成一个单词遍历
				wordList.emplace_back(word);        //所有单词用wordList储存
			}
		}
		//递归处理子节点
		for (auto pair : cur->mapNode_)
		{
			preOrder(pair.second, word, wordList);
		}
	}
};

int main()
{

	return 0;
}