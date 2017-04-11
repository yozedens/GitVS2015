#pragma once

#include<io.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>

using namespace std;

void getFiles(string path, vector<string>& files);
vector<string> readContent(char* filePath);
vector<int> img2vector(string fileName);
vector<vector<int>> getDataSet(char* filePath, vector<string> &labels);


void matrix2file(vector<vector<int>> matrix, string fileName);


class Cfloatstr
{
public:
	double flo;
	string str;
};

bool compCfs(Cfloatstr a, Cfloatstr b);

template<typename T>
string classify(vector<T> inX, vector<vector<T>> dataSet, vector<string> labels, int k)
//string classify(vector<double> inX, vector<vector<double>> dataSet, vector<string> labels, int k)
{
	/*kNN���ຯ��
	inX��δ������������ݣ�dataSet����������labels����ǩ��k:kֵ
	return value�� �������ݵķ����ǩ

	date: 2017-04-08
	by: �����
	*/

	vector<Cfloatstr> labels_with_dis;//������ı�ǩ��
									  //����������������������ŷ�Ͼ���
	for (unsigned int j = 0; j < dataSet.size(); ++j)
	{
		double dis = 0;
		for (unsigned int i = 0; i < dataSet[j].size(); ++i)
		{
			dis += (dataSet[j][i] - inX[i])*(dataSet[j][i] - inX[i]);
		}
		dis = sqrt(dis);
		Cfloatstr vStr = { dis,labels[j] };//{����, ��ǩ}
		labels_with_dis.push_back(vStr);
	}
	sort(labels_with_dis.begin(), labels_with_dis.end(), compCfs);//����������,��ѵ�����ϴ���k��Сʱ������ð�ݷ�ѡȡ��������ǰk�����ɽ�ʡʱ��

																  //����ǰk�������Ӧ��ǩ���ֵĴ����������������
	map<string, int> count_labels;
	string label;
	for (int i = 0; i < k; i++)
	{
		label = labels_with_dis[i].str;
		++count_labels[label];
	}
	//�ҳ��������ı�ǩ��
	int max_count = count_labels.begin()->second;
	label = count_labels.begin()->first;
	for (auto i : count_labels)
	{
		if (max_count < i.second)
		{
			max_count = i.second;
			label = i.first;
		}
	}
	//�����ҵ��ı�ǩ��
	return label;
}


template<typename T>
void kNNTest(vector<vector<T>> testSet, vector<string> testLabels, vector<vector<T>> dataSet, vector<string> labels, int k)
{
	//�㷨����
	double count_wrong = 0;
	for (unsigned int j = 0; j < testSet.size(); ++j)
	{
		string label = classify(testSet[j], dataSet, labels, k);
		cout << j + 1 << "times, " << "the classifier return: " << label << ",the real answer is " << testLabels[j] << endl;
		if (label != testLabels[j])
		{
			++count_wrong;
			cout << "Wrong!!!" << endl;
		}
	}
	count_wrong /= (double)testSet.size();

	cout << "The total error rate is�� " << count_wrong << endl;

}