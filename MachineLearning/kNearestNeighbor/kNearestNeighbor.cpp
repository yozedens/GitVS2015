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

string classify(vector<double> inX, vector<vector<double>> dataSet, vector<string> labels, int k)
{
	/*kNN分类函数
	 inX：未分类的输入数据，dataSet：样本集，labels：标签，k:k值
	 return value： 输入数据的分类标签

	 date: 2017-04-08
	 by: 余祖登
	*/

	vector<Cfloatstr> labels_with_dis;//带距离的标签集
	//计算输入数据与各样本点的欧氏距离
	for (unsigned int j = 0; j < dataSet.size(); ++j)
	{
		double dis = 0;
		for (unsigned int i = 0; i < dataSet[j].size(); ++i)
		{
			dis += (dataSet[j][i] - inX[i])*(dataSet[j][i] - inX[i]);
		}
		dis = sqrt(dis);
		Cfloatstr vStr = { dis,labels[j] };//{距离, 标签}
		labels_with_dis.push_back(vStr);
	}
	sort(labels_with_dis.begin(), labels_with_dis.end(), compCfs);//按距离排序

	//计算前k个距离对应标签出现的次数，存入关联容器
	map<string, int> count_labels;
	string label;
	for (int i = 0; i < k; i++)
	{
		label = labels_with_dis[i].str;
		++count_labels[label];
	}
	//找出出现最多的标签名
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
	//返回找到的标签名
	return label;
}

void autoNorm(vector<vector<double>> &dataSet)
{
	//归一化特征值
	int len = dataSet[0].size();
	vector<double> maxVal, minVal;
	for (auto val : dataSet[0])//置入第一个数据行
	{
		maxVal.push_back(val);
		minVal.push_back(val);
	}
	for (auto data : dataSet)//找出每个特征的最大值和最小值
	{
		for (int i = 0; i < len;++i)
		{
			if (data[i]>maxVal[i])
				maxVal[i] = data[i];
			if (data[i]<minVal[i])
				minVal[i] = data[i];
		}
	}
	for (auto &data : dataSet)
	{
		for (int i = 0; i < len; ++i)
		{
			data[i] = (data[i] - minVal[i]) / (maxVal[i] - minVal[i]);
		}
	}	
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
	while (getline(file, dataStr))//读取一行
	{
		//cout << dataStr << endl;
		vector<double> vf;
		istringstream data(dataStr);//从字符传中读取字符
		while (data >> f)
		{
			vf.push_back(f);
			//cout << f << endl;
		}
		vf.pop_back();//移除最后一个
		labels.push_back(to_string(f));//最后一个字符串保存到labels中
		dataSet.push_back(vf);
		//cout <<"dataSet[0][0]: "<< dataSet[0][0] << endl;
	}

	file.close();
}

void kNNTest(vector<vector<double>> testSet, vector<string> testLabels, vector<vector<double>> dataSet, vector<string> labels, int k)
{
	//算法测试
	double count_wrong = 0;
	for (unsigned int j = 0; j < testSet.size(); ++j)
	{
		string label = classify(testSet[j], dataSet, labels, k);
		cout << j + 1 << "times, " << "the classifier came back with: " << label << ",the real answer is " << testLabels[j] << endl;
		if (label != testLabels[j])
		{
			++count_wrong;
			cout << "Wrong!!!" << endl;
		}
	}
	count_wrong /= (double)testSet.size();

	cout << "The total error rate is： " << count_wrong << endl;

}

int main()
{
	vector<vector<double>> dataSetX, testSetX;
	vector<string> labelsX, testLabelsX;
	vector<double> inXX = { 94900,	6.724021,	0.7 };
	int k = 10;



	readFile("datingTrainSet.txt", dataSetX, labelsX);
	autoNorm(dataSetX);

	readFile("datingTestSet.txt", testSetX, testLabelsX);
	autoNorm(testSetX);
	kNNTest(testSetX, testLabelsX, dataSetX, labelsX, k);//算法测试

	cout << "------------------------------------------------------" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "inX的分类是： " << classify(inXX, dataSetX, labelsX, k) << endl;

	system("pause");
}