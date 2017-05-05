#pragma once

#include<vector>
#include<string>
#include<cmath>
#include<regex>
#include<cctype> 
#include<algorithm>
#include"coutContainer.h"

using namespace std;
//������ʽ��ֳ��ַ���Ϊ�����������ҹ��˵�һЩ�ַ���
vector<string> splitSent(const string &str)
{
	vector<string> splitResult;
	regex sep("[ \t\n]*[ ,;.\t\n][ \t\n]*");//separated by , ; or . and whitespaces(space��tab��newline)
	sregex_token_iterator p(str.cbegin(), str.cend(),//sequence
		sep,//separator
		-1);//-1:values between separators
	sregex_token_iterator e;

	for (; p != e; ++p)
	{
		if((*p).length()>2)//����
			splitResult.push_back(*p);
	}
	return splitResult;
}

//�ַ���������Ժ���
int stringTest()
{
	//string data = "<person>\n"
	//	" <first>Nico</first>\n"
	//	" <last>Josuttis</last>\n"
	//	"</person>\n";
	//cout <<data.length()<<" "<< data << endl;


	string names = "nico, jim, helmut, Paul, tim, john paul, rita";
	names = { "Hi Peter,\n\
\n\
With Jose out of town, do you want to\n\
meet once in a while to keep things\n\
going and do some interesting stuff ?\n\
\n\
Let me know\n\n\n\n\
Eugene"};
	transform(names.begin(), names.end(),
		names.begin(),
		tolower
		/*		[](unsigned char c) {
		return tolower(c);
		}*/);
	cout << names << endl;

	vector<string> splitResult = splitSent(names);
	coutVec(splitResult, "splitResult : \n", 10,"|");


	//	testingNB();

	return 0;
}