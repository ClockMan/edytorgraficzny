//$$---- Form CPP ----
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
	if(!scaleBinarization->Checked)
		cfg_->setInt("limitB",125);
	else
	{
		cfg_->setInt("limitB",1);
		cfg_->setInt("limitB",EditLimit->Text.ToIntDef(2));
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
	
	limitB->Position = cfg_->getInt("limitB");
	limitBShow->Text = IntToStr(cfg_->getInt("limitB"));
}
//---------------------------------------------------------------------------

void __fastcall TcfgWin::limitBChange(TObject *Sender)
{
		limitBShow->Text = limitB->Position;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::limitbShowChange(TObject *Sender)
{
		int limitB = limitBShow->Text.ToIntDef(0);
		if(limitB < 0 || limitB > 255) limitB = 0;

		limitB->Position = limitB;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::StandardBinarizationClick(TObject *Sender)
{
	limitB->Enabled = false;
	limitBShow->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWindow::FreeBinarizationClick(TObject *Sender)
{
	limitB->Enabled = true;
	limitBShow->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWin::FormClose(TObject *Sender, TCloseAction &Action)
{
		cfg_ = 125;
		Action = caFree;
}
//---------------------------------------------------------------------------
