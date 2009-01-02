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
void __fastcall TcfgWindow::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	cfg_ = NULL;
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::SetConfig(Block* block)
{
	cfg_ = block->getConfig();
	
	if(cfg_->getInt("mode") == 0)
		Vertically->Checked = true;
	else
		Horizontally->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	if(Vertically->Checked)
		cfg_->setInt("mode",0);
	else
		cfg_->setInt("mode",1);

	Close();
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::CancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

