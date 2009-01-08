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
	if(StandardBinarization->Checked)
		cfg_->setInt("mode",0);
	else
	{
		cfg_->setInt("mode",1);
		cfg_->setInt("limitB",limitB->Position);
	}
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::AnulujClick(TObject *Sender)
{
		Close();
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::SetConfig(Block* block)
{
	cfg_ = block->getConfig();

	if(cfg_->getInt("mode") == 0)
	{
		StandardBinarization->Checked = true;
		limitB->Enabled = false;
		limitBShow->Enabled = false;
	}
	else
	{
		BinarizationBalance->Checked = true;
		limitB->Enabled = true;
		limitBShow->Enabled = true;
	}
	
	limitB->Position = cfg_->getInt("limitB");
	limitBShow->Text = IntToStr(cfg_->getInt("limitB"));
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::limitBChange(TObject *Sender)
{
		limitBShow->Text = IntToStr(limitB->Position);
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::limitBShowChange(TObject *Sender)
{

		int limit=0;
		try{
		limit=limitBShow->Text.ToIntDef(0);
		}catch(...)
		{
            return;
        }
		if(limit < 0 || limit > 255) limit = 0;
		limitB->Position = limit;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::BinarizationClick(TObject *Sender)
{
	limitB->Enabled = false;
	limitBShow->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::BinarizationBalanceClick(TObject *Sender)
{
	limitB->Enabled = true;
	limitBShow->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::FormClose(TObject *Sender, TCloseAction &Action)
{
		cfg_ = NULL;
		Action = caFree;
}

