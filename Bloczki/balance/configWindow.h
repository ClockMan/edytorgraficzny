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
        TButton *OK;
        TTrackBar *poziomR;
        TEdit *poziomRShow;
        TGroupBox *GroupBox1;
        TButton *Cancel;
        TTrackBar *poziomG;
        TTrackBar *poziomB;
        TEdit *poziomGShow;
        TEdit *poziomBShow;
        TStaticText *R;
        TStaticText *G;
        TStaticText *B;
        void __fastcall OKClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CancelClick(TObject *Sender);
        void __fastcall poziomRChange(TObject *Sender);
        void __fastcall poziomRShowChange(TObject *Sender);
        void __fastcall poziomGChange(TObject *Sender);
        void __fastcall poziomGShowChange(TObject *Sender);
        void __fastcall poziomBChange(TObject *Sender);
        void __fastcall poziomBShowChange(TObject *Sender);
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
