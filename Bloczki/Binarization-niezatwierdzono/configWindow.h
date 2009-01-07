//---------------------------------------------------------------------------

#ifndef configWindowH
#define configWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

#include "../../Program/engine/Block.h"
//---------------------------------------------------------------------------
class TcfgWin : public TForm
{
__published:	// IDE-managed Components
	TButton *OK;
	TButton *Anuluj;
	TGroupBox *Binarization;
	TTrackBar *limitB;
	TEdit *limitBShow;
	TRadioButton *BinarizationBalance;
	TRadioButton *StandardBinarization;
	void __fastcall OKClick(TObject *Sender);
	void __fastcall AnulujClick(TObject *Sender);
	void __fastcall BinarizationClick(TObject *Sender);
	void __fastcall BinarizationBalanceClick(TObject *Sender);
	void __fastcall limitBChange(TObject *Sender);
	void __fastcall limitBShowChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	BlockConfig* cfg_;
public:		// User declarations
	void __fastcall SetConfig(Block*);
	__fastcall TcfgWin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TcfgWin *cfgWin;
//---------------------------------------------------------------------------
#endif
