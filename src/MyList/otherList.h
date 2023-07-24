#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

namespace delia
{
	template<class T>
	struct _list_node
	{
		T _val;
		_list_node<T>* _prev;
		_list_node<T>* _next;

		_list_node(const T& val = T())
			:_val(val)
			, _prev(nullptr)
			, _next(nullptr)
		{};
	};


	//节点的指针原生行为不满足迭代器定义，在这里，迭代器通过类来封装节点的指针重载运算符来控制

	//对于T&，类模板实例化出两个类，一个是T&类，一个是const T&类，同理，T*也一样。
	//使用template<class T,class Ref,class Ptr>类模板就会实例化出来两个类，一个是T,T&, T*的，一个是T,const T&, const T*的	 
	//template _list_iterator<T, T&, T*> _iterator;
	//template _list_iterator<T, const T&, const T*> const_iterator;

	//这样就不需要再去定义一个如下const的迭代器类：
	//template<class T>
	//struct _list_const_iterartor
	//{
	//	typedef _list_node<T> node;
	//	typedef _list_const_iterartor<T> self;

	//	node* _pnode;
	//}
	// 

	template<class T, class Ref, class Ptr>
	struct _list_iterator//使用_list_iterator类来封装node*
	{
		typedef _list_node<T> node;
		typedef _list_iterator<T, Ref, Ptr> self;

		node* _pnode;

		//构造函数
		_list_iterator(node* pnode)
			:_pnode(pnode)
		{}

		//拷贝构造、赋值运算符重载、析构函数，编译器默认生成即可

		//解引用，返回左值，是拷贝，因此要用引用返回
		Ref operator*()
		{
			return _pnode->_val;
		}

		//结构体指针解引用，返回节点值的引用
		Ptr operator->()
		{
			return &_pnode->_val;
		}

		//!=重载
		bool operator!=(const self& s) const
		{
			return _pnode != s._pnode;
		}

		//==重载
		bool operator==(const self& s) const
		{
			return _pnode == s._pnode;
		}

		//前置++  it.operator(&it)
		self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		//后置++ 返回++之前的值  it.operator(&it,0)
		self operator++(int)
		{
			self tmp(*this);
			_pnode = _pnode->_next;
			return tmp;
		}

		//前置--  it.operator(&it)
		self& operator--()
		{
			_pnode = _pnode->prev;
			return *this;
		}

		//后置++ 返回++之前的值  it.operator(&it,0)
		self operator--(int)//临时对象不能用引用返回，所以self没有加&
		{
			self tmp(*this);
			_pnode = _pnode->_prev;
			return tmp;
		}
	};

	template<class T>
	class list
	{
		typedef _list_node<T> node;
	public:
		typedef _list_iterator<T, T&, T*> iterator;//重命名迭代器
		typedef _list_iterator<T, const T&, const T*> const_iterator;//重命名const迭代器

																	 //构造函数
		list()
		{
			_head = new node;//会调_list_node的构造函数
			_head->_next = _head;//整个链表只有头节点，先构造一个没有实际节点的链表
			_head->_prev = _head;//整个链表只有头节点，先构造一个没有实际节点的链表
		}

		//拷贝构造 lt1(lt)
		list(const list<T>& lt)
		{
			//1.先构造一个只有头节点的空list：创建头节点，头节点的前一个是自己，头节点的后一个是自己
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;

			//2.将lt的元素全部尾插到新链表
			for (const auto& e : lt)
			{
				push_back(e);
			}
		}

		//赋值运算符重载  lt1 = lt  传统写法
			//list<T>& operator=(list<T>& lt)
			//{
			//	if(this != lt)
			//	{
			//		for (auto& e : lt)
			//		{
			//			push_back(e);
			//		}
			//	}
			//}

			//赋值运算符重载  lt1 = lt  现代写法
			list<T>& operator=(list<T>& lt)
		{
			swap(_head, lt._head);
			return *this;
		}

		//析构
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);//尾节点的下一个节点位置即头节点
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);//尾节点的下一个节点位置即头节点
		}

		//插入节点
		void insert(iterator pos, const T& x)
		{
			assert(pos._pnode);
			node* newnode = new node(x);//构造节点

			node* prev = pos._pnode->_prev;//为方便后续操作，给插入位置的前一个节点起了个名字，pos是迭代器对象

										   //插入节点
			newnode->_next = pos._pnode;
			pos._pnode->_prev = newnode;
			prev->_next = newnode;
			newnode->_prev = prev;

		}

		//删除节点
		iterator erase(iterator pos)
		{
			assert(pos._pnode);//判断该位置节点是否存在
			assert(pos != end());//end()是最后一个节点的下一个节点位置，也就是头节点，头节点不能删，需要断言

			node* prev = pos._pnode->_prev;//pos位置节点的前一个节点
			node* next = pos._pnode->_next;//pos位置节点的后一个节点

										   //删除节点
			delete pos._pnode;
			prev->_next = next;
			next->_prev = prev;

			return iterator(next);//删除之后pos失效，把下一个位置的迭代器给它
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}

		//头插
		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		//尾插
		void push_back(const T& x)
		{
			insert(end()--, x);
		}

		//头删
		void pop_front()
		{
			erase(begin());
		}

		//尾删
		void pop_back()
		{
			erase(--end());
		}

		//判空
		bool empty()
		{
			return _head->_next == _head;
		}

		//求节点个数
		size_t size()
		{
			iterator it = begin();
			size_t sz = 0;
			while (it != end())//时间复杂度O(N)
			{
				it++;
				sz++;
			}

			return sz;
		}
	private:
		node * _head;
	};

	void PrintList(const list<int>& lt)
	{
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << it._pnode->_val << " ";
			it++;
		}
		cout << endl;
	}

	void test_list1()
	{
		list<int> l1;
		l1.push_back(5);
		l1.push_back(8);
		l1.push_back(20);
		l1.push_back(9);

		PrintList(l1);

		list<int> l2;
		l2 = l1;
		PrintList(l2);

		cout << endl;
	}
}
