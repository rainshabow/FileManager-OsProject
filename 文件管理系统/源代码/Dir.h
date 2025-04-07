#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

class Dir;
class File;
ostream &operator << (ostream &os, Dir &temp);
Dir *backToTop(Dir *temp);
Dir *cdPath(Dir *temp, string _path, bool access);

int iswriting = 0;
stringstream data;
void P()
{
	iswriting = 1;

	fstream data("data",ios::in | ios::out | ios::binary);
	data << iswriting;
	data.close();
}
void V()
{
	iswriting = 0;

	fstream data("data",ios::in | ios::out | ios::binary);
	data << iswriting;
	data.close();
}


class File
{
	public:
		string name;//名称
		string path;//绝对路径
		int size;   //大小, 以行数计
		bool isLocked;//锁定状态
		vector<string> data;
		int lseek = 0;

		File(string _name = "", string _path = "", int _size = 0, bool _isLocked = 0, int _lseek = 0)
		{
			name = _name;
			path = _path;
			size = _size;
			isLocked = _isLocked;
			lseek = _lseek;
		}

		void checkData(int head = -1, int tail = -1)
		{
			if (isLocked)
			{
				cout << "文件已被锁定, 无法读取" << endl;
				return;
			}
			if (lseek == 0 || head != -1 || tail != -1)//不以lseek偏移量为基础的输出
			{
				int start = 0;
				int end = data.size();

				if (head != -1) end = head;
				if (end > data.size()) end = data.size();

				if (tail != -1) start = data.size() - tail;
				if (start < 0) start = 0;

				for (int i = start; i < end; i++)
					cout << data[i] << endl;
			}
			else//以lseek偏移量为基础的输出
			{
				int count = lseek;
				for (int i = 0; i < data.size(); i++)
					if (count != 0) 
					{
						if (count < (int)data[i].size())//对输入不完全行进行处理
						{
							string thisLine = data[i].substr(count, data[i].size() - count);
							cout << thisLine << endl;
							count = 0;
						}
						else count -= (int)data[i].size();
						//cout << count << endl;
					}
					else cout << data[i] << endl;
			}
		}

		void writeData()
		{
			if (isLocked)
			{
				cout << "文件已被锁定, 无法写入" << endl;
				return;
			}

			if (iswriting == 1)
			{
				cout << "其他进程正在写入文件, 请稍候" << endl;
				return;
			}
			else P();
			cout << "请写入文件内容, 以独立一行的/end结束输入:" << endl;

			if (lseek == 0) 
			{
				data.clear();

				string temp;
				while (getline(cin, temp, '\n'))
				{
					if (temp == "/end") break;
					else data.push_back(temp);
				}
			}
			else 
			{
				int count = lseek;
				int i;
				string subLine = "";
				for (i = 0; i < data.size(); i++)
					if (count != 0)
					{
						if (count < (int)data[i].size())//对输入不完全行进行处理
						{
							subLine = data[i].substr(0, count);
							count = 0;
						}
						else count -= (int)data[i].size();
					}
					else
					{
						if (subLine == "")
							data.erase(data.begin() + i, data.end());
						else 
						{
							data[i - 1] = subLine;
							data.erase(data.begin() + i, data.end());
						}
						break;
					}
				checkData();

				string temp;
				while (getline(cin, temp, '\n'))
				{
					if (temp == "/end") break;
					else if (subLine != "")
					{
						data[data.size() - 1] += temp;
						subLine = "";
					}
					else data.push_back(temp);
				}
			}
			size = data.size();

			if (!iswriting)
			{
				cout << "文件读写出现异步问题" << endl;
				return;
			}
			else V();

			cout << "文件写入结束" << endl;
		}

		void setlseek(int seek = 0)
		{
			lseek += seek;
			if (lseek < 0) lseek = 0;

			int sumSize = 0;
			for (int i = 0; i < data.size(); i++)
				sumSize += data[i].size();
			if (lseek > sumSize) lseek = sumSize;
		}

		bool flock(bool _isLocked = 1)
		{
			if (iswriting)
			{
				cout << "其他进程正在写入文件, 请稍候" << endl;
				return 0;
			}
			return isLocked = _isLocked;
		}
} Files;

class Dir//节点类, 用于构建目录
{
	public:
		string name;	//当前节点名
		string path;    //绝对路径
		bool type;  //类型, 1表示当前路径是文件夹, 0表示当前路径是文件
		int nums;   //成员数量
		vector<Dir *> childs;	//成员路径, 指向下一级的所有成员
		Dir *father; //指向上一级节点
		File *file;  //若为文件, 则指向对应的文件数据

		Dir()
		{
			name = " ";
			path = "QSY/";
			type = 0;
			nums = 0;
			father = this;
			file = NULL;
		}

		bool hasFather()
		{
			if (father != this && father != NULL) return 1;
			else return 0;
		}

		void linkToFile(File *_file)//将节点与文件连接
		{
			if (!type) file = _file;
		}

		void showChilds()//输出下一级节点
		{
			if (!childs.size())
			{
				if (type) cout << "空" << endl;
				return;
			}

			for (int i = 0; i < childs.size(); i++)
				cout << *childs[i] << endl;
		}

		void showPath()//输出绝对路径
		{
			cout << path << endl;
		}

		void showAll(string head = "")//输出该节点以下的所有节点
		{
			if (!childs.size() && head == "")
			{
				if (type) cout << "空" << endl;
				return;
			}

			for (int i = 0; i < childs.size(); i++)
			{
				//递归输出子孙节点
				cout << head << *childs[i] << endl;
				if (childs[i]->childs.size()) childs[i]->showAll(head + "\t");
			}
		}

		void createFileChild(string _name)
		{
			if (iswriting)
			{
				cout << "其他进程正在写入文件, 请稍候" << endl;
				return;
			}

			if (type == 0)
			{
				cout << "无法在文件下创建子项" << endl;
				return;
			}

			//查重
			for (int i = 0; i < childs.size(); i++)
				if (childs[i]->name == _name && !childs[i]->type)
				{
					cout << "该级目录下已存在该名称的文件" << endl;
					return;
				}

			//填写信息
			Dir *temp = new Dir();
			temp->type = 0;
			temp->name = _name;
			temp->father = this;
			temp->path = path + temp->name + "/";
			temp->nums = 0;
			temp->file = new File(temp->name, temp->path);

			childs.push_back(temp);
			nums = childs.size();
		}

		void removeFileChild(string _name)//移除子文件
		{
			if (iswriting)
			{
				cout << "其他进程正在写入文件, 请稍候" << endl;
				return;
			}

			bool search = 0;
			for (int i = 0; i < childs.size(); i++)
				if (childs[i]->name == _name && !childs[i]->type)
				{
					if (childs[i]->file->isLocked) //文件被锁定时
					{
						cout << "文件" << _name << "已被锁定, 无法操作" << endl;
						return;
					}
					childs.erase(childs.begin() + i);
					cout << "文件" << path << "/" << _name << "已移除" << endl;
					search = 1;
					break;
				}
			nums = childs.size();
			if (!search) cout << "文件" << _name << "不存在于当前目录下" << endl;
		}

		void createDirChild(string _name)//创建子文件夹
		{
			if (iswriting)
			{
				cout << "其他进程正在写入文件, 请稍候" << endl;
				return;
			}

			if (type == 0)
			{
				cout << "无法在文件下创建子项" << endl;
				return;
			}

			//查重
			for (int i = 0; i < childs.size(); i++)
				if (childs[i]->name == _name && childs[i]->type)
				{
					cout << "该级目录下已存在该名称的文件夹" << endl;
					return;
				}

			//填写信息
			Dir *temp = new Dir();
			temp->type = 1;
			temp->name = _name;
			temp->father = this;
			temp->path = path + temp->name + "/";
			temp->nums = 0;
			nums++;
			childs.push_back(temp);
		}

		void removeDirChild(string _name, bool _switch = 0)//移除子文件夹
		{
			if (iswriting)
			{
				cout << "其他进程正在写入文件, 请稍候" << endl;
				return;
			}

			bool search = 0;//记录查找结果
			for (int i = 0; i < childs.size(); i++)
				if (childs[i]->name == _name && childs[i]->type)
				{
					if(_switch) childs[i]->removeAllChild();
					childs.erase(childs.begin() + i);
					cout << "文件" << path << "/" << _name << "已移除" << endl;
					search = 1;
					break;
				}
			nums = childs.size();
			if (!search) cout << "文件夹" << _name << "不存在于当前目录下" << endl;
		}

		void removeAllChild()//移除所有子对象
		{
			while(childs.size() > 0)
			{
				childs[0]->removeAllChild();
				cout << "文件";
				if (childs[0]->type) cout << "夹";
				cout << childs[0]->path << "已移除" << endl;
				childs.erase(childs.begin());
			}
		}

		void toFile(ostream &os, vector<File> &fileArray)//将该节点以下的内容写入输出流
		{
			os << name << " " << type << " " << childs.size() << endl;
			if (file != NULL) fileArray.push_back(*file);
			for (int i = 0; i < childs.size(); i++)
				childs[i]->toFile(os, fileArray);
		}

		void Init (istream &is)//为root初始化
		{
			string readLine = "";//输入限制在一行
			while(readLine == "" || readLine == "\n")//规避空行
				getline(is, readLine, '\n');

			stringstream ss;
			ss << readLine;
			ss >> name >> type >> nums;
			//cout << name << type << nums;
			if (hasFather()) path = father->path + name + "/";
			else path = "QSY/";
			if (!type) file = new File(name, path);
			for (int i = 0; i < nums; i++)
			{
				//递归初始化子项
				Dir *child = new Dir();
				child->father = this;
				child->Init(is);
				childs.push_back(child);
			}
		}

} *root;

ostream &operator << (ostream &os, Dir &temp)
{
	os << temp.name;
	if (temp.type)
	{
		os << "  文件夹";
		os << "  子成员数量: " << temp.nums;
//		if (temp.father != &temp)
//			os << "  父节点:" << temp.father->name;
	}
	else
	{
		os << "  文件";
		if (temp.file != NULL)
			os << "  大小: " << temp.file->data.size() << "行";
		else
			os << "  大小: 0行";
	}

	return os;
}

Dir *backToTop(Dir *temp)//回到最顶级节点
{
	while (temp->hasFather())
		temp = temp->father;
	return temp;
}

Dir *cdName(Dir *temp, string name, bool access = 0)//相对路径访问
{
	for (int i = 0; i < temp->childs.size(); i++)
		if (temp->childs[i]->name == name)
		{
			if (!temp->childs[i]->type && !access)
			{
				cout << "无法使用cd命令打开文件, 请改用open命令" << endl;
				return temp;
			}
			else return temp->childs[i];
		}
	return NULL;
}

Dir *cdPath(Dir *temp, string _path, bool access = 0)//绝对路径访问
{
	if (_path[_path.size() - 1] != '/')
		_path.push_back('/');

	stringstream ss;
	ss << _path;

	string part;
	vector<string> parts;
	while (getline(ss, part, '/'))
		parts.push_back(part);

	temp = backToTop(temp);
	for (int i = 1; i < parts.size(); i++)//从1开始, 因为不遍历根目录
	{
		bool searched = 0;
		for (int o = 0; o < temp->childs.size(); o++)
			if (temp->childs[o]->name == parts[i])
			{
				if (!temp->childs[o]->type && !access)
				{
					cout << "无法使用cd命令访问文件, 已跳转至父文件夹" << endl;
					searched = 1;
					break;
				}
				else
				{
					temp = temp->childs[o];
					searched = 1;
					break;
				}
			}
		if (!searched)
		{
			cout << "路径" << _path << "不存在" << endl;
			return NULL;
		}
	}

	//为用户试图使用cd命令访问根目录或用户目录的行为提供处理
	if (access == 0 && parts.size() == 1 && parts[0] == "QSY")
	{
		cout << "没有访问根目录的权限" << endl;
		return NULL;
	}

	return temp;
}

Dir *cd(Dir *thisDir, string path, bool access = 0)//相对路径与绝对路径综合
{
	Dir *temp = cdName(thisDir, path, access);
	if (temp != NULL) return temp;
	else
	{
		//cout << "请求的节点在当前目录下不存在, 已切换至全局路径" << endl;
		Dir *temp2 = cdPath(thisDir, path, access);
		if (temp2 != NULL) return temp2;
	}
	return NULL;
}

Dir *openFile(Dir *temp, string name)
{
	for (int i = 0; i < temp->childs.size(); i++)
		if (temp->childs[i]->name == name && !temp->childs[i]->type)
		{
//			if (temp->childs[i].file->isLocked) //文件被锁定时
//			{
//				cout << "文件" << name << "已被锁定, 无法打开" << endl;
//				return NULL;
//			}
			temp->childs[i]->file->lseek = 0;
			cout << "文件" << name << "已打开" << endl;
			return temp->childs[i];
		}
	cout << "文件" << name << "不存在于当前目录下" << endl;
	return NULL;
}

Dir *copyTo(Dir *temp, string oldPath, string newPath)
{
	if (iswriting)
	{
		cout << "其他进程正在写入文件, 请稍候" << endl;
		return NULL;
	}

	Dir *oldDir = cd(temp, oldPath, 1);
	Dir *newDir = cd(temp, newPath, 1);

	if (oldDir == NULL || oldDir->type)
	{

		cout << oldPath << "不是一个符合要求的文件" << endl;
		return NULL;
	}

	if (newDir == NULL || !newDir->type)
	{
		cout << newPath << "不是一个符合要求的文件夹" << endl;
		return NULL;
	}

	if (oldDir->file->isLocked) //文件被锁定时
	{
		cout << "文件" << oldPath << "已被锁定, 无法操作" << endl;
		return NULL;
	}
//	cout << *oldDir << endl;
//	cout << *newDir << endl;
//	cout << *temp << endl;
	//对新文件信息进行修改
	Dir *moveDir = new Dir();
	moveDir->name = oldDir->name;

	bool search = 1;
	int n = 0;
	while (search)//避免重名
	{
		search = 0;
		for (int i = 0; i < newDir->childs.size(); i++)
			if (!newDir->childs[i]->type && newDir->childs[i]->name == moveDir->name)
			{
				if (n == 0)moveDir->name += "_copy";
				else moveDir->name = oldDir->name + "_copy" + to_string(n);
				search = 1;
				n++;
			}
	}

	moveDir->type = oldDir->type;
	moveDir->father = newDir;
	moveDir->path = newDir->path + moveDir->name + "/";
	if (oldDir->file != NULL)
	{
		File *moveFile = new File(moveDir->name, moveDir->path);
		moveFile->data = oldDir->file->data;
		moveFile->size = oldDir->file->data.size();
		moveDir->file = moveFile;
	}
	newDir->childs.push_back(moveDir);
	newDir->nums = newDir->childs.size();

	return newDir;
}

void File_Init(istream &is, Dir *temp)
{
	string _name;
	string _path;
	int _size;
	bool _isLocked;
	int _lseek;
	while (is >> _name >> _size >> _path >> _isLocked >> _lseek)
	{
		File *file = new File(_name, _path, _size, _isLocked, _lseek);
		//cout << _name << " " << _size << " " << _path << endl;

		string line;
		getline(is, line, '\n');
		for (int i = 0; i < _size; i++)
		{
			getline(is, line, '\n');
			//cout << "文件内容: " << line << endl;
			file->data.push_back(line);
		}

		backToTop(temp);

		temp = cdPath(temp, _path, 1);
		//cout << "寻找到的文件路径:" << temp->path << endl;
		temp->linkToFile(file);
		//cout << temp->file->data[0] << endl;
	}
}

void import(Dir *thisRoot, string iPath, string sPath)
{
	if (iswriting)
	{
		cout << "其他进程正在写入文件, 请稍候" << endl;
		return;
	}

	fstream iFile(iPath, ios::in | ios::out);
	Dir *sFDir = cd(thisRoot, sPath);

	if (!iFile.is_open())
	{
		cout << "无法打开文件" << iPath << endl;
		return;
	}
	if (sFDir == NULL || sFDir->type == 0)
	{
		cout << "无法找到文件夹" << sPath << endl;
		return;
	}

	// 找到最后一个斜杠的位置
	size_t found = iPath.find_last_of("/\\");
	// 获取文件名
	string fileName = iPath.substr(found + 1);

	//填写节点及文件信息
	Dir *sDir = new Dir();
	sDir->father = sFDir;
	sDir->name = fileName;
	sDir->type = 0;
	sDir->path = sDir->father->path + sDir->name + "/";

	File *sFile = new File(sDir->name, sDir->path);
	sDir->file = sFile;

	string temp;
	while (getline(iFile, temp, '\n'))
	{
		cout << temp << endl;
		sFile->data.push_back(temp);
	}
	sFile->size = sFile->data.size();

	thisRoot->childs.push_back(sDir);
	thisRoot->nums = thisRoot->childs.size();

	cout << "文件已导入至" << thisRoot->path <<", 大小为"<< sFile->data.size() << endl;
}

void _export(Dir *thisRoot, string sPath, string oPath)
{
	if (iswriting)
	{
		cout << "其他进程正在写入文件, 请稍候" << endl;
		return;
	}

	Dir *sDir = cd(thisRoot, sPath, 1);
	if (sDir == NULL || sDir->type == 1)
	{
		cout << "无法找到文件" << sPath << endl;
		return;
	}

	//获取输出文件名
	if (oPath[oPath.size() - 1] != '/') oPath.push_back('/');
	oPath += sDir->name;
	if (oPath.size() < 4 || oPath.substr(oPath.length() - 4) != ".txt")
		oPath += ".txt";

	//输出文件
	fstream outPut(oPath, ios::in | ios::out | ios::trunc);
	for (int i = 0; i < sDir->file->data.size(); i++)
	{
		outPut << sDir->file->data[i] << endl;
	}

	//检查导出结果
	fstream iFile(oPath, ios::in | ios::out);
	if (!iFile.is_open())
		cout << "文件" << oPath << "导出失败, 路径不存在或程序无权限于该路径下创建文件" << endl;
	else
		cout << "文件" << oPath << "导出成功" << endl;
}


