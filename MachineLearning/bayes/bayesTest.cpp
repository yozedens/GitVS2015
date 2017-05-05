
#include"coutContainer.h"
#include"bayes.h"
#include"dealContentFiles.h"
#include"dealString.h"

void loadDataSet(vvMatrix &dataSet, vector<int> &classVec)
{
	dataSet = { { "my","dog","has","flea","problems","help","please" },
	{ "maybe","not","take","him","to","dog","park","stupid" },
	{ "my","dalmation","is","so","cute","i","love","him" },
	{ "stop","posting","stupid","worthless","garbage" },
	{ "mr","licks","ate","my","steak","how","to","stop","him" },
	{ "quit","buying","worthless","dog","food","stupid" } };
	classVec = { 0,1,0,1,0,1 };
}

//垃圾邮件测试函数
void spamTest()
{
	vvMatrix dataSet = {};
	vector<int> classVec;

	vector<string> files;
	//labels = files;
	char* filePathhan = ".\\email\\ham";
	files = readContent(filePathhan);//获取文件名列表
	auto lenfiles = files.size();
	for (size_t i = 0; i < lenfiles; i++)//逐个文件读取
	{
		ifstream file(files[i]);
		istreambuf_iterator<char> beg(file), end;
		string fileStr(beg, end);//将整个文本存入一个string中
		transform(fileStr.begin(), fileStr.end(),
			fileStr.begin(),
			tolower);			//大写字符全部变小写
		vector<string> splitResult = splitSent(fileStr);//拆分为单词
		dataSet.push_back(splitResult);//存入数据集
		classVec.push_back(0);
		file.close();
		//cout << "read : " << files[i] << endl;
		//coutVec(splitResult, "splitResult :\n", 10);
	}

	files = readContent(".\\email\\spam");//获取文件名列表
	lenfiles = files.size();
	for (size_t i = 0; i < lenfiles; i++)//逐个文件读取
	{
		ifstream file(files[i]);
		istreambuf_iterator<char> beg(file), end;
		string fileStr(beg, end);//将整个文本存入一个string中
		transform(fileStr.begin(), fileStr.end(),
			fileStr.begin(),
			tolower);			//大写字符全部变小写
		vector<string> splitResult = splitSent(fileStr);//拆分为单词
		dataSet.push_back(splitResult);//存入数据集
		classVec.push_back(1);
		file.close();
		//cout << "read : " << files[i] << endl;
		//coutVec(splitResult, "splitResult :\n", 10);
	}

	set<string> vocabSet = createVocabList(dataSet);
	vvMatrix testMat;//测试数据集，基础内容为string
	vector<int> testClassVec;

	srand((unsigned int)time(0)); // use current time as seed for random generator
	for (int i = 0; i < 10; i++)
	{
		int randomIdx = rand() % (int)dataSet.size();//随机选取一个
		testMat.push_back(dataSet[randomIdx]);
				
		//cout << randomIdx << endl;
		//coutVec(dataSet[randomIdx],"dataSet[randomIdx]:\n",10);

		dataSet.erase(dataSet.begin() + i);
		testClassVec.push_back(classVec[randomIdx]);
		classVec.erase(classVec.begin() + i);

		
	}
	vector<vector<int>> trainMat;//训练集，基础内容为int
	vector<int> trainClassVec = classVec;
	for (auto doc : dataSet)
	{
		//trainMat.push_back(setOfWords2Vec(vocabSet, doc));
		trainMat.push_back(bagOfWords2VecMN(vocabSet, doc));

	}

	CReTrainBN0 reTrain = trainNB(trainMat, trainClassVec);//训练分类器

	int errorCount = 0;
	for (size_t i = 0; i < 10;++i)
	{
		int classRe = clssifyNB(bagOfWords2VecMN(vocabSet, testMat[i]), reTrain);
		if (classRe !=testClassVec[i])
		{
			errorCount += 1;
			cout << "the return of clssifyNB is :" << classRe << ",but the real class is:" << testClassVec[i] << endl;
		}
		
	}
	cout << "the error rate is: " << errorCount / 10.0 << endl;
}

//训练器、分类器测试函数
int testingNB()
{
	vector<vector<int>> trainMat;
	vvMatrix dataSet = {};
	vector<int> classVec;

	loadDataSet(dataSet, classVec);
	coutVecVec(dataSet, "\n[dataSet : \n]",10);
	coutVec(classVec,"\n[classVec : \n]", 2);

	set<string> vocabSet = createVocabList(dataSet);
	coutVec(vocabSet, "\n[vocabSet : \n]", 10);
	cout << "length of vocabList = " << vocabSet.size() << endl;

	for (auto Doc : dataSet)
		trainMat.push_back(setOfWords2Vec(vocabSet, Doc));
	coutVecVec(trainMat, "\n[trainMat : \n]", 1);

	CReTrainBN0 resultTrain = trainNB(trainMat, classVec);
	cout << "pAbusive = " << resultTrain.pAbusive << endl;
	coutVec(resultTrain.p0Num, "\n[p0Num : \n]", 10);
	coutVec(resultTrain.p1Num, "\n[p1Num : ]",10);

	vector<string> testEntry = { "love","my","dalmation" };
	coutVec(testEntry,"\n[testEntry : \n]", 10);
	vector<int> thisDoc = setOfWords2Vec(vocabSet, testEntry);
	cout << "classified as: " << clssifyNB(thisDoc, resultTrain) << endl;

	testEntry = { "stupid","garbage" };
	coutVec(testEntry, "\n[testEntry : \n]",10);
	thisDoc = setOfWords2Vec(vocabSet, testEntry);
	cout << "classified as: " << clssifyNB(thisDoc, resultTrain) << endl;

	cout << "\n----------The End!---------- \n";

	int a[10] = { 1,2,3 };
	//cout<<typeid(trainMat[0][0]).name();
	coutVec(a,"a: ",2);
	return 0;
}

int main()
{
	for (int i = 0; i < 100;++i)
		spamTest();
	//stringTest();
	system("pause");
}

