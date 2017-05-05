#include"bayes.h"



//����һ�������������ĵ��г��ֵĲ��ظ��ʵ����򼯺�
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

//�ʼ�ģ�ͣ��������ĵ�inputSet���մʻ��vocabListת��Ϊһ����Ӧ�ʻ��Ƿ���ֵĲο�����
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

//�ʴ�ģ�ͣ��������ĵ�inputSet���մʻ��vocabListת��Ϊһ����Ӧ�ʻ���ּ��εĲο�����
vector<int> bagOfWords2VecMN(const set<string> &vocabList, const vector<string> &inputSet)
{
	map<string, int> mVec;
	for (auto str : vocabList)//��ʼ��Ϊ0
		mVec.insert({ str,0 });
	for (auto word : inputSet)
	{
		if (vocabList.find(word) != vocabList.end())
		{
			mVec[word] += 1;//��ʼ�ģ��Ψһ��ͬ���Ǵ˴��ۼӣ�����������¼1
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

//���ر�Ҷ˹������ѵ������
CReTrainBN0 trainNB0(const vector<vector<int>> &trainMatrix, const vector<int> &trainCategory)
{
	auto numTrainDocs = trainMatrix.size();
	auto numWords = trainMatrix[0].size();
	double pAbusive = 0.0;//�������ĵ��ĸ���p(c1)��������������
	for (auto num : trainCategory)
	{
		pAbusive += num / (double)numTrainDocs;
	}
	vector<double> p0Num(numWords), p1Num(numWords);//����ΪnumWords������ʻ���ȶ�Ӧ
	int p0Denom = 0, p1Denom = 0;
	for (size_t i = 0; i < numTrainDocs; ++i)//��ÿһ���ĵ����в���
	{
		if (trainCategory[i] == 1)//������ĵ������������ĵ�
		{
			p1Denom += count(trainMatrix[i].begin(), trainMatrix[i].end(), 1);//ͳ�Ƶ�����
			for (size_t j = 0; j < numWords; j++)//�Դʻ����ÿ���ʻ�
			{
				p1Num[j] += trainMatrix[i][j];
			}
		}
		else
		{
			p0Denom += count(trainMatrix[i].begin(), trainMatrix[i].end(), 1);//ͳ�Ƶ�����
			for (size_t j = 0; j < numWords; j++)//�Դʻ����ÿ���ʻ�
			{
				p0Num[j] += trainMatrix[i][j];
			}
		}
	}
	for (size_t i = 0; i < numWords; i++)//����ʻ����ÿ���ʻ��ڶ�Ӧ����ĵ��г��ֵĸ���
	{
		p0Num[i] = p0Num[i] / (double)p0Denom;
		p1Num[i] = p1Num[i] / (double)p1Denom;
	}
	CReTrainBN0 reTrainBN0 = { pAbusive,p0Num,p1Num };
	return reTrainBN0;
}

//���ر�Ҷ˹������ѵ������,�޸İ�1
CReTrainBN0 trainNB(const vector<vector<int>> &trainMatrix, const vector<int> &trainCategory)
{
	/*
		1���޸�p0Num��p1Num��p0Denom��p1Denom�ĳ�ֵ���������Ϊ0ֵ
		2�������޸�Ϊ������ʽ����������С�������������
	*/
	auto numTrainDocs = trainMatrix.size();
	auto numWords = trainMatrix[0].size();
	double pAbusive = 0.0;//���1�ĵ��ĸ���p(c1)��������������
	for (auto num : trainCategory)
	{
		pAbusive += num / (double)numTrainDocs;
	}
	vector<double> p0Num(numWords, 1.0), p1Num(numWords, 1.0);//����ΪnumWords������ʻ���ȶ�Ӧ
	int p0Denom = 2, p1Denom = 2;
	for (size_t i = 0; i < numTrainDocs; ++i)//��ÿһ���ĵ����в���
	{
		if (trainCategory[i] == 1)//������ĵ��������1�ĵ�
		{
			p1Denom += count(trainMatrix[i].begin(), trainMatrix[i].end(), 1);//ͳ�Ƶ�����
			for (size_t j = 0; j < numWords; j++)//�Դʻ����ÿ���ʻ�
			{
				p1Num[j] += trainMatrix[i][j];
			}
		}
		else
		{
			p0Denom += count(trainMatrix[i].begin(), trainMatrix[i].end(), 1);//ͳ�Ƶ�����
			for (size_t j = 0; j < numWords; j++)//�Դʻ����ÿ���ʻ�
			{
				p0Num[j] += trainMatrix[i][j];
			}
		}
	}
	for (size_t i = 0; i < numWords; i++)//����ʻ����ÿ���ʻ��ڶ�Ӧ����ĵ��г��ֵĸ���
	{
		p0Num[i] = log(p0Num[i] / (double)p0Denom);//��Ȼ����
		p1Num[i] = log(p1Num[i] / (double)p1Denom);
	}
	CReTrainBN0 reTrainBN0 = { pAbusive,p0Num,p1Num };
	return reTrainBN0;
}
//��ӡ�����ݼ�

//���ر�Ҷ˹���ຯ��
int clssifyNB(const vector<int> &thisDoc, const CReTrainBN0 &resultTrain)
{
	auto lenDoc = thisDoc.size();
	double p1 = 0.0, p0 = 0.0;
	for (size_t i = 0; i < lenDoc; ++i)
	{
		p1 += thisDoc[i] * resultTrain.p1Num[i];
		p0 += thisDoc[i] * resultTrain.p0Num[i];
	}
	p1 += log(resultTrain.pAbusive);//��Ȼ����
	p0 += log(1 - resultTrain.pAbusive);
	if (p1>p0)//���ر�Ҷ˹����׼��
	{
		return 1;
	}
	else
	{
		return 0;
	}

}



