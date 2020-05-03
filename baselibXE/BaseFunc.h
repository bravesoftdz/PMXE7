// ---------------------------------------------------------------------------

#ifndef BaseFuncH
#define BaseFuncH
#include <stdio.h>
//#include "APIbase.h"
#include "Version.h"
// ---------------------------------------------------------------------------
extern PACKAGE void ClearTempFile(String FileName);
extern PACKAGE String GetSpecStr(String srcstr, String begstr, String endstr, int &endpos);
extern PACKAGE String OpenTempFile(String PrefixString);
extern PACKAGE void DeleteTempFile(String FileName);
extern PACKAGE FILE* OpenLogFile(String PrefixString);
extern PACKAGE void WriteLogFile(FILE* FileHandle, String msg);

// ***************************************************************************
extern PACKAGE double DataCarry(double data, int scale, int method);
extern PACKAGE double Mod(double x, double y);
extern PACKAGE String EncAndDec(String Password, bool Encrypt = true, int Factor = 1);
extern PACKAGE String GetInifileValue(String lpSection, String lpKey, String lpFilename);
extern PACKAGE bool SetInifileValue(String lpSection, String lpKey, String lpValue, String lpFilename);
extern PACKAGE String GetComputerIP(String ComputerName);
extern PACKAGE String GetMachineName();
extern PACKAGE String GetRemoteName(String szAddr);
extern PACKAGE int ScanPort(char *szServer, int &lDefPort, int lCount);
// ɨ��ָ���������Ķ˿�,�ҵ�δʹ�ö˿�,�򷵻ص�һ�����򷵻�0(lDefPort)
// ����ֵ
// 0-�ɹ�,��������ʧ��1-
extern PACKAGE String GetGUIDString(void);
extern PACKAGE String GetShortGuid();
extern PACKAGE String GetMacAddr(String ip);
// �ɹ�����GUIDֵ,ʧ�ܷ��ؿ�ֵ

extern PACKAGE String RebuildSQLStatement(String sqlstr);

extern PACKAGE int MakePrimalKey(const char *szPwd);
extern PACKAGE bool DynamicEncrypt(const void *source, void *dest, int len, int key);
extern PACKAGE bool DynamicDecrypt(const void *source, void *dest, int len, int key);

#define CREATION_FILE_TIME   0
#define LASTACCESS_FILE_TIME 1
#define LASTWRITE_FILE_TIME  2

extern PACKAGE int GetFileDateTime(String lpFileName, LPSYSTEMTIME lpFileTime, DWORD dwFileTimeType);
extern PACKAGE int SetFileDateTime(String lpFileName, LPSYSTEMTIME lpFileTime, DWORD dwFileTimeType);

extern PACKAGE BOOL SetShareVariable(String szVarName, String szValue);
extern PACKAGE DWORD GetShareVariable(String szVarName, String &szValue);

extern PACKAGE void OpenFileNormal(const Char *szFileName);
extern PACKAGE void OpenFileModal(const Char *szFileName);
// ���������ַ���
extern PACKAGE String __fastcall BuildConnStr(int dbtype, String dbserver, String dbname, String dbuid, String dbpwd);
#endif