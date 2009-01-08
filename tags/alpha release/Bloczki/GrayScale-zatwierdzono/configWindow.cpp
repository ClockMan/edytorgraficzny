//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TcfgWindow *cfgWindow;
//---------------------------------------------------------------------------
__fastcall TcfgWindow::TcfgWindow(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::CancelClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	cfg_= NULL;
	Action = caFree;	
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::SetConfig(Block* block)
{
	cfg_ = block->getConfig();
	
	if(cfg_->getInt("mode") == 0)
	{
		GreyScale->Checked = true;
		TrackLimit->Enabled = false;
		EditLimit->Enabled = false;
	}
	else
	{
		GreyBalance->Checked = true;
		TrackLimit->Enabled = true;
		EditLimit->Enabled = true;
	}
	
	TrackLimit->Position = cfg_->getInt("limit");
	EditLimit->Text = IntToStr(cfg_->getInt("limit"));
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	if(GreyScale->Checked)
		cfg_->setInt("mode",0);
	else
	{
		cfg_->setInt("mode",1);
    cfg_->setInt("limit",EditLimit->Text.ToIntDef(2));
	}
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::TrackLimitChange(TObject *Sender)
{
	EditLimit->Text = IntToStr(TrackLimit->Position);
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::EditLimitChange(TObject *Sender)
{
	int limit = EditLimit->Text.ToIntDef(2);
	if(limit < 2 || limit > 50) limit = 2;
	
	TrackLimit->Position = limit;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::GreyScaleClick(TObject *Sender)
{
	TrackLimit->Enabled = false;
	EditLimit->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TcfgWindow::GreyBalanceClick(TObject *Sender)
{
	TrackLimit->Enabled = true;
	EditLimit->Enabled = true;
}
//---------------------------------------------------------------------------

