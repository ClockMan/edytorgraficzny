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
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	if(Binarization->Checked)
		cfg_->setInt("mode",0);
	else
	{
		cfg_->setInt("mode",1);
		cfg_->setInt("limitB",limitBShow->Text.ToIntDef(0));
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
		Binarization->Checked = true;
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
		int limitB = limitBShow->Text.ToIntDef(0);
		if(limitB < 0 || limitB > 255) limitB = 0;

		limitB->Position = limitB;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::BinarizationClick(TObject *Sender)
{
	limitB->Enabled = false;
	limitBShow->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWindow::BinarizationBalanceClick(TObject *Sender)
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

