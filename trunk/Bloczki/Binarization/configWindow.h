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
	TButton *Button1;
	TButton *Button2;
	TGroupBox *GroupBox1;
	TCheckBox *CheckBox1;
	TTrackBar *limitB;
	TEdit *limitBShow;
private:	// User declarations
public:		// User declarations
	__fastcall TcfgWin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TcfgWin *cfgWin;
//---------------------------------------------------------------------------
#endif
