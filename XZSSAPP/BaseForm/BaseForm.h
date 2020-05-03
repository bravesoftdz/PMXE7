//---------------------------------------------------------------------------

#ifndef BaseFormH
#define BaseFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "ClientBroker.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TfrmBaseForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBarTop;
	TLabel *lbTitle;
	TToolBar *ToolBarBottom;
	TButton *btClose;
	TPanel *MainPanel;
	TStyleBook *StyleBook1;
	TVertScrollBox *ClientVertScrollBox;
	TVertScrollBox *MainVertScrollBox;
	void __fastcall btCloseClick(TObject *Sender);
	void __fastcall FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds);
	void __fastcall FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds);
private:	// User declarations
	TClientBroker *FClientBroker;
	int FModuleCode;
	System::Types::TRectF FKBBounds;
	bool FNeedOffset;
	void __fastcall UpdateKBBounds();
	void __fastcall RestorePosition();
protected:
	TClientDataSet* __fastcall Execute(String Resource, TRESTRequestMethod Method, TRESTRequestParameterList *Params);
	TClientDataSet* __fastcall csGetData(String Resource, TRESTRequestParameterList *Params);
	TClientDataSet* __fastcall PostData(String Resource, TRESTRequestParameterList *Params);
	TClientDataSet* __fastcall GetElementData(String ElementName);
public:		// User declarations
	__fastcall TfrmBaseForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param);
    __fastcall TfrmBaseForm(TComponent* Owner,TClientBroker *clBroker);
	__property TClientBroker *ClientBroker={ read=FClientBroker,write=FClientBroker};
	__property int ModuleCode={ read=FModuleCode,write=FModuleCode};
	void __fastcall PhoneDialer(String APhoneNum);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBaseForm *frmBaseForm;
//---------------------------------------------------------------------------
#endif