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
		map<string, string> user;   //用于存储用户名与密码的键值对, 其中用户名为键
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

			cout << "欢迎使用文件管理系统" << endl;
			//执行登录操作的循环体
			while (_switch != 3)
			{
				userAreaCheck(root);//检查用户是否有对应的文件夹, 没有则创建
				cout << "请选择需要进行的操作(1.登录/2.注册/3.退出):";

				cin >> _switch;
				while (_switch != 1 && _switch != 2 && _switch != 3)
				{
					cout << "不正确的输入, 请重新输入(1.登录/2.注册/3.退出):";
					cin >> _switch;
				}

				switch (_switch)
				{
					case 1:
						cout << "示例用户:Administrator 密码:000000" << endl;
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
						string _name = "不存在 用户";//使用非法名称避免用户采用该名称
						string _code;
						string _code2 = "确认用 密码";

						do
						{
							cout << "请输入用户名称:";
							cin >> _name;
							if (user.count(_name) != 0)
								cout << "用户已存在, 请重新输入" << endl;
						}
						while (user.count(_name) != 0);
						while (_code != _code2)
						{
							cout << "请输入密码:";
							cin >> _code;

							cout << "请确认密码:";
							cin >> _code2;

							if (_code != _code2)
								cout << "两次密码不一致, 请重新输入" << endl;
						}

						bool confirm = 0;
						cout << "确认创建用户" << _name << "(1.确认/0.取消):";
						cin >> confirm;
						if (confirm)
						{
							User temp(_name, _code);
							user[_name] = _code;
							users.push_back(temp);
							cout << "用户" << _name << "已注册" << endl;
						}
						else cout << "创建已取消" << endl;

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
			cout << "请输入用户名: ";
			cin >> name;

			string code;
			cout << "请输入密码: ";
			cin >> code;

			if (user[name] == code)
			{
				userName = name;
				cout << "登录成功" << endl;
				return 1;
			}

			cout << "登录失败" << endl;
			return 0;
		}

		void userAreaCheck(Dir *&root)//确保每一个用户都有其对应的文件夹
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
