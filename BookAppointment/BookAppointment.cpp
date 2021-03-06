// BookAppointment.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "header.h"
#include <graphics.h>
#include "string"
#include<conio.h>
#include<iostream>
#include<mmstream.h>
#include<corecrt_memcpy_s.h>
#pragma comment (lib,"winmm.lib")
#define MAXBUFLEN 255  
using namespace std;
//using system.Data.Sqlclient;

class User
{
	char UserID[6];
	char Password[20];
public:
	void search()
	{
		int  i = 0, a = 0;;
		char L1[20], L2[20], L3[20], L4[20], L5[20],L6[20];
		long lenOut1, lenOut2, lenOut3, lenOut4, lenOut5,lenOut6;
		char sql[100];
		int search;
		cout << "请选择查询方式：\n\t1、书名\n\t2、出版年份\n\t3、出版社\n\t4、退出";
		cin>>search;
		switch (search)
		{
		case 1:
			cout << "请输入书名：\n";
			char Name[20];
			cin >> Name;
			apply();
			sprintf_s(sql, "select * from BookData where Name='%s';", Name);
			retcode = SQLExecDirectA(hstmt, (SQLCHAR*)sql, SQL_NTS); //SQL_NTS表示字符串以NULL字符结尾
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLBindCol(hstmt, 6, SQL_C_CHAR, L6, sizeof(L6), &lenOut6);
			while (SQL_NO_DATA != SQLFetch(hstmt))
			{
				i++;
				printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5, L6);
			}
			cout << "\n\n\n***************************   共检索到" << i << "条数据   *****************************************" << endl;
			break;
		case 2:
			cout << "请输入出版年份：（yyyy-mm-dd）\n";
			char Date[20];
			cin >> Date;
			apply();
			sprintf_s(sql, "select * from BookData where Date='%s';", Date);
			retcode = SQLExecDirectA(hstmt, (SQLCHAR*)sql, SQL_NTS); //SQL_NTS表示字符串以NULL字符结尾
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLBindCol(hstmt, 6, SQL_C_CHAR, L6, sizeof(L6), &lenOut6);
			if (retcode == SQL_ERROR)
			{
				printf("输入错误");
				break;
			}
			while (SQL_NO_DATA != SQLFetch(hstmt))
			{
				i++;
				printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5, L6);
			}
			cout << "\n\n\n***************************   共检索到" << i << "条数据   *****************************************" << endl;
			release();
			break;
		case 3:
			cout << "请输入出版社名：\n";
			char Publisher[20];
			cin >> Publisher;
			apply();
			sprintf_s(sql, "select * from BookData where Publisher='%s';", Publisher);
			retcode = SQLExecDirectA(hstmt, (SQLCHAR*)sql, SQL_NTS); //SQL_NTS表示字符串以NULL字符结尾
			retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, L1, sizeof(L1), &lenOut1);
			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, L2, sizeof(L2), &lenOut2);
			retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, L3, sizeof(L3), &lenOut3);
			retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, L4, sizeof(L4), &lenOut4);
			retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, L5, sizeof(L5), &lenOut5);
			retcode = SQLBindCol(hstmt, 6, SQL_C_CHAR, L6, sizeof(L6), &lenOut6);
			while (SQL_NO_DATA != SQLFetch(hstmt))
			{
				i++;
				printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n", i, L1, L2, L3, L4, L5, L6);
			}
			cout << "\n\n\n***************************   共检索到" << i << "条数据   *****************************************" << endl;
			release();
			break;
		case 4 :
			break;
		}
	}
	void order()
	{

	}

};
class admin :public User
{
public:
	char AdminUserID[6];
	char AdminPassword[20];
	bool Login(char *AdminUserID, char *AdminPassword)
	{
		apply();
		char sql[100];
		char pass[20];//存放该用户数据库获取的密码
		long lenOut;
		//cin >> AdminUserID>>AdminPassword;
		sprintf_s(sql, "select Password from Users where UserID='%s';", AdminUserID);
		retcode = SQLExecDirectA(hstmt, (SQLCHAR*)sql, SQL_NTS);
		retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, pass, sizeof(pass), &lenOut);
		while (SQL_NO_DATA != SQLFetch(hstmt))
		{
			TrimSpace(pass);
			if (strcmp(pass, AdminPassword) == 0)
			{
				printf("登陆成功\n");
				return TRUE;
			}
			else
			{
				printf("密码错误\n");
				return FALSE;
			}
		}
//		if (retcode == SQL_SUCCESS)
//		{
//			printf("用户名验证成功\n");
//			char pass[20];//存放该用户数据库获取的密码
////			char L1[20];
//			long lenOut;
//			retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, pass, sizeof(pass), &lenOut);
//			retcode = SQLFetch(hstmt);
//			//printf("%s\n", L1);
//			TrimSpace(pass);
//			if (strcmp(pass,AdminPassword)==0)
//			{
//				printf("登陆成功\n");
//				return TRUE;
//			}
//			else
//			{
//				printf("密码错误\n");
//				return FALSE;
//			}
//		}
//		else
//		{
//			printf("用户名验证失败\n");
//			return FALSE;
//		}
		release();
	}
	void insert(char *a, char*b, char*c)
	{
		char sql[100];
		//sprintf(sql, "insert into UserTable values(%s,%s,%s);",a,b,c);
		if (retcode == SQL_SUCCESS)
		{
			retcode = SQLExecDirectA(hstmt, (SQLCHAR*)sql, SQL_NTS);
		}
		if ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO))
		{
			printf("执行成功");
		}
	}
	void deleteData()
	{

	}
};

int main()
{
	printf("欢迎来到图书管理系统！\n");
	Sleep(1000);
	system("cls");

	if (Connect(szDSN, userID, passWORD) == 1)
		printf("数据库连接成功\n");

	int action;
	while (1)
	{
		cout << "请选择功能：\n\t1、图书查询\n\t2、管理员登陆\n\t3、用户注册\n";
		cin >> action;
		switch (action)
		{
		case 1:
			User Casualuser;
			Start:
			Casualuser.search();
			cout << "继续查询吗？Y/N" << endl;
			action = _getch();
			if (action == 'Y' || action=='y') 
			{
				goto
					Start;
			}
			break;
		case 2:
			admin admin;
			//admin.Login()
			cout << "请输入用户ID" << endl;
			cin >> admin.AdminUserID;
			cout << "请输入用户密码" << endl;
			cin >> admin.AdminPassword;
			admin.Login((char*)admin.AdminUserID, (char*)admin.AdminPassword);
			break;
		case 3:
			break;
		}
	}
	system("pause");
	return(0);
}

