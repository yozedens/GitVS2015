#include"bayes.h"



//创建一个包含在所有文档中出现的不重复词的有序集合
set<string> createVocabList(const vvMatrix &dataSet)
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

//词集模型，将输入文档inputSet按照词汇表vocabList转化为一个对应词汇是否出现的参考向量
vector<int> setOfWords2Vec(const set<string> &vocabList, const vector<string> &inputSet)
{
	map<string, int> mVec;
	for (auto str : vocabList)
		mVec.insert({ str,0 });
	for (auto word : inputSet)
	{
		if (vocabList.find(word) != vocabList.end())
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

//词袋模型，将输入文档inputSet按照词汇表vocabList转化为一个对应词汇出现几次的参考向量
vector<int> bagOfWords2VecMN(const set<string> &vocabList, const vector<string> &inputSet)
{
	map<string, int> mVec;
	for (auto str : vocabList)//初始化为0
		mVec.insert({ str,0 });
	for (auto word : inputSet)
	{
		if (vocabList.find(word) != vocabList.end())
		{
			mVec[word] += 1;//与词集模型唯一不同的是此处累加，而不单单记录1
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

//朴素贝叶斯分类器训练函数
CReTrainBN0 trainNB0(const vector<vector<int>> &trainMatrix, const vector<int> &trainCategory)
{
	auto numTrainDocs = trainMatrix.size();
	auto numWords = trainMatrix[0].size();
	double pAbusive = 0.0;//侮辱性文档的概率p(c1)，数量除以总数
	for (auto num : trainCategory)
	{
		pAbusive += num / (double)numTrainDocs;
	}
	vector<double> p0Num(numWords), p1Num(numWords);//长度为numWords，即与词汇表长度对应
	int p0Denom = 0, p1Denom = 0;
	for (size_t i = 0; i < numTrainDocs; ++i)//对每一个文档进行操作
	{
		if (trainCategory[i] == 1)//如果该文档属于侮辱性文档
		{
			p1Denom += count(trainMatrix[i].begin(), trainMatrix[i].end(), 1);//统计单词数
			for (size_t j = 0; j < numWords; j++)//对词汇表中每个词汇
			{
				p1Num[j] += trainMatrix[i][j];
			}
		}
		else
		{
			p0Denom += count(trainMatrix[i].begin(), trainMatrix[i].end(), 1);//统计单词数
			for (size_t j = 0; j < numWords; j++)//对词汇表中每个词汇
			{
				p0Num[j] += trainMatrix[i][j];
			}
		}
	}
	for (size_t i = 0; i < numWords; i++)//计算词汇表中每个词汇在对应类别文档中出现的概率
	{
		p0Num[i] = p0Num[i] / (double)p0Denom;
		p1Num[i] = p1Num[i] / (double)p1Denom;
	}
	CReTrainBN0 reTrainBN0 = { pAbusive,p0Num,p1Num };
	return reTrainBN0;
}

//朴素贝叶斯分类器训练函数,修改版1
CReTrainBN0 trainNB(const vector<vector<int>> &trainMatrix, const vector<int> &trainCategory)
{
	/*
		1、修改p0Num、p1Num、p0Denom、p1Denom的初值，避免概率为0值
		2、概率修改为对数形式，避免多个很小数相乘造成下溢出
	*/
	auto numTrainDocs = trainMatrix.size();
	auto numWords = trainMatrix[0].size();
	double pAbusive = 0.0;//类别1文档的概率p(c1)，数量除以总数
	for (auto num : trainCategory)
	{
		pAbusive += num / (double)numTrainDocs;
	}
	vector<double> p0Num(numWords, 1.0), p1Num(numWords, 1.0);//长度为numWords，即与词汇表长度对应
	int p0Denom = 2, p1Denom = 2;
	for (size_t i = 0; i < numTrainDocs; ++i)//对每一个文档进行操作
	{
		if (trainCategory[i] == 1)//如果该文档属于类别1文档
		{
			p1Denom += count(trainMatrix[i].begin(), trainMatrix[i].end(), 1);//统计单词数
			for (size_t j = 0; j < numWords; j++)//对词汇表中每个词汇
			{
				p1Num[j] += trainMatrix[i][j];
			}
		}
		else
		{
			p0Denom += count(trainMatrix[i].begin(), trainMatrix[i].end(), 1);//统计单词数
			for (size_t j = 0; j < numWords; j++)//对词汇表中每个词汇
			{
				p0Num[j] += trainMatrix[i][j];
			}
		}
	}
	for (size_t i = 0; i < numWords; i++)//计算词汇表中每个词汇在对应类别文档中出现的概率
	{
		p0Num[i] = log(p0Num[i] / (double)p0Denom);//自然对数
		p1Num[i] = log(p1Num[i] / (double)p1Denom);
	}
	CReTrainBN0 reTrainBN0 = { pAbusive,p0Num,p1Num };
	return reTrainBN0;
}
//打印该数据集

//朴素贝叶斯分类函数
int clssifyNB(const vector<int> &thisDoc, const CReTrainBN0 &resultTrain)
{
	auto lenDoc = thisDoc.size();
	double p1 = 0.0, p0 = 0.0;
	for (size_t i = 0; i < lenDoc; ++i)
	{
		p1 += thisDoc[i] * resultTrain.p1Num[i];
		p0 += thisDoc[i] * resultTrain.p0Num[i];
	}
	p1 += log(resultTrain.pAbusive);//自然对数
	p0 += log(1 - resultTrain.pAbusive);
	if (p1>p0)//朴素贝叶斯分类准则
	{
		return 1;
	}
	else
	{
		return 0;
	}

}



