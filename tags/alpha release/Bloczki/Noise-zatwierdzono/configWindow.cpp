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
	if(mono->Checked)
		cfg_->setInt("mode",0);
	else
	        cfg_->setInt("mode",1);

        cfg_->setInt("level",poziomShow->Text.ToIntDef(0));
        
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

        if(cfg_->getInt("mode") == 0)
                mono->Checked = true;
	else
                color->Checked = true;
	
	poziom->Position = cfg_->getInt("level");
	poziomShow->Text = IntToStr(cfg_->getInt("level"));
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::CancelClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::poziomChange(TObject *Sender)
{
        poziomShow->Text = poziom->Position;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::poziomShowChange(TObject *Sender)
{
        int level = poziomShow->Text.ToIntDef(0);
	if(level < 0 || level > 255) level = 0;
	
	poziom->Position = level;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::monoClick(TObject *Sender)
{
        mono->Checked = true;        
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::colorClick(TObject *Sender)
{
        color->Checked = true;
}
//---------------------------------------------------------------------------

