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
	//计算给定数据集的香农熵,dataSet最后一列是标签
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
		if (featVec[axis] == value)//选定合适的数据行
		{
			vector<string> reducedFeatVec = featVec;
			reducedFeatVec.erase(reducedFeatVec.begin() + axis);//移除用于划分的特征
			//int len = featVec.size();
			//for (int i = 0; i < len; ++i)
			//{
			//	if(i!=axis)//抽取除划分特征外的所有特征
			//		reducedFeatVec.push_back(featVec[i]);
			//}
			retDataSet.push_back(reducedFeatVec);
		}
	}
	return retDataSet;
}

int chooseBestFeatureToSplit(vector<vector<string>> dataSet)
{
	//选择最好的数据集划分方式
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
	if (classList.size()==1)//类别完全相同则停止继续划分
	{
		//return dataSet[0][0] + " : " + classList.begin()->first + ", ";
		return classList.begin()->first;

	}
	if (dataSet[0].size()==1)//遍历完所有特征时返回出现次数最多的
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
	string strTree = "{" + bestFeatLabel + ": {";//该string用于输出字符串形式的决策树，对算法本身无实际作用
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
	strTree.pop_back();//移除末尾的逗号
	strTree.pop_back();//移除末尾的空格

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
	if (classList.size() == 1)//类别完全相同则停止继续划分
	{
		//return dataSet[0][0] + " : " + classList.begin()->first + ", ";
		//CTreeNode* p = new CTreeNode;
		p->arrivedFeature = classList.begin()->first;
		return p;

	}
	if (dataSet[0].size() == 1)//遍历完所有特征时返回出现次数最多的
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
	//string strTree = "{" + bestFeatLabel + ": {";//该string用于输出字符串形式的决策树，对算法本身无实际作用
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
	//strTree.pop_back();//移除末尾的逗号
	//strTree.pop_back();//移除末尾的空格
	//strTree += "}}";
	return p;
}

void coutVecVecStr(const vector<vector<string>>& data)
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

void readFile(const char* fileName, vector<vector<string>> &dataSet)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	string dataStr;
	string f;
	while (getline(file, dataStr))//读取一行
	{
		//cout << dataStr << endl;
		vector<string> vf;
		istringstream data(dataStr);//从字符传中读取字符
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


