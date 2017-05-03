

#include"bayes.h"

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