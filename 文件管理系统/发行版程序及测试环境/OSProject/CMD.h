#include<iostream>
#include<sstream>
#include<vector>
#include<map>

#include"Login.h"
using namespace std;

class CMD   //指令类, 用于解析指令
{
	public:
		vector<string> currentCmd;  //当前指令
		CMD(){}
		string GetCMD() //获取指令
		{
			cout << "请输入指令: ";

			//获取单行输入
			string CMD;
			getline(cin, CMD, '\n');
			while (CMD == "\n" || CMD == "") //防止未读取到字符的情况发生
				getline(cin, CMD, '\n');
			stringstream ss;
			ss << CMD;

			//转存至currentCmd, 每个string为指令的一个部分
			currentCmd.clear();
			string CMDPart;
			while (ss >> CMDPart)
				currentCmd.push_back(CMDPart);

			return currentCmd[0];
		}

		void CheckCurrentCmd()  //显示当前指令
		{
			if (!currentCmd.size())
			{
				cout << "未输入指令" << endl;
				return;
			}

			cout << "指令分为" << currentCmd.size() << "部分:";
			for (int i = 0; i < currentCmd.size() - 1; i++)
				cout << currentCmd[i] << ", ";
			cout << currentCmd[currentCmd.size() - 1] << endl;
		}

		void CheckHelp(string cmd = "") // 指令help, 用于显示指令集
		{
			if (cmd == "") {
				cout << "以下是本文件管理系统的指令集:" << endl;
				cout << "指令名 [必填项] (可选项)" << endl;
				cout << "目录类:" << endl;
				cout << "cd [路径]\t进入目录" << endl;
				cout << "dir\t显示当前目录" << endl;
				cout << "mkdir [目录名]\t创建目录" << endl;
				cout << "rmdir [目录名] (-a)\t删除目录" << endl;
				cout << "文件类:" << endl;
				cout << "create [文件名]\t创建文件" << endl;
				cout << "delete [文件名]\t删除文件" << endl;
				cout << "move [文件路径] [文件夹路径]\t移动文件" << endl;
				cout << "copy [文件路径] (文件夹路径)\t拷贝文件" << endl;
				cout << "open [文件名]\t打开文件" << endl;
				cout << "以下命令需先打开文件" << endl;
				cout << "close\t关闭文件" << endl;
				cout << "read\t读文件" << endl;
				cout << "write\t写文件" << endl;
				cout << "flock (-u)\t文件加锁/解锁" << endl;
				cout << "head [num/-num]\t显示文件的前num行" << endl;
				cout << "tail [num/-num]\t显示文件的后num行" << endl;
				cout << "lseek [offset]\t文件读写指针的移动，从文件指针当前位置处向后移动 offset，负数时向前移动offset" << endl;
				cout << "其他:" << endl;
				cout << "import [外部路径] (内部路径)" << endl;
				cout << "export [内部路径] [外部路径]" << endl;
				cout << "help (指令名)\t 显示帮助文档" << endl;
				cout << "exit\t退出文件管理系统" << endl;
			}
			else if (cmd == "cd")
			{
				cout << "cd [路径]\t进入目录" << endl;
				cout << "进入给定的路径文件夹, 可以是绝对路径, 也可以是相对路径" << endl;
				cout << "示例:" << endl;
				cout << "cd A" << endl;
				cout << "cd QSY/Administrator/A" << endl;
			}
			else if (cmd == "dir")
			{
				cout << "dir\t显示当前目录" << endl;
				cout << "显示当前目录下的树状结构" << endl;
			}
			else if (cmd == "mkdir")
			{
				cout << "mkdir [目录名]\t创建目录" << endl;
				cout << "在当前文件夹下创建指定名称的文件夹" << endl;
				cout << "示例:" << endl;
				cout << "mkdir os" << endl;
			}
			else if (cmd == "rmdir")
			{
				cout << "rmdir [目录名] (-a)\t删除目录" << endl;
				cout << "在当前文件夹下移除指定名称的文件夹, 添加-a后缀进行递归删除" << endl;
				cout << "示例:" << endl;
				cout << "rmdir os" << endl;
				cout << "rmdir os -a" << endl;
			}
			else if (cmd == "create")
			{
				cout << "create [文件名]\t创建文件" << endl;
				cout << "在当前文件夹下创建指定名称的文件" << endl;
				cout << "示例:" << endl;
				cout << "create abc" << endl;
			}
			else if (cmd == "delete")
			{
				cout << "delete [文件名]\t删除文件" << endl;
				cout << "在当前文件夹下删除指定名称的文件" << endl;
				cout << "示例:" << endl;
				cout << "delete abc" << endl;
			}
			else if (cmd == "copy")
			{
				cout << "copy [文件路径] (文件夹路径)\t拷贝文件" << endl;
				cout << "将指定路径的文件复制到指定路径的文件夹下, 不指定文件夹则默认为当前文件夹" << endl;
				cout << "示例:" << endl;
				cout << "copy abc" << endl;
				cout << "copy abc QSY/Administrator/A" << endl;
				cout << "copy QSY/Administrator/A/abc f" << endl;
			}
			else if (cmd == "move")
			{
				cout << "move [文件路径] [文件夹路径]\t移动文件" << endl;
				cout << "将指定路径的文件移动到指定路径的文件夹下" << endl;
				cout << "示例:" << endl;
				cout << "move abc QSY/Administrator/A" << endl;
				cout << "move QSY/Administrator/A/abc f" << endl;
			}
			else if (cmd == "open")
			{
				cout << "open [文件名]\t打开文件" << endl;
				cout << "打开当前文件夹下指定名称的文件" << endl;
				cout << "示例:" << endl;
				cout << "open abc" << endl;
			}
			else if (cmd == "close")
			{
				cout << "close\t关闭文件" << endl;
				cout << "关闭当前打开的文件, 返回上级文件夹(需先打开文件)" << endl;
			}
			else if (cmd == "read")
			{
				cout << "read\t读文件" << endl;
				cout << "输出当前读写指针至文件末尾的内容(需先打开文件)" << endl;
			}
			else if (cmd == "write")
			{
				cout << "write\t写文件" << endl;
				cout << "写出当前读写指针至文件末尾的内容(需先打开文件)" << endl;
			}
			else if (cmd == "flock")
			{
				cout << "flock (-u)\t文件加锁/解锁" << endl;
				cout << "文件加锁, 禁止读取, 写入, 复制, 移动等操作. 带-u后缀时为解锁(需先打开文件)" << endl;
				cout << "示例:" << endl;
				cout << "flock abc" << endl;
				cout << "flock abc -u" << endl;
			}
			else if (cmd == "head")
			{
				cout << "head [num/-num]\t显示文件的前num行" << endl;
				cout << "示例:" << endl;
				cout << "head 10" << endl;
				cout << "head -10, 此处的'-'为后缀标志" << endl;
			}
			else if (cmd == "tail")
			{
				cout << "tail [num/-num]\t显示文件的后num行" << endl;
				cout << "示例:" << endl;
				cout << "tail 10" << endl;
				cout << "tail -10, 此处的'-'为后缀标志" << endl;
			}
			else if (cmd == "lseek")
			{
				cout << "lseek [offset]\t文件读写指针的移动，从文件指针当前位置处向后移动 offset，负数时向前移动offset" << endl;
				cout << "移动文件的读写指针, 会影响读写操作" << endl;
				cout << "示例:" << endl;
				cout << "lseek  10" << endl;
				cout << "lseek  -10, 此处的'-'为负号" << endl;
			}
			else if (cmd == "import")
			{
				cout << "import [外部路径] (内部路径)" << endl;
				cout << "导入一个外部文件至指定内部路径, 缺省时指定为当前路径" << endl;
				
			}
			else if (cmd == "export")
			{
				cout << "export [内部路径] (外部路径)" << endl;
				cout << "导出一个内部文件至指定外部路径, 缺省时指定为工程目录" << endl;
			}
			else
			{
				cout << "没有相关指令的帮助信息" << endl;
			}
		}

		bool ProcessCmd() //处理指令
		{
			if (!currentCmd.size())
			{
				cout << "无指令" << endl;
			}

			if (currentCmd[0] == "create" && currentCmd.size() == 2)
			{
				string name = currentCmd[1];
				root->createFileChild(name);
			}
			else if (currentCmd[0] == "delete" && currentCmd.size() == 2)
			{
				string name = currentCmd[1];
				root->removeFileChild(name);
			}
			else if (currentCmd[0] == "open" && currentCmd.size() == 2)
			{
				Dir *temp = openFile(root, currentCmd[1]);
				if (temp != NULL) root = temp;
			}
			else if (currentCmd[0] == "close" && currentCmd.size() == 1)
			{
				if (root->file != NULL)
				{
					root = root->father;
					cout << "文件已关闭" << endl;
				}
				else cout << "请先打开文件" << endl;
			}
			else if	(currentCmd[0] == "read" && currentCmd.size() == 1)
			{
				if (root->file != NULL)
				{
					root->file->checkData();
				}
				else cout << "请先打开文件" << endl;
			}
			else if (currentCmd[0] == "write" && currentCmd.size() == 1)
			{
				if (root->file != NULL)
				{
					root->file->writeData();
				}
				else cout << "请先打开文件" << endl;
			}
			else if (currentCmd[0] == "copy" && currentCmd.size() >= 2)
			{
				if (currentCmd.size() == 2)
					copyTo(root, currentCmd[1], root->path);
				else if (currentCmd.size() == 3)
					copyTo(root, currentCmd[1], currentCmd[2]);
			}
			else if (currentCmd[0] == "move" && currentCmd.size() >= 2)
			{
				Dir *temp = root;
				root = copyTo(root, currentCmd[1], currentCmd[2]);
				if (root == NULL)
				{
					root = temp;
					return 0;
				}
				root = cd(root, temp->path);
				root->removeFileChild(currentCmd[1]);
			}
			else if (currentCmd[0] == "flock" && currentCmd.size() >= 1)
			{
				if (currentCmd.size() == 1 || (currentCmd.size() == 2 && currentCmd[1] == "-c"))
				{
					if (!root->type)
					{
						root->file->flock();
						cout << "上锁完成" << endl;
					}
					else cout << "无法对文件夹上锁";
				}
				else if (currentCmd.size() == 2 && currentCmd[1] == "-u")
				{
					if (!root->type)
					{
						root->file->flock(0);
						cout << "解锁完成" << endl;
					}
					else cout << "无法对文件夹解锁";
				}
			}
			else if (currentCmd[0] == "head" && currentCmd.size() == 2)
			{
				if (!root->type)
				{
					string number = currentCmd[1];
					if (number[0] == '-') number.erase(0, 1);

					int n = stoi(number);
					root->file->checkData(n);
				}
				else cout << "无法对文件夹使用head命令";
			}
			else if (currentCmd[0] == "tail" && currentCmd.size() == 2)
			{
				if (!root->type)
				{
					string number = currentCmd[1];
					if(number[0] == '-') number.erase(0, 1);

					int n = stoi(number);
					root->file->checkData(-1, n);
				}
				else cout << "无法对文件夹使用tail命令";
			}
			else if (currentCmd[0] == "lseek" && currentCmd.size() == 2)
			{
				if (!root->type)
				{
					string number = currentCmd[1];
					int n = stoi(number);
					root->file->setlseek(n);
					cout << "已设置文本偏移量为" << root->file->lseek << endl;
				}
				else cout << "无法对文件夹使用lseek命令";
			}
			else if (currentCmd[0] == "cd" && currentCmd.size() == 2)
			{
				if (currentCmd.size() == 2)
				{
					Dir *temp = cd(root, currentCmd[1]);
					if (temp != NULL) root = temp;
				}
			}
			else if (currentCmd[0] == "dir" && currentCmd.size() == 1)
			{
				root->showPath();
				root->showAll();
			}
			else if (currentCmd[0] == "mkdir" && currentCmd.size() == 2)
			{
				string name = currentCmd[1];
				root->createDirChild(name);
			}
			else if (currentCmd[0] == "rmdir" && currentCmd.size() >= 2)
			{
				if (currentCmd.size() == 2) {
					string name = currentCmd[1];
					root->removeDirChild(name);
				}
				else if (currentCmd.size() == 3 && currentCmd[2] == "-a")
				{
					string name = currentCmd[1];
					root->removeDirChild(name,1);
				}
			}
			else if (currentCmd[0] == "import" && currentCmd.size() >= 2)
			{
				if (currentCmd.size() == 2)
					import(root, currentCmd[1], root->path);
				else
					import(root, currentCmd[1], currentCmd[2]);
			}
			else if (currentCmd[0] == "export" && currentCmd.size() >= 2)
			{
				if (currentCmd.size() == 2)
					_export(root, currentCmd[1], "./");
				else
					_export(root, currentCmd[1], currentCmd[2]);
			}
			else if (currentCmd[0] == "help")
			{
				if (currentCmd.size() == 1) CheckHelp();
				else if (currentCmd.size() == 2) CheckHelp(currentCmd[1]);
			}
			else if (currentCmd[0] == "exit")
			{
				cout << "系统已退出" << endl;
				return 1;
			}
			else
			{
				cout << "指令格式错误, 请使用help指令获取指令帮助" << endl;
			}

			return 0;
		}
} CMD;
