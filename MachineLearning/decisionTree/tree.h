#pragma once
#include<string>
#include<vector>
#include<iostream>

using namespace std;

class CTreeNode
{
public:
	string valueForLastFeature;
	string arrivedFeature;
	vector<CTreeNode*> childs;
	void print();
};

void CTreeNode::print()
{
	cout << "{" << valueForLastFeature << " : {" << arrivedFeature << ":";
	for (auto node : childs)
	{
		node->print();
	}
	cout << "}}" << endl;
}

CTreeNode* BuildTree(CTreeNode* p){

	string str1, str2;
	cout << "���������ַ������� : " << endl;
	cin >> str1 >> str2;
	p = new CTreeNode;
	p->arrivedFeature = str2;
	p->valueForLastFeature = str1;
	cout << "����ýڵ���ӽڵ���Ŀ :" << endl;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		CTreeNode* newnode = new CTreeNode;
		newnode = BuildTree(newnode);
		p->childs.push_back(newnode);
	}
	return p;
}

void PreOrderTraverse(CTreeNode* p) {
	//����ݹ����������  
	bool flg = 0;
	if (p) {//����㲻Ϊ�յ�ʱ��ִ��
		cout << "";
		if (p->valueForLastFeature!="")
		{
			cout << p->valueForLastFeature << ":A";
		}
		
		cout << p->arrivedFeature << ": {";
		for (CTreeNode* subT : p->childs) {
			PreOrderTraverse(subT);
			flg = 1;
		}
		if (!flg)
		{
			cout << "\b\b\b"<<",";
		}
		//cout << "\b";
		else
		{
			cout << "}";
		}
		
		
	}
}//PreOrderTraverse   