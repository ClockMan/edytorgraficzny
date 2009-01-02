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
	TCSpinEdit *CSpinEdit10;
	TCSpinEdit *CSpinEdit11;
	TCSpinEdit *CSpinEdit12;
	TCSpinEdit *CSpinEdit13;
	TCSpinEdit *CSpinEdit14;
	TCSpinEdit *CSpinEdit15;
	TCSpinEdit *CSpinEdit16;
	TCSpinEdit *CSpinEdit17;
	TCSpinEdit *CSpinEdit18;
	TCSpinEdit *CSpinEdit19;
	TCSpinEdit *CSpinEdit20;
	TCSpinEdit *CSpinEdit21;
	TCSpinEdit *CSpinEdit22;
	TCSpinEdit *CSpinEdit23;
	TCSpinEdit *CSpinEdit24;
	TCSpinEdit *CSpinEdit25;
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
