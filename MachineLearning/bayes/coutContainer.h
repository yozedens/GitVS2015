#pragma once
//��ʹ��copy�����������(Container)�е�Ԫ��, ���Դ���forѭ��.
/*
ͷ�ļ�:
#include <algorithm>
#include <iterator>
��ʽ: std::copy(cont.begin(), cont.end(),std::ostream_iterator<Type>(std::cout, " "));*/
//copy(vocabSet.begin(), vocabSet.end(), ostream_iterator<string>(cout, " "));

#include<iostream>
using namespace std;

//�����׼������ӡ��������vector<T>,����TӦΪ���������ͻ�ָ������
template<typename T>
void coutVec(const T &data, const string& optcstr = "", const int &widthOfElemPrint = 4,const string& separator=" ")
{
	cout << optcstr;
	//��ӡ����������
	for (auto str : data)
	{
		cout << left << setw(widthOfElemPrint) << str << separator;
	}
	cout << endl;
}

//˫���׼��������vector<vector<T>>��set<set<T>>,����TӦΪ���������ͻ�ָ�����ͣ���ӡ����
template<typename TT>
void coutVecVec(const TT &data, const string& optcstr = "", const int &widthOfElemPrint = 4)
{
	cout << optcstr;

	//��ӡ����������
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
