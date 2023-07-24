#pragma once

#include <assert.h>
namespace nb
{
	template<class T>
	class vector
	{
	public:

		// vector�ĵ�������һ��ԭ��ָ��

		typedef T* iterator;

		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator begin() const
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		iterator end() const
		{
			return _finish;
		}

		const_iterator cbegin() const
		{
			return _start;
		}

		const_iterator cend() const
		{
			return _finish;
		}

		// construct and destroy

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
		}

		vector(int n, const T& value = T())
		{
			reserve(n);
			for (int i = 0; i < n; ++i)
			{
				_start[i] = value;
			}
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			//������
			vector<T> tmp(v.cbegin(), v.cend());//��Ҫ����const�汾��begin��end
			swap(tmp);
		}

		vector<T>& operator= (vector<T> v)
		{
			swap(v);
			return *this;
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}

		// capacity

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endOfStorage - _start;
		}

		bool empty() const
		{
			return _finish == _start;
		}

		void clear()
		{
			_finish = _start;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				int oldSize = size();//ԭsize
				T* tmp = new T[n];
				//memcpy(tmp, _start, sizeof(T) * oldSize); // --> ������memcpy��������Զ������ͻᷢ������
				// memcpy��ǳ����
				//_start��Ϊ�ղ���Ҫ������
				if (_start)
				{
					for (int i = 0; i < oldSize; ++i)
					{
						tmp[i] = _start[i];//���ø�ֵ���������������
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = tmp + oldSize;
				_endOfStorage = _start + n;
			}
		}

		void resize(size_t n, const T& value = T())
		{
			if (n > capacity())
			{
				reserve(n);
			}
			if (n > size())
			{
				while (_finish < _start + n)
				{
					*_finish = value;
					_finish++;
				}
			}
			else
			{
				_finish = _start + n;
			}
		}

		///access///

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return *(_start + pos);
		}

		const T& operator[](size_t pos) const
		{
			assert(pos < _finish);
			//return *(_start + pos);
			return _start[pos];
		}

		///modify/

		void push_back(const T& x)
		{
			if (_finish == _endOfStorage)
			{
				size_t newCapacity = _endOfStorage == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
			}
			*_finish = x;
			_finish++;
		}

		void pop_back()
		{
			assert(!empty());
			_finish--;
		}

		void swap(vector<T>& v)
		{
			//������Ա
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
		}

		// ������ʧЧ : ��������Ұָ������
		iterator insert(iterator pos, const T& val)//��posλ��ǰ�����
		{
			assert(pos >= _start);
			assert(pos < _finish);
			//�������
			if (_finish == _endOfStorage)
			{
				size_t len = pos - _start;
				size_t newCapacity = _endOfStorage == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
				//���ݻᵼ�� pos ������ʧЧ����Ҫ����pos
				pos = _start + len;
			}

			//Ų������
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = val;
			_finish++;
			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			iterator end = pos + 1;
			while (end != _finish)
			{
				*(end - 1) = *(end);
				++end;
			}
			_finish--;
			return pos;
		}

	private:

		iterator _start; // ָ�����ݿ�Ŀ�ʼ

		iterator _finish; // ָ����Ч���ݵ�β

		iterator _endOfStorage; // ָ��洢������β
	};
}

