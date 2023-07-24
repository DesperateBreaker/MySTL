#pragma once
#include<iostream>
#define NULL nullptr

namespace myVectorNew
{

double g_nNewSpaceRatio = 1.5;      			// ÿ�ο����¿ռ�ı���

template <class T>
class MyVector {
public:
	// 0.���������
	MyVector()
		: m_itStart(NULL)
		, m_itFinish(NULL)
		, m_itEnd(NULL)
	{
	}

	MyVector(int nSize_, const T& tValue_ = T())				// n ��ֵ����
	{
		reserve(nSize_);

		for (int i = 0; i < nSize_; ++i)
		{
			m_itStart[i] = tValue_;
		}

		m_itFinish = m_itStart + nSize_;
	}

	template<class InputIterator>
	MyVector(InputIterator itFirst_, InputIterator itLast_)		// ���������乹��
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

	MyVector(const MyVector<T>& v_)								// ��������
		: m_itStart(NULL)
		, m_itFinish(NULL)
		, m_itEnd(NULL)
	{
		// ����ֱ��ʹ�õ��������乹�� 
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

	// 1.���������
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
		// 0.��鷶Χ
		if (itPos_ < m_itStart || itPos_ >= m_itFinish)
			throw"Out of Range!";

		// 1.�������
		if (m_itFinish == m_itEnd)
		{
			// ����m_nCapacityΪԭ����g_nNewSpaceRatio��������g_nNewSpaceRatioȡ1.5
			size_t _itOffset = itPos_ - m_itStart;
			size_t _nNewCapacity = (size_t)(ceil)(capacity() * g_nNewSpaceRatio);
			if (_nNewCapacity == 0)
				_nNewCapacity = 1;

			reserve(_nNewCapacity);

			itPos_ = m_itStart + _itOffset;				// ���ݺ������ʧЧ����Ҫ����
		}

		// 2.Ų������
		iterator _itNowEnd = m_itFinish - 1;
		while (_itNowEnd != itPos_)
		{
			*(_itNowEnd + 1) = *_itNowEnd;
			--_itNowEnd;
		}
		
		*itPos_ = tData_;
		m_itFinish++;
		
		//���� Pos ��Ϊ�˽��������ʧЧ����
		//���û��������ⲿ���µ�������λ��
		return itPos_;
	}

	iterator erase(iterator itPos_)
	{
		// 0.��鷶Χ
		if (itPos_ < m_itStart || itPos_ >= m_itFinish)
			throw"Out of Range!";

		// 1.Ų������
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

	// 2.����
	size_t size() const;									// Vector �����ݸ���
	size_t capacity() const;								// Vector ������
	bool reserve(size_t nNewCapacity_);						// �ı�����
	bool resize(size_t nNewSize_, const T& tData_ = T());	// �ı�����

	// 3.����
	void push_back(const T& tData_);					// �� Vector ĩβ��������
	void pop_back();									// ɾ�� Vector ĩβ������
	bool empty() const;									// �Ƿ�Ϊ��
	void clear();										// ��ղ���
	void swap(MyVector<T>& v_);							// ֱ��ʹ�ÿ�swap��Ҫ1�ο������졢2�θ�ֵ��3�����������ֻ������Ա����
	void print() const;									// ���ڴ�ӡ Vector ��Ԫ�أ������ڻ����������͵Ĵ�ӡ

	// 4.����
	T at(size_t index_) const;							// ���ʵ� index ��Ԫ��
	T front() const;									// ���ʵ� 1 ��Ԫ��
	T back() const;										// ������� 1 ��Ԫ��

	T &operator[](size_t pos_);
	const T &operator[](size_t pos_) const;
	MyVector<T>& operator=(MyVector<T> v_);

private:
	iterator m_itStart;									// ָ����Ԫ��
	iterator m_itFinish;								// ָ��βԪ�� + 1
	iterator m_itEnd;									// ָ��ռ�β�� + 1
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
	// 0.��ǰ���� >= ������������Ҫ���κ�����
	if (nNewCapacity_ <= capacity())
		return true;

	// 1.�����¿ռ�
	size_t _nOldSize = size();
	T* pNew = new T[nNewCapacity_];

	// 2.����ԭ�����ݲ��ͷ�ԭ�ڴ�
	// memcpy(pNew, m_itStart, sizeof(T*) * _nOldSize);	      // memcpy ��ǳ�����������Զ������Ϳ��ܻ����	
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
	// ������ǰ���������·���ռ�
	if (nNewSize_ > capacity())
		reserve(nNewSize_);

	// ����ԭ size ��ʹ�� Data ��䣬����ɾ��
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
	// �ռ䲻��ʱ���·���ռ�
	if (m_itFinish == m_itEnd)
	{
		// ����m_nCapacityΪԭ����g_nNewSpaceRatio��������g_nNewSpaceRatioȡ1.5
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
MyVector<T>& MyVector<T>::operator=(MyVector<T> v_)			// ��Ϊʹ��swap�����Բ�Ҫ��&
{
	swap(v_);
	return *this;
}


// �����ռ��������
}








