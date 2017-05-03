#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<algorithm>
#include<cctype> 
#include"bayes.h"


using namespace std;

//正则表达式拆分字符串
vector<string> splitSent(const string &str)
{
	vector<string> splitResult;
	regex sep("[ \t\n]*[,;.][ \t\n]");//separated by , ; or . and whitespaces(space、tab、newline)
	sregex_token_iterator p(str.cbegin(), str.cend(),//sequence
							sep,//separator
							-1);//-1:values between separators
	sregex_token_iterator e;

	for (; p != e; ++p)
	{
		splitResult.push_back(*p);
	}	
	return splitResult;
}

int main()
{
	//string data = "<person>\n"
	//	" <first>Nico</first>\n"
	//	" <last>Josuttis</last>\n"
	//	"</person>\n";
	//cout <<data.length()<<" "<< data << endl;


	string names = "nico, jim, helmut, Paul, tim, john paul, rita";

	transform(names.begin(), names.end(),
		names.begin(),
		[](unsigned char c) {
		return tolower(c);
	});
	cout << names << endl;

	vector<string> splitResult = splitSent(names);
	coutVec(splitResult, "splitResult : \n", 10);


//	testingNB();

	system("pause");
	return 0;
}