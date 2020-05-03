//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include <System.Ioutils.hpp>
#include "HouseView.h"
#include "ShowHSView.h"
#include "FSTMessageDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CommBase"
#pragma resource "*.fmx"
THouseViewForm *HouseViewForm;
//---------------------------------------------------------------------------
__fastcall THouseViewForm::THouseViewForm(TComponent* Owner,TClientBroker * ABroker)
	: TCommBaseForm(Owner,ABroker)
{
#if  defined(__ANDROID__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	AppPath= System::Ioutils::TPath::GetDocumentsPath();
#else
	AppPath = ExtractFilePath(ParamStr(0));
#endif
	AppPath=System::Ioutils::TPath::Combine(AppPath, "HouseView");  //����ͼ·��
	MedalQuery=new TZClientQuery(this,ABroker);
	WaitAniIndicator->Visible=false;
	ShowViewForm=NULL;
    fmtSettings=fmtSettings.Create();
	fmtSettings.DateSeparator   = '-';
	fmtSettings.TimeSeparator   = ':';
	fmtSettings.ShortDateFormat = "yyyy-MM-dd";
	fmtSettings.ShortTimeFormat = "HH:mm:ss";
}
//---------------------------------------------------------------------------
__fastcall THouseViewForm::~THouseViewForm()
{
   delete MedalQuery ;
}
//---------------------------------------------------------------------------
//ֱ�Ӷ�λ����
void __fastcall THouseViewForm::SetCurHouseType(String EstName,String BdgName,String HousType)
{
	int estIndex=cbHsgFKID_Est->Items->IndexOf(EstName);
	if(estIndex<0)
	   estIndex=0;
	cbHsgFKID_Est->ItemIndex=estIndex;
	InitBdgNameComboBox();    //ˢ��һ��¥��
	int bdgIndex=cbHsgFKID_Bdg->Items->IndexOf(BdgName);
	if(bdgIndex<0)
	   bdgIndex=0;
	cbHsgFKID_Bdg->ItemIndex=bdgIndex;
	int htIndex=cbHsgHouseType->Items->IndexOf(HousType);
	if(htIndex<0)
	   htIndex=0;
	cbHsgHouseType->ItemIndex=htIndex;
   SearchAction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::InitEstNameComboBox()
{
  cbHsgFKID_Est->Clear();
  TListBoxItem * newBoxItem=new TListBoxItem(cbHsgFKID_Est);
//  newBoxItem->Text=L"����¥��";
//  newBoxItem->TagString="0"; //¥��ID
//  cbHsgFKID_Est->AddObject(newBoxItem);
   Query->Close();
   Query->SQL->Text="select EstatePKID,EstateCode,EstateName from tbEstate order by EstateCode";
   Query->Open();
   Query->First();
   while(!Query->Eof)
   {
		newBoxItem=new TListBoxItem(cbHsgFKID_Est);
		newBoxItem->Text=Query->FieldByName("EstateName")->AsString;
		newBoxItem->TagString=Query->FieldByName("EstatePKID")->AsString;
		cbHsgFKID_Est->AddObject(newBoxItem);
		Query->Next();
   }
   Query->Close();
  if(cbHsgFKID_Est->Count>0)
  {
	 cbHsgFKID_Est->ItemIndex=0;
	 InitBdgNameComboBox();
  }
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::InitBdgNameComboBox()
{
  cbHsgFKID_Bdg->Clear();
  TListBoxItem * newBoxItem=new TListBoxItem(cbHsgFKID_Bdg);
  newBoxItem->Text=L"����¥��";
  newBoxItem->TagString="0"; //ID
  cbHsgFKID_Bdg->AddObject(newBoxItem);
  if(cbHsgFKID_Est->ItemIndex>-1) //��ѡ��ĳ¥��
  {
   Query->Close();
   Query->SQL->Text="select BdgPKID,BdgName from tbBuilding where BdgFKID_Est="+QuotedStr(cbHsgFKID_Est->Selected->TagString);
   Query->Open();
   Query->First();
   while(!Query->Eof)
   {
		newBoxItem=new TListBoxItem(cbHsgFKID_Bdg);
		newBoxItem->Text=Query->FieldByName("BdgName")->AsString;
		newBoxItem->TagString=Query->FieldByName("BdgPKID")->AsString;
		cbHsgFKID_Bdg->AddObject(newBoxItem);
		Query->Next();
   }
   Query->Close();
  }
  if(cbHsgFKID_Bdg->Count>0)
   cbHsgFKID_Bdg->ItemIndex=0;
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::cbHsgFKID_EstClosePopup(TObject *Sender)
{
   InitBdgNameComboBox();
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::InitHouseTypeComboBox()
{
  cbHsgHouseType->Clear();
  TListBoxItem * newBoxItem=new TListBoxItem(cbHsgHouseType);
  newBoxItem->Text=L"���л���";
  newBoxItem->TagString="0";
  cbHsgHouseType->AddObject(newBoxItem);
   Query->Close();
   Query->SQL->Text="select HsgHTPKID,HsgHTRemark from tbHsg_HouseType";
   Query->Open();
   Query->First();
   while(!Query->Eof)
   {
		newBoxItem=new TListBoxItem(cbHsgHouseType);
		newBoxItem->Text=Query->FieldByName("HsgHTRemark")->AsString;
		newBoxItem->TagString=Query->FieldByName("HsgHTPKID")->AsString;
		cbHsgHouseType->AddObject(newBoxItem);
		Query->Next();
   }
   Query->Close();
  if(cbHsgHouseType->Count>0)
   cbHsgHouseType->ItemIndex=0;
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::InitControl()
{
 	InitEstNameComboBox();
	InitBdgNameComboBox();
	InitHouseTypeComboBox();
}
//---------------------------------------------------------------------------
String __fastcall THouseViewForm::GetFilters()
{
  String custFilters="";
  if(cbHsgFKID_Est->ItemIndex>-1)  //¥��
  {
	custFilters="EstMdaFKID_Est="+QuotedStr(cbHsgFKID_Est->Selected->TagString);
  }
  if(cbHsgFKID_Bdg->ItemIndex>0) //¥��
  {
   if(custFilters>" ")
		custFilters=custFilters+" and ";
	custFilters=custFilters+"EstMdaFKID_Bdg="+QuotedStr(cbHsgFKID_Bdg->Selected->TagString);
  }
  if(cbHsgHouseType->ItemIndex>0) //����
  {
   if(custFilters>" ")
		custFilters=custFilters+" and ";
	custFilters=custFilters+"EstMdaHouseType="+QuotedStr(cbHsgHouseType->Selected->TagString);
  }
  return custFilters;
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::FillHouseList()
{
   String SQLStr="SELECT EstMdaPKID,EstMdaFKID_Est,EstMdaFKID_Bdg,EstMdaFloor,EstMdaFKID_Hsg,EstMdaHouseType"
	  ",EstMdaType,EstMdaName,EstMdaSaveType,EstMdaFileName,EstMdaDat,EstMdaCreateDate,"
	"isnull(EstateName,'') as EstateName,isnull(BdgName,'') as BdgName,"
	"isnull(HsgHTRemark,'') as HsgHTRemark,"
	"isnull(HsgNum,'') as HsgNum "
	" from tbEstateMedia "
	"left join tbEstate on tbEstateMedia.EstMdaFKID_Est=tbEstate.EstatePKID "
	"left join tbBuilding on tbEstateMedia.EstMdaFKID_Bdg=tbBuilding.BdgPKID "
	"left join tbHsg_HouseType on tbEstateMedia.EstMdaHouseType=tbHsg_HouseType.HsgHTPKID "
	"left join tbhousing on tbEstateMedia.EstMdaFKID_Hsg=tbhousing.HsgPKID "
	"where "+GetFilters();
  try{
	  lvHouseList->BeginUpdate();
	  lvHouseList->Items->Clear();
	  MedalQuery->Close();
	  MedalQuery->SQL->Text=SQLStr;
	  MedalQuery->Open();
	  while(!MedalQuery->Eof)
	  {
		 String mFileName=AppPath;
		 String EstMdaFKID_Est=MedalQuery->FieldByName("EstMdaFKID_Est")->AsString;
		 String EstMdaFKID_Bdg=MedalQuery->FieldByName("EstMdaFKID_Bdg")->AsString;
		 String EstMdaHouseType=MedalQuery->FieldByName("EstMdaHouseType")->AsString;
		 String EstMdaFKID_Hsg=MedalQuery->FieldByName("EstMdaFKID_Hsg")->AsString;

		 String EstateName=MedalQuery->FieldByName("EstateName")->AsString;
		 String BdgName=MedalQuery->FieldByName("BdgName")->AsString;
		 String HsgHTRemark=MedalQuery->FieldByName("HsgHTRemark")->AsString;
		 String HsgNum=MedalQuery->FieldByName("HsgNum")->AsString;

		 String EstMdaName=MedalQuery->FieldByName("EstMdaName")->AsString;
		 int    EstMdaFloor=MedalQuery->FieldByName("EstMdaFloor")->AsInteger;
		 int mType=MedalQuery->FieldByName("EstMdaType")->AsInteger;
		 String mText="";
		 String dText="";
		 if(EstMdaFKID_Est>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Est);
		  mText=EstateName;
		 }
		 if(EstMdaFKID_Bdg>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Bdg);
		  mText=mText+"-"+BdgName;
		 }
		 if(EstMdaFloor!=0) //¥����ߵ�����
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,IntToStr(EstMdaFloor));
		  mText=mText+"-"+IntToStr(EstMdaFloor);
		 }
		 if(EstMdaHouseType>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaHouseType);
		  mText=mText+"-"+HsgHTRemark;
		 }
		 if(EstMdaFKID_Hsg>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Hsg);
		  mText=mText+"-"+HsgNum;
		 }
		 mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaName);
		 switch(mType)
		 {
			 case 1: //ͼƬ
			 dText=L"ͼƬ:"+EstMdaName;
			 break;
			 case 2: //����
			 dText=L"����:"+EstMdaName;
			 break;
			 default:  //��Ƶ
			 dText=L"��Ƶ:"+EstMdaName;
		  }
		 TListViewItem* vItem=lvHouseList->Items->Add();
		// vItem->ButtonText=mFileName;
		 vItem->Text=mText;
		 vItem->Detail=dText;
		 MedalQuery->Next();
	  }
  }
  __finally
  {
   lvHouseList->EndUpdate();
  }
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::lvHouseListButtonClick(const TObject *Sender, const TListViewItem *AItem,
          const TListItemSimpleControl *AObject)
{
	 if(MedalQuery->RecordCount>0)
	 {
		 MedalQuery->RecNo= const_cast<TListViewItem*>(AItem)->Index+1;
		 String mFileName=AppPath;
		 String EstMdaFKID_Est=MedalQuery->FieldByName("EstMdaFKID_Est")->AsString;
		 String EstMdaFKID_Bdg=MedalQuery->FieldByName("EstMdaFKID_Bdg")->AsString;
		 String EstMdaHouseType=MedalQuery->FieldByName("EstMdaHouseType")->AsString;
		 String EstMdaFKID_Hsg=MedalQuery->FieldByName("EstMdaFKID_Hsg")->AsString;

		 String EstateName=MedalQuery->FieldByName("EstateName")->AsString;
		 String BdgName=MedalQuery->FieldByName("BdgName")->AsString;
		 String HsgHTRemark=MedalQuery->FieldByName("HsgHTRemark")->AsString;
		 String HsgNum=MedalQuery->FieldByName("HsgNum")->AsString;

		 String EstMdaName=MedalQuery->FieldByName("EstMdaName")->AsString;
		 int    EstMdaFloor=MedalQuery->FieldByName("EstMdaFloor")->AsInteger;
		 int mType=MedalQuery->FieldByName("EstMdaType")->AsInteger;
		 String mText="";
		 if(EstMdaFKID_Est>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Est);
		  mText=EstateName;
		 }
		 if(EstMdaFKID_Bdg>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Bdg);
		  mText=mText+"-"+BdgName;
		 }
		 if(EstMdaFloor!=0)
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,IntToStr(EstMdaFloor));
		  mText=mText+"-"+IntToStr(EstMdaFloor);
		 }
		 if(EstMdaHouseType>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaHouseType);
		  mText=mText+"-"+HsgHTRemark;
		 }
		 if(EstMdaFKID_Hsg>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Hsg);
		  mText=mText+"-"+HsgNum;
		 }
		 mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaName);
	   if(FileExists(mFileName))
	   {
		  // ShowMessage(mFileName+L"�ļ�û�����ص�����");
		   switch(mType)
		 {
			 case 1: //ͼƬ
			 case 2: //����
			 {
			 if( ShowViewForm==NULL)
				 ShowViewForm=new TShowViewForm(this);
			 ShowViewForm->MType=mType;
			 ShowViewForm->ModuleText=mText;
			 ShowViewForm->MFileName=mFileName;
             ShowViewForm->Show();
			 }
			 break;
			 case 3:  //��Ƶ
			 {
				#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(__ANDROID__)
					MediaPlayer1->FileName = mFileName;
				#endif
					MediaPlayer1->Play();
			 }
			 break;
		  }
	   }
	   else
         ShowMessage(L"�����Ҳ����ļ�,������ͨ��[���ظ���]����ȡ!");
	 }
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::DownLoadActionExecute(TObject *Sender)
{
   TMessageDialogEventProc msgDialogCloseProc=&DoDowndLoadProc;
   ShowMessageBox(L"���ظ��¹��̿��ܱȽϳ־�,��ȷ��Ҫ������?",msgDialogCloseProc);
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::DoDowndLoadProc(System::Uitypes::TModalResult AResult)
{
 if(AResult==mrYes)
 {
	try{
		WaitAniIndicator->Visible=true;
		WaitAniIndicator->Enabled=true;
		DowndLoadListFile();
	}
	__finally
	{
		WaitAniIndicator->Visible=false;
		WaitAniIndicator->Enabled=false;
	}
 }
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::DowndLoadListFile()
{
	 // TMemoryStream *ms=new TMemoryStream();
	  int iUpdateCount=0;
	  MedalQuery->First();
	  while(!MedalQuery->Eof)
	  {
		 String mFileName=AppPath;
		 String MedalID=MedalQuery->FieldByName("EstMdaPKID")->AsString;
		 String EstMdaFKID_Est=MedalQuery->FieldByName("EstMdaFKID_Est")->AsString;
		 String EstMdaFKID_Bdg=MedalQuery->FieldByName("EstMdaFKID_Bdg")->AsString;
		 String EstMdaHouseType=MedalQuery->FieldByName("EstMdaHouseType")->AsString;
		 String EstMdaFKID_Hsg=MedalQuery->FieldByName("EstMdaFKID_Hsg")->AsString;


		 String EstMdaName=MedalQuery->FieldByName("EstMdaName")->AsString;
		 int    EstMdaFloor=MedalQuery->FieldByName("EstMdaFloor")->AsInteger;
		 int mType=MedalQuery->FieldByName("EstMdaType")->AsInteger;
		 TDateTime mfileCreateDate= StrToDate(MedalQuery->FieldByName("EstMdaCreateDate")->AsString,fmtSettings);
		 String dText="";
		 if(EstMdaFKID_Est>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Est);
		 }
		 if(EstMdaFKID_Bdg>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Bdg);
		 }
		 if(EstMdaFloor!=0)
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,IntToStr(EstMdaFloor));
		 }
		 if(EstMdaHouseType>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaHouseType);
		 }
		 if(EstMdaFKID_Hsg>"")
		 {
		  mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaFKID_Hsg);
		 }
		 ForceDirectories(mFileName);// ����Ŀ¼
		 mFileName=System::Ioutils::TPath::Combine(mFileName,EstMdaName);
		 if(FileExists(mFileName))
		 {
		 //��ȡ�ļ�����ʱ��
		  TDateTime lcoalFileDateTime=System::Ioutils::TFile::GetCreationTime(mFileName);
		  if(lcoalFileDateTime<mfileCreateDate)  //����
			{
			  lbTitle->Text=L"��������:"+EstMdaName;
			  Application->ProcessMessages();
			  TMemoryStream *ms=dynamic_cast<TMemoryStream*>(ClientBroker->GetHouseViewStream(MedalID));
			  if(ms->Size>0)
			  {
			   ms->SaveToFile(mFileName);
			   iUpdateCount++;
			  }
			}

		 }
		 else //����
		 {
		   lbTitle->Text=L"��������:"+EstMdaName;
		   Application->ProcessMessages();
		   TMemoryStream *ms=dynamic_cast<TMemoryStream*>(ClientBroker->GetHouseViewStream(MedalID));
		   if(ms->Size>0)
		   {
			   ms->SaveToFile(mFileName);
			   iUpdateCount++;
		   }
		 }

		 MedalQuery->Next();
	  }
	lbTitle->Text=L"����ͼ";
	 ShowMessage(L"���θ�����"+IntToStr(iUpdateCount)+L"���ļ�");
}
//---------------------------------------------------------------------------
void __fastcall THouseViewForm::SearchActionExecute(TObject *Sender)
{
	try{
		WaitAniIndicator->Visible=true;
		WaitAniIndicator->Enabled=true;
		FillHouseList();
	}
	__finally
	{
		WaitAniIndicator->Visible=false;
		WaitAniIndicator->Enabled=false;
	}

}
//---------------------------------------------------------------------------
