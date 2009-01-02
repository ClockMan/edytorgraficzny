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
//---------------------------------------------------------------------------
class TcfgWindow : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
	TGroupBox *GroupBox1;
	TButton *Open;
	TEdit *EditPath;
	TButton *OK;
	TButton *Cancel;
	TRadioButton *bit_1;
	TRadioButton *bit_4;
	TRadioButton *bit_8;
	TRadioButton *bit_16;
	TRadioButton *bit_24;
	TRadioButton *bit_32;
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OKClick(TObject *Sender);
	void __fastcall OpenClick(TObject *Sender);
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
