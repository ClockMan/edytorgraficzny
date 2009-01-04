//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TcfgWin *cfgWin;
//---------------------------------------------------------------------------
__fastcall TcfgWin::TcfgWin(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::OKClick(TObject *Sender)
{
		cfg_->setInt("R",poziomRShow->Text.ToIntDef(0));
        cfg_->setInt("G",poziomGShow->Text.ToIntDef(0));
        cfg_->setInt("B",poziomBShow->Text.ToIntDef(0));
        
		Close();
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::FormClose(TObject *Sender, TCloseAction &Action)
{
        cfg_ = NULL;
        Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::SetConfig(Block* block)
{
		cfg_ = block->getConfig();
	
		poziomR->Position = cfg_->getInt("R");
		poziomRShow->Text = IntToStr(cfg_->getInt("R"));
        poziomG->Position = cfg_->getInt("G");
		poziomGShow->Text = IntToStr(cfg_->getInt("G"));
        poziomR->Position = cfg_->getInt("R");
		poziomBShow->Text = IntToStr(cfg_->getInt("B"));
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::CancelClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::poziomRChange(TObject *Sender)
{
        poziomRShow->Text = poziomR->Position;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::poziomRShowChange(TObject *Sender)
{
        int R = poziomRShow->Text.ToIntDef(0);
		if(R < -255 || R > 255) R = 0;

		poziomR->Position = R;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::poziomGChange(TObject *Sender)
{
        poziomGShow->Text = poziomG->Position;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::poziomGShowChange(TObject *Sender)
{
        int G = poziomGShow->Text.ToIntDef(0);
		if(G < -255 || G > 255) G = 0;

		poziomG->Position = G;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::poziomBChange(TObject *Sender)
{
        poziomBShow->Text = poziomB->Position;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::poziomBShowChange(TObject *Sender)
{
        int B = poziomBShow->Text.ToIntDef(0);
		if(B < -255 || B > 255) B = 0;

		poziomB->Position = B;
}
//---------------------------------------------------------------------------

