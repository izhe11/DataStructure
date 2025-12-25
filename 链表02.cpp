#include <iostream>

using namespace std;

//节点
struct Node
{
	Node(int data = 0) :data(data), next(nullptr) {}; //构造函数
	int data;
	Node* next;
};

//单链表
class Clink
{
public:
	//构造函数
	Clink()   
	{
		head = new Node();   //初始化head
	}
	~Clink()
	{
		//节点释放,移动头节点循环释放所有节点
		Node* p = head;
		while (p != nullptr)
		{
			head = head->next;   //头节点后移
			delete p;         
			p = head;
		}
		head = nullptr;         //head置空，避免野指针
	}

public:
	//链表尾插
	void InsertTail(int val)
	{
		//寻到尾节点
		Node* p = head;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		//生成要插入的新节点
		Node* node = new Node(val);
		//把新节点挂在尾节点后面
		p->next = node;
	}
	//链表头插
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next = head->next;    //把原链表头节点的地址域赋给要插入的新节点
		head->next = node;          //把原链表头节点地址域设置为新节点的地址
	}
	//链表节点删除,按值,双指针
	void Remove(int val)
	{
		Node* q = head;    //指向头节点
		Node* p = head->next;   //指向第一个节点

		while (p != nullptr)    //寻找要删除的节点
		{
			if (p->data == val)
			{
				q->next = p->next;   //要删除的节点地址域赋给上一节点，链接删除节点前后的节点
				delete p;
				return;
			}
			else
			{
				q = p;        //先移动q
				p = p->next;  //再移动p
			}
		}
	}
	//删除多个节点
	void RemoveAll(int val)
	{
		Node* q = head;    
		Node* p = head->next;   

		while (p != nullptr)    
		{
			if (p->data == val)
			{
				q->next = p->next;   
				delete p;
				//对指针p进行重置，继续往后寻找要删除的节点
				p=q->next;
			}
			else
			{
				q = p;        
				p = p->next;  
			}
		}
	}
	//链表逆序
	void Reverse(Clink& link)
	{
		Node* phead = link.head;   
		Node* p = phead->next;     

		if (p == nullptr)
		{
			return;
		}
		phead->next = nullptr;    //断开头节点，为后续头插准备

		while (p != nullptr)
		{
			Node* q = p->next;    //p的下一个节点
			//p指针指向的节点进行头插法,参考链表头插
			p->next = phead->next;
			phead->next = p;
			p = q;                //p指针后移
		}
	}
	//节点数据查找
	bool Find(int val)
	{
		Node* p = head->next;  //从头节点后的一个开始
		while (p != nullptr)
		{
			if (p->data == val)
			{
				return true;
			}
			else
			{
				p = p->next;
			}
		}
		return false;
	}
	//链表打印
	void Show()
	{
		Node* p = head->next;         //头节点无有效数据，从后一个节点开始打印
		while (p != nullptr)
		{
			std::cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

private:
	Node* head;   //链表头节点
	friend bool GetkNode(Clink& link, int k, int& val);
	friend void MergeLink(Clink& link1, Clink& link2);
};

int main()
{
	Clink link;
	link.InsertTail(12);
	link.InsertTail(3);
	link.InsertTail(8);

	link.InsertHead(8);
	link.InsertHead(78);
	
	link.Show();
	link.Reverse(link);
	link.Show();

	int k = 2;
	int val;
	if (GetkNode(link, k, val))
		cout << "倒数第" << k << "个为：" << val << endl;
}

//求倒数第k个节点的值
//先求正数第k个节点，当p指针移动到第k个节点时，p与pre同时移动
//直到p为nullptr，此时pre指向的节点即为所求
bool GetkNode(Clink& link, int k, int& val)
{
	Node* phead = link.head;
	Node* pre = phead;
	Node* p = phead;

	if (k < 1)
	{
		return false;
	}
	//p指针移动到第k个节点
	for (int i = 0; i < k; i++)
	{
		p = p->next;
		if (p == nullptr)
		{
			return false;
		}
	}

	//此时p在第k个节点，pre在头节点
	while (p != nullptr)       
	{
		pre = pre->next;
		p = p->next;
	}

	val = pre->data;
	return true;
}

//合并两个有序单链表,link2并入link1中
void MergeLink(Clink& link1, Clink& link2)
{
	Node* p = link1.head->next;
	Node* q = link2.head->next;
	Node* last = link1.head;
	link2.head->next = nullptr;      //link2头节点置空

	while (p != nullptr && q != nullptr)
	{
		if (p->data < q->data)    //p->data小则移动p
		{
			last->next = p;
			p = p->next;
			last = last->next;
		}
		else                      //q->data小则移动q
		{
			last->next = q;
			q = q->next;
			last = last->next;
		}
	}
	//一个链表比较完，另一个链表剩余节点都挂在最后
	if (p != nullptr)
	{
		last->next = p;
	}
	else
	{
		last->next = q;
	}
}