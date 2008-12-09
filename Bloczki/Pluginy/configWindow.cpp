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
	delete cfg_;
	cfg_ = 0;
	Action = caFree;
}
//---------------------------------------------------------------------------
void TcfgWindow::SetConfig(Block* block)
{
	cfg_ = block->getConfig();
	cfg_->addInt("mode",0);
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::VerticallyClick(TObject *Sender)
{
	cfg_->setInt("mode",0);
}
//---------------------------------------------------------------------------

void __fastcall TcfgWindow::HorizontallyClick(TObject *Sender)
{
	cfg_->setInt("mode",1);
}
//---------------------------------------------------------------------------

void __fastcall TcfgWindow::Button1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

