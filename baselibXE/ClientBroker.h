//---------------------------------------------------------------------------

#ifndef ClientBrokerH
#define ClientBrokerH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <IndyPeerImpl.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.DB.hpp>
#include "CZDataSet.h"
#include "MsgStream.h"
#include "loginfo.h"
#include "DataSnapClientDataSet.h"
#include "CallbackClient.h"
class PACKAGE TZClientDataSet;
class PACKAGE TLoginUserClient;
class PACKAGE TWorkFlowServerClient;
class PACKAGE THouseViewClient;
class TSendUserMessageClient;
// ---------------------------------------------------------------------------
class PACKAGE TClientBroker
{
private:
		String FDevCorp;
		String FSoftName;
		String FVersion;
		String FHomePage;
		String FEmail;
		String FAgentAddress;
		int FAgentPort;
		int FIsSystemer;
		bool FAppConnected;
		String FAccBookName;

		String FftpInteranetIP;
		String FftpInternetIP;
		String FftpUserName;
		String FftpPassword;
		int FftpPort;
		bool FftpNeedFTP;
		bool FftpPassive;
		String FUpdateURL;

		// mail
		String FMailServer;
		String FSendEMail;
		String FMailUserName;
		String FMailPassword;
		int FMailPort;


		TCZDataSet* FUserDataSet;
		bool FRemoter;
		int FSysDbType;
		int FAccDbType;


		TList* CDataSetList;
		TCZDataSet  *FClientLibs;  // 保存已启装载动态链接库
		TCZDataSet  *FClientForms; // 保存已启动窗体信息
		TCZDataSet  *FAccBooks;    // 保存当前系统可提供的账套信息
		TDataSnapClientDataSet *FModuleRight; // 保存当前用户的操作权限
		String FGlobeVarStr;


		String FServerID;     // 代理服务器ID
		String FLocalMachineName; //
		String FLocalIP; //
		String ClientPath; //
		//////////////////////////////////////////////////
		String FLogonCode; // 登录号
		String FUserCode; // 当前登录用户编码
		String FUserName; // 当前登录用户名
		String FUserEmpID;
		String FQQID; // QQID
		String FQQPassword; // QQ登陆口令
		String FPassword; // 当前登录用户密码
		String FAccBookID; // 账套ID
		//////////////////////////////////////////////////
		String FAppServerIP; // 应用服务器IP
		int FAppServerPort; // 应用服务器端口
		int FUserCount; // 在线用户数
		String LogStr;
		int FTimeOut;
		int FExecuteTime;
		bool FRecvAccBook;
		int FUpdateTimes;
		bool FIsTrial;
		String FModuleList;
		int FProjectLevel;
		String FCommunicationProtocol;

		int  FClientID;
		bool FInstanceOwner;
	    TEvent *FEvent;
		// ----------------------------------------------------------------
		int ClientBrokerStatus;
		String BrokerErrorMessage;

		// ----------------------------------------------------------------
		TSQLConnection *DSConnection;
		TLoginUserClient *LoginUserClient;
		TWorkFlowServerClient *WorkFlowServerClient;
		THouseViewClient *HouseViewClient;
		TDSClientCallbackChannelManager* LChannelManager;
		TCallbackClient * MsgCallBack;
		TSendUserMessageClient *FSendUserMessageClient;
		//	THookMsgCallback FHookCallBack;
		// ----------------------------------------------------------------
		void __fastcall GetAccInforJSON();
		void __fastcall GetAccInforJSONBack(TJSONObject *fdata); // 初始化账套数据
		// 确认应用服务器登录
		void __fastcall RefershUserCount(); // 刷新在线用户数
		void __fastcall RefreshGlobeVar();
		void __fastcall BuildGlobeVar(TDataSnapClientDataSet *DataSet);

		void __fastcall MessageCallBackHook(TJSONObject* Arg); // 接收消息
		// 发送系统到服务器消息 type:11-邮件，12-短消息，13-备忘录
		void __fastcall SendUserMessage(int type, String FID);
		int dwCurStatus;


		bool __fastcall GetLogInfo(TLogInfo *logInfo);
		void __fastcall GetAllModuleRight();
		void __fastcall GetCurUserInfo();

		String __fastcall get_DevCorp();
		String __fastcall get_SoftName();
		String __fastcall get_Version();
		String __fastcall get_HomePage();
		String __fastcall get_Email();
		int __fastcall get_UserCount();
		bool __fastcall get_Active();
		void __fastcall SetLogonCode(String Value);
		void __fastcall SetUserCode(String Value);

		bool __fastcall GetConnected();
		void __fastcall ReConnetToAgentAndApp();

		TDBXConnection* __fastcall GetDBXConnection();
		void __fastcall AppOnConnect(TObject * Sender);
		void __fastcall AppOnDisConnect(TObject * Sender);
		void __fastcall OnDBXConnErrorEvent(TDBXError* FDBXError);

protected:
		void __fastcall ClientCommTerminate(TObject *Sender);
		void __fastcall SetHookCallBack(THookMsgCallback Value);
		THookMsgCallback __fastcall GetHookCallBack();
public:
		__fastcall TClientBroker(TComponent* Owner);
		__fastcall virtual ~TClientBroker();
public:
		bool __fastcall InitClientComm(); // 初始化ClientComm
		DWORD __fastcall GetRemoteVersion();
		void __fastcall GetLogUserInfo(TLogInfo &Info);
		DWORD __fastcall GetModuleList(String &szModuleList);
		DWORD __fastcall GetFormCode(DWORD dwModule);
		DWORD __fastcall GetClassCode(DWORD dwModule);
		int __fastcall GetModuleRight(DWORD dwModule, String &szRight);
		int __fastcall GetModuleDefRight(DWORD dwModule, String &szRight);
		int __fastcall GetModuleDefFunc(DWORD dwModule, String &szFunc);
		int __fastcall GetDataAccess(DWORD dwModule, String &szRight);
		DWORD __fastcall GetProjectLevel();

		bool __fastcall RegMsgCallBack();          // 登录
		void __fastcall LogOut();         // 注销
		void __fastcall GetModuleData(TDataSnapClientDataSet *DataSet);
		TStream* __fastcall GetClassList();      //直接返回数据集
		TStream* __fastcall GetAutoCodeFields(); //直接返回数据集
		TStream* __fastcall ListOfLoginUser();
		TJSONObject* __fastcall GetClassListJO();
		TJSONObject* __fastcall GetAutoCodeFieldsJO();
		TJSONArray* __fastcall GetUserList();
		TJSONArray* __fastcall GetDepartmentAndUsersList();
		bool __fastcall ChangePwd(String szNewPwd);

		void __fastcall CloseAllForms();
		void __fastcall ShowForm(int modulecode, String param, bool bShow = true);
		void __fastcall CloseForm(int formid);
		void __fastcall InitUserDataSet(TDataSnapClientDataSet* value);

		void __fastcall AddClientDataSet(TZClientDataSet *cds);
		void __fastcall DeleteClientDataSet(TZClientDataSet *cds);
		//返回当前工作流ID
		String __fastcall ServerWorkFlowStart(String FlowDefID, String Subject, String Content, String BusWindow, String BusCode, int Rank, String PrjID, String Report);
		//返回是否调用成功
		bool __fastcall ServerWorkFlowExec(String FlowDefID, String WorkInsID, String TaskInsID, String TskStatus, String TskComments, TJSONArray* varJsonArray);
		TJSONObject* GetTaskdefList(String TaskInsID);
		TJSONObject* GetVariableList(String TaskInsID);
		TStream* GetTaskdefListDS(String TaskInsID);
		TStream* GetVariableListDS(String TaskInsID);
		TStream* GetWorkFlowChart(String FlowID,bool isDef);
		TStream* GetTaskListDS(String AUserID, int ACompletedState, String AOtherCondition);
		bool TaskCanUpdate(String TaskInsID);
		//户型图文件处理
		TStream* __fastcall GetHouseViewStream(String AKeyID);
		bool __fastcall UpdateHouseViewFile(String AKeyID, String AFileName, TStream* AStream);

public:
		__property TDBXConnection* DBXConnection = {read=GetDBXConnection};
		__property String GlobeVarStr = {read = FGlobeVarStr};
		__property int TimeOut = {read = FTimeOut, write = FTimeOut};
		__property int SysDbType = {read = FSysDbType, write = FSysDbType};
		__property int AccDbType = {read = FAccDbType, write = FAccDbType};
		__property TCZDataSet *ClientForms = {read = FClientForms};
		__property TCZDataSet *ClientLibs = {read = FClientLibs};
		__property bool Active = {read = get_Active};
		__property String UserCode = {read = FUserCode};
		__property String UserEmpID = {read = FUserEmpID};
		__property String Password = {read = FPassword, write = FPassword};
		__property String AccBookID = {read = FAccBookID, write = FAccBookID};
		__property int UserCount = {read = get_UserCount};
		__property String DevCorp = {read = get_DevCorp};
		__property String SoftName = {read = get_SoftName};
		__property String Version = {read = get_Version};
		__property String HomePage = {read = get_HomePage};
		__property String Email = {read = get_Email};
		__property String AgentAddress = {read = FAgentAddress, write = FAgentAddress};
		__property int AgentPort = {read = FAgentPort, write = FAgentPort};
		__property TCZDataSet *AccBooks = {read = FAccBooks};
		__property bool Connected = {read = GetConnected};
		__property bool AppConnected = {read = FAppConnected};
		__property int IsSystemer = {read = FIsSystemer, write = FIsSystemer};
		__property String UserName = {read = FUserName};
		__property String AccBookName = {read = FAccBookName, write = FAccBookName};
		__property String CommunicationProtocol ={read = FCommunicationProtocol, write = FCommunicationProtocol};

		// ftp
		__property String ftpInteranetIP = {read = FftpInteranetIP, write = FftpInteranetIP};
		__property String ftpInternetIP = {read = FftpInternetIP, write = FftpInternetIP};
		__property String ftpUserName = {read = FftpUserName, write = FftpUserName};
		__property String ftpPassword = {read = FftpPassword, write = FftpPassword};
		__property int ftpPort = {read = FftpPort, write = FftpPort};
		__property bool ftpNeedFTP = {read = FftpNeedFTP, write = FftpNeedFTP};
		__property bool ftpPassive = {read = FftpPassive, write = FftpPassive};
		__property TCZDataSet* UserDataSet = {read = FUserDataSet};
		__property String LogonCode = {read = FLogonCode, write = SetLogonCode};

		//UpdateURL
		__property String UpdateURL = {read = FUpdateURL, write = FUpdateURL};

		// QQ
		__property String QQID = {read = FQQID};
		__property String QQPassword = {read = FQQPassword};

		// 是否是远程连接
		__property bool Remoter = {read = FRemoter, write = FRemoter};

		// 邮件发送服务
		__property String MailServer = {read = FMailServer, write = FMailServer};
		__property String ESendMail = {read = FSendEMail, write = FSendEMail};
		__property String MailUserName = {read = FMailUserName, write = FMailUserName};
		__property String MailPassword = {read = FMailPassword, write = FMailPassword};
		__property int MailPort = {read = FMailPort, write = FMailPort};
		// 工作流引擎
		//消息处理钩子
		__property THookMsgCallback HookCallBack = {read = GetHookCallBack,write = SetHookCallBack};
};
// ---------------------------------------------------------------------------
#endif
