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
	Action = caFree;	
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::SetConfig(Block* block)
{
	cfg_ = block->getConfig();
	
	if(!cfg_->isInt("mode"))
		cfg_->addInt("mode",0);
	else
		if(cfg_->getInt("mode") == 0)
			GreyScale->Checked = true;
		else
			GreyBalance->Checked = true;

	if(!cfg_->isInt("limit"))
		cfg_->addInt("limit",2);
	else
	{
		TrackLimit->Position = cfg_->getInt("limit");
		EditLimit->Text = IntToStr(cfg_->getInt("limit"));
	}
}
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	if(GreyScale->Checked)
		cfg_->setInt("mode",0);
	else
		cfg_->setInt("mode",1);

	Close();
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::TrackLimitChange(TObject *Sender)
{
	EditLimit->Text = IntToStr(TrackLimit->Position);
	cfg_->setInt("limit",TrackLimit->Position);
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::EditLimitChange(TObject *Sender)
{
	int limit = EditLimit->Text.ToIntDef(2);
	if(limit < 2 || limit > 50) limit = 2;
	
	TrackLimit->Position = limit;
	cfg_->setInt("limit",EditLimit->Text.ToIntDef(2));
}
//---------------------------------------------------------------------------
