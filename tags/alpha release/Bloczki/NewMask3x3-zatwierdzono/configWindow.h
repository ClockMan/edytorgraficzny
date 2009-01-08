//---------------------------------------------------------------------------

#ifndef configWindowH
#define configWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>

#include "../../Program/engine/Block.h"
#include <ExtCtrls.hpp>
#include "cspin.h"
//---------------------------------------------------------------------------
class TcfgWindow : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TButton *OK;
	TButton *Cancel;
	TCSpinEdit *CSpinEdit1;
	TCSpinEdit *CSpinEdit2;
	TCSpinEdit *CSpinEdit3;
	TCSpinEdit *CSpinEdit4;
	TCSpinEdit *CSpinEdit5;
	TCSpinEdit *CSpinEdit6;
	TCSpinEdit *CSpinEdit7;
	TCSpinEdit *CSpinEdit8;
	TCSpinEdit *CSpinEdit9;
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OKClick(TObject *Sender);
private:	// User declarations
	BlockConfig* cfg_;
public:		// User declarations
	void __fastcall SetConfig(Block*);
	__fastcall TcfgWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TcfgWindow *cfgWindow;
//---------------------------------------------------------------------------
#endif
