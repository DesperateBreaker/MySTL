#pragma once
#include<iostream>
#define NULL nullptr
#define assert _ASSERT
#define SORT_MAX 16

namespace mylist
{
	/*----------------- ListNode Start -----------------*/
	// ���� list �� node �ڵ�
	template<class T>
	struct ListNode
	{
		ListNode<T>* m_pRev;				// ��һ�ڵ��ַ
		ListNode<T>* m_pNext;				// ��һ�ڵ��ַ
		T m_data;							// ����

		ListNode(const T& data_ = T())
			: m_pRev(NULL)
			, m_pNext(NULL)
			, m_data(data_)
		{
		}
	};
	/*------------------ ListNode End ------------------*/


	/*----------------- Iterator Start -----------------*/
	// ���� iterator
	template<class T, class Ref, class Ptr>
	struct _List_Iterator
	{
		typedef ListNode<T> Node;
		typedef _List_Iterator<T, Ref, Ptr> Self;

		Node* m_pNode;

		_List_Iterator() {}
		_List_Iterator(Node* pNode_) : m_pNode(pNode_) {}						// �ڵ㹹��
		// _List_Iterator(const iterator& x) : m_pNode(x.m_pNode) {}

		Ref operator*() { return m_pNode->m_data; }								// ���� *     Ref:T&/const T&
		Ptr operator->() { return &m_pNode->m_data; }							// ���� ->	  Ptr:T*/const T*
		_List_Iterator<T, Ref, Ptr>& operator++();								// ���� ++it
		_List_Iterator<T, Ref, Ptr> operator++(int);							// ���� it++
		_List_Iterator<T, Ref, Ptr>& operator--();								// ���� --it
		_List_Iterator<T, Ref, Ptr> operator--(int);							// ���� it--
		bool operator==(const _List_Iterator<T, Ref, Ptr>& it_) const;			// ���� ==
		bool operator!=(const _List_Iterator<T, Ref, Ptr>& it_) const;			// ���� !=
	};

	template<class T, class Ref, class Ptr>
	_List_Iterator<T, Ref, Ptr>& _List_Iterator<T, Ref, Ptr>::operator++()
	{
		m_pNode = m_pNode->m_pNext;						// ++it �ȼӺ�ȡ
		return *this;
	}

	template<class T, class Ref, class Ptr>
	_List_Iterator<T, Ref, Ptr> _List_Iterator<T, Ref, Ptr>::operator++(int)
	{
		_List_Iterator<T, Ref, Ptr> _tmp(*this);		// it++ ��ȡ���
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

		// 0.���������
		MyList();
		MyList(const MyList<T>& List_);
		template<class InputIterator>
		MyList(InputIterator itFirst_, InputIterator itLast_);		
		~MyList();

		// 1.���������
		iterator begin();							// ָ����Ԫ�ص�����
		const_iterator begin() const;				// ָ����Ԫ�� const ������
		const_iterator cbegin() const;				// ָ����Ԫ�� const ������
		iterator end();								// ָ��ĩβ�ĵ�����				
		const_iterator end() const;					// ָ��ĩβ�� const ������
		const_iterator cend() const;				// ָ��ĩβ�� const ������


		// 2.����
		bool empty() const;							// list �Ƿ�Ϊ��
		size_t size() const;						// list ��Ԫ�صĸ���

		// 3.����
		void swap(MyList<T>& List_);				// �������� list
		void push_back(const T& Data_);				// ��ĩβ���Ԫ��
		void push_front(const T& Data_);			// ��ͷ�����Ԫ��
		void pop_back();							// ɾ��ĩβԪ��
		void pop_front();							// ɾ��ͷ��Ԫ��
		void clear();								// ��� list
		void sort();								// ��������Ĭ������

		void print();								// ��ӡ������������

		template<class InputIterator>
		void insert(iterator itPos_, InputIterator itFirst_, InputIterator itLast_);	// TODO:��������Ԫ��
		void insert(iterator itPos_, size_t num_, const T& Data_);						// TODO:���� n ��Ԫ��
		
		iterator insert(iterator itPos_, const T& Data_);								// ָ��λ�ò���Ԫ��
		iterator erase(iterator itPos_);												// ɾ��ָ��λ��Ԫ��


		// 4.�����������
		MyList<T>& operator=(MyList<T> List_);

	private:
		Node* m_head;

		void empty_initialize();														// �ṩ�� list �ĳ�ʼ��
		void transfer(iterator itPos_, iterator itFirst_, iterator itLast_);			// TODO:��[itFirst_, itLast_)�ڵ�����Ԫ���ƶ��� itPos ֮ǰ
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

		// �ִ�д��
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

		// TODO:ÿ�ε��øú�������Ҫ���㣬ʱ�临�Ӷ� O(N),���Ż���
		// �����Ա m_nSize ��¼��ֵ���Կռ任ʱ��
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
		// ������ SORT_MAX ʱʹ�ÿ������򣬷���ʹ�ò�������
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
		// ˼�룺�ҵ�β���ڵ㡢��β���ڵ���½ڵ���������
		Node* _tailNode = m_head->m_pRev;		// β���ڵ�
		Node* _newNode = new Node(Data_);		// ʹ�� nData_ �½��ڵ�
		_tailNode->m_pNext = _newNode;			// β���ڵ�� pNext ָ���½ڵ�
		_newNode->m_pRev = _tailNode;			// �½ڵ�� pRev ָ��β���ڵ�
		m_head->m_pRev = _newNode;				// ����β���ڵ�
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
		// ���ﲻ�������õķ�ʽ��������ֵ��ı�
		swap(List_);
		return *this;
	}

	template<class T>
	void MyList<T>::empty_initialize()
	{
		// list �ĳ�ʼ��
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

			// TODO:������
		}
	}

	template<class T>
	void MyList<T>::insert_sort()
	{
		// TODO:
		// �ƺ� list ���ÿ�������
	}

	template<class T>
	void MyList<T>::fast_sort()
	{
		// TODO:
		
	}
	/*-------------------- List End --------------------*/
}