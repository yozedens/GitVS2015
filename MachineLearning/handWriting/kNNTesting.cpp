#include"handWriting.h"

using namespace std;

int main()
{
	char* filePath = ".\\trainingDigits";
	vector<string> labels;
	vector<vector<int>> dataSet = getDataSet(filePath, labels);
	
	/*string fileOutPath = ".\\Out\\";
	string fileOut = "trainingDigits.txt";
	matrix2file(dataSet, fileOutPath + fileOut);//д���ļ�����˹�����������ȡ�Ƿ���ȷ
	*/
	char* testPath = ".\\testDigits";
	vector<string> testlabels;
	vector<vector<int>> testSet = getDataSet(testPath, testlabels);

	kNNTest(testSet, testlabels, dataSet, labels, 3);


	system("pause");
	return 0;
}