#pragma once
#include"MyList.h"
// #include"otherList.h"
#include<list>
#include<algorithm>
using namespace mylist;

bool TestCopyConstruction()
{
	MyList<int> _list1;
	_list1.push_back(1);
	std::cout << _list1.size() << std::endl;
	MyList<int> _List2(_list1);

	const MyList<int> _List3(_list1);


	return true;
}

bool TestPushBack()
{
	MyList<int> _list1;
	for (int _i = 1; _i <= 10; _i++)
		_list1.push_back(_i);

	int _temp = 1;
	for (const auto& e : _list1)
		if (e != _temp++)
		{
			throw"push back error";
		}
	
	return true;
}

struct stu
{
	int id;
	double money;
	char name;
};

bool cmp2(stu stu1, stu stu2)
{
	return stu1.id > stu2.id;
}

#define DBL_MAX         1.7976931348623158e+308 /* max value */
#define __CUT(x, low, up)	((x) = std::min((x), (up)), (x) = std::max((x), (low)))

int main()
{
	// TestCopyConstruction();
	// TODO:
	// TestPushBack();
	
	double _nfaf = DBL_MAX * 9;
	bool _bfaf = isinf(_nfaf);
	double _nl = __CUT(_nfaf, 0., DBL_MAX);
	std::cout << _nl;


	/*stu stu1{ 1,20,'a' };
	stu stu2{ 9,25,'d' };
	stu stu3{ 4,14,'b' };
	stu stu4{ 6,17,'e' };
	stu stu5{ 8,9,'c' };

	std::list<stu> _list1;
	_list1.push_back(stu1);
	_list1.push_back(stu2);
	_list1.push_back(stu3);
	_list1.push_back(stu4);
	_list1.push_back(stu5);*/


	// _list1.sort(cmp2);
	
	
	return 0;
}