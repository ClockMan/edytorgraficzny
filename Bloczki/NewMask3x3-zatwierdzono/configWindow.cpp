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
	CSpinEdit1->Value=cfg_->getInt("d1_1");
	CSpinEdit2->Value=cfg_->getInt("d1_2");
	CSpinEdit3->Value=cfg_->getInt("d1_3");
	CSpinEdit4->Value=cfg_->getInt("d2_1");
	CSpinEdit5->Value=cfg_->getInt("d2_2");
	CSpinEdit6->Value=cfg_->getInt("d2_3");
	CSpinEdit7->Value=cfg_->getInt("d3_1");
	CSpinEdit8->Value=cfg_->getInt("d3_2");
	CSpinEdit9->Value=cfg_->getInt("d3_3");
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	cfg_->setInt("d1_1",CSpinEdit1->Value);
	cfg_->setInt("d1_2",CSpinEdit2->Value);
	cfg_->setInt("d1_3",CSpinEdit3->Value);
	cfg_->setInt("d2_1",CSpinEdit4->Value);
	cfg_->setInt("d2_2",CSpinEdit5->Value);
	cfg_->setInt("d2_3",CSpinEdit6->Value);
	cfg_->setInt("d3_1",CSpinEdit7->Value);
	cfg_->setInt("d3_2",CSpinEdit8->Value);
	cfg_->setInt("d3_3",CSpinEdit9->Value);
	Close();
}
//---------------------------------------------------------------------------


