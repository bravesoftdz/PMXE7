//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "BaseListShow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseListForm"
#pragma resource "*.fmx"
TfrmBaseListShow *frmBaseListShow;
//---------------------------------------------------------------------------
__fastcall TfrmBaseListShow::TfrmBaseListShow(TComponent* Owner)
	: TfrmBaseListForm(Owner)
{
	InitListShowForm();
}
//---------------------------------------------------------------------------
__fastcall TfrmBaseListShow::TfrmBaseListShow(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,String Param)
	: TfrmBaseListForm(Owner,clBroker,ModuleCode,Param)
{
   InitListShowForm();
}
__fastcall TfrmBaseListShow::TfrmBaseListShow(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,TZClientDataSet *FDataSet,String Param)
	: TfrmBaseListForm( Owner, clBroker,ModuleCode,FDataSet,Param)
{
	 InitListShowForm();
}
void __fastcall TfrmBaseListShow::SetOptCtrlStatus(int status)
{
   OperateStatus = status;
  if(OperateRight.Pos(FR_SYSTEMWRITE) <= 0 && OperateRight.Pos(FR_SYSTEMREAD) > 0) //ֻ��Ȩ��
  {
	LookAction->Enabled=true;
	EditAction->Enabled=false;
	AddAction->Enabled=false;
	DelAction->Enabled=false;
  }
  else
  {
	switch(status)     //������༭״̬����
	{
	  case 0: //���
		LookAction->Enabled=true;
		AddAction->Enabled=true;
		DelAction->Enabled=true;
		EditAction->Enabled=true;
        break;
      case 1: //����
        break;
      case 2: //�޸�
        break;
      default:
        break;
    }
    if(RecordCount <= 0)   //��ǰ���ݼ���
    {
		EditAction->Enabled=false;
		AddAction->Enabled=true;
		DelAction->Enabled=false;
		LookAction->Enabled=false;
    }
  }
  SetUserCtrlStatus();   //��״̬�����û�����״̬
}
void __fastcall TfrmBaseListShow::LookActionExecute(TObject *Sender)
{
  BrowseRecord();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaseListShow::DelActionExecute(TObject *Sender)
{
  DelData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseListShow::QueryActionExecute(TObject *Sender)
{
  QueryData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseListShow::EditActionExecute(TObject *Sender)
{
  EditData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseListShow::CloseActionExecute(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseListShow::AddActionExecute(TObject *Sender)
{
 AddData();
}
//---------------------------------------------------------------------------
