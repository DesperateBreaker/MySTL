#include "pch.h"
#include "../MyList/MyList.h"

/* 样例
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
*/
using namespace mylist;

TEST(TestConstruction, TestDefaultConstruction)							// 默认构造 GTest
{
	MyList<int>* _pList1 = new MyList<int>;
	ASSERT_NE(_pList1, nullptr);
	
	delete _pList1;
	_pList1 = nullptr;
}

TEST(TestConstruction, TestCopyConstruction)							// 拷贝构造 GTest
{
	MyList<int> _list1;
	_list1.push_back(1);
	MyList<int>* _pList2 = new MyList<int>(_list1);
	ASSERT_NE(_pList2, nullptr);

	delete _pList2;
	_pList2 = nullptr;
}

TEST(TestConstruction, TestRangeConstruction)							// 区间构造 GTest
{
	EXPECT_EQ(1, 1);

	// TODO:
}

TEST(TestPushAndPop, TestPushBack)
{
	MyList<int> _list1;
	for (int _i = 1; _i <= 10; _i++)
		_list1.push_back(_i);

	int _temp = 1;
	for (const auto& e : _list1)
		EXPECT_EQ(e, _temp++);
}

TEST(TestPushAndPop, TestPushFront)
{
	MyList<int> _list1;
	for (int _i = 1; _i <= 5; _i++)
		_list1.push_back(_i);

	_list1.push_front(99);

	EXPECT_EQ(*(_list1.begin()), 99);
}

TEST(TestPushAndPop, TestPopBack)
{
	MyList<int> _list1;
	
	_list1.push_back(1);
	_list1.push_back(2);

	_list1.pop_back();
	EXPECT_EQ(*(--_list1.end()), 1);

}

TEST(TestPushAndPop, TestPopFront)
{
	MyList<int> _list1;

	_list1.push_back(1);
	_list1.push_back(2);

	_list1.pop_front();
	EXPECT_EQ(*(_list1.begin()), 2);
}

TEST(TestSizeAndEmpty, TestEmpty)										// EmptyGTest
{
	MyList<int> _list1;
	EXPECT_TRUE(_list1.empty());
	_list1.push_back(1);
	EXPECT_FALSE(_list1.empty());
}

TEST(TestSizeAndEmpty, TestSize)										// SizeGTest
{
	MyList<int> _list1;
	EXPECT_EQ(_list1.size(), 0);
	_list1.push_back(1);
	EXPECT_EQ(_list1.size(), 1);
}

TEST(TestEraseAndClear, TestErase)										// EraseGTest
{
	MyList<int> _list1;
	_list1.push_back(0);
	_list1.push_back(1);
	_list1.push_back(2);

	MyList<int>::iterator _it = _list1.begin();
	_it++;
	_it = _list1.erase(_it);

	EXPECT_EQ(*_it, 2);
	EXPECT_EQ(_list1.size(), 2);
}

TEST(TestEraseAndClear, TestClear)										// ClearGTest
{
	MyList<int> _list1;
	_list1.push_back(0);
	_list1.push_back(1);
	_list1.push_back(2);

	_list1.clear();
	EXPECT_EQ(_list1.size(), 0);
	EXPECT_TRUE(_list1.empty());
}

TEST(TestInsert, TestInsert1)										// InsertGTest
{
	MyList<int> _list1;
	_list1.push_back(0);
	_list1.push_back(2);
	_list1.push_back(3);

	MyList<int>::iterator _it = _list1.begin();
	_it++;
	_it = _list1.insert(_it, 1);
	EXPECT_EQ(*_it, 1);
	EXPECT_EQ(_list1.size(), 4);
}

