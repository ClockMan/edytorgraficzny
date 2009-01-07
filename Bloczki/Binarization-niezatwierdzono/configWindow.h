//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef configWindowH
#define configWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
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
	void __fastcall AnulujClick(TObject *Sender);
	void __fastcall StandardBinarizationClick(TObject *Sender);
	void __fastcall BinarizationBalanceClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TcfgWin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TcfgWin *cfgWin;
//---------------------------------------------------------------------------
#endif
