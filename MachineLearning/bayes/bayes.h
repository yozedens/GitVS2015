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
	double pAbusive;//类别1文档的概率
	vector<double> p0Num//词汇表对于单词属于类别0的概率向量
		, p1Num;//词汇表对于单词属于类别1的概率向量
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
int clssifyNB(const vector<int> &thisDoc, const CReTrainBN0 &resultTrain);

int testingNB();
void loadDataSet(vvMatrix &dataSet, vector<int> &classVec);
void spamTest();
#endif
