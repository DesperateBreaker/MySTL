#pragma once

#include <assert.h>
namespace nb
{
	template<class T>
	class vector
	{
	public:

		// vector的迭代器是一个原生指针

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
			//精简复用
			vector<T> tmp(v.cbegin(), v.cend());//需要调用const版本的begin、end
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
				int oldSize = size();//原size
				T* tmp = new T[n];
				//memcpy(tmp, _start, sizeof(T) * oldSize); // --> 不能用memcpy，如果是自定义类型会发生错误
				// memcpy是浅拷贝
				//_start不为空才需要拷数据
				if (_start)
				{
					for (int i = 0; i < oldSize; ++i)
					{
						tmp[i] = _start[i];//调用赋值运算符重载完成深拷贝
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
			//交换成员
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
		}

		// 迭代器失效 : 扩容引起，野指针问题
		iterator insert(iterator pos, const T& val)//在pos位置前面插入
		{
			assert(pos >= _start);
			assert(pos < _finish);
			//检查容量
			if (_finish == _endOfStorage)
			{
				size_t len = pos - _start;
				size_t newCapacity = _endOfStorage == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
				//扩容会导致 pos 迭代器失效，需要更新pos
				pos = _start + len;
			}

			//挪动数据
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

		iterator _start; // 指向数据块的开始

		iterator _finish; // 指向有效数据的尾

		iterator _endOfStorage; // 指向存储容量的尾
	};
}

