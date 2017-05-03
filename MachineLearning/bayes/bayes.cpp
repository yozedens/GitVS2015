#include<iostream>
#include<iterator>

#include<fstream>
#include<sstream> 
#include<vector>
#include<set>
#include<map>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;

//类矩阵数据类型
typedef vector<vector<string>> vvMatrix;//类矩阵数据类型

void loadDataSet(vvMatrix &dataSet, vector<int> &classVec)
{
	dataSet = { {"my","dog","has","flea","problems","help","please"},
				{"maybe","not","take","him","to","dog","park","stupid"},
				{ "my","dalmation","is","so","cute","i","love","him" },
				{ "stop","posting","stupid","worthless","garbage" },
				{ "mr","licks","ate","my","steak","how","to","stop","him" },
				{ "quit","buying","worthless","dog","food","stupid"} };
	classVec = { 0,1,0,1,0,1 };
}

set<string> createVocabList(vvMatrix dataSet)
{
	set<string> vocabSet;
	for (auto vecStr : dataSet)
	{
		for (auto str : vecStr)
		{
			vocabSet.insert(str);
		}
	}
	return vocabSet;
}

vector<int> setOfWords2Vec(set<string> vocabList, vector<string> inputSet)
{
	map<string, int> mVec;
	for (auto str : vocabList)
		mVec.insert({ str,0 });
	for (auto word : inputSet)
	{
		if (vocabList.find(word)!=vocabList.end())
		{
			mVec[word] = 1;
		}
		else
		{
			cout << "the word: " << word << " is not in my Vocabulary! " << endl;
		}
	}
	vector<int> reVec;
	for (auto data : mVec)
	{
		reVec.push_back(data.second);
	}
	return reVec;
}

void trainNB0(vector<vector<int>> trainMatrix, vector<int> trainCategory)
{
	auto numTrainDocs = trainMatrix.size();
	auto numWords = trainMatrix[0].size();
	double pAbusive = 0.0;//侮辱性文档的概率p(c1)，数量除以总数
	for (auto num : trainCategory)
	{
		pAbusive += num / (double)numTrainDocs;
	}
	vector<double> p0Num, p1Num;
	double p0Denom, p1Denom;
	for (auto i = 0; i < numTrainDocs; ++i)
	{

	}
}

//打印该数据集
void coutVecVecStr(const vector<vector<string>> &data)
{
	//打印该数据类型
	cout << endl;
	for (auto vecStr : data)
	{
		for (auto str : vecStr)
		{
			cout << str << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	vvMatrix dataSet = { };
	vector<int> classVec;
	//vector<string> inputDataSet;
	//coutVecVecStr(dataSet);

	loadDataSet(dataSet, classVec);
	//coutVecVecStr(dataSet);

	set<string> vocabSet = createVocabList(dataSet);
	//使用copy函数输出容器(Container)中的元素, 可以代替for循环.
	/*
	头文件: 
	#include <algorithm>
	#include <iterator>
	格式: std::copy(cont.begin(), cont.end(),std::ostream_iterator<Type>(std::cout, " "));*/
	copy(vocabSet.begin(), vocabSet.end(), ostream_iterator<string>(cout, " "));
	cout << "\nlength of vocabList = " << vocabSet.size() << endl;

	vector<int> reslutVec = setOfWords2Vec(vocabSet, dataSet[3]);

	copy(reslutVec.begin(), reslutVec.end(), ostream_iterator<int>(cout, " "));
	system("pause");
}