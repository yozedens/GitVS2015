#pragma once
#ifndef BAYES_H
#define BAYES_H

#include<iostream>
#include<iomanip>
#include<iterator>
#include <typeinfo>
#include<fstream>
#include<sstream> 
#include<vector>
#include<set>
#include<map>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

class CReTrainBN0
{
public:
	double pAbusive;
	vector<double> p0Num, p1Num;
};

//类矩阵数据类型
typedef vector<vector<string>> vvMatrix;//类矩阵数据类型

//创建一个包含在所有文档中出现的不重复词的有序集合
set<string> createVocabList(const vvMatrix &dataSet);

//词集模型，将输入文档inputSet按照词汇表vocabList转化为一个对应词汇是否出现的参考向量
vector<int> setOfWords2Vec(const set<string> &vocabList, const vector<string> &inputSet);

//词袋模型，将输入文档inputSet按照词汇表vocabList转化为一个对应词汇出现几次的参考向量
vector<int> bagOfWords2VecMN(const set<string> &vocabList, const vector<string> &inputSet);

//朴素贝叶斯分类器训练函数
CReTrainBN0 trainNB0(const vector<vector<int>> &trainMatrix, const vector<int> &trainCategory);

//朴素贝叶斯分类器训练函数,修改版1
CReTrainBN0 trainNB(const vector<vector<int>> &trainMatrix, const vector<int> &trainCategory);

//朴素贝叶斯分类函数
int clssifyNB(vector<int> thisDoc, CReTrainBN0 resultTrain);


//可使用copy函数输出容器(Container)中的元素, 可以代替for循环.
/*
头文件:
#include <algorithm>
#include <iterator>
格式: std::copy(cont.begin(), cont.end(),std::ostream_iterator<Type>(std::cout, " "));*/
//copy(vocabSet.begin(), vocabSet.end(), ostream_iterator<string>(cout, " "));

//单层标准容器打印函数，如vector<T>,其中T应为简单数据类型或指针类型
template<typename T>
void coutVec(const T &data, const string& optcstr = "", const int &widthOfElemPrint = 4)
{
	cout << optcstr;
	//打印该数据类型
	for (auto str : data)
	{
		cout << left << setw(widthOfElemPrint) << str << ' ';
	}
	cout <<endl;
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


int testingNB();
void loadDataSet(vvMatrix &dataSet, vector<int> &classVec);
#endif
