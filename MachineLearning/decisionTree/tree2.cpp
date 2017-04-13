//#include"tree.h"
#include<iostream>  
#include<vector>

using namespace std;
class BiTNode {
public:
	char data;
	//BiTNode *lchild, *rchild;//左右孩子  
	vector<BiTNode* > childs;//数目不定的孩子  

};
BiTNode* T;
BiTNode* CreateBiTree(BiTNode* T);
void Inorder(BiTNode* T);
void PreOrderTraverse(BiTNode* T);
void Posorder(BiTNode* T);
//===========================================主函数  
int main1() {
	cout << "创建一颗树，其中A->Z字符代表树的数据，用“#”表示空树:" << endl;
	T = CreateBiTree(T);
	cout << "先序递归遍历：" << endl;
	PreOrderTraverse(T);
	cout << endl;
	cout << "后序递归遍历：" << endl;
	Posorder(T);
	cout << endl;
	system("pause");
	return 1;
}
//=============================================先序递归创建二叉树树  
BiTNode* CreateBiTree(BiTNode* T) {
	//按先序输入二叉树中结点的值（一个字符），空格字符代表空树，  
	//构造二叉树表表示二叉树T。  
	char ch;
	cout << "输入一个字符数据 : " << endl;
	cin >> ch;
	if (ch == '#')
		T = NULL;  
	else {
		T = new BiTNode;//产生新的子树  
		T->data = ch;//由getchar（）逐个读入来  
		cout << "输入该节点的子节点数目 :" << endl;
		int num;
		cin >> num;
		for (int i = 0; i < num; i++)
		{
			BiTNode* new_node=new BiTNode;
			new_node = CreateBiTree(new_node);
			T->childs.push_back(new_node);
		}
		//T->lchild = CreateBiTree(T->lchild);//递归创建左子树  
		//T->rchild = CreateBiTree(T->rchild);//递归创建右子树  
	}
	return T;
}//CreateTree  
 //===============================================先序递归遍历二叉树  
void PreOrderTraverse(BiTNode* T) {
	//先序递归遍历二叉树  
	if (T) {//当结点不为空的时候执行  
		cout << T->data;
		for (BiTNode* subT : T->childs)
			PreOrderTraverse(subT);
		//PreOrderTraverse(T->lchild);//  
		//PreOrderTraverse(T->rchild);
	}
	else cout << "";
}//PreOrderTraverse   
 //=================================================后序递归遍历二叉树  
void Posorder(BiTNode* T) {
	if (T) {
		for (auto subT : T->childs)
			Posorder(subT);
		cout << T->data;//访问根结点  
	}
	else cout << "";
}
//================================================= 
