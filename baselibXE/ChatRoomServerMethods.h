//---------------------------------------------------------------------------

#ifndef ChatRoomServerMethodsH
#define ChatRoomServerMethodsH
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "DSClientProxy.h"
//---------------------------------------------------------------------------
class PACKAGE TChatRoomServerMethods
{
private:
	TMessageManageClient* FMessageManageClient;
public:
	__fastcall TChatRoomServerMethods(TDBXConnection *ADBXConnection);
	__fastcall TChatRoomServerMethods(TDBXConnection *ADBXConnection, bool AInstanceOwner);
	__fastcall ~TChatRoomServerMethods();
	TJSONArray* __fastcall GetUserList();
	System::UnicodeString __fastcall GetHTMLEscapedString(System::UnicodeString Value);
	bool __fastcall UpdateCurUserCallbackClientID(System::UnicodeString Value);
	bool __fastcall SendMessageToAll(System::UnicodeString Msg);
	bool __fastcall SendMessageToUser(System::UnicodeString Msg, System::UnicodeString UserID);
	bool __fastcall SendMessageToDepartment(System::UnicodeString Msg, System::UnicodeString DepartmentID);
	bool __fastcall SendMessageToGroup(System::UnicodeString Msg, System::UnicodeString GroupID);
	bool __fastcall SendMessageToFollow(System::UnicodeString Msg);
	bool __fastcall SendMessageToJob(String const Msg, String const JobID);
	bool __fastcall SendMessageToRole(String const Msg, String const RoleID);
	bool __fastcall SendCMDToFollow(System::UnicodeString cmdStr);
	bool __fastcall SendCMDToAll(System::UnicodeString cmdStr);
	bool __fastcall SendCMDToUser(System::UnicodeString cmdStr, System::UnicodeString UserID);
	bool __fastcall SendCMDToDepartment(System::UnicodeString cmdStr, System::UnicodeString DepartmentID);
	bool __fastcall SendCMDToGroup(System::UnicodeString cmdStr, System::UnicodeString GroupID);
	bool __fastcall SendCMDToJob(String const cmdStr, String const JobID);
	bool __fastcall SendCMDToRole(String const cmdStr, String const RoleID);
	bool __fastcall SendMgrMessage(int itype, System::UnicodeString Msg);
};
#endif
