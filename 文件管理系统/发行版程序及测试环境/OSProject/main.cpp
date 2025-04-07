#include <iostream>
#include <fstream>
#include <sstream>
#include "Data.h"
void Init()
{
	//Data.showData();
	//stringstream data;
	//Data.readBinary(data);

	ifstream data("data", ios::in | ios::binary);
	if (!data.is_open()) cout << "�ļ���ʧ��" << endl;

	data >> iswriting;
	//cout << iswriting;

	Login.Init(data);//��ʼ���û���Ϣ
	cout << "��ȡ�û���Ϣ���" << endl;

	root = new Dir();
	root->Init(data);//��ʼ���ڵ�ָ��
	cout << "��ȡϵͳĿ¼���" << endl;
	File_Init(data, root);
	cout << "��ȡϵͳ�ļ����" << endl;

	Login.Run(root);
	//data.close();
}

void reload(string currentPath)
{
	//stringstream data;
	//Data.readBinary(data);
	ifstream data("data", ios::in | ios::binary);
	if (!data.is_open()) cout << "�ļ���ʧ��" << endl;

	
	data >> iswriting;

	Login.Init(data);//��ʼ���û���Ϣ
	//cout << "��ȡ�û���Ϣ���" << endl;

	root = new Dir();
	root->Init(data);//��ʼ���ڵ�ָ��
	//cout << "��ȡϵͳĿ¼���" << endl;

	File_Init(data, root);
	//root->showAll();
	//cout << "�����������" << endl;
	root = cd(root, currentPath, 1);
	//data.close();
}

int main()
{
	Init();
	Data.writeData();
	while (1)
	{
		cout << endl;
		root->showPath();
		root->showChilds();
		CMD.GetCMD();
		reload(root->path);
		//CMD.CheckCurrentCmd();
		if (CMD.ProcessCmd()) break;

		Data.writeData();
	}
	Data.writeData();
}
