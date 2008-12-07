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
	TRadioButton *Vertically;
	TRadioButton *Horizontally;
	TButton *Button1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall VerticallyClick(TObject *Sender);
	void __fastcall HorizontallyClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	BlockConfig* cfg_;
public:		// User declarations
	void SetConfig(Block*);
	__fastcall TcfgWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TcfgWindow *cfgWindow;
//---------------------------------------------------------------------------
#endif
