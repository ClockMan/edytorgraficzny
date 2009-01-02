//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
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
	cfg_ = NULL;
	Action = caFree;	
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::SetConfig(Block* block)
{
	cfg_ = block->getConfig();
	CSpinEdit1->Value=cfg_->getInt("data");
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	cfg_->setInt("data",CSpinEdit1->Value);
	Close();
}
//---------------------------------------------------------------------------


