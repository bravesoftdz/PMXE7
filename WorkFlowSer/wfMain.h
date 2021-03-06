//---------------------------------------------------------------------------

#ifndef wfMainH
#define wfMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "wfClientBroker.h"
#include <Data.DB.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DSCommonServer.hpp>
#include <Datasnap.DSServer.hpp>
#include <Datasnap.DBClient.hpp>
#include <Soap.SOAPConn.hpp>
//---------------------------------------------------------------------------
class TfrmWFmain : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	TwfClientBroker * FClientBroker ;
	void __fastcall ReadOption();
	void __fastcall RunWFServer();
public:		// User declarations
	__fastcall TfrmWFmain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWFmain *frmWFmain;
//---------------------------------------------------------------------------
#endif
