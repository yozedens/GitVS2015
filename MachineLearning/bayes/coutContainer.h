#pragma once
//可使用copy函数输出容器(Container)中的元素, 可以代替for循环.
/*
头文件:
#include <algorithm>
#include <iterator>
格式: std::copy(cont.begin(), cont.end(),std::ostream_iterator<Type>(std::cout, " "));*/
//copy(vocabSet.begin(), vocabSet.end(), ostream_iterator<string>(cout, " "));

#include<iostream>
using namespace std;

//单层标准容器打印函数，如vector<T>,其中T应为简单数据类型或指针类型
template<typename T>
void coutVec(const T &data, const string& optcstr = "", const int &widthOfElemPrint = 4,const string& separator=" ")
{
	cout << optcstr;
	//打印该数据类型
	for (auto str : data)
	{
		cout << left << setw(widthOfElemPrint) << str << separator;
	}
	cout << endl;
}

//双层标准容器（如vector<vector<T>>、set<set<T>>,其中T应为简单数据类型或指针类型）打印函数
template<typename TT>
void coutVecVec(const TT &data, const string& optcstr = "", const int &widthOfElemPrint = 4)
{
	cout << optcstr;

	//打印该数据类型
	for (auto vecStr : data)
	{
		for (auto str : vecStr)
		{
			cout << left << setw(widthOfElemPrint) << str << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
