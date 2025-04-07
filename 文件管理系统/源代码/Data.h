#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include "CMD.h"
using namespace std;

class Data//���������ļ��Ķ�д
{
	public:
		vector<string> lines;
		Data(string path = "data")
		{
			fstream data(path, ios::in | ios::out | ios::binary);

			string temp;
			while (getline(data, temp, '\n'))
				lines.push_back(temp);

			data.close();
		}

		void createBinary()
		{
			// ��ȡ�ı��ļ�
			ifstream infile("data");

			// �����������ļ�
			ofstream outfile("data.bin", ios::binary | ios::out);

			// ���ж�ȡ�ı��ļ��е����ݣ�����ÿһ��ת��Ϊ�����Ƹ�ʽд�뵽�������ļ���
			string line;
			while (getline(infile, line)) {
				// д���ַ�������
				int length = line.length();
				outfile.write(reinterpret_cast<const char*>(&length), sizeof(length));

				// д���ַ�������
				outfile.write(line.c_str(), length);
			}

			// �ر��ļ���
			//infile.close();
			outfile.close();

			return;
		}

		void readBinary(stringstream& outfile)
		{
			// ��ȡ�������ļ�
			ifstream infile("data.bin", ios::binary | ios::in);

			// �����ı��ļ�
			//ofstream outfile("data");

			// ������ȡ�������ļ��е����ݣ�������ת��Ϊ�ı���ʽд�뵽�ı��ļ���
			int length;
			while (infile.read(reinterpret_cast<char*>(&length), sizeof(length))) {
				// �����ڴ����洢�ַ�������
				char* buffer = new char[length + 1]; // +1 ��Ϊ������ַ���������
				infile.read(buffer, length);
				buffer[length] = '\0'; // ����ַ���������

				// ���ַ���д���ı��ļ���
				outfile << buffer << endl;

				// �ͷ��ڴ�
				delete[] buffer;
			}

			// �ر��ļ���
			infile.close();
			//outfile.close();

			return;
		}

		void showData()
		{
			for (int i = 0; i < lines.size(); i++)
				cout << lines[i] << endl;
		}

		void writeData()//����д��
		{
			ofstream data("data", ios::out | ios::trunc | ios::binary);
			vector<File> FileArray;
			//��¼��Ϣ����
			data << iswriting << endl;
			data << Login.users.size() << endl;
			for (int i = 0; i < Login.users.size(); i++)
				data << Login.users[i].name << " " << Login.users[i].code << endl;
			//Ŀ¼����
			Dir* top = backToTop(root);
			top->toFile(data, FileArray);

			//�ļ�����
			//if (!FileArray.size()) cout << "���ļ�" << endl;
			//else cout << "д���ļ�" << FileArray.size() << "��" << endl;
			for (int i = 0 ; i < FileArray.size(); i++)
			{
				data << FileArray[i].name << " " << FileArray[i].data.size() << " " << FileArray[i].path << " " << FileArray[i].isLocked << " " << FileArray[i].lseek << endl;
				//cout << FileArray[i].path << endl;
				for (int o = 0; o < FileArray[i].data.size(); o++)
					data << FileArray[i].data[o] << endl;
			}

			//data << "�������޸�" << endl;
			data.close();
			//cout << "�����ѱ���" << endl;
			createBinary();
		}

} Data;
