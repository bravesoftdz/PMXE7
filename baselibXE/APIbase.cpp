// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "APIbase.h"
/****************************************************************************
 prj standard edition release :101 trial:111  ��Ŀ������׼��
 prj profession edition release:102 trial:112 ��Ŀ����רҵ��
 prj enterprise edition release:103 trial:113 ��Ŀ������ҵ��
 est standard edition release:201 trial:211    ���ز���׼��
 est profession edition release: 202 trial:212 ���ز�רҵ��
 sale edition release: 203 trial:213           ��¥ϵͳ
 gl standard edition release:301 trial:311     ��·��Ŀ������׼��
 gl profession edition release 302 trial:312   ��·��Ŀ����רҵ��
 fsp standard edition release:401 trial:412    Ͷ����Ŀ������׼��
 fsp profession edition release 402 trial:412  Ͷ����Ŀ����רҵ��
 vip edition edition release 501 trial:511     ����ϵͳ
 ****************************************************************************/
const int MAX_BUFFER_LEN = 255;
const DWORD LOCAL_VERSION = 111;
const char LOCAL_VERSION_STRING[] = "@#ZWSVERSION$%";
// ---------------------------------------------------------------------------

#pragma package(smart_init)
TClientBroker* GClientBroker;
TCZDataSet *USERLISTQUERY;
unsigned  ClientOwnerHandle;
DWORD FST_ERROR_CODE;
String FST_ERROR_MSG;
// ---------------------------------------------------------------------------

TClientBroker* GetClientComm() {

   return  GClientBroker;
}

// ---------------------------------------------------------------------------
TCZDataSet * GetUserListQuery() {

   return  USERLISTQUERY;
}

// ---------------------------------------------------------------------------
DWORD GetRemoteVersion() {

   return GClientBroker->GetRemoteVersion();
}

// ---------------------------------------------------------------------------
void GetLogUserInfo(TLogInfo &Info) {

	GClientBroker->GetLogUserInfo(Info);
}

BOOL ValidateVersion(ValidVerFlag flag) {
	if (GetRemoteVersion() == GetLocalVersion()) {
		return true;
	}
	else {
		if (flag == vfExitNoHint) {
			exit(0);
		}
		else if (flag == vfExitAndHint) {
			ShowMessage(L"�汾�Ų�ƥ��,ϵͳ���Զ��˳�.");
			exit(0);
		}
		return false;
	}
}

// ---------------------------------------------------------------------------
void SetErrorMessage(DWORD dwErrCode, String lpErrMsg) {
 FST_ERROR_CODE=dwErrCode;
 FST_ERROR_MSG=lpErrMsg;
}

// ---------------------------------------------------------------------------
DWORD GetErrorMessage(String &lpBuffer) {

   lpBuffer=FST_ERROR_MSG;
   return FST_ERROR_CODE;
}

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
DWORD GetModuleList(String &szModuleList) {

  return GClientBroker->GetModuleList(szModuleList);
}

// ---------------------------------------------------------------------------
unsigned int GetOwnerHandle() {

	return ClientOwnerHandle;
}

// ---------------------------------------------------------------------------
DWORD GetFormCode(DWORD dwModule) {

	return GClientBroker->GetFormCode(dwModule);
}

// ---------------------------------------------------------------------------
DWORD GetClassCode(DWORD dwModule) {

	return GClientBroker->GetClassCode(dwModule);
}

// ---------------------------------------------------------------------------
int GetModuleRight(DWORD dwModule, String &szRight) {

   return GClientBroker->GetModuleRight(dwModule,szRight);
}

// ---------------------------------------------------------------------------
int CheckModuleRight(DWORD dwModule, String szRightId) {

	String szRight;
	int retPos=-1;
	if(GetModuleRight(dwModule,szRight))
	{
	 retPos=szRight.Pos(szRightId);
	}
	return retPos;
}

// ---------------------------------------------------------------------------
int GetModuleDefRight(DWORD dwModule, String &szRight) {

	return GClientBroker->GetModuleDefRight(dwModule,szRight);
}

// ---------------------------------------------------------------------------
int CheckModuleDefRight(DWORD dwModule, String szRightId) {

	String szRight;
	int retPos=-1;
	if(GetModuleDefRight(dwModule,szRight))
	{
	 retPos=szRight.Pos(szRightId);
	}
	return retPos;
}

// ---------------------------------------------------------------------------
int GetModuleDefFunc(DWORD dwModule, String &szFunc) {

	return GClientBroker->GetModuleDefFunc(dwModule,szFunc);
}

// ---------------------------------------------------------------------------
int CheckModuleDefFunc(DWORD dwModule, String szFuncId) {

	String szFunc;
	int retPos=-1;
	if(GetModuleDefFunc(dwModule, szFunc))
	  retPos=szFunc.Pos(szFuncId);
	return retPos;
}

// ---------------------------------------------------------------------------
int GetDataAccess(DWORD dwModule, String &szRight) {

  return GClientBroker->GetDataAccess(dwModule,szRight);
}

// ---------------------------------------------------------------------------
int CheckDataAccess(DWORD dwModule, String szUid, String szRightId) {

	String szRight, szCmpStr;
	int retPos=-1;
	if(GetDataAccess(dwModule, szRight))
	{
	   szCmpStr = szUid + ":" + szRightId;
	   retPos= szRight.Pos(szCmpStr);
	}
	return retPos;
}

// ---------------------------------------------------------------------------
DWORD GetProjectLevel() {

  return GClientBroker->GetProjectLevel();
}

// ---------------------------------------------------------------------------
void ShowClientForm(int ModuleCode, String Param)
{
	GClientBroker->ShowForm(ModuleCode,Param);
}

// ---------------------------------------------------------------------------
//void ShowClientFormModal(int ModuleCode, String Param)
//{
//   GClientBroker->ShowFormModal(ModuleCode,Param);
//}
//// ---------------------------------------------------------------------------
//void ShowFormModalByFormCode(int FormCode, String Param)
//{
//	GClientBroker->ShowFormModalByFormCode(FormCode,Param);
//}
// ---------------------------------------------------------------------------
void CloseClientForm( int FormID)
{
	GClientBroker->CloseForm(FormID);
}
// ---------------------------------------------------------------------------