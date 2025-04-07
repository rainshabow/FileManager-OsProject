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
	if (!data.is_open()) cout << "文件打开失败" << endl;

	data >> iswriting;
	//cout << iswriting;

	Login.Init(data);//初始化用户信息
	cout << "读取用户信息完成" << endl;

	root = new Dir();
	root->Init(data);//初始化节点指针
	cout << "读取系统目录完成" << endl;
	File_Init(data, root);
	cout << "读取系统文件完成" << endl;

	Login.Run(root);
	//data.close();
}

void reload(string currentPath)
{
	//stringstream data;
	//Data.readBinary(data);
	ifstream data("data", ios::in | ios::binary);
	if (!data.is_open()) cout << "文件打开失败" << endl;

	
	data >> iswriting;

	Login.Init(data);//初始化用户信息
	//cout << "读取用户信息完成" << endl;

	root = new Dir();
	root->Init(data);//初始化节点指针
	//cout << "读取系统目录完成" << endl;

	File_Init(data, root);
	//root->showAll();
	//cout << "数据重载完成" << endl;
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
