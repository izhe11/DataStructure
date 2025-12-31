#include <iostream>
#include <functional>
using namespace std;

//BST树（二叉树） 
template <typename T,typename Compare=less<T>>
class BSTree
{
public:
	BSTree():root_(nullptr){}    //构造函数
	~BSTree() {}

	//非递归插入操作
	void nonInsert(const T& val)          
	{
		if (root_ == nullptr)     //树为空，生成根节点
		{
			root_ = new Node(val);
			return;
		}
		//搜索插入位置，记录父节点
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				parent = cur;
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				//val与节点元素值相同，不插入
				return;
			}
		}
		//val插入到parent的孩子节点中
		if (val < parent->data_)
		{
			parent->left_ = new Node(val);
		}
		else
		{
			parent->right_ = new Node(val);
		}
	}
	//非递归删除操作
	void nonRemove(const T& val)
	{
		if (root_ = nullptr)   //树为空时
		{
			return;
		}

		Node* parent = nullptr;   //记录父节点位置
		Node* cur = root_;        //记录当前节点位置
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				parent = cur;
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				break;   //表示已找到待删除节点位置
			}
		}
		//未找到待删除节点
		if (cur == nullptr)
		{
			return;
		}
		//1.左右孩子都不为空的情况，存在左右节点
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			parent = cur;
			Node* pre = cur->left_;    //找到前驱节点（待删节点左边值最大的节点）
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;   //把前驱节点(pre)的值放到待删除节点处(cur)
			cur = pre;                 //cur指向前驱节点，之后只需删除pre即可
		}

		//2.左右孩子为空或有一个为空，存在1个或0个
		//把待删节点的孩子节点写入父节点，即可删除待删节点
		Node* child = cur->left_;
		if (child == nullptr)      //存在0个的情况
		{
			child = cur->right_;
		}

		if (parent == nullptr)
		{
			root_ = child;        //如果删除的是根节点，则把child作为根节点
		}
		else
		{
			if (parent->left_ == cur)  //存在1个的情况
			{
				parent->left_ = child;     //在左边
			}
			else
			{
				parent->right_ = child;    //在右边
			}
		}

		delete cur;                   //删除待删节点
	}
	//非递归查询元素
	bool nonQuery(const T& val)
	{
		Node* cur = root_;    //从根节点开始
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				return true;       //成功找到
			}
			else if (cur->data_ < val)
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		return false;              //未找到
	}
	//递归前序遍历 VLR
	void preOrder()
	{
		cout << "递归前序遍历：";
		preOrder(root_);
		cout << endl;
	}
	//递归中序遍历 LVR
	void midOrder()
	{
		cout << "递归中序遍历：";
		midOrder(root_);
		cout << endl;
	}
	//递归后序遍历 LRV
	void postOrder()
	{
		cout << "递归后序遍历：";
		postOrder(root_);
		cout << endl;
	}
	//递归层序遍历
	void levelOrder()
	{
		cout << "递归层序遍历：";
		int h = levelNumber();
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);
		}
		cout << endl;
	}
	//递归求二叉树层数
	int levelNumber()
	{
		return levelNumber(root_);
	}
	//递归求二叉数节点个数
	int nodeNumber()
	{
		return nodeNumber(root_);
	}

private:
	//节点定义
	struct Node
	{
		Node(T data=T()):data_(data),left_(nullptr),right_(nullptr){}        //初始化
		T data_;      //数据域
		Node* left_;  //左孩子
		Node* right_; //右孩子
	};
	//前序递归函数 VLR
	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";     //打印 V
			preOrder(node->left_);          //访问左孩子 L
			preOrder(node->right_);         //访问右孩子 R
		}
	}
	//中序递归函数 LVR
	void midOrder(Node* node)
	{
		if (node != nullptr)
		{
			midOrder(node->left_);       //访问左孩子 L
			cout << node->data_ << " ";  //打印 V
			midOrder(node->right_);      //访问右孩子 R
		}
	}
	//后序递归函数 LRV
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_);       //访问左孩子 L
			postOrder(node->right_);      //访问右孩子 R
			cout << node->data_ << " ";  //打印 V
		}
	}
	//层序递归函数
	void levelOrder(Node* node, int i)
	{
		if (node == nullptr)
			return;
		if (i == 0)
		{
			cout << node->data_ << " ";
			return;
		}
		levelOrder(node->left_, i - 1);
		levelOrder(node->right_, i - 1);
	}
	//求二叉数层数递归函数，从根节点开始计算，返回二叉树层数
	int levelNumber(Node* node)
	{
		if (node == nullptr)
			return 0;
		int left = levelNumber(node->left_);             //L 左节点   
		int right = levelNumber(node->right_);           //R 右节点
		return left > right ? left + 1 : right + 1;      //较大者为层数
	}
	//递归求二叉数节点个数，从根节点开始计算，返回二叉树节点个数
	int nodeNumber(Node* node)
	{
		if (node == nullptr)
			return 0;
		int left = nodeNumber(node->left_);               //L 左节点
		int right = nodeNumber(node->right_);             //R 右节点
		return left + right + 1;
	}
	Node* root_;      //指向根节点
};

int main()
{
	int arr[] = { 58,24,67,0,34,62,69,5 };
	BSTree <int> test;
	for (int v : arr)
	{
		test.nonInsert(v);
	}
	test.nonInsert(12);
	test.preOrder();
	test.midOrder();
	test.postOrder();
	test.levelOrder();

	return 0;
}