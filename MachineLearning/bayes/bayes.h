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

//�������������
typedef vector<vector<string>> vvMatrix;//�������������

//����һ�������������ĵ��г��ֵĲ��ظ��ʵ����򼯺�
set<string> createVocabList(const vvMatrix &dataSet);

//�ʼ�ģ�ͣ��������ĵ�inputSet���մʻ��vocabListת��Ϊһ����Ӧ�ʻ��Ƿ���ֵĲο�����
vector<int> setOfWords2Vec(const set<string> &vocabList, const vector<string> &inputSet);

//�ʴ�ģ�ͣ��������ĵ�inputSet���մʻ��vocabListת��Ϊһ����Ӧ�ʻ���ּ��εĲο�����
vector<int> bagOfWords2VecMN(const set<string> &vocabList, const vector<string> &inputSet);

//���ر�Ҷ˹������ѵ������
CReTrainBN0 trainNB0(const vector<vector<int>> &trainMatrix, const vector<int> &trainCategory);

//���ر�Ҷ˹������ѵ������,�޸İ�1
CReTrainBN0 trainNB(const vector<vector<int>> &trainMatrix, const vector<int> &trainCategory);

//���ر�Ҷ˹���ຯ��
int clssifyNB(vector<int> thisDoc, CReTrainBN0 resultTrain);


//��ʹ��copy�����������(Container)�е�Ԫ��, ���Դ���forѭ��.
/*
ͷ�ļ�:
#include <algorithm>
#include <iterator>
��ʽ: std::copy(cont.begin(), cont.end(),std::ostream_iterator<Type>(std::cout, " "));*/
//copy(vocabSet.begin(), vocabSet.end(), ostream_iterator<string>(cout, " "));

//�����׼������ӡ��������vector<T>,����TӦΪ���������ͻ�ָ������
template<typename T>
void coutVec(const T &data, const string& optcstr = "", const int &widthOfElemPrint = 4)
{
	cout << optcstr;
	//��ӡ����������
	for (auto str : data)
	{
		cout << left << setw(widthOfElemPrint) << str << ' ';
	}
	cout <<endl;
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


int testingNB();
void loadDataSet(vvMatrix &dataSet, vector<int> &classVec);
#endif
