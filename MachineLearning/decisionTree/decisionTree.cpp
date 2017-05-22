#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<cmath>
#include<fstream>
#include<sstream>
#include"tree.h"

using namespace std;


double calcShannonEnt(vector<vector<string>> dataSet)
{
	//����������ݼ�����ũ��,dataSet���һ���Ǳ�ǩ
	size_t numEntries = dataSet.size();
	map<string, int> labelCounts;
	for (auto featVec : dataSet)
	{
		string currentLabel = featVec.back();
		labelCounts[currentLabel]++;
	}
	double shannonEnt = 0.0;
	for (auto label : labelCounts)
	{
		double prob = double(label.second) / (double)numEntries;
		shannonEnt -= prob*log(prob)/log(2);
	}
	return shannonEnt;
}

vector<vector<string>> splitDataSet(vector<vector<string>> dataSet, int axis, string value)
{
	vector<vector<string>> retDataSet;
	for (auto featVec : dataSet)
	{
		if (featVec[axis] == value)//ѡ�����ʵ�������
		{
			vector<string> reducedFeatVec = featVec;
			reducedFeatVec.erase(reducedFeatVec.begin() + axis);//�Ƴ����ڻ��ֵ�����
			//int len = featVec.size();
			//for (int i = 0; i < len; ++i)
			//{
			//	if(i!=axis)//��ȡ���������������������
			//		reducedFeatVec.push_back(featVec[i]);
			//}
			retDataSet.push_back(reducedFeatVec);
		}
	}
	return retDataSet;
}

int chooseBestFeatureToSplit(vector<vector<string>> dataSet)
{
	//ѡ����õ����ݼ����ַ�ʽ
	size_t numFeatures = dataSet[0].size() - 1;
	double baseEntropy = calcShannonEnt(dataSet);
	double bestInfoGain = 0.0;
	int bestFeature = -1;
	for (int i = 0; i < numFeatures; i++)
	{
		set<string> featList;
		for (auto featVec : dataSet)
		{
			featList.insert(featVec[i]);
		}
		double newEntropy = 0.0;
		for (auto value : featList)
		{
			vector<vector<string>> subDataSet = splitDataSet(dataSet, i, value);
			double prob = subDataSet.size() / (double)dataSet.size();
			newEntropy += prob*calcShannonEnt(subDataSet);
		}
		double infoGain = baseEntropy - newEntropy;
		if (infoGain > bestInfoGain)
		{
			bestInfoGain = infoGain;
			bestFeature = i;
		}
	}
	return bestFeature;
}

string createTree(vector<vector<string>> dataSet, vector<string> labels)
{
	map<string, int> classList;
	for (auto vecStr : dataSet)
	{
		classList[vecStr.back()]++;
	}
	if (classList.size()==1)//�����ȫ��ͬ��ֹͣ��������
	{
		//return dataSet[0][0] + " : " + classList.begin()->first + ", ";
		return classList.begin()->first;

	}
	if (dataSet[0].size()==1)//��������������ʱ���س��ִ�������
	{
		string majorityClass = classList.begin()->first;
		int maxCount = classList.begin()->second;
		for (auto classl :classList)
		{
			if (classl.second>maxCount)
			{
				maxCount = classl.second;
				majorityClass = classl.first;
			}
		}
		return "All : " + majorityClass;
	}
	int bestFeat = chooseBestFeatureToSplit(dataSet);
	string bestFeatLabel = labels[bestFeat];
	string strTree = "{" + bestFeatLabel + ": {";//��string��������ַ�����ʽ�ľ����������㷨������ʵ������
	vector<string> subLabels = labels;
	subLabels.erase(subLabels.begin() + bestFeat);
	set<string> featValues;
	for (auto example : dataSet)
	{
		featValues.insert(example[bestFeat]);
	}
	for (string value : featValues)
	{
		strTree += value + " : " + createTree(splitDataSet(dataSet, bestFeat, value), subLabels) + ", ";
	}
	strTree.pop_back();//�Ƴ�ĩβ�Ķ���
	strTree.pop_back();//�Ƴ�ĩβ�Ŀո�

	strTree += "}}";
	return strTree;
}

CTreeNode* createTree(CTreeNode* p, vector<vector<string>> dataSet, vector<string> labels)
{
	map<string, int> classList;
	for (auto vecStr : dataSet)
	{
		classList[vecStr.back()]++;
	}
	if (classList.size() == 1)//�����ȫ��ͬ��ֹͣ��������
	{
		//return dataSet[0][0] + " : " + classList.begin()->first + ", ";
		//CTreeNode* p = new CTreeNode;
		p->arrivedFeature = classList.begin()->first;
		return p;

	}
	if (dataSet[0].size() == 1)//��������������ʱ���س��ִ�������
	{
		string majorityClass = classList.begin()->first;
		int maxCount = classList.begin()->second;
		for (auto classl : classList)
		{
			if (classl.second>maxCount)
			{
				maxCount = classl.second;
				majorityClass = classl.first;
			}
		}
		//CTreeNode* p = new CTreeNode;
		p->arrivedFeature = majorityClass;
		return p;
	}
	int bestFeat = chooseBestFeatureToSplit(dataSet);
	string bestFeatLabel = labels[bestFeat];
	//string strTree = "{" + bestFeatLabel + ": {";//��string��������ַ�����ʽ�ľ����������㷨������ʵ������
	vector<string> subLabels = labels;
	subLabels.erase(subLabels.begin() + bestFeat);
	set<string> featValues;
	for (auto example : dataSet)
	{
		featValues.insert(example[bestFeat]);
	}
	//CTreeNode* p = new CTreeNode;
	p->arrivedFeature = bestFeatLabel;
	for (string value : featValues)
	{
		CTreeNode* newNode = new CTreeNode;
		newNode->valueForLastFeature = value;
		newNode = createTree(newNode, splitDataSet(dataSet, bestFeat, value), subLabels);
		p->childs.push_back(newNode);

		
		//strTree += value + " : " + createTree(splitDataSet(dataSet, bestFeat, value), subLabels) + ", ";
	}
	//strTree.pop_back();//�Ƴ�ĩβ�Ķ���
	//strTree.pop_back();//�Ƴ�ĩβ�Ŀո�
	//strTree += "}}";
	return p;
}

void coutVecVecStr(const vector<vector<string>>& data)
{
	//��ӡ����������
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

void readFile(const char* fileName, vector<vector<string>> &dataSet)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	string dataStr;
	string f;
	while (getline(file, dataStr))//��ȡһ��
	{
		//cout << dataStr << endl;
		vector<string> vf;
		istringstream data(dataStr);//���ַ����ж�ȡ�ַ�
		while (data >> f)
		{
			vf.push_back(f);
			//cout << f << endl;
		}
		dataSet.push_back(vf);
		//cout <<"dataSet[0][0]: "<< dataSet[0][0] << endl;
	}

	file.close();
}

int main()
{
	/*vector<vector<string>> dataSet = { { "1","1","yes" },
									   { "1","1","yes" },
									   { "1","0","no" },
									   { "0","1","no" },
									   { "0","1","no" } };
	vector<string> labels = { "no surfacing","flippers" };
	cout << createTree(dataSet, labels) << endl;*/
	vector<vector<string>> dataSet;
	char fileName[11] = "lenses.txt";
	readFile(fileName, dataSet);
	vector<string> labels = { "age","prescript","astigmatic","tearRate" };
	cout << createTree(dataSet, labels) << endl;


	//coutVecVecStr(dataSet);
	//cout << calcShannonEnt(dataSet) << endl;
	//vector<vector<string>> sDataSet = splitDataSet(dataSet, 0, "1");
	//coutVecVecStr(sDataSet);
	//cout << chooseBestFeatureToSplit(dataSet)<<endl;

	/*vector<string> dataS = { "0", "1", "no" };
	int a = 2;
	dataS.erase(dataS.begin() + a);
	for (string d : dataS)
	{
		cout << d << " ";
	}
	cout << endl;*/

	CTreeNode* T = new CTreeNode;
	T = createTree(T, dataSet, labels);
	//T = BuildTree(T);
	//T->print();
	PreOrderTraverse(T);

	system("pause");
	return 0;
}


