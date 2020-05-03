/****************************************************************************
 *                                                                           *
 * APIbase.h -- Basic  API Definitions                                  *
 *                                                                           *
 * Copyright (c) 2000-2008,  All rights reserved.                            *
 * last modify sunny zhan 2008,6,7                                                                          *
 ****************************************************************************/
// ---------------------------------------------------------------------------

#ifndef APIbaseH
#define APIbaseH
#include "coredef.h"
#include "loginfo.h"
#include "CZDataSet.h"
#include "ClientBroker.h"
#include "Version.h"
enum DataMethod {dmRound, dmInteger, dmUpInt};
enum TValidType {vtMaster = 1, vtDetail = 2, vtMasterDetail = 3};
enum TValidAffect {vaCurRecNo = 1, vaAll = 2};
// ---------------------------------------------------------------------------
extern PACKAGE DWORD FST_ERROR_CODE;
extern PACKAGE String FST_ERROR_MSG;
extern PACKAGE TClientBroker* GClientBroker;
extern PACKAGE unsigned  ClientOwnerHandle;
extern PACKAGE TCZDataSet *USERLISTQUERY;
extern PACKAGE TClientBroker* GetClientComm();
extern PACKAGE TCZDataSet * GetUserListQuery();
extern PACKAGE BOOL ValidateVersion(ValidVerFlag flag);
extern PACKAGE DWORD GetRemoteVersion();
extern PACKAGE void SetErrorMessage(DWORD dwErrCode, String lpErrMsg);
extern PACKAGE DWORD GetErrorMessage(String &lpBuffer);

extern PACKAGE DWORD GetModuleList _DEPRECATED_ATTRIBUTE0 (String &szModuleList);

extern PACKAGE unsigned GetOwnerHandle _DEPRECATED_ATTRIBUTE0 ();
extern PACKAGE DWORD GetFormCode(DWORD dwModule);
extern PACKAGE DWORD GetClassCode(DWORD dwModule);

extern PACKAGE int GetModuleRight(DWORD dwModule, String &szRight);
extern PACKAGE int CheckModuleRight(DWORD dwModule, String szRightId);

extern PACKAGE int GetModuleDefRight(DWORD dwModule, String &szRight);
extern PACKAGE int CheckModuleDefRight(DWORD dwModule, String szRightId);

extern PACKAGE int GetModuleDefFunc(DWORD dwModule, String &szFunc);
extern PACKAGE int CheckModuleDefFunc(DWORD dwModule, String szFuncId);

extern PACKAGE int GetDataAccess(DWORD dwModule, String &szRight);
extern PACKAGE int CheckDataAccess(DWORD dwModule, String szUid,
	String szRightId);

extern PACKAGE DWORD GetProjectLevel();
extern PACKAGE void GetLogUserInfo(TLogInfo &Info);

/* ���������ӿ���ȡ������Ȩ��ʽ�Ѹı䣬��ǰ̨��Ҫ����
 int GetGroupData(String &szGroup);
 int GetUserData(String &szUser);
 */
// ��ȡϵͳ������Ʊ����ҵ����Ϳɲ��������ֶ�
//extern PACKAGE int GetMidClassList _DEPRECATED_ATTRIBUTE0 (String &szClassData);
//extern PACKAGE int GetMidClassUseCodeField _DEPRECATED_ATTRIBUTE0 (String &szClassUseCodeField);
extern PACKAGE void ShowClientForm( int ModuleCode, String Param);
//extern PACKAGE void ShowClientFormModal( int ModuleCode, String Param);
//extern PACKAGE void ShowFormModalByFormCode( int FormCode, String Param);
extern PACKAGE void CloseClientForm( int FormID);

#endif