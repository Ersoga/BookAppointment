
#include <stdio.h>      
#include <string.h>      
#include <windows.h>      
#include <sql.h>     
#include <sqlext.h>      
#include <sqltypes.h>      
#include <odbcss.h> 
#pragma once


SQLHENV henv = SQL_NULL_HENV;    //环境句柄
SQLHDBC hdbc = SQL_NULL_HDBC;    //连接句柄
SQLHSTMT hstmt = SQL_NULL_HSTMT; //语句句柄

RETCODE retcode;                    //结果返回集
SQLCHAR szDSN[15] = "BookData";        //数据源名称  
SQLCHAR userID[6] = "sa";           //数据库用户ID  
SQLCHAR passWORD[29] = "1443619775";//用户密码  


int Connect(SQLCHAR *szDSN, SQLCHAR *userID, SQLCHAR *passWORD)
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);//分配ODBC环境
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)) {
		//		MessageBoxA(hwnd, "分配环境句柄失败", "失败", 8);
		return FALSE;
	}
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//设置环境属性     
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//分配连接句柄
														  //retcode=SQLSetConnectAttrA(hdbc, SQL_TIMEDATE_ADD_INTERVALS, (SQLPOINTER)"日期", 4);//设置连接属性
	retcode = SQLConnectA(hdbc, szDSN, SQL_NTS, userID, SQL_NTS, passWORD, SQL_NTS);//连接
																					//判断连接是否成功    
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
void Disconnect()
{
	//1. 断开数据库连接
	//2.释放连接句柄.
	//3.释放环境句柄(如果不再需要在这个环境中作更多连接)
	SQLDisconnect(hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
}
void apply()//分配语句句柄
{
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
}
void release()
{
	retcode = SQLCloseCursor(hstmt);
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);//释放语句句柄
}
//void trim(string &s)
//{
//
//	if (!s.empty())
//	{
//		s.erase(0, s.find_first_not_of(" "));
//		s.erase(s.find_last_not_of(" ") + 1);
//	}
//
//}
/*
*去掉字符串首尾的 \x20 \r \n 字符
*/
void TrimSpace(char* str)
{
	char *start = str - 1;
	char *end = str;
	char *p = str;
	while (*p)
	{
		switch (*p)
		{
		case ' ':
		case '\r':
		case '\n':
		{
			if (start + 1 == p)
				start = p;
		}
		break;
		default:
			break;
		}
		++p;
	}
	//现在来到了字符串的尾部 反向向前
	--p;
	++start;
	if (*start == 0)
	{
		//已经到字符串的末尾了
		*str = 0;
		return;
	}
	end = p + 1;
	while (p > start)
	{
		switch (*p)
		{
		case ' ':
		case '\r':
		case '\n':
		{
			if (end - 1 == p)
				end = p;
		}
		break;
		default:
			break;
		}
		--p;
	}
	memmove(str, start, end - start);
	*(str + (int)end - (int)start) = 0;
}

//去掉首尾空格