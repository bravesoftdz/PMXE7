//---------------------------------------------------------------------------

#ifndef AppSetupH
#define AppSetupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Xml.Win.msxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
//---------------------------------------------------------------------------
class TfrmAppSetup : public TForm
{
__published:	// IDE-managed Components
	TButton *btCancel;
	TButton *btSave;
	TStatusBar *StatusBar1;
	TPageControl *PageControl1;
	TTabSheet *TabDBConnection;
	TTabSheet *TabSerSetting;
	TGroupBox *GroupBox2;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label5;
	TEdit *edHTTP;
	TEdit *edTCPIP;
	TEdit *edServerName;
	TListView *lvServerList;
	TPanel *Panel1;
	TButton *btAdd;
	TButton *btEdit;
	TButton *btDelete;
	TActionList *ActionList1;
	TAction *acAdd;
	TAction *acEdit;
	TAction *acDelete;
	TButton *btStart;
	TButton *btStop;
	TButton *btReg;
	TButton *btUnReg;
	TLabel *Label1;
	TLabel *Label4;
	TEdit *edUser;
	TEdit *edPassword;
	TLabel *Label6;
	TEdit *edPeriod;
	TLabel *Label7;
	TAction *acSerStart;
	TAction *acSerStop;
	TAction *acSerInstall;
	TAction *acSerUnInst;
	TPopupMenu *PopupMenu1;
	TMenuItem *miStart;
	TMenuItem *miStop;
	TMenuItem *miInstall;
	TMenuItem *miUnInstall;
	TAction *acSCReg;
	TAction *acSCUnReg;
	TAction *acSCStart;
	TAction *acSCStop;
	TAction *acRefresh;
	void __fastcall btCancelClick(TObject *Sender);
	void __fastcall btSaveClick(TObject *Sender);
	void __fastcall edHTTPKeyPress(TObject *Sender, char &Key);
	void __fastcall acSerStartExecute(TObject *Sender);
	void __fastcall acSerStopExecute(TObject *Sender);
	void __fastcall acSerInstallExecute(TObject *Sender);
	void __fastcall acSerUnInstExecute(TObject *Sender);
	void __fastcall acAddExecute(TObject *Sender);
	void __fastcall acEditExecute(TObject *Sender);
	void __fastcall acDeleteExecute(TObject *Sender);
	void __fastcall lvServerListSelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall acSCRegExecute(TObject *Sender);
	void __fastcall acSCUnRegExecute(TObject *Sender);
	void __fastcall acSCStartExecute(TObject *Sender);
	void __fastcall acSCStopExecute(TObject *Sender);
	void __fastcall acRefreshExecute(TObject *Sender);

private:	// User declarations
	String ServerName;
	void __fastcall ReadOptions();
	void __fastcall WriteOptions();
	void __fastcall ChangeItemStatus(TListItem *AItem);
	String __fastcall ServiceStatus(String ServerName);
	void __fastcall ChangeSCAction();
public:		// User declarations
	__fastcall TfrmAppSetup(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAppSetup *frmAppSetup;
//---------------------------------------------------------------------------
#endif