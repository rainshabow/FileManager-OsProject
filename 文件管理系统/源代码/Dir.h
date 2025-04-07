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
		string name;//����
		string path;//����·��
		int size;   //��С, ��������
		bool isLocked;//����״̬
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
				cout << "�ļ��ѱ�����, �޷���ȡ" << endl;
				return;
			}
			if (lseek == 0 || head != -1 || tail != -1)//����lseekƫ����Ϊ���������
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
			else//��lseekƫ����Ϊ���������
			{
				int count = lseek;
				for (int i = 0; i < data.size(); i++)
					if (count != 0) 
					{
						if (count < (int)data[i].size())//�����벻��ȫ�н��д���
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
				cout << "�ļ��ѱ�����, �޷�д��" << endl;
				return;
			}

			if (iswriting == 1)
			{
				cout << "������������д���ļ�, ���Ժ�" << endl;
				return;
			}
			else P();
			cout << "��д���ļ�����, �Զ���һ�е�/end��������:" << endl;

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
						if (count < (int)data[i].size())//�����벻��ȫ�н��д���
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
				cout << "�ļ���д�����첽����" << endl;
				return;
			}
			else V();

			cout << "�ļ�д�����" << endl;
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
				cout << "������������д���ļ�, ���Ժ�" << endl;
				return 0;
			}
			return isLocked = _isLocked;
		}
} Files;

class Dir//�ڵ���, ���ڹ���Ŀ¼
{
	public:
		string name;	//��ǰ�ڵ���
		string path;    //����·��
		bool type;  //����, 1��ʾ��ǰ·�����ļ���, 0��ʾ��ǰ·�����ļ�
		int nums;   //��Ա����
		vector<Dir *> childs;	//��Ա·��, ָ����һ�������г�Ա
		Dir *father; //ָ����һ���ڵ�
		File *file;  //��Ϊ�ļ�, ��ָ���Ӧ���ļ�����

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

		void linkToFile(File *_file)//���ڵ����ļ�����
		{
			if (!type) file = _file;
		}

		void showChilds()//�����һ���ڵ�
		{
			if (!childs.size())
			{
				if (type) cout << "��" << endl;
				return;
			}

			for (int i = 0; i < childs.size(); i++)
				cout << *childs[i] << endl;
		}

		void showPath()//�������·��
		{
			cout << path << endl;
		}

		void showAll(string head = "")//����ýڵ����µ����нڵ�
		{
			if (!childs.size() && head == "")
			{
				if (type) cout << "��" << endl;
				return;
			}

			for (int i = 0; i < childs.size(); i++)
			{
				//�ݹ��������ڵ�
				cout << head << *childs[i] << endl;
				if (childs[i]->childs.size()) childs[i]->showAll(head + "\t");
			}
		}

		void createFileChild(string _name)
		{
			if (iswriting)
			{
				cout << "������������д���ļ�, ���Ժ�" << endl;
				return;
			}

			if (type == 0)
			{
				cout << "�޷����ļ��´�������" << endl;
				return;
			}

			//����
			for (int i = 0; i < childs.size(); i++)
				if (childs[i]->name == _name && !childs[i]->type)
				{
					cout << "�ü�Ŀ¼���Ѵ��ڸ����Ƶ��ļ�" << endl;
					return;
				}

			//��д��Ϣ
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

		void removeFileChild(string _name)//�Ƴ����ļ�
		{
			if (iswriting)
			{
				cout << "������������д���ļ�, ���Ժ�" << endl;
				return;
			}

			bool search = 0;
			for (int i = 0; i < childs.size(); i++)
				if (childs[i]->name == _name && !childs[i]->type)
				{
					if (childs[i]->file->isLocked) //�ļ�������ʱ
					{
						cout << "�ļ�" << _name << "�ѱ�����, �޷�����" << endl;
						return;
					}
					childs.erase(childs.begin() + i);
					cout << "�ļ�" << path << "/" << _name << "���Ƴ�" << endl;
					search = 1;
					break;
				}
			nums = childs.size();
			if (!search) cout << "�ļ�" << _name << "�������ڵ�ǰĿ¼��" << endl;
		}

		void createDirChild(string _name)//�������ļ���
		{
			if (iswriting)
			{
				cout << "������������д���ļ�, ���Ժ�" << endl;
				return;
			}

			if (type == 0)
			{
				cout << "�޷����ļ��´�������" << endl;
				return;
			}

			//����
			for (int i = 0; i < childs.size(); i++)
				if (childs[i]->name == _name && childs[i]->type)
				{
					cout << "�ü�Ŀ¼���Ѵ��ڸ����Ƶ��ļ���" << endl;
					return;
				}

			//��д��Ϣ
			Dir *temp = new Dir();
			temp->type = 1;
			temp->name = _name;
			temp->father = this;
			temp->path = path + temp->name + "/";
			temp->nums = 0;
			nums++;
			childs.push_back(temp);
		}

		void removeDirChild(string _name, bool _switch = 0)//�Ƴ����ļ���
		{
			if (iswriting)
			{
				cout << "������������д���ļ�, ���Ժ�" << endl;
				return;
			}

			bool search = 0;//��¼���ҽ��
			for (int i = 0; i < childs.size(); i++)
				if (childs[i]->name == _name && childs[i]->type)
				{
					if(_switch) childs[i]->removeAllChild();
					childs.erase(childs.begin() + i);
					cout << "�ļ�" << path << "/" << _name << "���Ƴ�" << endl;
					search = 1;
					break;
				}
			nums = childs.size();
			if (!search) cout << "�ļ���" << _name << "�������ڵ�ǰĿ¼��" << endl;
		}

		void removeAllChild()//�Ƴ������Ӷ���
		{
			while(childs.size() > 0)
			{
				childs[0]->removeAllChild();
				cout << "�ļ�";
				if (childs[0]->type) cout << "��";
				cout << childs[0]->path << "���Ƴ�" << endl;
				childs.erase(childs.begin());
			}
		}

		void toFile(ostream &os, vector<File> &fileArray)//���ýڵ����µ�����д�������
		{
			os << name << " " << type << " " << childs.size() << endl;
			if (file != NULL) fileArray.push_back(*file);
			for (int i = 0; i < childs.size(); i++)
				childs[i]->toFile(os, fileArray);
		}

		void Init (istream &is)//Ϊroot��ʼ��
		{
			string readLine = "";//����������һ��
			while(readLine == "" || readLine == "\n")//��ܿ���
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
				//�ݹ��ʼ������
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
		os << "  �ļ���";
		os << "  �ӳ�Ա����: " << temp.nums;
//		if (temp.father != &temp)
//			os << "  ���ڵ�:" << temp.father->name;
	}
	else
	{
		os << "  �ļ�";
		if (temp.file != NULL)
			os << "  ��С: " << temp.file->data.size() << "��";
		else
			os << "  ��С: 0��";
	}

	return os;
}

Dir *backToTop(Dir *temp)//�ص�����ڵ�
{
	while (temp->hasFather())
		temp = temp->father;
	return temp;
}

Dir *cdName(Dir *temp, string name, bool access = 0)//���·������
{
	for (int i = 0; i < temp->childs.size(); i++)
		if (temp->childs[i]->name == name)
		{
			if (!temp->childs[i]->type && !access)
			{
				cout << "�޷�ʹ��cd������ļ�, �����open����" << endl;
				return temp;
			}
			else return temp->childs[i];
		}
	return NULL;
}

Dir *cdPath(Dir *temp, string _path, bool access = 0)//����·������
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
	for (int i = 1; i < parts.size(); i++)//��1��ʼ, ��Ϊ��������Ŀ¼
	{
		bool searched = 0;
		for (int o = 0; o < temp->childs.size(); o++)
			if (temp->childs[o]->name == parts[i])
			{
				if (!temp->childs[o]->type && !access)
				{
					cout << "�޷�ʹ��cd��������ļ�, ����ת�����ļ���" << endl;
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
			cout << "·��" << _path << "������" << endl;
			return NULL;
		}
	}

	//Ϊ�û���ͼʹ��cd������ʸ�Ŀ¼���û�Ŀ¼����Ϊ�ṩ����
	if (access == 0 && parts.size() == 1 && parts[0] == "QSY")
	{
		cout << "û�з��ʸ�Ŀ¼��Ȩ��" << endl;
		return NULL;
	}

	return temp;
}

Dir *cd(Dir *thisDir, string path, bool access = 0)//���·�������·���ۺ�
{
	Dir *temp = cdName(thisDir, path, access);
	if (temp != NULL) return temp;
	else
	{
		//cout << "����Ľڵ��ڵ�ǰĿ¼�²�����, ���л���ȫ��·��" << endl;
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
//			if (temp->childs[i].file->isLocked) //�ļ�������ʱ
//			{
//				cout << "�ļ�" << name << "�ѱ�����, �޷���" << endl;
//				return NULL;
//			}
			temp->childs[i]->file->lseek = 0;
			cout << "�ļ�" << name << "�Ѵ�" << endl;
			return temp->childs[i];
		}
	cout << "�ļ�" << name << "�������ڵ�ǰĿ¼��" << endl;
	return NULL;
}

Dir *copyTo(Dir *temp, string oldPath, string newPath)
{
	if (iswriting)
	{
		cout << "������������д���ļ�, ���Ժ�" << endl;
		return NULL;
	}

	Dir *oldDir = cd(temp, oldPath, 1);
	Dir *newDir = cd(temp, newPath, 1);

	if (oldDir == NULL || oldDir->type)
	{

		cout << oldPath << "����һ������Ҫ����ļ�" << endl;
		return NULL;
	}

	if (newDir == NULL || !newDir->type)
	{
		cout << newPath << "����һ������Ҫ����ļ���" << endl;
		return NULL;
	}

	if (oldDir->file->isLocked) //�ļ�������ʱ
	{
		cout << "�ļ�" << oldPath << "�ѱ�����, �޷�����" << endl;
		return NULL;
	}
//	cout << *oldDir << endl;
//	cout << *newDir << endl;
//	cout << *temp << endl;
	//�����ļ���Ϣ�����޸�
	Dir *moveDir = new Dir();
	moveDir->name = oldDir->name;

	bool search = 1;
	int n = 0;
	while (search)//��������
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
			//cout << "�ļ�����: " << line << endl;
			file->data.push_back(line);
		}

		backToTop(temp);

		temp = cdPath(temp, _path, 1);
		//cout << "Ѱ�ҵ����ļ�·��:" << temp->path << endl;
		temp->linkToFile(file);
		//cout << temp->file->data[0] << endl;
	}
}

void import(Dir *thisRoot, string iPath, string sPath)
{
	if (iswriting)
	{
		cout << "������������д���ļ�, ���Ժ�" << endl;
		return;
	}

	fstream iFile(iPath, ios::in | ios::out);
	Dir *sFDir = cd(thisRoot, sPath);

	if (!iFile.is_open())
	{
		cout << "�޷����ļ�" << iPath << endl;
		return;
	}
	if (sFDir == NULL || sFDir->type == 0)
	{
		cout << "�޷��ҵ��ļ���" << sPath << endl;
		return;
	}

	// �ҵ����һ��б�ܵ�λ��
	size_t found = iPath.find_last_of("/\\");
	// ��ȡ�ļ���
	string fileName = iPath.substr(found + 1);

	//��д�ڵ㼰�ļ���Ϣ
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

	cout << "�ļ��ѵ�����" << thisRoot->path <<", ��СΪ"<< sFile->data.size() << endl;
}

void _export(Dir *thisRoot, string sPath, string oPath)
{
	if (iswriting)
	{
		cout << "������������д���ļ�, ���Ժ�" << endl;
		return;
	}

	Dir *sDir = cd(thisRoot, sPath, 1);
	if (sDir == NULL || sDir->type == 1)
	{
		cout << "�޷��ҵ��ļ�" << sPath << endl;
		return;
	}

	//��ȡ����ļ���
	if (oPath[oPath.size() - 1] != '/') oPath.push_back('/');
	oPath += sDir->name;
	if (oPath.size() < 4 || oPath.substr(oPath.length() - 4) != ".txt")
		oPath += ".txt";

	//����ļ�
	fstream outPut(oPath, ios::in | ios::out | ios::trunc);
	for (int i = 0; i < sDir->file->data.size(); i++)
	{
		outPut << sDir->file->data[i] << endl;
	}

	//��鵼�����
	fstream iFile(oPath, ios::in | ios::out);
	if (!iFile.is_open())
		cout << "�ļ�" << oPath << "����ʧ��, ·�������ڻ������Ȩ���ڸ�·���´����ļ�" << endl;
	else
		cout << "�ļ�" << oPath << "�����ɹ�" << endl;
}


