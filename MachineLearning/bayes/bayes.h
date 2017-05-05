#pragma once
#ifndef BAYES_H
#define BAYES_H

#include<iostream>
#include<iomanip>
#include<iterator>
#include<typeinfo>
#include<fstream>
#include<sstream> 
#include<vector>
#include<set>
#include<map>
#include<string>
#include<cmath>
#include<regex>
#include<cctype> 
#include<algorithm>

using namespace std;

class CReTrainBN0
{
public:
	double pAbusive;//���1�ĵ��ĸ���
	vector<double> p0Num//�ʻ����ڵ����������0�ĸ�������
		, p1Num;//�ʻ����ڵ����������1�ĸ�������
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
int clssifyNB(const vector<int> &thisDoc, const CReTrainBN0 &resultTrain);

int testingNB();
void loadDataSet(vvMatrix &dataSet, vector<int> &classVec);
void spamTest();
#endif
