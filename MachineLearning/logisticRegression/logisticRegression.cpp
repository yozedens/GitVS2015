#include<iostream>
#include<fstream>
#include<sstream> 
#include<vector>
#include<string>
#include<cmath>

#include"E:\yuzudeng\GitVS2015\MachineLearning\bayes\coutContainer.h"

using namespace std;

void readFile2(const char* fileName, vector<vector<double>> &dataSet, vector<double> &labels)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	double data1, data2, data3;
	while (file>> data1>> data2>> data3)//读取一行
	{
		vector<double> vf = {1.0};
		vf.push_back(data1);
		vf.push_back(data2);
		dataSet.push_back(vf);
		labels.push_back(data3);//最后一个字符串保存到labels中	
	}

	file.close();
}

double sigmoid(const double& inX)
{
	return 1.0 / (1 + exp(-inX));
}


vector<double> sigmoid(const vector<double>& inX)
{
	vector<double> reVecD;
	for (auto inx : inX)
	{
		reVecD.push_back(1.0 / (1 + exp(-inx)));
	}
	return reVecD;
}
vector<double> matMultiply(const vector<vector<double>> &dataSet, const vector<double> &labels)
{
	size_t lenDataSet = dataSet.size();
	size_t lenLabels = labels.size();
	if (lenDataSet == 0 || lenLabels == 0 || dataSet[0].size() != lenLabels)
	{
		cout << "can not do this multiply!\n";
		return;
	}
	vector<double> result;
	for (size_t i = 0; i < lenDataSet; i++)
	{
		for (size_t j = 0; j < lenLabels; j++)
		{
			result.push_back(dataSet[i][j] * labels[j]);
		}
	}
	return result;
}

vector<double> gradAscent(const vector<vector<double>> &dataSet, const vector<double> &labels)
{
	int lenOneData = dataSet[0].size();
	vector<double> weights(lenOneData, 1.0);
	for (size_t i = 0; i < 500; i++)
	{
		vector<double> h = sigmoid(matMultiply(dataSet, weights));

	}
	return weights;

}

int main()
{
	vector<vector<double>> dataSetX, testSetX;
	vector<double> labelsX, testLabelsX;


	readFile2("testSet.txt", dataSetX, labelsX);
	coutVecVec(dataSetX, "dataSet:\n", 10);
	coutVec(labelsX, "labelsX:\n");


	system("pause");
}