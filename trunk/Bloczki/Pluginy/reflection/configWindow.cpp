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
	Action = caFree;
}
//---------------------------------------------------------------------------
void TcfgWindow::SetConfig(Block* block)
{
	cfg_ = block->getConfig();
	
	if(!cfg_->isInt("mode"));
		cfg_->addInt("mode",0);
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

