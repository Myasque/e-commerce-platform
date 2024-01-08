#pragma once
#define BUYER 0
#define SELLER 1
#define ACCOUT_LEN 10
#define PASSWORD_LEN 10

#include<cstdio>
#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include"file.h"

using namespace std;

class user 
{
	int type=0;//0是消费者，1是商家
	string accout;
	string password;
public:
	virtual int get_user_type()=0;
	void enroll();// 注册
	string login() const; // 登录
	void change_password();// 修改密码
	
};


class buyer : public user//继承类：消费者
{    
	unsigned int remain=0;
public:
	int get_user_type() { return BUYER; };
	unsigned int ask_money(string accout)const;// 账号中余额的查询
	void recharge(int money,string accout);// 充值
	void consume(int money, string accout);// 消费
};


class  seller : public user {   //继承类：卖家
public:
	int get_user_type() { return SELLER; };
};


 void user:: enroll()//注册
{
	 file f;
	 string temp;
	 fstream file("user.txt", ios::app);
	 if (!file)
	 {
		 cout << "文件打开失败！" << endl;
		 return;
	 }

	 cout << "请输入要注册的账户名：（" <<ACCOUT_LEN<<"个字符以内)"<< endl;
	 cin >> temp;	
	 while (temp.size() >= ACCOUT_LEN)//判断长度
	 {
		 cout << "您输入的账户名过长，请重新输入：" << endl;
		 cin >> temp;
	 }
	 while (f.find_in_file("user.txt",temp))//判断是否重复
	 {
		 cout << "该用户名已被注册，请重新输入：" << endl;
		 cin >> temp;
	 }
	 file << temp << endl;//每行存一个账户
	 
	 cout << "请输入您的密码：" << endl;
	 cin >> temp;
	 file << temp << endl;//账户的下一行存密码

	 file << "0" << endl;//初始余额默认为0

	 cout << "注册成功！" << endl;
	 file.close();
}






 string user::login() const
 {
	 string accout_in;
	 string password_in,password_file;
	 int n_line;
	 file f;
	 char data[10] = {0};
	 cout << "请输入您的用户名：";
	 cin >> accout_in;
	 n_line = f.find_in_file("user.txt",accout_in);//得到了账户所在的行数
	 while (n_line==0)
	 {
		 cout << "您输入的用户名未注册，请重新输入：" << endl;
		 cin >> accout_in;
		 n_line = f.find_in_file("user.txt",accout_in);
	 }
	 n_line++;//密码所在行数
	 cout << "请输入您的密码：" << endl;
	 cin >> password_in;
	 strcpy_s(data,f.read_line_data("user.txt", n_line));
	 password_file = f.char_to_str(data);
	 while (password_in!=password_file)
	 {
		 cout << "密码错误！请重新输入：" << endl;
		 cin >> password_in;
	 }
	 cout << "登录成功！" << endl;
	 return accout_in;
 }


 void user::change_password()
 {
	 string accout_in;
	 char password_new[10];
	 int n_line=0;
	 file f;
	 cout << "请输入账户名：" << endl;
	 cin >> accout_in;
	 cout << "请输入新的密码：" << endl;
	 cin >> password_new;
	 n_line = f.find_in_file("user.txt", accout_in);
	 n_line++;//指向密码行
	 f.modify_line_data("user.txt", n_line, password_new);
 }
 
 unsigned int buyer::ask_money(string accout) const// 账号中余额的查询
 {
	 file f;
	 string temp;
	 int n_remain;
	 int n_line = 0;
	 char remain[10] = { 0 };
	
	 n_line = f.find_in_file("user.txt", accout);
	 n_line+=2;//指向余额行
	 strcpy_s(remain, f.read_line_data("user.txt", n_line));
	 temp = remain;//为了转换为int而先转换为string
	 n_remain = stoi(temp);
	 return n_remain;
 }

 void buyer:: recharge(int money,string accout) 
 {
	 string accout_in;
	 string temp;
	 file f;
	 int n_line = 0;
	 int remain = 0;
	 
	 char remain_new[10] = { 0 };
	

	 n_line = f.find_in_file("user.txt", accout);
	 n_line += 2;//指向余额行；
	 remain = ask_money(accout);
	 remain += money;
	 temp = to_string(remain);
	 strcpy_s(remain_new,temp.data());
	 f.modify_line_data("user.txt", n_line, remain_new);
	 cout << "充值成功！" << endl;
 }

 void buyer::consume(int money, string accout)
 {
	 string accout_in;
	 string temp;
	 file f;
	 int n_line = 0;
	 int remain = 0;
	 char remain_new[10] = { 0 };
	
	 n_line = f.find_in_file("user.txt", accout);
	 n_line += 2;//指向余额行；
	 remain = ask_money(accout);
	 remain -= money;
	 temp = to_string(remain);
	 strcpy_s(remain_new, temp.data());
	 f.modify_line_data("user.txt", n_line, remain_new);
	 cout << "消费成功。" << endl;

 }