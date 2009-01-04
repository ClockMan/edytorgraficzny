//---------------------------------------------------------------------------

#ifndef configWindowH
#define configWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "../../Program/engine/Block.h"
//---------------------------------------------------------------------------
class TcfgWindow : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
        TRadioButton *mediana;
        TRadioButton *erozja;
	TButton *OK;
	TButton *Cancel;
        TRadioButton *ekspansja;
        TRadioButton *otwarcie;
        TRadioButton *zamkniecie;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OKClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
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
