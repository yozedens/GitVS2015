#include<iostream>
#include<fstream>
#include<sstream> 
#include<vector>
#include<map>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;


class Cfloatstr
{
public:
	double flo;
	string str;
};

bool compCfs(Cfloatstr a, Cfloatstr b)
{
	if (a.flo < b.flo)
		return 1;
	else
		return 0;
}

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
	sort(labels_with_dis.begin(), labels_with_dis.end(), compCfs);//����������

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

void autoNormONE(vector<vector<double>> &dataSet)
{
	//��һ������ֵ
	size_t len = dataSet[0].size();
	vector<double> maxVal, minVal;
	for (auto val : dataSet[0])//�����һ��������
	{
		maxVal.push_back(val);
		minVal.push_back(val);
	}
	for (auto data : dataSet)//�ҳ�ÿ�����������ֵ����Сֵ
	{
		for (size_t i = 0; i < len; ++i)
		{
			if (data[i]>maxVal[i])
				maxVal[i] = data[i];
			if (data[i]<minVal[i])
				minVal[i] = data[i];
		}
	}
	for (auto &data : dataSet)
	{
		for (size_t i = 0; i < len; ++i)
		{
			data[i] = (data[i] - minVal[i]) / (maxVal[i] - minVal[i]);
			//cout << data[i] <<" ";
		}
		//cout << endl;
	}
}

void autoNormTWO(vector<vector<double>> &dataSet, vector<vector<double>> &testSet)
{
	//��һ������ֵ
	vector<vector<double>> allSet;
	allSet.insert(allSet.end(), dataSet.begin(), dataSet.end());
	allSet.insert(allSet.end(), testSet.begin(), testSet.end());//�ϲ���������

	size_t len = allSet[0].size();
	vector<double> maxVal, minVal;
	for (auto val : allSet[0])//�����һ��������
	{
		maxVal.push_back(val);
		minVal.push_back(val);
	}
	for (auto data : allSet)//�ҳ�ÿ�����������ֵ����Сֵ
	{
		for (size_t i = 0; i < len; ++i)
		{
			if (data[i]>maxVal[i])
				maxVal[i] = data[i];
			if (data[i]<minVal[i])
				minVal[i] = data[i];
		}
	}
	for (auto &data : dataSet)//��һ��dataSet
	{
		for (int i = 0; i < len; ++i)
		{
			data[i] = (data[i] - minVal[i]) / (maxVal[i] - minVal[i]);
			//cout << data[i] <<" ";
		}
		//cout << endl;
	}
	for (auto &data : testSet)//��һ��testSet
	{
		for (int i = 0; i < len; ++i)
		{
			data[i] = (data[i] - minVal[i]) / (maxVal[i] - minVal[i]);
			//cout << data[i] <<" ";
		}
		//cout << endl;
	}
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

void readFile(const char* fileName, vector<vector<double>> &dataSet, vector<string> &labels)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	string dataStr;
	double f;
	while (getline(file, dataStr))//��ȡһ��
	{
		cout << dataStr << endl;
		vector<double> vf;
		istringstream data(dataStr);//���ַ����ж�ȡ�ַ�
		while (data >> f)
		{
			vf.push_back(f);
			cout << f << endl;
		}
		vf.pop_back();//�Ƴ����һ��
		labels.push_back(to_string(f));//���һ���ַ������浽labels��
		dataSet.push_back(vf);
		//cout <<"dataSet[0][0]: "<< dataSet[0][0] << endl;
	}

	file.close();
}

void readFile2(const char* fileName, vector<vector<double>> &dataSet, vector<string> &labels)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	string dataStr, subStr;
	double f;
	int index = 0;
	while (getline(file, dataStr))//��ȡһ��
	{
		//cout << dataStr << endl;
		vector<double> vf;
		istringstream data(dataStr);//���ַ����ж�ȡ�ַ�
		for (int i = 1; i <= 3; ++i)
		{
			data >> f;
			vf.push_back(f);
			//cout << f << endl;
		}
		data >> subStr;
		labels.push_back(subStr);//���һ���ַ������浽labels��
		dataSet.push_back(vf);
		//cout <<"labels[index]: "<< labels[index++] << endl;
	}

	file.close();
}


int main()/*mainPerson()*/
{
	vector<vector<double>> dataSetX, testSetX;
	vector<string> labelsX, testLabelsX;
	vector<double> inXX = { 94900,	6.724021,	0.7 };
	int k = 3;



	readFile2("datingTrainSet2.txt", dataSetX, labelsX);

	readFile2("datingTestSet2.txt", testSetX, testLabelsX);
	//readFile("datingTrainSet.txt", testSetX, testLabelsX);

	autoNormTWO(dataSetX, testSetX);

	kNNTest(testSetX, testLabelsX, dataSetX, labelsX, k);//�㷨����

	cout << "------------------------------------------------------" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "inX�ķ����ǣ� " << classify(inXX, dataSetX, labelsX, k) << endl;

	system("pause");
	return 0;
}