//---------------------------------------------------------------------------

#ifndef configWindowH
#define configWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "../../Program/engine/Block.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TcfgWindow : public TForm
{
__published:	// IDE-managed Components
	TButton *Cancel;
	TButton *OK;
	TGroupBox *GroupBox1;
	TRadioButton *bit_1;
	TRadioButton *bit_4;
	TRadioButton *bit_8;
	TRadioButton *bit_16;
	TRadioButton *bit_24;
	TRadioButton *bit_32;
	TButton *Button1;
	TEdit *EditPath;
	TSaveDialog *SaveDialog1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
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
