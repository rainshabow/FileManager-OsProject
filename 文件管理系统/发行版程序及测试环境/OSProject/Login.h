#include<iostream>
#include<vector>
#include<map>
#include<fstream>

#include"Dir.h"
using namespace std;

class User
{
	public:
		string name;
		string code;
		User(string _name, string _code)
		{
			name = _name;
			code = _code;
		}
};

class Login
{
	public:
		vector<User> users;
		map<string, string> user;   //���ڴ洢�û���������ļ�ֵ��, �����û���Ϊ��
		Login()
		{
		}

		void Init(istream &data)
		{
			users.clear();
			user.clear();

			int num;
			data >> num;
			for (int i = 0; i < num ; i++)
			{
				string name;
				string code;
				data >> name >> code;

				User temp(name, code);
				user[name] = code;
				users.push_back(temp);
			}

			string temp;
			getline(data, temp, '\n');
		}

		void Run(Dir *&_root)
		{
			int _switch = 0;
			string userName;

			cout << "��ӭʹ���ļ�����ϵͳ" << endl;
			//ִ�е�¼������ѭ����
			while (_switch != 3)
			{
				userAreaCheck(root);//����û��Ƿ��ж�Ӧ���ļ���, û���򴴽�
				cout << "��ѡ����Ҫ���еĲ���(1.��¼/2.ע��/3.�˳�):";

				cin >> _switch;
				while (_switch != 1 && _switch != 2 && _switch != 3)
				{
					cout << "����ȷ������, ����������(1.��¼/2.ע��/3.�˳�):";
					cin >> _switch;
				}

				switch (_switch)
				{
					case 1:
						cout << "ʾ���û�:Administrator ����:000000" << endl;
						if (!login(userName)) break;
						else for (int i = 0; i < _root->childs.size(); i++)
								if (_root->childs[i]->name == userName)
								{
									_root = _root -> childs[i];
									return;
								}
						break;
					case 2:
					{
						string _name = "������ �û�";//ʹ�÷Ƿ����Ʊ����û����ø�����
						string _code;
						string _code2 = "ȷ���� ����";

						do
						{
							cout << "�������û�����:";
							cin >> _name;
							if (user.count(_name) != 0)
								cout << "�û��Ѵ���, ����������" << endl;
						}
						while (user.count(_name) != 0);
						while (_code != _code2)
						{
							cout << "����������:";
							cin >> _code;

							cout << "��ȷ������:";
							cin >> _code2;

							if (_code != _code2)
								cout << "�������벻һ��, ����������" << endl;
						}

						bool confirm = 0;
						cout << "ȷ�ϴ����û�" << _name << "(1.ȷ��/0.ȡ��):";
						cin >> confirm;
						if (confirm)
						{
							User temp(_name, _code);
							user[_name] = _code;
							users.push_back(temp);
							cout << "�û�" << _name << "��ע��" << endl;
						}
						else cout << "������ȡ��" << endl;

						break;
					}
					case 3:
						exit(0);
					default:
						//TODO
						break;
				}
			}
			return;
		}

		bool login(string &userName)
		{
			string name;
			cout << "�������û���: ";
			cin >> name;

			string code;
			cout << "����������: ";
			cin >> code;

			if (user[name] == code)
			{
				userName = name;
				cout << "��¼�ɹ�" << endl;
				return 1;
			}

			cout << "��¼ʧ��" << endl;
			return 0;
		}

		void userAreaCheck(Dir *&root)//ȷ��ÿһ���û��������Ӧ���ļ���
		{
			root = backToTop(root);
			for (int p = 0; p < users.size(); p++)
			{
				bool searched = 0;
				for (int q = 0; q < root->childs.size(); q++)
					if (users[p].name == root->childs[q]->name)
					{
						searched = 1;
						break;
					}
				if (!searched) root->createDirChild(users[p].name);
			}
		}
} Login;
