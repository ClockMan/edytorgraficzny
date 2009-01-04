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
		mediana->Checked = true;
	else if(cfg_->getInt("mode") == 1)
                erozja->Checked = true;
        else if(cfg_->getInt("mode") == 2)
                ekspansja->Checked = true;
        else if(cfg_->getInt("mode") == 3)
                otwarcie->Checked = true;
        else
                zamkniecie->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	if(mediana->Checked)
		cfg_->setInt("mode",0);
	else if(erozja->Checked)
		cfg_->setInt("mode",1);
        else if(ekspansja->Checked)
		cfg_->setInt("mode",2);
        else if(otwarcie->Checked)
		cfg_->setInt("mode",3);
        else
                cfg_->setInt("mode",4);

	Close();
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::CancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

