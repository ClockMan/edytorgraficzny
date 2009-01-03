//---------------------------------------------------------------------------

#ifndef configWindowH
#define configWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "../../Program/engine/Block.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TcfgWin : public TForm
{
__published:	// IDE-managed Components
        TRadioButton *mono;
        TRadioButton *color;
        TButton *OK;
        TTrackBar *poziom;
        TEdit *poziomShow;
        TGroupBox *GroupBox1;
        TButton *Cancel;
        void __fastcall OKClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CancelClick(TObject *Sender);
        void __fastcall poziomChange(TObject *Sender);
        void __fastcall poziomShowChange(TObject *Sender);
        void __fastcall monoClick(TObject *Sender);
        void __fastcall colorClick(TObject *Sender);
private:	// User declarations
        BlockConfig* cfg_;
public:		// User declarations
        __fastcall TcfgWin(TComponent* Owner);
        void __fastcall SetConfig(Block*);
};
//---------------------------------------------------------------------------
extern PACKAGE TcfgWin *cfgWin;
//---------------------------------------------------------------------------
#endif
