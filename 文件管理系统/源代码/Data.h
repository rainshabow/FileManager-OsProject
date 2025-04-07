#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include "CMD.h"
using namespace std;

class Data//控制数据文件的读写
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
			// 读取文本文件
			ifstream infile("data");

			// 创建二进制文件
			ofstream outfile("data.bin", ios::binary | ios::out);

			// 逐行读取文本文件中的数据，并将每一行转换为二进制格式写入到二进制文件中
			string line;
			while (getline(infile, line)) {
				// 写入字符串长度
				int length = line.length();
				outfile.write(reinterpret_cast<const char*>(&length), sizeof(length));

				// 写入字符串内容
				outfile.write(line.c_str(), length);
			}

			// 关闭文件流
			//infile.close();
			outfile.close();

			return;
		}

		void readBinary(stringstream& outfile)
		{
			// 读取二进制文件
			ifstream infile("data.bin", ios::binary | ios::in);

			// 创建文本文件
			//ofstream outfile("data");

			// 逐条读取二进制文件中的数据，并将其转换为文本格式写入到文本文件中
			int length;
			while (infile.read(reinterpret_cast<char*>(&length), sizeof(length))) {
				// 分配内存来存储字符串内容
				char* buffer = new char[length + 1]; // +1 是为了添加字符串结束符
				infile.read(buffer, length);
				buffer[length] = '\0'; // 添加字符串结束符

				// 将字符串写入文本文件中
				outfile << buffer << endl;

				// 释放内存
				delete[] buffer;
			}

			// 关闭文件流
			infile.close();
			//outfile.close();

			return;
		}

		void showData()
		{
			for (int i = 0; i < lines.size(); i++)
				cout << lines[i] << endl;
		}

		void writeData()//数据写出
		{
			ofstream data("data", ios::out | ios::trunc | ios::binary);
			vector<File> FileArray;
			//登录信息部分
			data << iswriting << endl;
			data << Login.users.size() << endl;
			for (int i = 0; i < Login.users.size(); i++)
				data << Login.users[i].name << " " << Login.users[i].code << endl;
			//目录部分
			Dir* top = backToTop(root);
			top->toFile(data, FileArray);

			//文件部分
			//if (!FileArray.size()) cout << "无文件" << endl;
			//else cout << "写出文件" << FileArray.size() << "个" << endl;
			for (int i = 0 ; i < FileArray.size(); i++)
			{
				data << FileArray[i].name << " " << FileArray[i].data.size() << " " << FileArray[i].path << " " << FileArray[i].isLocked << " " << FileArray[i].lseek << endl;
				//cout << FileArray[i].path << endl;
				for (int o = 0; o < FileArray[i].data.size(); o++)
					data << FileArray[i].data[o] << endl;
			}

			//data << "数据已修改" << endl;
			data.close();
			//cout << "数据已保存" << endl;
			createBinary();
		}

} Data;
