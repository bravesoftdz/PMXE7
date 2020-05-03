//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Info.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include "ModeInter.hpp"
#include "DecEnc.h"
#include "sms.h"
#define Address "www.mobset.com"
_di_smsPortType SendSevice;
//--------------------------------------------------------------------------------
#pragma package(smart_init)
TRecvThread *RecvThread;
TSendThread *SendThread;
TEndTimeThread *EndTimeThread;
int PWaitLong;
__fastcall TShortInfo::TShortInfo(int Flag)
{
	 FFlag = Flag;
     DllHandle = NULL;
     SendList = NULL;
	 IndexList = NULL;
     RecvThread = NULL;
     SendThread = NULL;
	 OnWriteErrorLog = NULL;
	 LoadDllFunc();
     FWaitLong = 1000;
     FRepeatCount = 3;//Ĭ��Ϊ����
	 FComPort=0; //Ĭ��com1
	 FModeType=0;//Ĭ��һ��
	 AccConn=new TADOConnection(NULL);
	 AccConn->LoginPrompt=false;
	 MainTimer = new TTimer(NULL);
}
//---------------------------------------------------------------------------
bool __fastcall TShortInfo::GetDllHandle()
{
/*
   if (DllHandle != NULL) return true;
   String dllfilename=ExtractFilePath(Forms::Application->ExeName)+"SmsSdk.dll";
   DllHandle = LoadLibrary(dllfilename.c_str());
   if(DllHandle)
   {
		(FARPROC&) Sms_Proxy = GetProcAddress(DllHandle,"Sms_Proxy");
		(FARPROC&) Sms_Connect= GetProcAddress(DllHandle,"Sms_Connect");
		(FARPROC&) Sms_DisConnect= GetProcAddress(DllHandle,"Sms_DisConnect");
		(FARPROC&) Sms_Send2 = GetProcAddress(DllHandle,"Sms_Send2");
		(FARPROC&) Sms_Get2 = GetProcAddress(DllHandle,"Sms_Get2");
   }
	else
   {
		FErrorStr = "SmsSdk.dll��̬�����ʧ��!" ;
		WriteErrorLog();
   }
   return DllHandle!=NULL;
*/
}

//---------------------------------------------------------------------------
String __fastcall TShortInfo::ErorType(int Flag)
{
   String ResultStr;
   switch( Flag)
   {
        case 100: ResultStr = "��Ȩ����(���������)";
               break;
        case 101: ResultStr = "��Ȩ���ʹ���(�������������)";
               break;
        case 102: ResultStr = "δ��ʼ�������ȳ�ʼ��";
               break;
        case 103: ResultStr = "DLL�ļ�����";
               break;
        case 200: ResultStr = "�˿ں����";
               break;
        case 201: ResultStr = "��֧�ֵĶ˿�";
               break;
        case 202: ResultStr = "��Ϣ����";
               break;
        case 203: ResultStr = "���ܷ��Ϳ���Ϣ";
               break;
        case 204: ResultStr = "�ֻ������";
               break;
        case 205: ResultStr = "�豸��";
               break;
        case 206: ResultStr = "������Ĵ�";
               break;
        case 207: ResultStr = "�����¼��";
               break;
        case 208: ResultStr = "���ø�ʽ��";
               break;
        case 209: ResultStr = "ϵͳæ";
               break;
		case 210: ResultStr = "���ͳ�ʱ";
               break;
		default : if(Flag >=500)
				  {
					int port = Flag - 499;
					ResultStr = IntToStr(port)+"�Ŷ˿ڲ����ڻ���������ռ��" ;
				  }
				  else
					ResultStr = "δ֪����";
   }
   return ResultStr;
}
//---------------------------------------------------------------------------
bool __fastcall  TShortInfo::LoadDllFunc()
{
	if (FFlag == 0)   //����è
	{
	  return LoadModeDll();
	}
    else     //��������
    {
	  return GetDllHandle();
	}
}
//---------------------------------------------------------------------------
__fastcall TShortInfo::~TShortInfo()
{
   int i;
   MainTimer->Enabled =false;
   delete AccConn;
   if (DllHandle != NULL)
       FreeLibrary(DllHandle);
   if (SendList != NULL)
       delete SendList;
   if (IndexList != NULL)
       delete IndexList;
   if (SendThread != NULL)
   {
       SendThread->Terminate();
   }
   if (RecvThread != NULL)
   {
       RecvThread->Terminate();
   }
   if (EndTimeThread != NULL)
   {
       EndTimeThread->Suspend();
       EndTimeThread->Terminate();
   }
   if (FFlag == 0)
	   fnCloseModem(FComPort);
   else
	   if(SendSevice)
         SendSevice->Release();
   delete MainTimer;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TShortInfo::Initializtion()
{
	int index,LResult,i=0;
	String Result;
	if (FFlag==0)
    {
		//fnCloseModem(-1);
		fnSetThreadMode(-1);
		for(int i=0;i<10;i++)
		  fnSetModemType(i,0);
		fnGetModemType(FComPort);
		fnInitModem(FComPort);
	}
    else
    {
	  try
	  {
		 SendSevice = GetsmsPortType(true);
		 StockDetails *SeviceDetail = SendSevice->directGetStockDetails(FCordId,FUserName,FPassword);
		 if(SeviceDetail->retCode == "Faild")
		 {
			 FErrorStr = "��������ʧ�ܣ�"+SeviceDetail->message;
			 WriteErrorLog();
			 return;
		 }
		 else
		 {
			 FErrorStr = "�������ӳɹ���\n���������:"+IntToStr(SeviceDetail->stockRemain)+"\n�����ܷ�����:"+IntToStr(SeviceDetail->sendTotal);
			 WriteErrorLog();
         }
	  }
      __finally
      {

      }
    }
	AccConn->ConnectionString=FAccConnectString;
	//��ʼ����������
	SendList = new TStringList();
	IndexList = new TStringList();
	//����ʹ�õ��߳�
	SendThread = new TSendThread(true);
	SendThread->SendFun = SendShortMessage;
    if (FFlag == 0)
    {
	   RecvThread = new TRecvThread(true);
       RecvThread->Recvfun = ReadShortMessage;
    }
    else
	   RecvThread = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TShortInfo::SendShortMessage()
{
	 int index = 0,result;
     String * PNo;
     String Str;
     String szHeader;
	 TADOQuery* Query = new TADOQuery(NULL);
	 TADOQuery* QueryTemp = new TADOQuery(NULL);
	 try{
		  Query->Close();
		  Query->Connection = AccConn;
		  QueryTemp->Connection = AccConn;
		  Query->SQL->Text = "Exec sd_OperMessage";//�ʼ�תΪ����Ϣ
		  Query->ExecSQL();

		  Query->Close();
		  Query->SQL->Text = "select  * from vi_SendCache";
		  Query->Open();
		  Query->First();
		  while (!Query->Eof)
		  {
			 if(FFlag == 0)
             {
                PNo = new String (IntToStr(index));
				SendList->AddObject(Query->FieldByName("SCTPKID")->AsString,(TObject *)PNo);
                IndexList->Add(IntToStr(SendList->Count));
				szHeader = Query->FieldByName("SCTRecvPsPhone")->AsString+","+
                           IntToStr(SendList->Count)+",0,"+
						   Query->FieldByName("SCTSendPsPhone")->AsString+",0,1";
				try
				{
					result=SendData(szHeader,Query->FieldByName("SCTConet")->AsString);
					if(result == -2)
					{
					  FErrorStr = "���Ͷ���ʧ�ܣ��˿ں�ָ����������Ƕ���è����û�нӺ�!";
					  WriteErrorLog();
					  return;
					}
					else if(result == -3)
					{
					  FErrorStr = "���Ͷ���ʧ�ܣ�����è����û�нӺû��ߵ�Դû�д�!";
					  WriteErrorLog();
					  return;
					}
					else if(result >=0 && result <= 10)
					{
                       result = 0;
                    }
					else if(result >= 100)
					{
					  FErrorStr = ErorType(result);
					  WriteErrorLog();
					}
				}
                catch(...)
                {
                    FErrorStr = "���Ͷ���ʧ��";
					WriteErrorLog();
				}
			 }
             else //���ط���
			 {
                try
                {
                    MainTimer->Enabled = false;
					result=SendData(Query->FieldByName("SCTRecvPsPhone")->AsString
									 ,Query->FieldByName("SCTConet")->AsString);
                    MainTimer->Enabled = true;
                }
                catch(...)
                {
                    FErrorStr = "���Ͷ���ʧ��";
                    WriteErrorLog();
                    MainTimer->Enabled = true;
				}
			 }

			  try
			  {
                  QueryTemp->Close();
				  Str ="Exec sd_OperShortMessage "+IntToStr(result)+",'"
							  +Query->FieldByName("SCTPKID")->AsString+"',"
                              +IntToStr(FRepeatCount);
                  QueryTemp->SQL->Text = Str;
                  QueryTemp->ExecSQL();
              }
			  catch(...)           
			  {
                 FErrorStr = "���ͺ���ʧ��";
                 WriteErrorLog();
			  }
              Query->Next();
		  }
	 }
	__finally
	{
		delete QueryTemp;
		delete Query;
	}
}
//---------------------------------------------------------------------------
int __fastcall TShortInfo::SendData(String Heard,String Detail)
{
   long lSmsID;
   int Status;
   int i = 0;
   if (FFlag == 0)//è����
   {
	   Status = fnGetStatus(FComPort);

	   if(Status <= -1)
	   {
		 return -2;
	   }
	   else if(Status <= 1)
	   {
		 return -3;
	   }
	   else
	   {
		 return fnSendMsg(FComPort,Heard.c_str(),Detail.c_str());
	   }
   }
   else
   {
	   SendStatus *resultStatus;
	   SendSevice = GetsmsPortType(true);
	   resultStatus = SendSevice->directSend(FCordId,FUserName,FPassword,Heard,Detail,"",1,"",1);
	   if(resultStatus->retCode == "Faild")
	   {
		  FErrorStr = "���ŷ���ʧ�ܣ�"+resultStatus->message;
		  WriteErrorLog();
		  return -1;
	   }
	   else
		  return 1;
   }
}
//---------------------------------------------------------------------------
void __fastcall TShortInfo::ReadShortMessage()
{
	 int result;
	 int index;
	 Char * szHeader;
	 Char * MainMessge;
	 int i,j;
     String *PNo;
     String Str,ID;
	 TADOQuery* Query = new TADOQuery(NULL);
	 Query->Connection=AccConn;
     try
     {
		szHeader = StrAlloc(500);
        MainMessge = StrAlloc(500);
		result = fnReadMsgEx(-1,szHeader,MainMessge);
		if ( result == 0 )
		{
			Str = szHeader;
			i = StrToInt(ResultStr(Str,1));
		   if (i > 0 && i < 6) //���շ�����Ϣ��Ϣ
		   {
			   j = IndexList->IndexOf(StrToInt(ResultStr(Str,5)));
			   if (j == -1)
			   {
				   FErrorStr = "���յ���Ϣ���޷����¶�Ӧ��¼";
				   WriteErrorLog();
				   return;
			   }
			   ID=SendList->Strings[j];
			   Query->Close() ;
			   PNo = (String *)SendList->Objects[j];
			   Query->SQL->Text = "Exec tbMsgSendRcd_updateState '"+ID+"',"+IntToStr(i);
			   try
			   {
				  Query->ExecSQL();
				  SendList->Delete(j);
				  IndexList->Delete(j);
			   }
			   catch(...)
			   {
				  FErrorStr = "��������ʧ��!";
				  WriteErrorLog();
			   }
		   }
		}
    }
    __finally
    {
        StrDispose(szHeader);
        StrDispose(MainMessge);
    }
}
//--------------------------------------------------------------
void __fastcall TShortInfo::StarTimer()
{
	MainTimer->Interval = FWaitLong;
	MainTimer->OnTimer = OnTimer;
    MainTimer->Enabled = true;
}
//-----------------------------------------------------------------
void __fastcall TShortInfo::WriteErrorLog()
{
    if (OnWriteErrorLog != NULL)
        OnWriteErrorLog(FErrorStr);
}
String __fastcall TShortInfo::ResultStr(String Source,int flag)
{
  int i,index;
  String Str;
  for (index = 1;index<=flag;index++)
  {
     i = Source.Pos(",");
     if (i != 0)
     {
         Str = Source.SubString(1,i-1);
         Source = Source.SubString(i+1,Source.Length()-i);
     }
     else
     {
        if (index==flag)
            return Source;
        else
            return "";
     }
  }
  return Str;
}
//------------------------------------------------------------
void __fastcall TShortInfo::OnTimer(TObject *Sender)
{
	if ( (StrToTime(FormatDateTime("HH:mm:ss",Now()))>=FBeginTime)
         &&(StrToTime(FormatDateTime("HH:mm:ss",Now()))<=FEndTime)
         )
	 {
		 if (RecvThread!= NULL && RecvThread->Suspended)
			 RecvThread->Resume();
		 if (SendThread!= NULL && SendThread->Suspended)
			 SendThread->Resume();
	 }
}
//---------------------------------------------------------------------------
__fastcall TSendThread::TSendThread(bool CreateSuspended )
        : TThread(CreateSuspended)
{
     FreeOnTerminate = true;
     this->Priority = tpIdle;
}
//---------------------------------------------------------------------------

void __fastcall TSendThread::Execute()
{
        //---- Place thread code here ----
        while (!this->Terminated)
        {
            if (SendFun!=NULL)
            {
                try
				{
                        Synchronize(SendFun);
                }
                catch(...)
                {
                         //�Ժ���
                }
            }
			this->Suspend();
        }
}

//---------------------------------------------------------------------------
__fastcall TRecvThread::TRecvThread(bool CreateSuspended )
        : TThread(CreateSuspended)
{
     FreeOnTerminate = true;
     this->Priority = tpIdle;
}

//---------------------------------------------------------------------------
void __fastcall TRecvThread::Execute()
{
        //---- Place thread code here ----
        while (!this->Terminated)
        {
            if (Recvfun!=NULL)
            {
               try
               {
                    Synchronize(Recvfun);
               }
               catch(...)
               {
                   //�Ժ���
               }
            }
			this->Suspend();
        }
}
//---------------------------------------------------------------------------
__fastcall TEndTimeThread::TEndTimeThread(bool CreateSuspended )
        : TThread(CreateSuspended)
{
     FreeOnTerminate = true;
     this->Priority = tpIdle ;
}
//---------------------------------------------------------------------------
void __fastcall TEndTimeThread::Execute()
{
        //---- Place thread code here ----
        while (!this->Terminated)
        {
			if ( (StrToTime(FormatDateTime("HH:mm:ss",Now()))>=FBeginTime)
				 &&(StrToTime(FormatDateTime("HH:mm:ss",Now()))<=FEndTime))
            {
				if (RecvThread != NULL && RecvThread->Suspended)
					RecvThread->Resume();
				else if (SendThread != NULL && SendThread->Suspended)
					SendThread->Resume();
            }
            else
            {
                if (RecvThread != NULL && (!RecvThread->Suspended))
                    RecvThread->Suspend();
				if (SendThread != NULL && (!SendThread->Suspended))
                    SendThread->Suspend();
            }
        }
}
String _fastcall TShortInfo::getStatus()
{
  return IntToStr(fnGetStatus(FComPort));
}