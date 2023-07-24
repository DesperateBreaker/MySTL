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


	//�ڵ��ָ��ԭ����Ϊ��������������壬�����������ͨ��������װ�ڵ��ָ�����������������

	//����T&����ģ��ʵ�����������࣬һ����T&�࣬һ����const T&�࣬ͬ��T*Ҳһ����
	//ʹ��template<class T,class Ref,class Ptr>��ģ��ͻ�ʵ�������������࣬һ����T,T&, T*�ģ�һ����T,const T&, const T*��	 
	//template _list_iterator<T, T&, T*> _iterator;
	//template _list_iterator<T, const T&, const T*> const_iterator;

	//�����Ͳ���Ҫ��ȥ����һ������const�ĵ������ࣺ
	//template<class T>
	//struct _list_const_iterartor
	//{
	//	typedef _list_node<T> node;
	//	typedef _list_const_iterartor<T> self;

	//	node* _pnode;
	//}
	// 

	template<class T, class Ref, class Ptr>
	struct _list_iterator//ʹ��_list_iterator������װnode*
	{
		typedef _list_node<T> node;
		typedef _list_iterator<T, Ref, Ptr> self;

		node* _pnode;

		//���캯��
		_list_iterator(node* pnode)
			:_pnode(pnode)
		{}

		//�������졢��ֵ��������ء�����������������Ĭ�����ɼ���

		//�����ã�������ֵ���ǿ��������Ҫ�����÷���
		Ref operator*()
		{
			return _pnode->_val;
		}

		//�ṹ��ָ������ã����ؽڵ�ֵ������
		Ptr operator->()
		{
			return &_pnode->_val;
		}

		//!=����
		bool operator!=(const self& s) const
		{
			return _pnode != s._pnode;
		}

		//==����
		bool operator==(const self& s) const
		{
			return _pnode == s._pnode;
		}

		//ǰ��++  it.operator(&it)
		self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		//����++ ����++֮ǰ��ֵ  it.operator(&it,0)
		self operator++(int)
		{
			self tmp(*this);
			_pnode = _pnode->_next;
			return tmp;
		}

		//ǰ��--  it.operator(&it)
		self& operator--()
		{
			_pnode = _pnode->prev;
			return *this;
		}

		//����++ ����++֮ǰ��ֵ  it.operator(&it,0)
		self operator--(int)//��ʱ�����������÷��أ�����selfû�м�&
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
		typedef _list_iterator<T, T&, T*> iterator;//������������
		typedef _list_iterator<T, const T&, const T*> const_iterator;//������const������

																	 //���캯��
		list()
		{
			_head = new node;//���_list_node�Ĺ��캯��
			_head->_next = _head;//��������ֻ��ͷ�ڵ㣬�ȹ���һ��û��ʵ�ʽڵ������
			_head->_prev = _head;//��������ֻ��ͷ�ڵ㣬�ȹ���һ��û��ʵ�ʽڵ������
		}

		//�������� lt1(lt)
		list(const list<T>& lt)
		{
			//1.�ȹ���һ��ֻ��ͷ�ڵ�Ŀ�list������ͷ�ڵ㣬ͷ�ڵ��ǰһ�����Լ���ͷ�ڵ�ĺ�һ�����Լ�
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;

			//2.��lt��Ԫ��ȫ��β�嵽������
			for (const auto& e : lt)
			{
				push_back(e);
			}
		}

		//��ֵ���������  lt1 = lt  ��ͳд��
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

			//��ֵ���������  lt1 = lt  �ִ�д��
			list<T>& operator=(list<T>& lt)
		{
			swap(_head, lt._head);
			return *this;
		}

		//����
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
			return iterator(_head);//β�ڵ����һ���ڵ�λ�ü�ͷ�ڵ�
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);//β�ڵ����һ���ڵ�λ�ü�ͷ�ڵ�
		}

		//����ڵ�
		void insert(iterator pos, const T& x)
		{
			assert(pos._pnode);
			node* newnode = new node(x);//����ڵ�

			node* prev = pos._pnode->_prev;//Ϊ�������������������λ�õ�ǰһ���ڵ����˸����֣�pos�ǵ���������

										   //����ڵ�
			newnode->_next = pos._pnode;
			pos._pnode->_prev = newnode;
			prev->_next = newnode;
			newnode->_prev = prev;

		}

		//ɾ���ڵ�
		iterator erase(iterator pos)
		{
			assert(pos._pnode);//�жϸ�λ�ýڵ��Ƿ����
			assert(pos != end());//end()�����һ���ڵ����һ���ڵ�λ�ã�Ҳ����ͷ�ڵ㣬ͷ�ڵ㲻��ɾ����Ҫ����

			node* prev = pos._pnode->_prev;//posλ�ýڵ��ǰһ���ڵ�
			node* next = pos._pnode->_next;//posλ�ýڵ�ĺ�һ���ڵ�

										   //ɾ���ڵ�
			delete pos._pnode;
			prev->_next = next;
			next->_prev = prev;

			return iterator(next);//ɾ��֮��posʧЧ������һ��λ�õĵ���������
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}

		//ͷ��
		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		//β��
		void push_back(const T& x)
		{
			insert(end()--, x);
		}

		//ͷɾ
		void pop_front()
		{
			erase(begin());
		}

		//βɾ
		void pop_back()
		{
			erase(--end());
		}

		//�п�
		bool empty()
		{
			return _head->_next == _head;
		}

		//��ڵ����
		size_t size()
		{
			iterator it = begin();
			size_t sz = 0;
			while (it != end())//ʱ�临�Ӷ�O(N)
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
