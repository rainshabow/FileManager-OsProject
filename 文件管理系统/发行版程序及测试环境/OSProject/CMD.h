#include<iostream>
#include<sstream>
#include<vector>
#include<map>

#include"Login.h"
using namespace std;

class CMD   //ָ����, ���ڽ���ָ��
{
	public:
		vector<string> currentCmd;  //��ǰָ��
		CMD(){}
		string GetCMD() //��ȡָ��
		{
			cout << "������ָ��: ";

			//��ȡ��������
			string CMD;
			getline(cin, CMD, '\n');
			while (CMD == "\n" || CMD == "") //��ֹδ��ȡ���ַ����������
				getline(cin, CMD, '\n');
			stringstream ss;
			ss << CMD;

			//ת����currentCmd, ÿ��stringΪָ���һ������
			currentCmd.clear();
			string CMDPart;
			while (ss >> CMDPart)
				currentCmd.push_back(CMDPart);

			return currentCmd[0];
		}

		void CheckCurrentCmd()  //��ʾ��ǰָ��
		{
			if (!currentCmd.size())
			{
				cout << "δ����ָ��" << endl;
				return;
			}

			cout << "ָ���Ϊ" << currentCmd.size() << "����:";
			for (int i = 0; i < currentCmd.size() - 1; i++)
				cout << currentCmd[i] << ", ";
			cout << currentCmd[currentCmd.size() - 1] << endl;
		}

		void CheckHelp(string cmd = "") // ָ��help, ������ʾָ�
		{
			if (cmd == "") {
				cout << "�����Ǳ��ļ�����ϵͳ��ָ�:" << endl;
				cout << "ָ���� [������] (��ѡ��)" << endl;
				cout << "Ŀ¼��:" << endl;
				cout << "cd [·��]\t����Ŀ¼" << endl;
				cout << "dir\t��ʾ��ǰĿ¼" << endl;
				cout << "mkdir [Ŀ¼��]\t����Ŀ¼" << endl;
				cout << "rmdir [Ŀ¼��] (-a)\tɾ��Ŀ¼" << endl;
				cout << "�ļ���:" << endl;
				cout << "create [�ļ���]\t�����ļ�" << endl;
				cout << "delete [�ļ���]\tɾ���ļ�" << endl;
				cout << "move [�ļ�·��] [�ļ���·��]\t�ƶ��ļ�" << endl;
				cout << "copy [�ļ�·��] (�ļ���·��)\t�����ļ�" << endl;
				cout << "open [�ļ���]\t���ļ�" << endl;
				cout << "�����������ȴ��ļ�" << endl;
				cout << "close\t�ر��ļ�" << endl;
				cout << "read\t���ļ�" << endl;
				cout << "write\tд�ļ�" << endl;
				cout << "flock (-u)\t�ļ�����/����" << endl;
				cout << "head [num/-num]\t��ʾ�ļ���ǰnum��" << endl;
				cout << "tail [num/-num]\t��ʾ�ļ��ĺ�num��" << endl;
				cout << "lseek [offset]\t�ļ���дָ����ƶ������ļ�ָ�뵱ǰλ�ô�����ƶ� offset������ʱ��ǰ�ƶ�offset" << endl;
				cout << "����:" << endl;
				cout << "import [�ⲿ·��] (�ڲ�·��)" << endl;
				cout << "export [�ڲ�·��] [�ⲿ·��]" << endl;
				cout << "help (ָ����)\t ��ʾ�����ĵ�" << endl;
				cout << "exit\t�˳��ļ�����ϵͳ" << endl;
			}
			else if (cmd == "cd")
			{
				cout << "cd [·��]\t����Ŀ¼" << endl;
				cout << "���������·���ļ���, �����Ǿ���·��, Ҳ���������·��" << endl;
				cout << "ʾ��:" << endl;
				cout << "cd A" << endl;
				cout << "cd QSY/Administrator/A" << endl;
			}
			else if (cmd == "dir")
			{
				cout << "dir\t��ʾ��ǰĿ¼" << endl;
				cout << "��ʾ��ǰĿ¼�µ���״�ṹ" << endl;
			}
			else if (cmd == "mkdir")
			{
				cout << "mkdir [Ŀ¼��]\t����Ŀ¼" << endl;
				cout << "�ڵ�ǰ�ļ����´���ָ�����Ƶ��ļ���" << endl;
				cout << "ʾ��:" << endl;
				cout << "mkdir os" << endl;
			}
			else if (cmd == "rmdir")
			{
				cout << "rmdir [Ŀ¼��] (-a)\tɾ��Ŀ¼" << endl;
				cout << "�ڵ�ǰ�ļ������Ƴ�ָ�����Ƶ��ļ���, ���-a��׺���еݹ�ɾ��" << endl;
				cout << "ʾ��:" << endl;
				cout << "rmdir os" << endl;
				cout << "rmdir os -a" << endl;
			}
			else if (cmd == "create")
			{
				cout << "create [�ļ���]\t�����ļ�" << endl;
				cout << "�ڵ�ǰ�ļ����´���ָ�����Ƶ��ļ�" << endl;
				cout << "ʾ��:" << endl;
				cout << "create abc" << endl;
			}
			else if (cmd == "delete")
			{
				cout << "delete [�ļ���]\tɾ���ļ�" << endl;
				cout << "�ڵ�ǰ�ļ�����ɾ��ָ�����Ƶ��ļ�" << endl;
				cout << "ʾ��:" << endl;
				cout << "delete abc" << endl;
			}
			else if (cmd == "copy")
			{
				cout << "copy [�ļ�·��] (�ļ���·��)\t�����ļ�" << endl;
				cout << "��ָ��·�����ļ����Ƶ�ָ��·�����ļ�����, ��ָ���ļ�����Ĭ��Ϊ��ǰ�ļ���" << endl;
				cout << "ʾ��:" << endl;
				cout << "copy abc" << endl;
				cout << "copy abc QSY/Administrator/A" << endl;
				cout << "copy QSY/Administrator/A/abc f" << endl;
			}
			else if (cmd == "move")
			{
				cout << "move [�ļ�·��] [�ļ���·��]\t�ƶ��ļ�" << endl;
				cout << "��ָ��·�����ļ��ƶ���ָ��·�����ļ�����" << endl;
				cout << "ʾ��:" << endl;
				cout << "move abc QSY/Administrator/A" << endl;
				cout << "move QSY/Administrator/A/abc f" << endl;
			}
			else if (cmd == "open")
			{
				cout << "open [�ļ���]\t���ļ�" << endl;
				cout << "�򿪵�ǰ�ļ�����ָ�����Ƶ��ļ�" << endl;
				cout << "ʾ��:" << endl;
				cout << "open abc" << endl;
			}
			else if (cmd == "close")
			{
				cout << "close\t�ر��ļ�" << endl;
				cout << "�رյ�ǰ�򿪵��ļ�, �����ϼ��ļ���(���ȴ��ļ�)" << endl;
			}
			else if (cmd == "read")
			{
				cout << "read\t���ļ�" << endl;
				cout << "�����ǰ��дָ�����ļ�ĩβ������(���ȴ��ļ�)" << endl;
			}
			else if (cmd == "write")
			{
				cout << "write\tд�ļ�" << endl;
				cout << "д����ǰ��дָ�����ļ�ĩβ������(���ȴ��ļ�)" << endl;
			}
			else if (cmd == "flock")
			{
				cout << "flock (-u)\t�ļ�����/����" << endl;
				cout << "�ļ�����, ��ֹ��ȡ, д��, ����, �ƶ��Ȳ���. ��-u��׺ʱΪ����(���ȴ��ļ�)" << endl;
				cout << "ʾ��:" << endl;
				cout << "flock abc" << endl;
				cout << "flock abc -u" << endl;
			}
			else if (cmd == "head")
			{
				cout << "head [num/-num]\t��ʾ�ļ���ǰnum��" << endl;
				cout << "ʾ��:" << endl;
				cout << "head 10" << endl;
				cout << "head -10, �˴���'-'Ϊ��׺��־" << endl;
			}
			else if (cmd == "tail")
			{
				cout << "tail [num/-num]\t��ʾ�ļ��ĺ�num��" << endl;
				cout << "ʾ��:" << endl;
				cout << "tail 10" << endl;
				cout << "tail -10, �˴���'-'Ϊ��׺��־" << endl;
			}
			else if (cmd == "lseek")
			{
				cout << "lseek [offset]\t�ļ���дָ����ƶ������ļ�ָ�뵱ǰλ�ô�����ƶ� offset������ʱ��ǰ�ƶ�offset" << endl;
				cout << "�ƶ��ļ��Ķ�дָ��, ��Ӱ���д����" << endl;
				cout << "ʾ��:" << endl;
				cout << "lseek  10" << endl;
				cout << "lseek  -10, �˴���'-'Ϊ����" << endl;
			}
			else if (cmd == "import")
			{
				cout << "import [�ⲿ·��] (�ڲ�·��)" << endl;
				cout << "����һ���ⲿ�ļ���ָ���ڲ�·��, ȱʡʱָ��Ϊ��ǰ·��" << endl;
				
			}
			else if (cmd == "export")
			{
				cout << "export [�ڲ�·��] (�ⲿ·��)" << endl;
				cout << "����һ���ڲ��ļ���ָ���ⲿ·��, ȱʡʱָ��Ϊ����Ŀ¼" << endl;
			}
			else
			{
				cout << "û�����ָ��İ�����Ϣ" << endl;
			}
		}

		bool ProcessCmd() //����ָ��
		{
			if (!currentCmd.size())
			{
				cout << "��ָ��" << endl;
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
					cout << "�ļ��ѹر�" << endl;
				}
				else cout << "���ȴ��ļ�" << endl;
			}
			else if	(currentCmd[0] == "read" && currentCmd.size() == 1)
			{
				if (root->file != NULL)
				{
					root->file->checkData();
				}
				else cout << "���ȴ��ļ�" << endl;
			}
			else if (currentCmd[0] == "write" && currentCmd.size() == 1)
			{
				if (root->file != NULL)
				{
					root->file->writeData();
				}
				else cout << "���ȴ��ļ�" << endl;
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
						cout << "�������" << endl;
					}
					else cout << "�޷����ļ�������";
				}
				else if (currentCmd.size() == 2 && currentCmd[1] == "-u")
				{
					if (!root->type)
					{
						root->file->flock(0);
						cout << "�������" << endl;
					}
					else cout << "�޷����ļ��н���";
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
				else cout << "�޷����ļ���ʹ��head����";
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
				else cout << "�޷����ļ���ʹ��tail����";
			}
			else if (currentCmd[0] == "lseek" && currentCmd.size() == 2)
			{
				if (!root->type)
				{
					string number = currentCmd[1];
					int n = stoi(number);
					root->file->setlseek(n);
					cout << "�������ı�ƫ����Ϊ" << root->file->lseek << endl;
				}
				else cout << "�޷����ļ���ʹ��lseek����";
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
				cout << "ϵͳ���˳�" << endl;
				return 1;
			}
			else
			{
				cout << "ָ���ʽ����, ��ʹ��helpָ���ȡָ�����" << endl;
			}

			return 0;
		}
} CMD;
