//#include"tree.h"
#include<iostream>  
#include<vector>

using namespace std;
class BiTNode {
public:
	char data;
	//BiTNode *lchild, *rchild;//���Һ���  
	vector<BiTNode* > childs;//��Ŀ�����ĺ���  

};
BiTNode* T;
BiTNode* CreateBiTree(BiTNode* T);
void Inorder(BiTNode* T);
void PreOrderTraverse(BiTNode* T);
void Posorder(BiTNode* T);
//===========================================������  
int main1() {
	cout << "����һ����������A->Z�ַ������������ݣ��á�#����ʾ����:" << endl;
	T = CreateBiTree(T);
	cout << "����ݹ������" << endl;
	PreOrderTraverse(T);
	cout << endl;
	cout << "����ݹ������" << endl;
	Posorder(T);
	cout << endl;
	system("pause");
	return 1;
}
//=============================================����ݹ鴴����������  
BiTNode* CreateBiTree(BiTNode* T) {
	//����������������н���ֵ��һ���ַ������ո��ַ����������  
	//������������ʾ������T��  
	char ch;
	cout << "����һ���ַ����� : " << endl;
	cin >> ch;
	if (ch == '#')
		T = NULL;  
	else {
		T = new BiTNode;//�����µ�����  
		T->data = ch;//��getchar�������������  
		cout << "����ýڵ���ӽڵ���Ŀ :" << endl;
		int num;
		cin >> num;
		for (int i = 0; i < num; i++)
		{
			BiTNode* new_node=new BiTNode;
			new_node = CreateBiTree(new_node);
			T->childs.push_back(new_node);
		}
		//T->lchild = CreateBiTree(T->lchild);//�ݹ鴴��������  
		//T->rchild = CreateBiTree(T->rchild);//�ݹ鴴��������  
	}
	return T;
}//CreateTree  
 //===============================================����ݹ����������  
void PreOrderTraverse(BiTNode* T) {
	//����ݹ����������  
	if (T) {//����㲻Ϊ�յ�ʱ��ִ��  
		cout << T->data;
		for (BiTNode* subT : T->childs)
			PreOrderTraverse(subT);
		//PreOrderTraverse(T->lchild);//  
		//PreOrderTraverse(T->rchild);
	}
	else cout << "";
}//PreOrderTraverse   
 //=================================================����ݹ����������  
void Posorder(BiTNode* T) {
	if (T) {
		for (auto subT : T->childs)
			Posorder(subT);
		cout << T->data;//���ʸ����  
	}
	else cout << "";
}
//================================================= 
