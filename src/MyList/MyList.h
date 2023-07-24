#pragma once
#include<iostream>
#define NULL nullptr
#define assert _ASSERT
#define SORT_MAX 16

namespace mylist
{
	/*----------------- ListNode Start -----------------*/
	// 定义 list 的 node 节点
	template<class T>
	struct ListNode
	{
		ListNode<T>* m_pRev;				// 上一节点地址
		ListNode<T>* m_pNext;				// 下一节点地址
		T m_data;							// 数据

		ListNode(const T& data_ = T())
			: m_pRev(NULL)
			, m_pNext(NULL)
			, m_data(data_)
		{
		}
	};
	/*------------------ ListNode End ------------------*/


	/*----------------- Iterator Start -----------------*/
	// 定义 iterator
	template<class T, class Ref, class Ptr>
	struct _List_Iterator
	{
		typedef ListNode<T> Node;
		typedef _List_Iterator<T, Ref, Ptr> Self;

		Node* m_pNode;

		_List_Iterator() {}
		_List_Iterator(Node* pNode_) : m_pNode(pNode_) {}						// 节点构造
		// _List_Iterator(const iterator& x) : m_pNode(x.m_pNode) {}

		Ref operator*() { return m_pNode->m_data; }								// 重载 *     Ref:T&/const T&
		Ptr operator->() { return &m_pNode->m_data; }							// 重载 ->	  Ptr:T*/const T*
		_List_Iterator<T, Ref, Ptr>& operator++();								// 重载 ++it
		_List_Iterator<T, Ref, Ptr> operator++(int);							// 重载 it++
		_List_Iterator<T, Ref, Ptr>& operator--();								// 重载 --it
		_List_Iterator<T, Ref, Ptr> operator--(int);							// 重载 it--
		bool operator==(const _List_Iterator<T, Ref, Ptr>& it_) const;			// 重载 ==
		bool operator!=(const _List_Iterator<T, Ref, Ptr>& it_) const;			// 重载 !=
	};

	template<class T, class Ref, class Ptr>
	_List_Iterator<T, Ref, Ptr>& _List_Iterator<T, Ref, Ptr>::operator++()
	{
		m_pNode = m_pNode->m_pNext;						// ++it 先加后取
		return *this;
	}

	template<class T, class Ref, class Ptr>
	_List_Iterator<T, Ref, Ptr> _List_Iterator<T, Ref, Ptr>::operator++(int)
	{
		_List_Iterator<T, Ref, Ptr> _tmp(*this);		// it++ 先取后加
		m_pNode = m_pNode->m_pNext;
		return _tmp;
	}

	template<class T, class Ref, class Ptr>
	_List_Iterator<T, Ref, Ptr>& _List_Iterator<T, Ref, Ptr>::operator--()
	{
		m_pNode = m_pNode->m_pRev;
		return *this;
	}

	template<class T, class Ref, class Ptr>
	_List_Iterator<T, Ref, Ptr> _List_Iterator<T, Ref, Ptr>::operator--(int)
	{
		_List_Iterator<T, Ref, Ptr> _tmp(*this);
		m_pNode = m_pNode->m_pRev;
		return _tmp;
	}

	template<class T, class Ref, class Ptr>
	bool _List_Iterator<T, Ref, Ptr>::operator==(const _List_Iterator<T, Ref, Ptr>& it_) const
	{
		return this->m_pNode == it_.m_pNode;
	}

	template<class T, class Ref, class Ptr>
	bool _List_Iterator<T, Ref, Ptr>::operator!=(const _List_Iterator<T, Ref, Ptr>& it_) const
	{
		return this->m_pNode != it_.m_pNode;
	}
	/*------------------ Iterator End ------------------*/


	/*------------------- List Start -------------------*/
	// list 
	template<class T>
	class MyList
	{
	public:
		typedef ListNode<T> Node;
		typedef _List_Iterator<T, T&, T*> iterator;
		typedef _List_Iterator<T, const T&, const T*> const_iterator;

		// 0.构造和析构
		MyList();
		MyList(const MyList<T>& List_);
		template<class InputIterator>
		MyList(InputIterator itFirst_, InputIterator itLast_);		
		~MyList();

		// 1.迭代器相关
		iterator begin();							// 指向首元素迭代器
		const_iterator begin() const;				// 指向首元素 const 迭代器
		const_iterator cbegin() const;				// 指向首元素 const 迭代器
		iterator end();								// 指向末尾的迭代器				
		const_iterator end() const;					// 指向末尾的 const 迭代器
		const_iterator cend() const;				// 指向末尾的 const 迭代器


		// 2.容量
		bool empty() const;							// list 是否为空
		size_t size() const;						// list 中元素的个数

		// 3.操作
		void swap(MyList<T>& List_);				// 交换两个 list
		void push_back(const T& Data_);				// 在末尾添加元素
		void push_front(const T& Data_);			// 在头部添加元素
		void pop_back();							// 删除末尾元素
		void pop_front();							// 删除头部元素
		void clear();								// 清空 list
		void sort();								// 排序函数，默认升序

		void print();								// 打印基本数据类型

		template<class InputIterator>
		void insert(iterator itPos_, InputIterator itFirst_, InputIterator itLast_);	// TODO:插入区间元素
		void insert(iterator itPos_, size_t num_, const T& Data_);						// TODO:插入 n 个元素
		
		iterator insert(iterator itPos_, const T& Data_);								// 指定位置插入元素
		iterator erase(iterator itPos_);												// 删除指定位置元素


		// 4.运算符的重载
		MyList<T>& operator=(MyList<T> List_);

	private:
		Node* m_head;

		void empty_initialize();														// 提供空 list 的初始化
		void transfer(iterator itPos_, iterator itFirst_, iterator itLast_);			// TODO:将[itFirst_, itLast_)内的所有元素移动到 itPos 之前
		void fast_sort();
		void insert_sort();
	};

	template<class T>
	MyList<T>::MyList()
	{
		empty_initialize();
	}

	template<class T>
	template<class InputIterator>
	MyList<T>::MyList(InputIterator itFirst_, InputIterator itLast_)
	{
		empty_initialize();
		while (itFirst_ != itLast_)
		{
			push_back(*itFirst_);
			*itFirst_++;
		}
	}

	template<class T>
	MyList<T>::MyList(const MyList<T>& List_)
	{
		empty_initialize();

		/*for (const auto& e : List_)
			push_back(e);*/

		// 现代写法
		MyList<T> _tmp(List_.begin(), List_.end());
		swap(_tmp);
	}

	template<class T>
	MyList<T>::~MyList()
	{
		clear();
		delete m_head;
		m_head = NULL;
	}

	template<class T>
	typename MyList<T>::iterator MyList<T>::begin()
	{
		return iterator(m_head->m_pNext);
	}

	template<class T>
	typename MyList<T>::const_iterator MyList<T>::cbegin() const
	{
		return const_iterator(m_head->m_pNext);
	}

	template<class T>
	typename MyList<T>::const_iterator MyList<T>::begin() const
	{
		return const_iterator(m_head->m_pNext);
	}

	template<class T>
	typename MyList<T>::iterator MyList<T>::end()
	{
		return iterator(m_head);
	}

	template<class T>
	typename MyList<T>::const_iterator MyList<T>::cend() const
	{
		return iterator(m_head);
	}

	template<class T>
	typename MyList<T>::const_iterator MyList<T>::end() const
	{
		return const_iterator(m_head);
	}

	template<class T>
	bool MyList<T>::empty() const
	{
		return m_head == m_head->m_pNext;
	}

	template<class T>
	size_t MyList<T>::size() const
	{
		const_iterator _it = begin();
		size_t _nSize = 0;
		while (_it != end())
		{
			_nSize++;
			_it++;
		}

		// TODO:每次调用该函数均需要计算，时间复杂度 O(N),可优化：
		// 定义成员 m_nSize 记录该值，以空间换时间
		// return m_nSize;

		return _nSize;
	}

	template<class T>
	void MyList<T>::swap(MyList<T>& List_)
	{
		std::swap(m_head, List_.m_head);
	}

	template<class T>
	void MyList<T>::clear()
	{
		iterator _it = begin();
		while (_it != end())
		{
			erase(_it++);
		}
	}

	template<class T>
	void MyList<T>::sort()
	{
		// 当大于 SORT_MAX 时使用快速排序，否则使用插入排序
		if (size() > SORT_MAX)
			fast_sort();
		else
			insert_sort();
	}

	template<class T>
	void MyList<T>::print()
	{
		iterator _it = begin();
		std::cout << std::endl << "---------- start ----------" << std::endl;
		while (_it != end())
		{
			std::cout << *_it << std::endl;
			_it++;
		}
		std::cout << "----------- end -----------" << std::endl;
	}

	template<class T>
	void MyList<T>::push_back(const T& Data_)
	{
		insert(end()--, Data_);
		
		/*
		// 思想：找到尾部节点、将尾部节点和新节点连接起来
		Node* _tailNode = m_head->m_pRev;		// 尾部节点
		Node* _newNode = new Node(Data_);		// 使用 nData_ 新建节点
		_tailNode->m_pNext = _newNode;			// 尾部节点的 pNext 指向新节点
		_newNode->m_pRev = _tailNode;			// 新节点的 pRev 指向尾部节点
		m_head->m_pRev = _newNode;				// 更新尾部节点
		_tailNode = _newNode;					// 
		*/
	}

	template<class T>
	void MyList<T>::push_front(const T& Data_)
	{
		insert(begin(), Data_);
	}

	template<class T>
	void MyList<T>::pop_back()
	{
		erase(--end());
	}

	template<class T>
	void MyList<T>::pop_front()
	{
		erase(begin());
	}

	template<class T>
	typename MyList<T>::iterator MyList<T>::insert(iterator itPos_, const T& Data_)
	{
		assert(itPos_.m_pNode);
		Node* _newNode = new Node(Data_);
		Node* _curNode = itPos_.m_pNode;

		_newNode->m_pRev = _curNode->m_pRev;
		_newNode->m_pNext = itPos_.m_pNode;

		_curNode->m_pRev->m_pNext = _newNode;
		_curNode->m_pRev = _newNode;

		return iterator(_newNode);
	}

	template<class T>
	typename MyList<T>::iterator MyList<T>::erase(iterator itPos_)
	{
		assert(itPos_.m_pNode);
		assert(itPos_ != end());
		
		Node* _preNode = itPos_.m_pNode->m_pRev;
		Node* _nextNode = itPos_.m_pNode->m_pNext;

		delete itPos_.m_pNode;
		_preNode->m_pNext = _nextNode;
		_nextNode->m_pRev = _preNode;

		return iterator(_nextNode);
	}

	template<class T>
	MyList<T>& MyList<T>::operator=(MyList<T> List_)
	{
		// 这里不能用引用的方式，否则右值会改变
		swap(List_);
		return *this;
	}

	template<class T>
	void MyList<T>::empty_initialize()
	{
		// list 的初始化
		m_head = new Node;
		m_head->m_pNext = m_head;
		m_head->m_pRev = m_head;
	}

	template<class T>
	void MyList<T>::transfer(iterator itPos_, iterator itFirst_, iterator itLast_)
	{
		if (itPos_ != itLast_)
		{
			itLast_.m_pNode->m_pRev->m_pNext = itPos_.m_pNode;
			itFirst_.m_pNode->m_pRev->m_pNext = itLast_.m_pNode;
			itPos_.m_pNode->m_pRev->m_pNext = itFirst_.m_pNode;

			Node* _pTemp = itPos_.m_pNode->m_pRev;

			// TODO:待完善
		}
	}

	template<class T>
	void MyList<T>::insert_sort()
	{
		// TODO:
		// 似乎 list 都用快速排序
	}

	template<class T>
	void MyList<T>::fast_sort()
	{
		// TODO:
		
	}
	/*-------------------- List End --------------------*/
}