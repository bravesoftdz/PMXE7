//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "HouseReserveEdit.h"
#include "CommFunc.h"
#include <System.DateUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DetailBaseForm"
#pragma resource "*.fmx"
THouseReserveEditForm *HouseReserveEditForm;
//---------------------------------------------------------------------------
__fastcall THouseReserveEditForm::THouseReserveEditForm(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,TZClientDataSet
								*FDataSet,int DataSetStatus)
	: TfrmDetailBaseForm(Owner,clBroker,ModuleCode,FDataSet, DataSetStatus)
{
	InitForm();
}
//---------------------------------------------------------------------------
__fastcall THouseReserveEditForm::THouseReserveEditForm(TComponent* Owner,TClientBroker * clBroker,
					int ModuleCode,String Param,int Flag)
	: TfrmDetailBaseForm(Owner,clBroker,ModuleCode,Param)
{
	InitForm();
   if(Flag==1)//�ӿͻ���ѯ������ Param=�ͻ�ID
   {
	  SetFormStatus(1); //����
	  SetCustomer(Param);
   }
   else if(Flag==2) //�ӷ�Դ��ѯ������ Param=����ID
   {
	  SetFormStatus(1); //����
	  SetHousing(Param);
   }
   else if(Flag==3) //ר��ΪOA��������,Param=BillID;
   {
	  this->MasterWhereString="HseRsvePKID="+QuotedStr(Param);
	  this->RefreshData();
	  SetFormStatus(0);//���״̬
   	  GetWorkflowDefine();  //Ϊ����ʾ����
   }

}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::InitForm()
{
	SelectPeople=NULL;
	SelectHouse=NULL;
	SelectCustomer=NULL;

//     ��ȡ�ж��Ƿ�����������  1,2
	   IsSalesManager=false;
	   Query->Close();
	   Query->SQL->Text="select EmpSalesPs from tbEmployeeData where EmpPKID='"+ClientBroker->UserEmpID+"'";
	   Query->Open();
	   if(Query->RecordCount>0)
	   {
		   IsSalesManager=Query->FieldByName("EmpSalesPs")->AsInteger==2;
	   }
	   Query->Close();
	 //������ҵ�����̹����¼���
	 OnBeforWorkFlowStart=BeforWorkFlowStart;
	 OnBeforWorkFlowExec=BeforWorkFlowExec;
	 //��Ч�ڲ���
	  valDays=1;
	  Query->Close();
	  Query->SQL->Text="select * from tbSysParameter where SysParamPKID='YDTerm'";
	  Query->Open();
	  if(Query->RecordCount>0)
	  {
		  if(Query->FieldByName("SysParamValue")->AsFloat>0)
		  {
			valDays=Query->FieldByName("SysParamValue")->AsFloat;
		  }
	  }
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::FormInitControl()
{ //���,����,�޸� ,true-�����ã�false-��ס
  LockControl(1,seHseRsveNum,false,true,false);
  LockControl(1,seHseRsveFKID_Client,false,true,false);
  LockControl(1,seHseRsveFKID_Hsg,false,true,false);
  LockControl(1,deHseRsveDate,false,true,true);
  LockControl(1,deHseRsveValidDate,false,true,true);
  LockControl(1,seHseRsveSubsAmtPct,false,true,true);
  LockControl(1,seHseRsveSubsAmt,false,true,true);
  LockControl(1,seHseRsveFKID_Consigner,false,true,true);
  LockControl(1,mmHseRsveRemark,false,true,true);
  WaitInputControl(1,seHseRsveFKID_Client);
  GetWorkflowDefine();
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::FormClearControl(int Section)
{
  FBillGuidID=GetGUIDString();
   //�ͻ�
  seHseRsveFKID_Client->Text = "";
  seHseRsveFKID_Client->TagString="";
  cboxClientSex->ItemIndex=0;
  clClientZJ->Text="";
  clClientPhone->Text="";
  clAddress->Text="";

   //��Ԫ
  seHseRsveFKID_Hsg->Text = "";
  seHseRsveFKID_Hsg->TagString ="";
  lbEstName->Text = "";
  lbLGName->Text = "";
  lbHseRsveArea->Text = "0";
  lbUseAre->Text = "0";
  seHseRsvePrice->Text = "0.0";
  seHseRsveTotal->Text = "0.0";
  lbDirection->Text = "";
  lbhouseType->Text = "";
  lbHouseModule->Text = "";
  lbHouseView->Text = "";
  lbHouseDecorate->Text = "";
  //Ԥ��
  seHseRsveNum->MaxLength=40;
  seHseRsveNum->Text = "";
  deHseRsveDate->Date=Now();//FormatDateTime("yyyy-mm-dd",Now());
  deHseRsveValidDate->Date =IncDay(deHseRsveDate->Date,valDays);
  seHseRsveSubsAmtPct->Text="0";
  seHseRsveSubsAmt->Text="0";
  seHseRsveFKID_Consigner->TagString=ClientBroker->UserEmpID;                //��ҵ����
  seHseRsveFKID_Consigner->Text=ClientBroker->UserName;
  scCombox->ItemIndex=0;
  seHouseAdv->TagString=ClientBroker->UserEmpID;                //��ҵ����
  seHouseAdv->Text=ClientBroker->UserName;
  //��ע
  mmHseRsveRemark->Lines->Text="";

}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::SendDataToDataSet(int Section)
{
  SetFieldValue("HseRsvePKID",FBillGuidID);
  SetFieldValue("HseRsveNum",seHseRsveNum->Text);
  SetFieldValue("HseRsveFKID_Est",lbEstName->TagString);
  SetFieldValue("HseRsveFKID_Bdg",lbLGName->TagString);
  SetFieldValue("LgName",lbLGName->Text);

  SetFieldValue("HseRsveFKID_Hsg",seHseRsveFKID_Hsg->TagString);
  SetFieldValue("UnitName",seHseRsveFKID_Hsg->Text);
  SetFieldValue("HseRsveNum",seHseRsveNum->Text);

  SetFieldValue("EstateName",lbEstName->Text);
  SetFieldValue("HsgOnRemark",lbDirection->Text);
  SetFieldValue("HsgFnRemark",lbhouseType->Text);
  SetFieldValue("HsgHTRemark",lbHouseModule->Text);
  SetFieldValue("HsgLeRemark",lbHouseView->Text);
  SetFieldValue("HsgDnRemark",lbHouseDecorate->Text);

  SetFieldValue("HseRsveFKID_Client",seHseRsveFKID_Client->TagString);
  SetFieldValue("ClientTheName",seHseRsveFKID_Client->Text);

  SetFieldValue("ClientSalerFKID",seHouseAdv->TagString);
  SetFieldValue("EmpName",seHouseAdv->Text);

  SetFieldValue("HseRsveDate",FormatDateTime("yyyy-mm-dd",deHseRsveDate->Date));
  SetFieldValue("HseRsveValidDate",FormatDateTime("yyyy-mm-dd",deHseRsveValidDate->Date));

  SetFieldValue("HseRsveArea",lbHseRsveArea->Text);
  SetFieldValue("HseRsvePrice",seHseRsvePrice->Text);

  SetFieldValue("HseRsveTotal",seHseRsveTotal->Text);

  SetFieldValue("HseRsveSubsAmtPct",seHseRsveSubsAmtPct->Text);
  SetFieldValue("HseRsveSubsAmt",seHseRsveSubsAmt->Text);

  SetFieldValue("HseRsveFavorable",0);
  SetFieldValue("HseRsveRebate",0);
  SetFieldValue("HseRsveFavorAmt",0);

  SetFieldValue("HseRsveProperty",scCombox->ItemIndex+1);
  SetFieldValue("HseRsveRemark",mmHseRsveRemark->Text);
  if(chkState->IsChecked)
  {
   SetFieldValue("HseRsveAmendDate",Now().FormatString("yyyy-mm-dd"));
   SetFieldValue("HseRsveAmender",this->ClientBroker->UserCode);
   SetFieldValue("HseRsveDataRights","1");
  }
  else
  {
   SetFieldValue("HseRsveAmendDate","");
   SetFieldValue("HseRsveAmender","");
   SetFieldValue("HseRsveDataRights","0");
  }

  SetFieldValue("HseRsveFKID_Consigner",seHseRsveFKID_Consigner->TagString);
  SetFieldValue("WtMan",seHseRsveFKID_Consigner->Text);

  SetFieldValue("ClientSex",cboxClientSex->ItemIndex);
  SetFieldValue("ClientAddress",clAddress->Text);
  SetFieldValue("ClientPhoneNum",clClientPhone->Text);
  SetFieldValue("ClientPaperName",clClientZJ->Text);
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::GetDataFromDataSet(int Section)
{
  //�ͻ�
  seHseRsveFKID_Client->Text=GetFieldValue("ClientTheName");
  seHseRsveFKID_Client->TagString=GetFieldValue("HseRsveFKID_Client");

  cboxClientSex->ItemIndex=GetFieldValue("ClientSex");
  clAddress->Text=GetFieldValue("ClientAddress");
  clClientPhone->Text=GetFieldValue("ClientPhoneNum");
  clClientZJ->Text=GetFieldValue("ClientPaperName");
  //Ԥ��
  FBillGuidID=GetFieldValue("HseRsvePKID");
  seHseRsveNum->Text=GetFieldValue("HseRsveNum");
  deHseRsveDate->Text=GetFieldValue("HseRsveDate");
  deHseRsveValidDate->Text=GetFieldValue("HseRsveValidDate");
  scCombox->ItemIndex=GetFieldValue("HseRsveProperty")-1;
  seHseRsveSubsAmtPct->Text=GetFieldValue("HseRsveSubsAmtPct");
  seHseRsveSubsAmt->Text=GetFieldValue("HseRsveSubsAmt");
  seHseRsveFKID_Consigner->Text=GetFieldValue("WtMan");
  seHseRsveFKID_Consigner->TagString=GetFieldValue("HseRsveFKID_Consigner");
  seHouseAdv->Text=GetFieldValue("EmpName");
  seHouseAdv->TagString=GetFieldValue("ClientSalerFKID");
  mmHseRsveRemark->Text=GetFieldValue("HseRsveRemark");
//����
  seHseRsveFKID_Hsg->Text=GetFieldValue("UnitName");
  seHseRsveFKID_Hsg->TagString=GetFieldValue("HseRsveFKID_Hsg");
  lbEstName->Text=GetFieldValue("EstateName");
  lbEstName->TagString=GetFieldValue("HseRsveFKID_Est");
  lbLGName->TagString=GetFieldValue("HseRsveFKID_Bdg");
  lbLGName->Text=GetFieldValue("LgName");
  lbDirection->Text=GetFieldValue("HsgOnRemark");
  lbhouseType->Text=GetFieldValue("HsgFnRemark");
  lbHouseModule->Text=GetFieldValue("HsgHTRemark");
  lbHouseView->Text=GetFieldValue("HsgLeRemark");
  lbHouseDecorate->Text=GetFieldValue("HsgDnRemark");
  seHseRsvePrice->Text=GetFieldValue("HseRsvePrice");
  lbHseRsveArea->Text=GetFieldValue("HseRsveArea");
  lbUseAre->Text=GetFieldValue("HsgInnerArea");
  seHseRsveTotal->Text=GetFieldValue("HseRsveTotal");
  chkState->IsChecked=GetFieldValue("HseRsveDataRights")=="1" ;
  //������ʵ��
  GetWorkflowRunID(FBillGuidID);
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::VerifyFieldData(int Section,int status)
{
   if(seHseRsveFKID_Client->Text.IsEmpty())
  {
    if(seHseRsveFKID_Client->CanFocus)
    	seHseRsveFKID_Client->SetFocus();
	throw Exception(L"��ѡ��ͻ�����");
  }

  if(deHseRsveDate->Text.Trim().IsEmpty())
  {
    if(deHseRsveDate->CanFocus)
    deHseRsveDate->SetFocus();
	throw Exception(L"������Ԥ������");
  }

  if(deHseRsveValidDate->Text.Trim().IsEmpty())
  {
    if(deHseRsveValidDate->CanFocus)
    	deHseRsveValidDate->SetFocus();
	throw Exception(L"��������Ч����");
  }

  if(deHseRsveValidDate->Date<=deHseRsveDate->Date)
  {
    if(deHseRsveValidDate->CanFocus)
    deHseRsveValidDate->SetFocus();
	throw Exception(L"��Ч���ޱ������Ԥ�����ڣ�");
  }

  if(seHseRsveFKID_Hsg->Text.Trim().IsEmpty())
  {
    if(seHseRsveFKID_Hsg->CanFocus)
    	seHseRsveFKID_Hsg->SetFocus();
	throw Exception(L"��ѡ��Ԥ����Ԫ");
  }

  Query->Close();
  Query->SQL->Text=String("select SysParamValue from tbSysParameter where SysParamPKID='EarnestMoney'");
  Query->Open();
  if(Query->RecordCount>0)
  {
	if (Query->FieldByName("SysParamValue")->AsFloat==0)
	{
		if(seHseRsveSubsAmt->Text.ToDouble()<=0)
		{
		  if(seHseRsveSubsAmt->CanFocus)
			seHseRsveSubsAmt->SetFocus();
		  throw Exception(L"�����붨����");
		}
	}
  }
  else
	if(seHseRsveSubsAmt->Text.ToDouble()<=0)
	{
      if(seHseRsveSubsAmt->CanFocus)
		seHseRsveSubsAmt->SetFocus();
      throw Exception(L"�����붨����");
	}
}
//---------------------------------------------------------------------------
bool __fastcall THouseReserveEditForm::BeforeUpdateData(int OptType)
{
   int UnitChgPriceState;
   bool canModife=(IsSalesManager||(VarToStr(GetFieldValue("ClientSalerFKID"))== ClientBroker->UserEmpID))&&(GetFieldValue("HseRsveProperty")==1);
   Query->Close();
   Query->SQL->Text=String("select * from tbSysParameter where SysParamClassCode='110'")
             +" and SysParamPKID='UnitChgPriceState'";
   Query->Open();
   if(Query->RecordCount>0)
   {
     if(Query->FieldValues["SysParamValue"]==0)
       UnitChgPriceState = 0 ;
     else
       UnitChgPriceState = 1 ;
   }
   else
     UnitChgPriceState = 0 ;
   Query->Close();
  switch(OptType)
  {
    case 1:
      if(UnitChgPriceState == 1)
      {
	   ShowMessage(_D("���ڵ�Ԫ����״̬����������"));
        return false;
      }
      return true;
    case 2:
      if(UnitChgPriceState == 1)
      {
	   ShowMessage(_D("���ڵ�Ԫ����״̬�������޸�"));
        return false;
      }
	  return canModife;
    case 3:
      if(UnitChgPriceState == 1)
      {
	   ShowMessage(_D("���ڵ�Ԫ����״̬������ɾ��"));
        return false;
      }
	  return canModife;
    default :
      return true;
  }
}
//---------------------------------------------------------------------------
/*
void __fastcall THouseReserveEditForm::SetUserCtrlStatus()
{
  //ֻ�����ݱ��˻������������ܲ����޸�����
  bool canModife=(IsSalesManager||(VarToStr(GetFieldValue("ClientSalerFKID"))== ClientBroker->UserEmpID))&&(scCombox->ItemIndex==0);
  bool bWriteRight=OperateRight.Pos(FR_SYSTEMWRITE)>0;
  bool bBrowse=MasterStatus == dsBrowse;
  DetailEditAction->Enabled=bWriteRight && canModife && bBrowse;
  SaveDetailAction->Enabled=bWriteRight && canModife && !bBrowse;
}*/
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::BeforWorkFlowStart(TWorkFlowStartData *AWorkFlowStartData)
{
  //����ǰ���ݲ���
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::BeforWorkFlowExec(TWorkFlowExecData *AWorkFlowExecData,TClientDataSet *varDataSet)
{
  //����ǰ���ݲ���
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::SetCustomer(String CustomerID)
{
   Query->Close();
   Query->SQL->Text="select tbClient.*, Saleman=isnull((select EmpName from tbEmployeeData where EmpPKID=ClientSalerFKID),'') from tbClient where ClientPKID="+QuotedStr(CustomerID);
   Query->Open();
   if(Query->RecordCount>0)
   {
	  seHseRsveFKID_Client->Text=Query->FieldByName("ClientTheName")->AsString;
	  seHseRsveFKID_Client->TagString=Query->FieldByName("ClientPKID")->AsString;

	  cboxClientSex->ItemIndex=Query->FieldByName("ClientSex")->AsInteger;
	  clAddress->Text=Query->FieldByName("ClientAddress")->AsString;
	  clClientPhone->Text=Query->FieldByName("ClientPhoneNum")->AsString;
	  clClientZJ->Text=Query->FieldByName("ClientPaperName")->AsString;
	  seHouseAdv->TagString=Query->FieldByName("ClientSalerFKID")->AsString;                //��ҵ����
	  seHouseAdv->Text=Query->FieldByName("Saleman")->AsString;
   }
   else
   {
	  clAddress->Text="";
	  clClientPhone->Text="";
	  clClientZJ->Text="";
	  seHouseAdv->TagString=ClientBroker->UserEmpID;                //��ҵ����
	  seHouseAdv->Text=ClientBroker->UserName;
   }
   Query->Close();
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::SetHousing(String HousingID)
{
   Query->Close();
   Query->SQL->Text="select tbHousing.*,"
					"isnull(EstateName,'') as EstateName,isnull(BdgName,'') as BdgName,"
					"isnull(HsgFnRemark,'') as HsgFnRemark,isnull(HsgHTRemark,'') as HsgHTRemark,"
					"isnull(HsgOnRemark,'') as HsgOnRemark,isnull(HsgLeRemark,'') as HsgLeRemark,"
					"isnull(HsgDnRemark,'') as HsgDnRemark from tbHousing "
					"left join tbEstate on tbHousing.HsgFKID_Est=tbEstate.EstatePKID "
					"left join tbBuilding on tbHousing.HsgFKID_Bdg=tbBuilding.BdgPKID "
					"left join tbHsg_Function on tbHousing.HsgFunction=tbHsg_Function.HsgFnPKID "
					"left join tbHsg_HouseType on tbHousing.HsgHouseType=tbHsg_HouseType.HsgHTPKID "
					"left join tbHsg_Orientation on tbHousing.HsgOrientation=tbHsg_Orientation.HsgOnPKID "
					"left join tbHsg_Landscape on tbHousing.HsgLandscape=tbHsg_Landscape.HsgLePKID "
					"left join tbHsg_Decoration on tbHousing.HsgDecoration=tbHsg_Decoration.HsgDnPKID where HsgPKID="+
					QuotedStr(HousingID);
   Query->Open();
   if(Query->RecordCount>0)
   {
	  seHseRsveFKID_Hsg->Text=Query->FieldByName("HsgName")->AsString;
	  seHseRsveFKID_Hsg->TagString=Query->FieldByName("HsgPKID")->AsString;
	  lbEstName->Text=Query->FieldByName("EstateName")->AsString;
	  lbEstName->TagString=Query->FieldByName("HsgFKID_Est")->AsString;
	  lbLGName->TagString=Query->FieldByName("HsgFKID_Bdg")->AsString;
	  lbLGName->Text=Query->FieldByName("BdgName")->AsString;
	  lbDirection->Text=Query->FieldByName("HsgOnRemark")->AsString;
	  lbhouseType->Text=Query->FieldByName("HsgFnRemark")->AsString;
	  lbHouseModule->Text=Query->FieldByName("HsgHTRemark")->AsString;
	  lbHouseView->Text=Query->FieldByName("HsgLeRemark")->AsString;
	  lbHouseDecorate->Text=Query->FieldByName("HsgDnRemark")->AsString;
	  seHseRsvePrice->Text=Query->FieldByName("HsgBuildAreaPrice")->AsString;
	  lbHseRsveArea->Text=Query->FieldByName("HsgFloorSpace")->AsString;
	  lbUseAre->Text=Query->FieldByName("HsgInnerArea")->AsString;
	  seHseRsveTotal->Text=Query->FieldByName("HsgSellTotal")->AsString;
   }
   Query->Close();
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::SetConsigner(String ConsignerID)
{
   Query->Close();
   Query->SQL->Text="select * from tbEmployeeData where EmpPKID="+QuotedStr(ConsignerID);
   Query->Open();
   if(Query->RecordCount>0)
   {
	   seHseRsveFKID_Consigner->Text=Query->FieldByName("EmpName")->AsString;
	   seHseRsveFKID_Consigner->TagString=Query->FieldByName("EmpPKID")->AsString;
   }
   Query->Close();
}
//---------------------------------------------------------------------------
void __fastcall THouseReserveEditForm::CustEditButtonClick(TObject *Sender)
{
  if(SelectCustomer==NULL)
	 SelectCustomer=new TSelectCustomerForm(this,&SetCustomer,this->ClientBroker);
  SelectCustomer->Show();
}
//---------------------------------------------------------------------------

void __fastcall THouseReserveEditForm::deHseRsveDateChange(TObject *Sender)
{
   deHseRsveValidDate->Date =IncDay(deHseRsveDate->Date,valDays);
}
//---------------------------------------------------------------------------

void __fastcall THouseReserveEditForm::HsgEditButtonClick(TObject *Sender)
{
  if(SelectHouse==NULL)
	SelectHouse=new TSelectHouseForm(this,&SetHousing,this->ClientBroker);
  SelectHouse->Show();
}
//---------------------------------------------------------------------------

void __fastcall THouseReserveEditForm::seHseRsveSubsAmtPctExit(TObject *Sender)
{

   double dSubRate=GetFloatFromStr(seHseRsveSubsAmtPct->Text);
   if(dSubRate>0)
   {
   double dPlanAmt=GetFloatFromStr(seHseRsveTotal->Text);
   double dSubAmt=dPlanAmt*dSubRate/100;
   dSubAmt=ConvertFloat(dSubAmt,ftsAmt);
   seHseRsveSubsAmt->Text=FloatToStr(dSubAmt);
   }
}
//---------------------------------------------------------------------------

void __fastcall THouseReserveEditForm::ConsignerEditButtonClick(TObject *Sender)
{
   if(SelectPeople==NULL)
   {
	SelectPeople=new TSelectPeopleForm(this,&SetConsigner,this->ClientBroker);
   }
	SelectPeople->Show();
}
//---------------------------------------------------------------------------

void __fastcall THouseReserveEditForm::CustomerExpanderResize(TObject *Sender)
{
 EditLayout->Height=CustomerExpander->Height+ReserveExpander->Height+HouseExpander->Height;
}
//---------------------------------------------------------------------------


