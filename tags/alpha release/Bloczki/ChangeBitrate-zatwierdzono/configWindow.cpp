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
	int rate;
	if(bit24->Checked) rate=pf24bit;
	else if(bit32->Checked) rate=pf32bit;
	else if(bit16->Checked) rate=pf15bit;
	else if(bit8->Checked) rate=pf8bit;
	else if(bit4->Checked) rate=pf4bit;
	else rate=pf1bit;
	if (cfg_->getInt("rate")!=rate) cfg_->setInt("rate",rate);
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

