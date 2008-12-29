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
	if(bit24->Checked) cfg_->setInt("rate",pf24bit);
	else if(bit32->Checked) cfg_->setInt("rate",pf32bit);
	else if(bit16->Checked) cfg_->setInt("rate",pf15bit);
	else if(bit8->Checked) cfg_->setInt("rate",pf8bit);
	else if(bit4->Checked) cfg_->setInt("rate",pf4bit);
	else cfg_->setString("rate",pf1bit);

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

	if(cfg_->getInt("rate") == pf24bit)
		bit24->Checked = true;
	else if(cfg_->getInt("rate") == pf32bit)
		bit32->Checked = true;
	else if(cfg_->getInt("rate") == pf15bit)
		bit16->Checked = true;
	else if(cfg_->getInt("rate") == pf8bit)
		bit8->Checked = true;
	else if(cfg_->getInt("rate") == pf4bit)
		bit4->Checked = true;
	else
		bit1->Checked = true;
}
//---------------------------------------------------------------------------

