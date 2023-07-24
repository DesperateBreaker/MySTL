#pragma once
#include<iostream>
#define NULL nullptr

namespace myVectorNew
{

double g_nNewSpaceRatio = 1.5;      			// 每次开辟新空间的倍数

template <class T>
class MyVector {
public:
	// 0.构造和析构
	MyVector()
		: m_itStart(NULL)
		, m_itFinish(NULL)
		, m_itEnd(NULL)
	{
	}

	MyVector(int nSize_, const T& tValue_ = T())				// n 个值构造
	{
		reserve(nSize_);

		for (int i = 0; i < nSize_; ++i)
		{
			m_itStart[i] = tValue_;
		}

		m_itFinish = m_itStart + nSize_;
	}

	template<class InputIterator>
	MyVector(InputIterator itFirst_, InputIterator itLast_)		// 迭代器区间构造
		: m_itStart(NULL)
		, m_itFinish(NULL)
		, m_itEnd(NULL)
	{
		while (itFirst_ != itLast_)
		{
			push_back(*itFirst_);
			++itFirst_;
		}
	}

	MyVector(const MyVector<T>& v_)								// 拷贝构造
		: m_itStart(NULL)
		, m_itFinish(NULL)
		, m_itEnd(NULL)
	{
		// 这里直接使用迭代器区间构造 
		MyVector<T> _vTemp(v_.cbegin(), v_.cend());
		swap(_vTemp);
	}

	~MyVector()
	{
		delete[] m_itStart;
		m_itStart = NULL;
		m_itFinish = NULL;
		m_itEnd = NULL;
	}

	// 1.迭代器相关
	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin() { return m_itStart; }
	iterator begin() const { return m_itStart; }
	const_iterator cbegin() const { return m_itStart; }
	iterator rbegin() { return m_itFinish; }
	iterator rbegin() const { return m_itFinish; }
	const_iterator crbegin() const { return m_itFinish; }
	
	iterator end() { return m_itFinish; }
	iterator end() const { return m_itFinish; }
	const_iterator cend() const { return m_itFinish; }
	iterator rend() { return m_itStart; }
	iterator rend() const { return m_itStart; }
	const_iterator rcend() const { return m_itStart; }

	iterator insert(iterator itPos_, const T& tData_)
	{
		// 0.检查范围
		if (itPos_ < m_itStart || itPos_ >= m_itFinish)
			throw"Out of Range!";

		// 1.检查容量
		if (m_itFinish == m_itEnd)
		{
			// 扩大m_nCapacity为原来的g_nNewSpaceRatio倍；这里g_nNewSpaceRatio取1.5
			size_t _itOffset = itPos_ - m_itStart;
			size_t _nNewCapacity = (size_t)(ceil)(capacity() * g_nNewSpaceRatio);
			if (_nNewCapacity == 0)
				_nNewCapacity = 1;

			reserve(_nNewCapacity);

			itPos_ = m_itStart + _itOffset;				// 扩容后迭代器失效，需要更新
		}

		// 2.挪动数据
		iterator _itNowEnd = m_itFinish - 1;
		while (_itNowEnd != itPos_)
		{
			*(_itNowEnd + 1) = *_itNowEnd;
			--_itNowEnd;
		}
		
		*itPos_ = tData_;
		m_itFinish++;
		
		//返回 Pos 是为了解决迭代器失效问题
		//让用户可以在外部更新迭代器的位置
		return itPos_;
	}

	iterator erase(iterator itPos_)
	{
		// 0.检查范围
		if (itPos_ < m_itStart || itPos_ >= m_itFinish)
			throw"Out of Range!";

		// 1.挪动数据
		iterator _itNowEnd = itPos_ + 1;
		while (_itNowEnd != m_itFinish)
		{
			*(_itNowEnd - 1) = *_itNowEnd;
			++_itNowEnd;
		}

		m_itFinish--;
		return itPos_;
	}

	iterator test(iterator itPos_, const T& tData_);

	// 2.容量
	size_t size() const;									// Vector 的数据个数
	size_t capacity() const;								// Vector 的容量
	bool reserve(size_t nNewCapacity_);						// 改变容量
	bool resize(size_t nNewSize_, const T& tData_ = T());	// 改变数量

	// 3.操作
	void push_back(const T& tData_);					// 向 Vector 末尾插入数据
	void pop_back();									// 删除 Vector 末尾的数据
	bool empty() const;									// 是否为空
	void clear();										// 清空操作
	void swap(MyVector<T>& v_);							// 直接使用库swap需要1次拷贝构造、2次赋值、3次深拷贝，这里只交换成员变量
	void print() const;									// 用于打印 Vector 中元素，仅用于基本数据类型的打印

	// 4.访问
	T at(size_t index_) const;							// 访问第 index 个元素
	T front() const;									// 访问第 1 个元素
	T back() const;										// 访问最后 1 个元素

	T &operator[](size_t pos_);
	const T &operator[](size_t pos_) const;
	MyVector<T>& operator=(MyVector<T> v_);

private:
	iterator m_itStart;									// 指向首元素
	iterator m_itFinish;								// 指向尾元素 + 1
	iterator m_itEnd;									// 指向空间尾部 + 1
};

template<class T>
typename MyVector<T>::iterator MyVector<T>::test(iterator itPos_, const T& tData_)
{
	std::cout << "---test---" << std::endl;
	return itPos_;
}

template<class T>
void MyVector<T>::swap(MyVector<T>& v_)
{
	std::swap(m_itStart, v_.m_itStart);
	std::swap(m_itFinish, v_.m_itFinish);
	std::swap(m_itEnd, v_.m_itEnd);
}

template<class T>
void MyVector<T>::print() const
{
	iterator _itNowPos = m_itStart;
	std::cout << std::endl << "---------- start ----------"<< std::endl;
	while (_itNowPos != m_itFinish)
	{
		std::cout << *_itNowPos << std::endl;
		++_itNowPos;
	}
	std::cout << "----------- end -----------" << std::endl;
}


template<class T>
size_t MyVector<T>::size() const
{
	return m_itFinish - m_itStart;
}

template<class T>
size_t MyVector<T>::capacity() const
{
	return m_itEnd - m_itStart;
}

template<class T>
bool MyVector<T>::reserve(size_t nNewCapacity_)
{
	// 0.当前容量 >= 新容量，不需要做任何事情
	if (nNewCapacity_ <= capacity())
		return true;

	// 1.开辟新空间
	size_t _nOldSize = size();
	T* pNew = new T[nNewCapacity_];

	// 2.拷贝原有数据并释放原内存
	// memcpy(pNew, m_itStart, sizeof(T*) * _nOldSize);	      // memcpy 是浅拷贝，拷贝自定义类型可能会出错	
	if (m_itStart != NULL)
	{
		for (int i = 0; i < _nOldSize; ++i)
		{
			pNew[i] = m_itStart[i];
		}
		delete[] m_itStart;
	}

	m_itStart = pNew;
	m_itFinish = pNew + _nOldSize;
	m_itEnd = pNew + nNewCapacity_;
}

template<class T>
bool MyVector<T>::resize(size_t nNewSize_, const T& tData_)
{
	// 超过当前容量得重新分配空间
	if (nNewSize_ > capacity())
		reserve(nNewSize_);

	// 超过原 size 则使用 Data 填充，否则删除
	if (nNewSize_ > size())
	{
		while (m_itFinish < m_itStart + nNewSize_)
		{
			*m_itFinish = tData_;
			++m_itFinish;
		}
	}
	else
	{
		m_itFinish = m_itStart + nNewSize_;
	}
}

template<class T>
void MyVector<T>::push_back(const T& tData_)
{
	// 空间不够时重新分配空间
	if (m_itFinish == m_itEnd)
	{
		// 扩大m_nCapacity为原来的g_nNewSpaceRatio倍；这里g_nNewSpaceRatio取1.5
		size_t _nNewCapacity = (size_t)(ceil)(capacity() * g_nNewSpaceRatio);
		if (_nNewCapacity == 0)
			_nNewCapacity = 1;

		reserve(_nNewCapacity);
	}

	*m_itFinish = tData_;
	m_itFinish++;
}

template<class T>
void MyVector<T>::pop_back()
{
	if (empty())
		throw"vector is empty!";

	m_itFinish--;
}

template<class T>
bool MyVector<T>::empty() const
{
	return m_itStart == m_itFinish;
}

template<class T>
void MyVector<T>::clear()
{
	m_itFinish = m_itStart;
}

template<typename T>
T MyVector<T>::at(size_t index_) const
{
	if (index_ >= 0 && index_ < size())
		return *(m_itStart + index_);

	throw"Out of range";
}

template<typename T>
T MyVector<T>::front() const
{
	if (empty())
		throw"vector is empty";

	return *m_itStart;
}

template<typename T>
T MyVector<T>::back() const
{
	if (empty())
		throw("vector is empty");

	return *(m_itFinish - 1);
}


template<class T>
T &MyVector<T>::operator[](size_t pos_)
{
	if (pos_ >= 0 && pos_ < size())
		return *(m_itStart + pos_);

	throw"Out of range";
}

template<class T>
const T &MyVector<T>::operator[](size_t pos_) const
{
	if (pos_ >= 0 && pos_ < size())
		return *(m_itStart + pos_);

	throw"Out of range";
}

template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector<T> v_)			// 因为使用swap，所以不要传&
{
	swap(v_);
	return *this;
}


// 命名空间结束括号
}








