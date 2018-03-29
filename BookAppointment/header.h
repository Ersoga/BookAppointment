
#include <stdio.h>      
#include <string.h>      
#include <windows.h>      
#include <sql.h>     
#include <sqlext.h>      
#include <sqltypes.h>      
#include <odbcss.h> 
#pragma once


SQLHENV henv = SQL_NULL_HENV;    //�������
SQLHDBC hdbc = SQL_NULL_HDBC;    //���Ӿ��
SQLHSTMT hstmt = SQL_NULL_HSTMT; //�����

RETCODE retcode;                    //������ؼ�
SQLCHAR szDSN[15] = "BookData";        //����Դ����  
SQLCHAR userID[6] = "sa";           //���ݿ��û�ID  
SQLCHAR passWORD[29] = "1443619775";//�û�����  


int Connect(SQLCHAR *szDSN, SQLCHAR *userID, SQLCHAR *passWORD)
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);//����ODBC����
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)) {
		//		MessageBoxA(hwnd, "���价�����ʧ��", "ʧ��", 8);
		return FALSE;
	}
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//���û�������     
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//�������Ӿ��
														  //retcode=SQLSetConnectAttrA(hdbc, SQL_TIMEDATE_ADD_INTERVALS, (SQLPOINTER)"����", 4);//������������
	retcode = SQLConnectA(hdbc, szDSN, SQL_NTS, userID, SQL_NTS, passWORD, SQL_NTS);//����
																					//�ж������Ƿ�ɹ�    
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
	//1. �Ͽ����ݿ�����
	//2.�ͷ����Ӿ��.
	//3.�ͷŻ������(���������Ҫ���������������������)
	SQLDisconnect(hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
}
void apply()//���������
{
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
}
void release()
{
	retcode = SQLCloseCursor(hstmt);
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);//�ͷ������
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
*ȥ���ַ�����β�� \x20 \r \n �ַ�
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
	//�����������ַ�����β�� ������ǰ
	--p;
	++start;
	if (*start == 0)
	{
		//�Ѿ����ַ�����ĩβ��
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

//ȥ����β�ո�