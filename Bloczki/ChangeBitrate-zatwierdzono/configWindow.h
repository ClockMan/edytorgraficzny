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
class TcfgWin : public TForm
{
__published:	// IDE-managed Components
        TRadioButton *bit1;
        TRadioButton *bit4;
        TRadioButton *bit8;
        TRadioButton *bit16;
        TRadioButton *bit24;
        TRadioButton *bit32;
        TButton *OK;
        void __fastcall OKClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
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
